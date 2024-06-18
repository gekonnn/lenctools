/*
** $Id: lopcodes.c,v 1.37 2005/11/08 19:45:36 roberto Exp $
** See Copyright Notice in lua.h
*/


#define lopcodes_c
#define LUA_CORE


#include "lopcodes.h"


/* ORDER OP */

const char *const luaP_opnames[NUM_OPCODES+1] = {
	NULL,
	"MOVE",
	"LOADK",
	"LOADBOOL",
	"LOADNIL",
	"GETUPVAL",
	"GETGLOBAL",
	"GETTABLE",
	"SETUPVAL", // clone
	"SETGLOBAL",
	"SETUPVAL",
	"SETTABLE",
	"NEWTABLE",
	"SUB", // clone
	"SELF",
	"DIV", // clone
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
	"TEST", // clone
	"JMP",
	"EQ",
	"LT",
	"LE",
	"TEST",
	"TESTSET",
	"CALL",
	"TAILCALL",
	"CLOSE", // clone
	"RETURN",
	"FORLOOP",
	"FORPREP",
	"TFORLOOP",
	"SETLIST",
	NULL, // op41
	"CLOSE",
	"CLOSURE",
	"VARARG",
	NULL
};


#define opmode(t,a,b,c,m) (((t)<<7) | ((a)<<6) | ((b)<<4) | ((c)<<2) | (m))

// repeating: sub, not, self, forloop
const lu_byte luaP_opmodes[NUM_OPCODES] = {
/*       T  A    B       C     mode		   opcode	*/
	opmode(0, 1, OpArgR, OpArgN, iABC),		// dummy
	opmode(0, 1, OpArgR, OpArgN, iABC), 	/* OP_MOVE */
	opmode(0, 1, OpArgK, OpArgN, iABx),		/* OP_LOADK */
	opmode(0, 1, OpArgU, OpArgU, iABC),		/* OP_LOADBOOL */
	opmode(0, 1, OpArgR, OpArgN, iABC),		/* OP_LOADNIL */
	opmode(0, 1, OpArgU, OpArgN, iABC),		/* OP_GETUPVAL */
	opmode(0, 1, OpArgK, OpArgN, iABx),		/* OP_GETGLOBAL */
	opmode(0, 1, OpArgR, OpArgK, iABC),		/* OP_GETTABLE */
	opmode(0, 0, OpArgU, OpArgN, iABC),		/* OP_SETUPVAL */ // clone
	opmode(0, 0, OpArgK, OpArgN, iABx),		/* OP_SETGLOBAL */
	opmode(0, 0, OpArgU, OpArgN, iABC),		/* OP_SETUPVAL */
	opmode(0, 0, OpArgK, OpArgK, iABC),		/* OP_SETTABLE */
	opmode(0, 1, OpArgU, OpArgU, iABC),		/* OP_NEWTABLE */
	opmode(0, 1, OpArgK, OpArgK, iABC),		/* OP_SUB */ // clone
	opmode(0, 1, OpArgR, OpArgK, iABC),		/* OP_SELF */
	opmode(0, 1, OpArgK, OpArgK, iABC),		/* OP_DIV */ // clone
	opmode(0, 1, OpArgK, OpArgK, iABC),		/* OP_ADD */
	opmode(0, 1, OpArgK, OpArgK, iABC),		/* OP_SUB */
	opmode(0, 1, OpArgK, OpArgK, iABC),		/* OP_MUL */
	opmode(0, 1, OpArgK, OpArgK, iABC),		/* OP_DIV */
	opmode(0, 1, OpArgK, OpArgK, iABC),		/* OP_MOD */
	opmode(0, 1, OpArgK, OpArgK, iABC),		/* OP_POW */
	opmode(0, 1, OpArgR, OpArgN, iABC),		/* OP_UNM */
	opmode(0, 1, OpArgR, OpArgN, iABC),		/* OP_NOT */
	opmode(0, 1, OpArgR, OpArgN, iABC),		/* OP_LEN */
	opmode(0, 1, OpArgR, OpArgR, iABC),		/* OP_CONCAT */
	opmode(1, 1, OpArgR, OpArgU, iABC),		/* OP_TEST */ // clone
	opmode(0, 0, OpArgR, OpArgN, iAsBx),	/* OP_JMP */
	opmode(1, 0, OpArgK, OpArgK, iABC),		/* OP_EQ */
	opmode(1, 0, OpArgK, OpArgK, iABC),		/* OP_LT */
	opmode(1, 0, OpArgK, OpArgK, iABC),		/* OP_LE */
	opmode(1, 1, OpArgR, OpArgU, iABC),		/* OP_TEST */
	opmode(1, 1, OpArgR, OpArgU, iABC),		/* OP_TESTSET */
	opmode(0, 1, OpArgU, OpArgU, iABC),		/* OP_CALL */
	opmode(0, 1, OpArgU, OpArgU, iABC),		/* OP_TAILCALL */
	opmode(0, 0, OpArgN, OpArgN, iABC),		/* OP_CLOSE */ // clone
	opmode(0, 0, OpArgU, OpArgN, iABC),		/* OP_RETURN */
	opmode(0, 1, OpArgR, OpArgN, iAsBx),	/* OP_FORLOOP */
	opmode(0, 1, OpArgR, OpArgN, iAsBx),	/* OP_FORPREP */
	opmode(1, 0, OpArgN, OpArgU, iABC),		/* OP_TFORLOOP */
	opmode(0, 0, OpArgU, OpArgU, iABC),		/* OP_SETLIST */
	opmode(0, 1, OpArgR, OpArgN, iABC),		// dummy, can't get to figure out op41
	opmode(0, 0, OpArgN, OpArgN, iABC),		/* OP_CLOSE */
	opmode(0, 1, OpArgU, OpArgN, iABx),		/* OP_CLOSURE */
	opmode(0, 1, OpArgU, OpArgN, iABC)		/* OP_VARARG */
};

