#include <cstdio>

#include "dasm.h"

#include "linear_sweep_dasm.h"
#include "recursive_search_dasm.h"

gbdsm::Disassembler::Disassembler(Rom rom)
    : rom_(std::move(rom)) {}

std::unique_ptr<gbdsm::Disassembler> gbdsm::create_dasm(gbdsm::Rom rom, gbdsm::DisassemblerAlgo algo)
{
    switch (algo) {
    case gbdsm::DisassemblerAlgo::LINEAR_SWEEP:
        return std::make_unique<gbdsm::LinearSweepDisassembler>(rom);
    case gbdsm::DisassemblerAlgo::RECURSIVE_SEARCH:
        return std::make_unique<gbdsm::RecursiveSearchDisassembler>(rom);
    default:
        gbdsm::abort("Unknown algorithm.\n");
        return nullptr;
    }
}
