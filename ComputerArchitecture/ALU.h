#ifndef ALU_H_
#define ALU_H_

#include <iostream>
#include "MEM.h"
#include "Utils.h"
#include "error.h"

using namespace std;

int ALU(int X, int Y, int C, int *Z);
int logicOperation(int X, int Y, int C);
int addSubtract(int X, int Y, int C);
int shiftOperation(int V, int Y, int C);
int checkZero(int S);
int checkSetLess(int X, int Y);
int ALUOperation();

/*
 * no s 0 sll 1 srl 2 sra 3
 * setless 4 5 6 7
 * add 8 10 sub 9 11
 * and 12 or 13 xor 14 nor 15
 */

int ALUOperation() {
	char buf[33], buf2[17];
	buf[32] = '\0'; buf2[16] = '\0';
	int Z;
	if (insType == 0) {//R
		if (rIns.Dfcnt == 0) {
			reg[rIns.Drd] = ALU(reg[rIns.Drt], rIns.Dsh, ALUControl, &Z);
		}
		else if (rIns.Dfcnt == 2) {
			reg[rIns.Drd] = ALU(reg[rIns.Drt], rIns.Dsh, ALUControl, &Z);
		}
		else if (rIns.Dfcnt == 3) {
			reg[rIns.Drd] = ALU(reg[rIns.Drt], rIns.Dsh, ALUControl, &Z);
		}
		else if (rIns.Dfcnt == 8) {//jr
			PC = reg[rIns.Drs];
		}
		else if (rIns.Dfcnt == 16) {//mfhi
			reg[rIns.Drd] = regHi;
		}
		else if (rIns.Dfcnt == 18) {//mflo
			reg[rIns.Drd] = regLo;
		}
		else if (rIns.Dfcnt == 24) {//mul¿¬»ê
			reg[rIns.Drd] = reg[rIns.Drs] * reg[rIns.Drt];
		}// bne
		else reg[rIns.Drd] = ALU(reg[rIns.Drs], reg[rIns.Drt], ALUControl, &Z);
	}
	else if (insType == 1) {//I
		if (iIns.op == 1) {//bltz
			if (ALU(reg[iIns.Drs], 0, ALUControl, &Z) == 1) {
				PC += iIns.Doperand - 4;
			}
		}
		else if (iIns.op == 4) {//beq
			ALU(reg[iIns.Drs], reg[iIns.Drt], 9, &Z);
			if (Z)
				PC += ALU(iIns.Doperand, 2, ALUControl, &Z) - 4;
		}
		else if (iIns.op == 5) {//bne
			ALU(reg[iIns.Drs], reg[iIns.Drt], 9, &Z);
			if (Z != 1)
				PC += ALU(iIns.Doperand, 2, ALUControl, &Z) - 4;
		}
		else if (iIns.op == 13) {//ori
			int tmp = ALU(reg[iIns.Drs], iIns.Doperand, ALUControl, &Z);
			tmp = ALU(tmp, 16, 1, &Z);
			reg[iIns.Drt] = ALU(tmp, 16, 2, &Z);
		}
		else if (iIns.op == 15) {//for lui
			reg[iIns.Drt] = ALU(iIns.Doperand, 16, ALUControl, &Z);//iIns.Drt·¹Áö½ºÅÍ »óÀ§ 2¹ÙÀÌÆ®¿¡operand°ªÀúÀå
		}
		else if (iIns.op == 43) {//sw
			dTOb(reg[iIns.Drt], buf, 32);
			cutbit(buf, 32, Cbin1, Cbin2, Cbin3, Cbin4);
			MEM(ALU(reg[iIns.Drs], iIns.Doperand, ALUControl, &Z), bTOd(Cbin1, 8), MEMWRITE, WORD);
			MEM(ALU(reg[iIns.Drs], iIns.Doperand + 1, ALUControl, &Z), bTOd(Cbin2, 8), MEMWRITE, WORD);
			MEM(ALU(reg[iIns.Drs], iIns.Doperand + 2, ALUControl, &Z), bTOd(Cbin3, 8), MEMWRITE, WORD);
			MEM(ALU(reg[iIns.Drs], iIns.Doperand + 3, ALUControl, &Z), bTOd(Cbin4, 8), MEMWRITE, WORD);
		}
		else if (iIns.op == 40) {//sb
			MEM(ALU(reg[iIns.Drs], iIns.Doperand, ALUControl, &Z), reg[iIns.Drt], MEMWRITE, WORD);
		}
		else if (iIns.op == 35) {//lw
			MEM(ALU(reg[iIns.Drs], iIns.Doperand, ALUControl, &Z), 0, MEMREAD, WORD);
			fusion(buf, Cbin1, Cbin2, Cbin3, Cbin4, 32);
			reg[iIns.Drt] = sbTOd(buf, 32);
		}
		else if (iIns.op == 32) {//lb
			MEM(ALU(reg[iIns.Drs], iIns.Doperand, ALUControl, &Z), 0, MEMREAD, BYTE);
			reg[iIns.Drt] = sbTOd(Cbin1, 8);
		}
		else reg[iIns.Drt] = ALU(reg[iIns.Drs], iIns.Doperand, ALUControl, &Z);
	}
	else if (insType == 2) {//J
		if (jIns.op == 2) {
			PC = jIns.DAddress * 4 - 4;
		}
		else if (jIns.op == 3) {//jal
			reg[31] = PC;
			PC = jIns.DAddress * 4 - 4;
		}
	}
	else return ALU_OPERATE_ERROR;
	return 0;
}

