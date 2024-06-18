# lenctools
<p>"lenctools" is a set of tools used to decompile .lenc files into .lua files and vice versa.</p>

Telltale games use <b>.lenc</b> files which store the Lua bytecode.<br/>
The .lenc format in some cases (especially in older Telltale games) utilizes swapping [opcodes](https://en.wikipedia.org/wiki/Opcode), which basically means they cannot be compiled or decompiled using standard tools.

## Tools
lenctools includes Lua 5.1.2 ([luac](https://www.lua.org/manual/5.1/luac.html)) and [unluac](https://sourceforge.net/projects/unluac/), both modified for use with the swapped opcodes.<br/>
- The `luac` tool will compile only into the Lua 5.1 bytecode.
- Opcodes in `unluac` were modified only for Lua version 5.1, meaning it will work with any other bytecode versions, without them being changed.

## Support
`luac` and `unluac` were tested and confirmed working on following games:
- The Walking Dead: A New Day
- The Walking Dead Season 2

# License
This project is licensed under the MIT License. See the `LICENSE.md` file for details.

# Credits
Original credits go to software's respective authors:<br>
- [unluac source code](https://sourceforge.net/projects/unluac/) - tehtmi<br/>
- [Lua 5.1.2 source code](https://www.lua.org/ftp/) - PUC-Rio<br/>