#include <cstdio>
#include <string>

#include "dasm.h"

#include "linear_sweep_dasm.h"
#include "recursive_search_dasm.h"

gbdsm::Disassembler::Disassembler(Rom rom)
    : rom_(std::move(rom)) {}

void gbdsm::Disassembler::print_inst(size_t PC, const gbdsm::Instruction& inst) const
{
    size_t found = 0;
    std::string to_print = inst.mnemonic;
    if ((found = to_print.find("%D8")) != std::string::npos) {
        to_print = to_print.replace(found, 3, to_hex(rom_[PC + 1]));
    }
    else if ((found = to_print.find("%D16")) != std::string::npos) {
        to_print = to_print.replace(found, 4, to_hex(rom_[PC + 1], rom_[PC + 2]));
    }
    else if ((found = to_print.find("R8")) != std::string::npos) {
        uint16_t target = (int8_t)rom_[PC + 1] + PC + inst.length;
        to_print = to_print.replace(found, 2, to_hex(target));
    }
    else if ((found = to_print.find("A8")) != std::string::npos) {
        to_print = to_print.replace(found, 2, to_hex(rom_[PC + 1]));
    }
    else if ((found = to_print.find("A16")) != std::string::npos) {
        to_print = to_print.replace(found, 3, to_hex(rom_[PC + 1], rom_[PC + 2]));
    }

    to_print = gbdsm::justify(20, to_print, to_hex(PC));

    std::printf("%s\n", to_print.c_str());
}

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
