#ifndef INSTRUCTIONDECODER_H_
#define INSTRUCTIONDECODER_H_

#include <iostream>
#include <String>
#include <vector>
#include "Utils.h"
#include "error.h"

using namespace std;

int InsDecode() {
	if (insType == 0) {//Rtype
		if (rIns.Dfcnt == 0) {
			cout << "sll " << regName[rIns.Drd] << ", " << regName[rIns.Drt] << ", " << rIns.Dsh << endl;
			ALUControl = 1;
		}
		else if (rIns.Dfcnt == 2) {
			cout << "srl " << regName[rIns.Drd] << ", " << regName[rIns.Drt] << ", " << rIns.Dsh << endl;
			ALUControl = 2;
		}
		else if (rIns.Dfcnt == 3) {
			cout << "sra " << regName[rIns.Drd] << ", " << regName[rIns.Drt] << ", " << rIns.Dsh << endl;
			ALUControl = 3;
		}
		else if (rIns.Dfcnt == 8) {
			cout << "jr " << regName[rIns.Drs] << endl;
		}
		else if (rIns.Dfcnt == 12) {
			cout << "SYSCALL" << endl;
			SYSCALLflag = true;
		}
		else if (rIns.Dfcnt == 16) {
			cout << "mfhi " << regName[rIns.Drd] << endl;
		}
		else if (rIns.Dfcnt == 18) {
			cout << "mflo " << regName[rIns.Drd] << endl;

		}
		else if (rIns.Dfcnt == 24) {
			cout << "mul " << regName[rIns.Drd] << ", " << regName[rIns.Drs] << ", " << regName[rIns.Drt] << endl;
		}
		else if (rIns.Dfcnt == 32) {
			cout << "add " << regName[rIns.Drd] << ", " << regName[rIns.Drs] << ", " << regName[rIns.Drt] << endl;
			ALUControl = 8;
		}
		else if (rIns.Dfcnt == 34) {
			cout << "sub " << regName[rIns.Drd] << ", " << regName[rIns.Drs] << ", " << regName[rIns.Drt] << endl;
			ALUControl = 9;
		}
		else if (rIns.Dfcnt == 36) {
			cout << "and " << regName[rIns.Drd] << ", " << regName[rIns.Drs] << ", " << regName[rIns.Drt] << endl;
			ALUControl = 12;
		}
		else if (rIns.Dfcnt == 37) {
			cout << "or " << regName[rIns.Drd] << ", " << regName[rIns.Drs] << ", " << regName[rIns.Drt] << endl;
			ALUControl = 13;
		}
		else if (rIns.Dfcnt == 38) {
			cout << "xor " << regName[rIns.Drd] << ", " << regName[rIns.Drs] << ", " << regName[rIns.Drt] << endl;
			ALUControl = 14;
		}
		else if (rIns.Dfcnt == 39) {
			cout << "nor " << regName[rIns.Drd] << ", " << regName[rIns.Drs] << ", " << regName[rIns.Drt] << endl;
			ALUControl = 15;
		}
		else if (rIns.Dfcnt == 43) {
			cout << "slt " << regName[rIns.Drd] << ", " << regName[rIns.Drs] << ", " << regName[rIns.Drt] << endl;
			ALUControl = 4;
		}
		else return WRONG_INSTRUCTION;
	}
	else if (insType == 1) {//Itype
		if (iIns.op == 1) {
			cout << "bltz " << regName[iIns.Drt] << ", " << regName[iIns.Drs] << endl;
			ALUControl = 4;
		}
		else if (iIns.op == 4) {
			cout << "beq " << regName[iIns.Drt] << ", " << regName[iIns.Drs] << ", ";
			cout << dec << iIns.Doperand << endl;
			ALUControl = 1;
		}
		else if (iIns.op == 5) {
			cout << "bne " << regName[iIns.Drt] << ", " << regName[iIns.Drs] << ", ";
			cout << dec << iIns.Doperand << endl;
			ALUControl = 1;
		}
		else if (iIns.op == 8) {
			cout << "addi " << regName[iIns.Drt] << ", " << regName[iIns.Drs] << ", " << iIns.Doperand << endl;
			//cout<<"addi's operand "<<iIns.operand<<endl;
			ALUControl = 8;
		}
		else if (iIns.op == 10) {
			cout << "slti " << regName[iIns.Drt] << ", " << regName[iIns.Drs] << ", " << iIns.Doperand << endl;
			ALUControl = 4;
		}
		else if (iIns.op == 12) {
			cout << "andi " << regName[iIns.Drt] << ", " << regName[iIns.Drs] << ", " << iIns.Doperand << endl;
			ALUControl = 12;
		}
		else if (iIns.op == 13) {
			cout << "ori " << regName[iIns.Drt] << ", " << regName[iIns.Drs] << ", " << iIns.Doperand << endl;
			ALUControl = 13;
		}
		else if (iIns.op == 14) {
			cout << "xori " << regName[iIns.Drt] << ", " << regName[iIns.Drs] << ", " << iIns.Doperand << endl;
			ALUControl = 14;
		}
		else if (iIns.op == 15) {
			cout << "lui " << regName[iIns.Drt] << ", " << regName[iIns.Drs] << ", " << iIns.Doperand << endl;
			ALUControl = 1;
		}
		else if (iIns.op == 32) {
			cout << "lb " << regName[iIns.Drt] << ", " << iIns.Doperand << "(" << regName[iIns.Drs] << ")" << endl;
			ALUControl = 8;
		}
		else if (iIns.op == 35) {
			cout << "lw " << regName[iIns.Drt] << ", " << iIns.Doperand << "(" << regName[iIns.Drs] << ")" << endl;
			ALUControl = 8;
		}
		else if (iIns.op == 36) {
			cout << "lbu " << regName[iIns.Drt] << ", " << iIns.Doperand << "(" << regName[iIns.Drs] << ")" << endl;
			ALUControl = 8;
		}
		else if (iIns.op == 40) {
			cout << "sb " << regName[iIns.Drt] << ", " << iIns.Doperand << "(" << regName[iIns.Drs] << ")" << endl;
			ALUControl = 8;
		}
		else if (iIns.op == 43) {
			cout << "sw " << regName[iIns.Drt] << ", " << iIns.Doperand << "(" << regName[iIns.Drs] << ")" << endl;
			ALUControl = 8;
		}
		else return WRONG_INSTRUCTION;
	}
	else {//Jtype
		if (jIns.op == 2) {
			cout << "j ";
			cout << hex << "0x" << jIns.DAddress * 4 << endl;
		}
		else if (jIns.op == 3) {
			cout << "jal ";
			cout << hex << "0x" << jIns.DAddress * 4 << endl;
		}
		else return WRONG_INSTRUCTION;
	}

	return 0;
}

#endif /* INSTRUCTIONDECODER_H_ */
