/*
** $Id: lopcodes.c,v 1.37 2005/11/08 19:45:36 roberto Exp $
** See Copyright Notice in lua.h
*/


#define lopcodes_c
#define LUA_CORE


#include "lopcodes.h"


/* ORDER OP */
const char* const luaP_opnames[NUM_OPCODES + 1] = {
	NULL,
	"MOVE",
	"LOADK",
	"LOADBOOL",
	"LOADNIL",
	"GETUPVAL",
	"GETGLOBAL",
	"GETTABLE",
	NULL,			/* unused */
	"SETGLOBAL",
	"SETUPVAL",
	"SETTABLE",
	"NEWTABLE",
	NULL,			/* unused */
	"SELF",
	NULL,			/* unused */
	"ADD",
	"SUB",
	"MUL",
	"DIV",
	"MOD",
	"POW",
	"UNM",
	"NOT",
	"LEN",
	"CONCAT",
	NULL,			/* unused */
	"JMP",
	"EQ",
	"LT",
	"LE",
	"TEST",
	"TESTSET",
	"CALL",
	"TAILCALL",
	NULL,			/* unused */
	"RETURN",
	"FORLOOP",
	"FORPREP",
	"TFORLOOP",
	"SETLIST",
	NULL,			/* unused */
	"CLOSE",
	"CLOSURE",
	"VARARG",
	NULL
};


#define opmode(t,a,b,c,m) (((t)<<7) | ((a)<<6) | ((b)<<4) | ((c)<<2) | (m))

const lu_byte luaP_opmodes[NUM_OPCODES] = {
	/*	I				   T  A  B       C		 mode		opcode	*/
	/* op0 */	opmode(0, 1, OpArgR, OpArgN, iABC),		/* OP_MOVE */		/* unused */
	/* op1 */	opmode(0, 1, OpArgR, OpArgN, iABC), 	/* OP_MOVE */
	/* op2 */	opmode(0, 1, OpArgK, OpArgN, iABx),		/* OP_LOADK */
	/* op3 */	opmode(0, 1, OpArgU, OpArgU, iABC),		/* OP_LOADBOOL */
	/* op4 */	opmode(0, 1, OpArgR, OpArgN, iABC),		/* OP_LOADNIL */
	/* op5 */	opmode(0, 1, OpArgU, OpArgN, iABC),		/* OP_GETUPVAL */
	/* op6 */	opmode(0, 1, OpArgK, OpArgN, iABx),		/* OP_GETGLOBAL */
	/* op7 */	opmode(0, 1, OpArgR, OpArgK, iABC),		/* OP_GETTABLE */
	/* op8 */	opmode(0, 0, OpArgU, OpArgN, iABC),		/* OP_SETUPVAL */	/* unused */
	/* op9 */	opmode(0, 0, OpArgK, OpArgN, iABx),		/* OP_SETGLOBAL */
	/* op10 */	opmode(0, 0, OpArgU, OpArgN, iABC),		/* OP_SETUPVAL */
	/* op11 */	opmode(0, 0, OpArgK, OpArgK, iABC),		/* OP_SETTABLE */
	/* op12 */	opmode(0, 1, OpArgU, OpArgU, iABC),		/* OP_NEWTABLE */
	/* op13 */	opmode(0, 1, OpArgK, OpArgK, iABC),		/* OP_SUB */		/* unused */
	/* op14 */	opmode(0, 1, OpArgR, OpArgK, iABC),		/* OP_SELF */
	/* op15 */	opmode(0, 1, OpArgK, OpArgK, iABC),		/* OP_DIV */		/* unused */
	/* op16 */	opmode(0, 1, OpArgK, OpArgK, iABC),		/* OP_ADD */
	/* op17 */	opmode(0, 1, OpArgK, OpArgK, iABC),		/* OP_SUB */
	/* op18 */	opmode(0, 1, OpArgK, OpArgK, iABC),		/* OP_MUL */
	/* op19 */	opmode(0, 1, OpArgK, OpArgK, iABC),		/* OP_DIV */
	/* op20 */	opmode(0, 1, OpArgK, OpArgK, iABC),		/* OP_MOD */
	/* op21 */	opmode(0, 1, OpArgK, OpArgK, iABC),		/* OP_POW */
	/* op22 */	opmode(0, 1, OpArgR, OpArgN, iABC),		/* OP_UNM */
	/* op23 */	opmode(0, 1, OpArgR, OpArgN, iABC),		/* OP_NOT */
	/* op24 */	opmode(0, 1, OpArgR, OpArgN, iABC),		/* OP_LEN */
	/* op25 */	opmode(0, 1, OpArgR, OpArgR, iABC),		/* OP_CONCAT */
	/* op26 */	opmode(1, 1, OpArgR, OpArgU, iABC),		/* OP_TEST */		/* unused */
	/* op27 */	opmode(0, 0, OpArgR, OpArgN, iAsBx),	/* OP_JMP */
	/* op28 */	opmode(1, 0, OpArgK, OpArgK, iABC),		/* OP_EQ */
	/* op29 */	opmode(1, 0, OpArgK, OpArgK, iABC),		/* OP_LT */
	/* op30 */	opmode(1, 0, OpArgK, OpArgK, iABC),		/* OP_LE */
	/* op31 */	opmode(1, 1, OpArgR, OpArgU, iABC),		/* OP_TEST */
	/* op32 */	opmode(1, 1, OpArgR, OpArgU, iABC),		/* OP_TESTSET */
	/* op33 */	opmode(0, 1, OpArgU, OpArgU, iABC),		/* OP_CALL */
	/* op34 */	opmode(0, 1, OpArgU, OpArgU, iABC),		/* OP_TAILCALL */
	/* op35 */	opmode(0, 0, OpArgN, OpArgN, iABC),		/* OP_CLOSE */		/* unused */
	/* op36 */	opmode(0, 0, OpArgU, OpArgN, iABC),		/* OP_RETURN */
	/* op37 */	opmode(0, 1, OpArgR, OpArgN, iAsBx),	/* OP_FORLOOP */
	/* op38 */	opmode(0, 1, OpArgR, OpArgN, iAsBx),	/* OP_FORPREP */
	/* op39 */	opmode(1, 0, OpArgN, OpArgU, iABC),		/* OP_TFORLOOP */
	/* op40 */	opmode(0, 0, OpArgU, OpArgU, iABC),		/* OP_SETLIST */
	/* op41 */	opmode(0, 1, OpArgR, OpArgN, iABC),		/* OP_MOVE */		/* unused */
	/* op42 */	opmode(0, 0, OpArgN, OpArgN, iABC),		/* OP_CLOSE */
	/* op43 */	opmode(0, 1, OpArgU, OpArgN, iABx),		/* OP_CLOSURE */
	/* op44 */	opmode(0, 1, OpArgU, OpArgN, iABC)		/* OP_VARARG */
};