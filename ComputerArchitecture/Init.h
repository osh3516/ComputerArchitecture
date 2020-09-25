#pragma once
#include <string.h>

void InitMEM(int InsNum, int DataNum) {
	for (int i = 0; i < InsNum * 4; i++) {
		progMEM[i] = -1;
	}
	for (int i = 0; i < DataNum * 4; i++) {
		dataMEM[i] = 0;
	}
	for (int i = 0; i < 8; i++) {
		Cbin1[i] = 0;
		Cbin2[i] = 0;
		Cbin3[i] = 0;
		Cbin4[i] = 0;
	}
	progMEMaddr = 0x400000; dataMEMaddr = 0x10000000; stakMEMaddr = 0x7ff00000;
}

void InitREG() {
	for (int i = 0; i < 32; i++) {
		reg[i] = 0;
	}
	reg[29] = 0x7fffffff;
}


void InitBreakPoint() {
	breakPoint.clear();
}