int ALU(int X, int Y, int C, int *Z) {
	int c32, c10, ret;
	c32 = (C >> 2) & 3;
	c10 = C & 3;
	if (c32 == 0) {
		ret = shiftOperation(X, Y, c10);
	}
	else if (c32 == 1) {
		ret = checkSetLess(X, Y);
	}
	else if (c32 == 2) {
		if (c10 == 0 || c10 == 2) ret = addSubtract(X, Y, 0);//µ¡¼À
		else ret = addSubtract(X, Y, 1);//»¬»ù
		*Z = checkZero(ret);
	}
	else {
		ret = logicOperation(X, Y, c10);
	}
	return ret;
}

int logicOperation(int X, int Y, int C) {
	if (C < 0 || C>3) {
		pErrorMessage(ALU_LOGIC_ERROR);
		return ALU_LOGIC_ERROR;
	}
	if (C == 0) {
		return X & Y;
	}
	else if (C == 1) {
		return X | Y;
	}
	else if (C == 2) {
		return X ^ Y;
	}
	else {
		return ~(X | Y);
	}
	return 0;
}

int addSubtract(int X, int Y, int C) {
	int ret;
	if (C < 0 || C>1) {
		pErrorMessage(ALU_ADDSUB_ERROR);
		return ALU_ADDSUB_ERROR;
	}
	if (C == 0) {
		ret = X + Y;
	}
	else if (C == 1) {
		ret = X - Y;
	}
	return ret;
}
int shiftOperation(int V, int Y, int C) {
	int ret;
	unsigned int V2 = V;
	if (C < 0 || C>3) {
		pErrorMessage(ALU_SHIFTOP_ERROR);
		return ALU_SHIFTOP_ERROR;
	}
	if (C == 0) {
		ret = V;
	}
	else if (C == 1) {
		ret = V << Y;
	}
	else if (C == 2) {
		ret = V2 >> Y;
	}
	else {
		ret = V >> Y;
	}
	return ret;
}
int checkZero(int S) {
	int ret;
	if (S == 0) ret = 1;
	else ret = 0;
	return ret;
}
int checkSetLess(int X, int Y) {
	int ret;
	if (X < Y) ret = 1;
	else ret = 0;
	return ret;
}

#endif /* ALU_H_ */
