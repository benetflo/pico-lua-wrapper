# lua_to_c_fixed.py
import sys

if len(sys.argv) < 2:
    print("Usage: python lua_to_c_fixed.py main.lua")
    sys.exit(1)

lua_file = sys.argv[1]
output_file = "lua_script.h"

with open(lua_file, "r") as f:
    lines = f.readlines()

# Slå ihop radbrytningar inuti parenteser
lua_code = ""
paren_level = 0
for line in lines:
    stripped = line.rstrip("\n")
    paren_level += stripped.count("(") - stripped.count(")")
    if paren_level > 0:
        lua_code += stripped + " "  # behåll mellanslag istället för newline
    else:
        lua_code += stripped + "\n"

with open(output_file, "w") as f:
    f.write('const char *lua_script = \n')
    for line in lua_code.splitlines():
        line = line.replace('\\', '\\\\').replace('"', '\\"')
        f.write(f'"{line}\\n"\n')
    f.write(';\n')

print(f"Generated {output_file} from {lua_file}")
