#ifndef INSTRUCTIONFETCH_H_
#define INSTRUCTIONFETCH_H_

#include <iostream>
#include <String>
#include <vector>
#include "Utils.h"
#include "error.h"
using namespace std;


int InsFetch(char s1[], char s2[], char s3[], char s4[]) {
	string opcode;
	int DOpcode;//decoding opcode
	for (int i = 0; i < 6; i++) {
		opcode += s1[i];
	}
	DOpcode = bTOd(opcode, 6);
	if (DOpcode == 0) { //RType
		insType = 0;
		rIns.op = DOpcode;
		rIns.fcnt.clear();
		rIns.rs.clear();
		rIns.rt.clear();
		rIns.rd.clear();
		rIns.sh.clear();
		for (int i = 6; i < 32; i++) {
			if (i < 8) rIns.rs += s1[i];//6 7
			else if (i < 11) rIns.rs += s2[i - 8];//8 9 10
			else if (i < 16) rIns.rt += s2[i - 8];//11 12 13 14 15
			else if (i < 21) rIns.rd += s3[i - 16];//16 17 18 19 20
			else if (i < 24) rIns.sh += s3[i - 16];//21 22 23
			else if (i < 26) rIns.sh += s4[i - 24];//24 25
			else if (i < 29) rIns.fcnt += s4[i - 24];//26 27 28
			else if (i < 32) rIns.fcnt += s4[i - 24];//29 30 31
		}
		rIns.Drs = bTOd(rIns.rs, 5);
		rIns.Drt = bTOd(rIns.rt, 5);
		rIns.Drd = bTOd(rIns.rd, 5);
		rIns.Dsh = bTOd(rIns.sh, 5);
		rIns.Dfcnt = bTOd(rIns.fcnt, 6);
	}
	else if (DOpcode == 2 || DOpcode == 3) { //JType
		insType = 2;
		jIns.op = DOpcode;
		for (int i = 6; i < 32; i++) {
			if (i < 8) jIns.address += s1[i];
			else if (i < 16) jIns.address += s2[i - 8];
			else if (i < 24) jIns.address += s3[i - 16];
			else if (i < 32) jIns.address += s4[i - 24];
		}
		jIns.DAddress = bTOd(jIns.address, 26);
		jIns.address.clear();
	}
	else { //IType
		insType = 1;
		iIns.op = DOpcode;
		iIns.operand.clear();
		iIns.rs.clear();
		iIns.rt.clear();
		for (int i = 6; i < 32; i++) {
			if (i < 8) iIns.rs += s1[i];//6 7
			else if (i < 11) iIns.rs += s2[i - 8];//8 9 10
			else if (i < 16) iIns.rt += s2[i - 8];//11 12 13 14 15
			else if (i < 24) iIns.operand += s3[i - 16];//16 17 18 19 20 21 22 23
			else if (i < 32) iIns.operand += s4[i - 24];//24 25 26 27 28 29 30 31
		}
		iIns.Drs = bTOd(iIns.rs, 5);
		iIns.Drt = bTOd(iIns.rt, 5);
		if (iIns.operand[0] == '1') {
			iIns.Doperand = (-1)*bTOd(make2bosoo(iIns.operand, 16), 16);
		}
		else iIns.Doperand = bTOd(iIns.operand, 16);
	}

	return insType;
}

#endif /* INSTRUCTIONFETCH_H_ */

