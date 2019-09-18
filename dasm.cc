#include <cstdio>

#include "dasm.h"
#include "common.h"

#include "linear_sweep_dasm.h"

gbdsm::Disassembler::Disassembler(Rom rom)
    : rom_(std::move(rom)) {}

std::unique_ptr<gbdsm::Disassembler> gbdsm::create_dasm(gbdsm::Rom rom)
{
    return std::make_unique<gbdsm::LinearSweepDisassembler>(rom);
}
