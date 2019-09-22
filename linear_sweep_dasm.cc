#include "linear_sweep_dasm.h"
#include "common.h"

gbdsm::LinearSweepDisassembler::LinearSweepDisassembler(Rom rom)
    : gbdsm::Disassembler(rom) {}

void gbdsm::LinearSweepDisassembler::disassemble(size_t start, size_t end)
{
    size_t PC = start;
    while (PC < end) {
        const auto& inst = gbdsm::INSTRUCTIONS[rom_[PC]];
        if (inst.length == 0) {
            // If we hit an unknown instruction, this is probably due
            // to interpreting data as code.
            PC += 1;
        }
        else if (inst.isPrefix()) {
            const auto& pre = gbdsm::PREFIXED_INSTRUCTIONS[rom_[PC + 1]];
            print_inst(PC, pre);
            PC += pre.length;
        }
        else {
            print_inst(PC, inst);
            PC += inst.length;
        }
    }
}
