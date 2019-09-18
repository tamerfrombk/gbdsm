#include <cstdio>

#include "dasm.h"
#include "common.h"
#include <algorithm>

template <class N>
static std::string to_hex(N n)
{
    std::string buf;
    while (n != 0) {
        int d = n % 16;
        char c = "0123456789ABCDEF"[d];
        buf.push_back(c);
        n /= 16;
    }
    buf.push_back('$');
    std::reverse(buf.begin(), buf.end());

    return buf;
}

static std::string to_hex(uint16_t n1, uint16_t n2)
{
    // flip the byte order
    uint16_t result = n1 | (n2 << 8);

    return to_hex(result);
}

gbdsm::Disassembler::Disassembler(Rom rom)
    : rom_(std::move(rom)) {}


void gbdsm::Disassembler::disassemble()
{
    unsigned PC = 0;
    while (PC < rom_.size()) {
        const auto& inst = gbdsm::INSTRUCTIONS[rom_[PC]];
        if (inst.length == 0) {
            // TODO: this is in place while jumps and visitation is not implemented
            // Without them implemented, we are interpreting data as code
            // TODO: Again, is it really this easy.
            std::printf("%.2X @ %.2X is unknown!\n", rom_[PC], PC);
            PC += 1;
        } 
        else if (inst.isJump()) {
            if (inst.op == 0xE9) {
                // JP (HL) is unsupported as it is a dynamic jump instruction
                // that cannot easily be traced
                gbdsm::abort("JP (HL) instruction not supported!\n");
            }
            else {
                print_inst(PC, inst);
                PC += inst.length;
            }
        }
        else if (inst.isPrefix()) {
            const auto& pre = gbdsm::PREFIXED_INSTRUCTIONS[rom_[PC + 1]];
            print_inst(PC, pre);
            PC += pre.length;
        }  // TODO: implement jumps and visitation
        else {
            print_inst(PC, inst);
            PC += inst.length;
        }
    }
}

void gbdsm::Disassembler::print_inst(unsigned pos, Instruction inst)
{
    size_t found = 0;
    std::string to_print = inst.mnemonic;
    if ((found = to_print.find("%D8")) != std::string::npos) {
        to_print = to_print.replace(found, 3, to_hex(rom_[pos + 1])); 
    }
    else if ((found = to_print.find("%D16")) != std::string::npos) {
        to_print = to_print.replace(found, 4, to_hex(rom_[pos + 1], rom_[pos + 2]));
    }
    else if ((found = to_print.find("R8")) != std::string::npos) {
        int8_t target = rom_[pos + 1] + pos + inst.length;
        to_print = to_print.replace(found, 3, to_hex(target)); 
    }
    else if ((found = to_print.find("A16")) != std::string::npos) {
        to_print = to_print.replace(found, 4, to_hex(rom_[pos + 1], rom_[pos + 2]));
    }

    std::printf("%s    ; $%.4X\n", to_print.c_str(), pos);
}
