import os
import re
from pathlib import Path

def fileToVarName(file):
    fileName = file.name
    clean_name = re.sub(r'[^\w]', '', fileName)
    if clean_name and clean_name[0].isdigit():
        clean_name = "_" + clean_name
    return clean_name if clean_name else "_empty"

def bin2hAll(target_dir, output_file, array_name):
    if not os.path.exists(target_dir):
        print(f"Error: {target_dir} not found.")
        return

    with open (output_file, "w") as headerFile:
        headerFile.write(f"#pragma once\n")
        headerFile.write(f"#include <vector>\n")
        headerFile.write(f"#include <utility>\n")
        headerFile.write(f"#include <string>\n")
        headerFile.write(f"#include <variant>\n")

        headerFile.write(f"//Generated from {file} using Mp3-compactor.py from compile-time.\n")
        
        headerFile.write(f"using PairData_t = std::pair<std::string, unsigned char>\n")
        headerFile.write(f"using PairLen_t = std::pair<std::string, int>\n")
        
        headerFile.write(f"const std::vector<std::variant<PairData_t, PairLen_t>> {array_name} = {{\n  ")

        for file in target_dir.iterdir():
            headerFile.write(f"PairData_t{{ \"{array_name}\",\n    ")

            with open (file, "rb") as f:
                data = f.read()

                #Write bytes in rows of 12
                for i, byte in enumerate(data):
                    f.write(f"0x{byte:02X}, ")
                    if (i + 1) % 12 == 0:
                        f.write("\n    ")

                f.write(f"\n  }},\n  ")
                f.write(f"PairLen_t{fileToVarName(f)}_len = {len(data)};\n\n")

            print(f"Successfully converted {target_dir} to {output_file}!")
        
        headerFile.write(f"\n}};\n\n")
        print(f"Finished converting {target_dir} to {output_file}!")




target_dir = Path().resolve().parent.parent / "mp3_src"
bin2hAll(target_dir, "mp3Binaries.h", "mp3Binaries")