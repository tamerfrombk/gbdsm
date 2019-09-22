#pragma once

#include <vector>
#include <cstdint>
#include <memory>

#include "common.h"
#include "ops.h"

namespace gbdsm {

using Rom = std::vector<uint8_t>;

class Disassembler {
public:
    Disassembler(Rom rom);

    virtual void disassemble(size_t start, size_t end) = 0;

protected:
    void print_inst(size_t PC, const gbdsm::Instruction& inst) const;

    Rom rom_;
};

std::unique_ptr<gbdsm::Disassembler> create_dasm(gbdsm::Rom rom, gbdsm::DisassemblerAlgo algo);

}
