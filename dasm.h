#pragma once

#include <vector>
#include <cstdint>
#include <memory>

#include "common.h"

namespace gbdsm {

using Rom = std::vector<uint8_t>;

class Disassembler {
public:
    Disassembler(Rom rom);

    virtual void disassemble(size_t start, size_t end) = 0;

protected:
    Rom rom_;
};

std::unique_ptr<gbdsm::Disassembler> create_dasm(gbdsm::Rom rom, gbdsm::DisassemblerAlgo algo);

}
