# lenctools
<p>lenctools is a set of tools used to decompile .lenc files into .lua files and vice versa.</p>

Telltale games use <b>.lenc</b> files which store the Lua bytecode, which in some cases (especially in older Telltale games) use swapped [opcodes](https://en.wikipedia.org/wiki/Opcode), which basically means they cannot be compiled or decompiled using standard tools.

> [!IMPORTANT]
> All tools contained in this repository are supposed to be used on Lua 5.1 scripts and bytecode with swapped opcodes!

## Tools
lenctools includes Lua 5.1.2 ([luac](https://www.lua.org/manual/5.1/luac.html)) and [unluac](https://sourceforge.net/projects/unluac/), both modified for use with the `.lenc` files using swapped opcodes.<br/><br/>
Alternatively, instead of using modified `unluac` you can also use the original version with the `--opmap` parameter specifying the [opmap.txt](src/misc/opmap.txt) file, included in the repository.

## Support
`luac` and `unluac` were tested and confirmed working on following games:
- The Walking Dead (season one)
- The Walking Dead: Season Two

# Credits
Original credits go to software's respective authors:<br>
- [unluac source code](https://sourceforge.net/projects/unluac/) - tehtmi<br/>
- [Lua 5.1.2 source code](https://www.lua.org/ftp/) - PUC-Rio<br/>