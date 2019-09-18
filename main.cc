#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <limits>

#include "ops.h"
#include "common.h"
#include "dasm.h"

static void print_help()
{
    std::puts("gbdsm -- The GameBoy ROM disassembler.");
    std::putchar('\n');

    std::puts("Usage: gbdsm '/path/to/rom.gb' [-h] [-b address] [-e address]");
    
    std::putchar('\n');

    std::puts("Optional arguments:");
    std::puts("-h            show this help message and exit.");
    std::puts("-b address    set the starting address for the disassembler in decimal. Defaults to 0x0.");
    std::puts("-e address    set the end address for the disassembler in decimal. Defaults to the end of ROM.");
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
        std::fclose(file);

        return gbdsm::Rom{};
    }

    std::fclose(file);

    return rom;
}

struct Args {
    std::string rom_path;
    size_t begin, end;
    bool print_help;
};

static Args parse_args(int argc, char **argv)
{
    Args args;
    if (argc < 2) { 
        return args;
    }

    if (std::strcmp("-h", argv[1]) == 0) {
        args.print_help = true;
        return args;
    }

    args.rom_path = argv[1];
    args.begin = 0;
    args.end = std::numeric_limits<size_t>::max();
    args.print_help = false;

    for (int i = 2; i < argc;) {
        if (std::strcmp(argv[i], "-b") == 0) {
            args.begin = std::stoull(argv[i + 1]);
            i += 2;
        } else if (std::strcmp(argv[i], "-e") == 0) {
            args.end = std::stoull(argv[i + 1]);
            i += 2;
        } else if (std::strcmp(argv[i], "-h") == 0) {
            args.print_help = true; 
            ++i;
        } else {
            gbdsm::error("Unrecognized argument %s.\n", argv[i]);
            std::exit(1);
        }
    }

    return args;
}


int main(int argc, char **argv)
{
    Args args = parse_args(argc, argv);
    if (args.print_help) {
        print_help();
        return 0;
    }

    if (args.rom_path.empty()) {
        gbdsm::error("The GameBoy ROM file was not supplied.\n");
        return 1;
    }

    if (args.end < args.begin) {
        gbdsm::error("The end (%zu) cannot be less than the beginning (%zu).\n",
                args.end, args.begin);
        return 1;
    }

    auto rom = read_rom(args.rom_path.c_str());
    if (rom.empty()) {
        gbdsm::error("Could not read %s.\n", args.rom_path.c_str());
        return 1;
    }

    if (args.end > rom.size()) {
        args.end = rom.size();
    }

    gbdsm::Disassembler dasm(rom);

    dasm.disassemble(args.begin, args.end);
}
