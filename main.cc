#include <cstdio>
#include <vector>
#include <fstream>
#include <iterator>

#include "ops.h"
#include "common.h"
#include "dasm.h"

static void print_help()
{
    std::puts("Help.");
}

static gbdsm::Rom read_rom(const char* path)
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
    gbdsm::Rom vec;
    vec.reserve(fileSize);

    // read the data:
    vec.insert(vec.begin(),
               std::istream_iterator<std::uint8_t>(file),
               std::istream_iterator<std::uint8_t>());

    return vec;
}


int main(int argc, char **argv)
{
    if (argc != 2) {
        gbdsm::error("Need input ROM.\n");
        print_help();
        return 1;
    }

    auto rom = read_rom(argv[1]);
    if (rom.empty()) {
        gbdsm::error("Can't read %s.\n", argv[1]);
        return 1;
    }

    gbdsm::Disassembler dasm(rom);

    dasm.disassemble();
}
