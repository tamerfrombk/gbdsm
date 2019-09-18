#include <cstdio>

#include "ops.h"
#include "common.h"
#include "dasm.h"

static void print_help()
{
    std::puts("Help.");
}

static size_t fsize(std::FILE *file)
{
    size_t curr = std::ftell(file);
    std::fseek(file, 0, SEEK_END);

    size_t size = std::ftell(file);

    std::fseek(file, curr, SEEK_SET);

    return size;
}

static gbdsm::Rom read_rom(const char* path)
{
    std::FILE *file = std::fopen(path, "rb");
    if (!file) {
        return gbdsm::Rom{};
    }

    size_t fileSize = fsize(file);

    gbdsm::Rom rom(fileSize, 0);

    size_t bytesRead = std::fread(rom.data(), sizeof(uint8_t), fileSize, file);
    if (bytesRead != fileSize) {
        gbdsm::error("%s expected to read %zu bytes but read %zu instead!\n",
                path, fileSize, bytesRead);
        std::fclose(file);

        return gbdsm::Rom{};
    }

    std::fclose(file);

    return rom;
}


int main(int argc, char **argv)
{
    if (argc != 2) {
        gbdsm::error("Need input ROM.\n");
        print_help();
        return 1;
    }

    auto rom = read_rom(argv[1]);
    if (rom.empty()) {
        gbdsm::error("Can't read %s.\n", argv[1]);
        return 1;
    }

    size_t end = rom.size();
    gbdsm::Disassembler dasm(rom);

    dasm.disassemble(0, end);
}
