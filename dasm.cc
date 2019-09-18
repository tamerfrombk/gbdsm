#include <cstdio>

#include "dasm.h"
#include "common.h"

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
    std::printf("%s    ; $%.4X\n", inst.mnemonic.c_str(), pos);
}
