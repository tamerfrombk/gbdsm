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
            gbdsm::abort("ERROR! %.2X @ %.2X length 0!\n", inst.op, PC);
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
    std::printf("%.2X | [%.2X] %s | %d\n", pos, inst.op, inst.mnemonic.c_str(), inst.length);
}
