package unluac.decompile;

import java.util.HashMap;
import java.util.Map;
import java.util.Map.Entry;

import unluac.Version;

public class OpcodeMap {

  private Op[] map;
  private Map<String, Op> lookup;
  
  public OpcodeMap(Map<Integer, Op> useropmap) {
    int max = -1;
    for(int opcode : useropmap.keySet()) {
      max = Math.max(opcode, max);
    }
    map = new Op[max + 1];
    for(Entry<Integer, Op> entry : useropmap.entrySet()) {
      map[entry.getKey()] = entry.getValue();
    }
    init_lookup();
    setup_lookup(false);
  }
  
  public OpcodeMap(Version.OpcodeMapType type) {
    init_lookup();
    if (type == LUA51) {
      map = new Op[45];
      map[0] = null;          // from MOVE       /* unused */
      map[1] = Op.MOVE;       // from LOADK
      map[2] = Op.LOADK;      // from LOADBOOL
      map[3] = Op.LOADBOOL;   // from LOADNIL
      map[4] = Op.LOADNIL;    // from GETUPVAL
      map[5] = Op.GETUPVAL;   // from GETGLOBAL
      map[6] = Op.GETGLOBAL;  // from GETTABLE
      map[7] = Op.GETTABLE;   // from SETGLOBAL
      map[8] = null;          // from SETUPVAL   /* unused */
      map[9] = Op.SETGLOBAL;  // from SETTABLE
      map[10] = Op.SETUPVAL;  // from NEWTABLE
      map[11] = Op.SETTABLE;  // from SELF
      map[12] = Op.NEWTABLE;  // from ADD
      map[13] = null;         // from SUB        /* unused */
      map[14] = Op.SELF;      // from MUL
      map[15] = null;         // from DIV        /* unused */
      map[16] = Op.ADD;       // from MOD
      map[17] = Op.SUB;       // from POW
      map[18] = Op.MUL;       // from UNM
      map[19] = Op.DIV;       // from NOT
      map[20] = Op.MOD;       // from LEN
      map[21] = Op.POW;       // from CONCAT
      map[22] = Op.UNM;       // from JMP
      map[23] = Op.NOT;       // from EQ
      map[24] = Op.LEN;       // from LT
      map[25] = Op.CONCAT;    // from LE
      map[26] = null;         // from TEST       /* unused */
      map[27] = Op.JMP;       // from TESTSET
      map[28] = Op.EQ;        // from CALL
      map[29] = Op.LT;        // from TAILCALL
      map[30] = Op.LE;        // from RETURN
      map[31] = Op.TEST;      // from FORLOOP
      map[32] = Op.TESTSET;   // from FORPREP
      map[33] = Op.CALL;      // from TFORLOOP
      map[34] = Op.TAILCALL;  // from SETLIST
      map[35] = null;         // from CLOSE      /* unused */
      map[36] = Op.RETURN;    // from CLOSURE
      map[37] = Op.FORLOOP;   // from VARARG
      map[38] = Op.FORPREP;   // "op38"
      map[39] = Op.TFORLOOP;  // "op39"
      map[40] = Op.SETLIST;   // "op40"
      map[41] = null;         // ?               /* unused */
      map[42] = Op.CLOSE;     // "op42"
      map[43] = Op.CLOSURE;   // "op43"
      map[44] = Op.VARARG;    // "op44"
      allow_53_math_lookup();
    } else {
      String m = String.format("Unsupported Lua version (%s)", type.name());
      throw new IllegalArgumentException(m);
    }
    setup_lookup(false);
  }
  
  public Op get(int opNumber) {
    if(opNumber >= 0 && opNumber < map.length) {
      return map[opNumber];
    } else {
      return null;
    }
  }
  
  public Op get(String name) {
    return lookup.get(name);
  }
  
  public int size() {
    return map.length;
  }
  
  private void init_lookup() {
    lookup = new HashMap<String, Op>();
  }
  
  private void allow_51_math_lookup() {
    Op[] ops = {Op.MOD, Op.LEN};
    allow_ops_lookup(ops);
  }
  
  private void allow_53_math_lookup() {
    Op[] ops = {Op.IDIV, Op.BAND, Op.BOR, Op.BXOR, Op.SHL, Op.SHR, Op.BNOT};
    allow_ops_lookup(ops);
  }
  
  private void allow_ops_lookup(Op[] ops) {
    for(Op op : ops) {
      String name = op.name;
      if(!lookup.containsKey(name)) {
        lookup.put(name, op);
      } else {
        throw new IllegalStateException();
      }
    }
  }
  
  private void setup_lookup(boolean validate) {
    for(int i = 0; i < map.length; i++) {
      if(map[i] != null) {
        String name = map[i].name;
        if(!lookup.containsKey(name)) {
          lookup.put(name, map[i]);
        } else if(validate) {
          throw new IllegalStateException(name);
        }
      } else if(validate) {
        throw new IllegalStateException();
      }
    }
  }
  
}

