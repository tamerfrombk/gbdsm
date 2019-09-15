#include <cstdio>

#include "dasm.h"
#include "common.h"

gbdsm::Disassembler::Disassembler(Rom rom)
    : rom_(std::move(rom)) {}


void gbdsm::Disassembler::disassemble()
{
    unsigned head = 0;
    while (head < rom_.size()) {
        const auto& inst = gbdsm::INSTRUCTIONS[rom_[head]];
        if (inst.length == 0) {
            // TODO: this is in place while jumps and visitation is not implemented
            // Without them implemented, we are interpreting data as code
            gbdsm::abort("ERROR! %.2X @ %.2X length 0!\n", inst.op, head);
        } 
        else if (inst.isJump()) {
            if (inst.op == 0xE9) {
                // JP (HL) is unsupported as it is a dynamic jump instruction
                // that cannot easily be traced
                gbdsm::abort("JP (HL) instruction not supported!\n");
            }
            else {
                print_inst(head, inst);
                head += inst.length;
            }
        }
        else if (inst.isPrefix()) {
            const auto& pre = gbdsm::PREFIXED_INSTRUCTIONS[rom_[head + 1]];
            print_inst(head, pre);
            head += pre.length;
        }  // TODO: implement jumps and visitation
        else {
            print_inst(head, inst);
            head += inst.length;
        }
    }
}

void gbdsm::Disassembler::print_inst(unsigned pos, Instruction inst)
{
    std::printf("%.2X | [%.2X] %s | %d\n", pos, inst.op, inst.mnemonic.c_str(), inst.length);
}
