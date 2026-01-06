/*
** $Id: lopcodes.h,v 1.102 2002/08/21 18:56:09 roberto Exp $
** Opcodes for Lua virtual machine
** See Copyright Notice in lua.h
*/

#ifndef lopcodes_h
#define lopcodes_h

#include "llimits.h"


/*===========================================================================
  We assume that instructions are unsigned numbers.
  All instructions have an opcode in the first 6 bits.
  Instructions can have the following fields:
	`A' : 8 bits
	`B' : 9 bits
	`C' : 9 bits
	`Bx' : 18 bits (`B' and `C' together)
	`sBx' : signed Bx

  A signed argument is represented in excess K; that is, the number
  value is the unsigned value minus K. K is exactly the maximum value
  for that argument (so that -max is represented by 0, and +max is
  represented by 2*max), which is half the maximum for the corresponding
  unsigned argument.
===========================================================================*/


enum OpMode {iABC, iABx, iAsBx};  /* basic instruction format */


/*
** size and position of opcode arguments.
*/
#define SIZE_C		9
#define SIZE_B		9
#define SIZE_Bx		(SIZE_C + SIZE_B)
#define SIZE_A		8

#define SIZE_OP		6

#define POS_C		SIZE_OP
#define POS_B		(POS_C + SIZE_C)
#define POS_Bx		POS_C
#define POS_A		(POS_B + SIZE_B)


/*
** limits for opcode arguments.
** we use (signed) int to manipulate most arguments,
** so they must fit in BITS_INT-1 bits (-1 for sign)
*/
#if SIZE_Bx < BITS_INT-1
#define MAXARG_Bx        ((1<<SIZE_Bx)-1)
#define MAXARG_sBx        (MAXARG_Bx>>1)         /* `sBx' is signed */
#else
#define MAXARG_Bx        MAX_INT
#define MAXARG_sBx        MAX_INT
#endif


#define MAXARG_A        ((1<<SIZE_A)-1)
#define MAXARG_B        ((1<<SIZE_B)-1)
#define MAXARG_C        ((1<<SIZE_C)-1)


/* creates a mask with `n' 1 bits at position `p' */
#define MASK1(n,p)	((~((~(Instruction)0)<<n))<<p)

/* creates a mask with `n' 0 bits at position `p' */
#define MASK0(n,p)	(~MASK1(n,p))

/*
** the following macros help to manipulate instructions
*/

#define GET_OPCODE(i)	(cast(OpCode, (i)&MASK1(SIZE_OP,0)))
#define SET_OPCODE(i,o)	((i) = (((i)&MASK0(SIZE_OP,0)) | cast(Instruction, o)))

#define GETARG_A(i)	(cast(int, (i)>>POS_A))
#define SETARG_A(i,u)	((i) = (((i)&MASK0(SIZE_A,POS_A)) | \
		((cast(Instruction, u)<<POS_A)&MASK1(SIZE_A,POS_A))))

#define GETARG_B(i)	(cast(int, ((i)>>POS_B) & MASK1(SIZE_B,0)))
#define SETARG_B(i,b)	((i) = (((i)&MASK0(SIZE_B,POS_B)) | \
		((cast(Instruction, b)<<POS_B)&MASK1(SIZE_B,POS_B))))

#define GETARG_C(i)	(cast(int, ((i)>>POS_C) & MASK1(SIZE_C,0)))
#define SETARG_C(i,b)	((i) = (((i)&MASK0(SIZE_C,POS_C)) | \
		((cast(Instruction, b)<<POS_C)&MASK1(SIZE_C,POS_C))))

#define GETARG_Bx(i)	(cast(int, ((i)>>POS_Bx) & MASK1(SIZE_Bx,0)))
#define SETARG_Bx(i,b)	((i) = (((i)&MASK0(SIZE_Bx,POS_Bx)) | \
		((cast(Instruction, b)<<POS_Bx)&MASK1(SIZE_Bx,POS_Bx))))

#define GETARG_sBx(i)	(GETARG_Bx(i)-MAXARG_sBx)
#define SETARG_sBx(i,b)	SETARG_Bx((i),cast(unsigned int, (b)+MAXARG_sBx))


#define CREATE_ABC(o,a,b,c)	(cast(Instruction, o) \
			| (cast(Instruction, a)<<POS_A) \
			| (cast(Instruction, b)<<POS_B) \
			| (cast(Instruction, c)<<POS_C))

#define CREATE_ABx(o,a,bc)	(cast(Instruction, o) \
			| (cast(Instruction, a)<<POS_A) \
			| (cast(Instruction, bc)<<POS_Bx))




/*
** invalid register that fits in 8 bits
*/
#define NO_REG		MAXARG_A


/*
** R(x) - register
** Kst(x) - constant (in constant table)
** RK(x) == if x < MAXSTACK then R(x) else Kst(x-MAXSTACK)
*/


/*
** grep "ORDER OP" if you change these enums
*/

typedef enum {
  OP_UNUSED0,
  OP_MOVE,
  OP_LOADK,
  OP_LOADBOOL,
  OP_LOADNIL,
  OP_GETUPVAL,
  OP_GETGLOBAL,
  OP_GETTABLE,
  OP_UNUSED8,
  OP_SETGLOBAL,
  OP_SETUPVAL,
  OP_SETTABLE,
  OP_NEWTABLE,
  OP_UNUSED13,
  OP_SELF,
  OP_UNUSED15,
  OP_ADD,
  OP_SUB,
  OP_MUL,
  OP_DIV,
  OP_POW,
  OP_UNM,
  OP_NOT,
  OP_CONCAT,
  OP_UNUSED24,
  OP_JMP,
  OP_EQ,
  OP_LT,
  OP_LE,
  OP_TEST,
  OP_CALL,
  OP_RETURN,
  OP_TAILCALL,
  OP_UNUSED33,
  OP_FORLOOP,
  OP_TFORLOOP,
  OP_TFORPREP,
  OP_SETLIST,
  OP_SETLISTO,
  OP_UNUSED39,
  OP_CLOSE,
  OP_CLOSURE,
  OP_UNUSED42,
  OP_UNUSED43,
  OP_UNUSED44
} OpCode;

#define NUM_OPCODES	(cast(int, OP_CLOSURE+1))



/*===========================================================================
  Notes:
  (1) In OP_CALL, if (B == 0) then B = top. C is the number of returns - 1,
      and can be 0: OP_CALL then sets `top' to last_result+1, so
      next open instruction (OP_CALL, OP_RETURN, OP_SETLIST) may use `top'.

  (2) In OP_RETURN, if (B == 0) then return up to `top'

  (3) For comparisons, B specifies what conditions the test should accept.

  (4) All `skips' (pc++) assume that next instruction is a jump
===========================================================================*/


/*
** masks for instruction properties
*/  
enum OpModeMask {
  OpModeBreg = 2,       /* B is a register */
  OpModeBrk,		/* B is a register/constant */
  OpModeCrk,           /* C is a register/constant */
  OpModesetA,           /* instruction set register A */
  OpModeK,              /* Bx is a constant */
  OpModeT		/* operator is a test */
  
};


extern const lu_byte luaP_opmodes[NUM_OPCODES];

#define getOpMode(m)            (cast(enum OpMode, luaP_opmodes[m] & 3))
#define testOpMode(m, b)        (luaP_opmodes[m] & (1 << (b)))


#ifdef LUA_OPNAMES
extern const char *const luaP_opnames[];  /* opcode names */
#endif



/* number of list items to accumulate before a SETLIST instruction */
/* (must be a power of 2) */
#define LFIELDS_PER_FLUSH	32


#endif
