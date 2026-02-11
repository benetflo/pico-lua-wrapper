# lua_to_c.py
import sys

if len(sys.argv) < 2:
    print("Usage: python lua_to_c.py main.lua")
    sys.exit(1)

lua_file = sys.argv[1]
output_file = "lua_script.h"

with open(lua_file, "r") as f:
    lines = f.readlines()

with open(output_file, "w") as f:
    f.write('const char *lua_script = \n')
    for line in lines:
        line = line.rstrip("\n")
        line = line.replace('\\', '\\\\') 
        line = line.replace('"', '\\"')    
        f.write(f'"{line}\\n"\n')         
    f.write(';\n')

print(f"Generated {output_file} from {lua_file}")
