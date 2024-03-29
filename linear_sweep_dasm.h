#pragma once

#include "dasm.h"
#include "ops.h"

namespace gbdsm {

class LinearSweepDisassembler
    : public Disassembler {
public:
    LinearSweepDisassembler(Rom rom);

    virtual void disassemble(size_t start, size_t end) override;

};

}
