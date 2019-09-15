#include "ops.h"
#include <cstdio>
#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>

using Rom = std::vector<std::uint8_t>;

static void print_help()
{
    std::puts("Help.");
}

static Rom read_rom(const char* path)
{
     // open the file:
    std::ifstream file(path, std::ios::binary);

    // Stop eating new lines in binary mode!!!
    file.unsetf(std::ios::skipws);

    // get its size:
    std::streampos fileSize;

    file.seekg(0, std::ios::end);
    fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // reserve capacity
    Rom vec;
    vec.reserve(fileSize);

    // read the data:
    vec.insert(vec.begin(),
               std::istream_iterator<std::uint8_t>(file),
               std::istream_iterator<std::uint8_t>());

    return vec;
}

static void print_inst(unsigned pos, const gbdsm::Instruction& inst)
{
    std::printf("%.2X | [%.2X] %s | %d\n", pos, inst.op, inst.mnemonic.c_str(), inst.length);
}

static void disassemble(const Rom& rom)
{
    unsigned head = 0;
    while (head < rom.size()) {
        const auto& inst = gbdsm::INSTRUCTIONS[rom[head]];
        if (inst.length == 0) {
            // TODO: this is in place while jumps and visitation is not implemented
            // Without them implemented, we are interpreting data as code
            std::printf("ERROR! %.2X @ %.2X length 0!\n", inst.op, head);
            break;
        } 
        else if (inst.isJump()) {
            if (inst.op == 0xE9) {
                // JP (HL) is unsupported as it is a dynamic jump instruction
                // that cannot easily be traced
                std::fprintf(stderr, "JP (HL) instruction not supported!\n");
                break;
            }
            else {
                print_inst(head, inst);
                head += inst.length;
            }
        }
        else if (inst.isPrefix()) {
            const auto& pre = gbdsm::PREFIXED_INSTRUCTIONS[rom[head + 1]];
            print_inst(head, pre);
            head += pre.length;
        }  // TODO: implement jumps and visitation
        else {
            print_inst(head, inst);
            head += inst.length;
        }
    }
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::puts("Need input ROM.");
        print_help();
        return 1;
    }

    auto rom = read_rom(argv[1]);
    if (rom.empty()) {
        std::printf("Can't read %s.\n", argv[1]);
        return 1;
    }

    disassemble(rom);
}
