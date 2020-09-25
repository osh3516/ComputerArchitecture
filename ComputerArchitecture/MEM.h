#pragma once
#include <iostream>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "InstructionDecoder.h"

#define MEMREAD 0
#define MEMWRITE 1
#define WORD 2
#define HALFWORD 1
#define BYTE 0

//주소저븐
//BYTE, HALF WORD

//바이너리파일메모리에적재
//프로그램부분만
int progMEM[0x100000], dataMEM[0x100000], stakMEM[0x100000];
int progMEMaddr = 0x400000, dataMEMaddr = 0x10000000, stakMEMaddr = 0x7ff00000;
char Cbin1[9], Cbin2[9], Cbin3[9], Cbin4[9];

void MEM(int A, int V, int nRW, int S) {//A=address, v=value, s=word
	int WM = 0;//어떤 메모리인지 체크
	int offset = A & 0xFFFFF;//오프셋을 만들어 어디에 저장할지 저장

	if (A >= 0x400000 && A < 0x500000) WM = 0; // program memory
	else if (A >= 0x10000000 && A < 0x100fffff) WM = 1; // data memory
	else if (A >= 0x7ff00000 && A < 0x7fffffff) WM = 2; // stack
	else {
		pErrorMessage(MEM_NOMEM_ERROR);
	}
	/////////////////////////////////////progMEM/////////////////////////////////////
	if (WM == 0 && S == 0) {//progMEM and byte
		if (nRW == 0) {//read return 시킴
			dTOb(progMEM[offset], Cbin1, 8);
		}
		else if (nRW == 1) {
			progMEM[offset] = V;
		}
		else {
			pErrorMessage(WRONG_INSTRUCTION);
			exit(1);
		}
	}

	else if (WM == 0 && S == 1) {//progMEM and word
		if (nRW == 0) {//read return 시킴
			dTOb(progMEM[offset], Cbin1, 8);
			dTOb(progMEM[offset + 1], Cbin2, 8);
		}
		else if (nRW == 1) {
			progMEM[offset] = V;
		}
		else {
			pErrorMessage(WRONG_INSTRUCTION);
			exit(1);
		}
	}

	else if (WM == 0 && S == 2) {//progMEM and word
		if (nRW == 0) {//read return 시킴
			dTOb(progMEM[offset], Cbin1, 8);
			dTOb(progMEM[offset + 1], Cbin2, 8);
			dTOb(progMEM[offset + 2], Cbin3, 8);
			dTOb(progMEM[offset + 3], Cbin4, 8);
		}
		else if (nRW == 1) {
			progMEM[offset] = V;
		}
		else {
			pErrorMessage(WRONG_INSTRUCTION);
			exit(1);
		}
	}


	/////////////////////////////////////dataMEM/////////////////////////////////////
	else if (WM == 1 && S == 0) {//dataMEM and byte
		if (nRW == 0) {//read return 시킴
			dTOb(dataMEM[offset], Cbin1, 8);
		}
		else if (nRW == 1) {
			dataMEM[offset] = V;
		}
		else {
			pErrorMessage(WRONG_INSTRUCTION);
			exit(1);
		}
	}

	else if (WM == 1 && S == 1) {//dataMEM and half word
		if (nRW == 0) {//read return 시킴
			dTOb(dataMEM[offset], Cbin1, 8);
			dTOb(dataMEM[offset + 1], Cbin2, 8);
		}
		else if (nRW == 1) {
			dataMEM[offset] = V;
		}
		else {
			pErrorMessage(WRONG_INSTRUCTION);
			exit(1);
		}
	}

	else if (WM == 1 && S == 2) {//dataMEM and word
		if (nRW == 0) {//read return 시킴
			dTOb(dataMEM[offset], Cbin1, 8);
			dTOb(dataMEM[offset + 1], Cbin2, 8);
			dTOb(dataMEM[offset + 2], Cbin3, 8);
			dTOb(dataMEM[offset + 3], Cbin4, 8);
		}
		else if (nRW == 1) {
			dataMEM[offset] = V;
		}
		else {
			pErrorMessage(WRONG_INSTRUCTION);
			exit(1);
		}
	}

	/////////////////////////////////////stakMEM/////////////////////////////////////

	else if (WM == 2 && S == 0) {//dataMEM and byte
		if (nRW == 0) {//read return 시킴
			dTOb(stakMEM[offset], Cbin1, 8);
		}
		else if (nRW == 1) {
			stakMEM[offset] = V;
		}
		else {
			pErrorMessage(WRONG_INSTRUCTION);
			exit(1);
		}
	}

	else if (WM == 2 && S == 1) {//dataMEM and half word
		if (nRW == 0) {//read return 시킴
			dTOb(stakMEM[offset], Cbin1, 8);
			dTOb(stakMEM[offset + 1], Cbin2, 8);
		}
		else if (nRW == 1) {
			stakMEM[offset] = V;
		}
		else {
			pErrorMessage(WRONG_INSTRUCTION);
			exit(1);
		}
	}

	else if (WM == 2 && S == 2) {//dataMEM and word
		if (nRW == 0) {//read return 시킴
			dTOb(stakMEM[offset], Cbin1, 8);
			dTOb(stakMEM[offset + 1], Cbin2, 8);
			dTOb(stakMEM[offset + 2], Cbin3, 8);
			dTOb(stakMEM[offset + 3], Cbin4, 8);
		}
		else if (nRW == 1) {
			stakMEM[offset] = V;
		}
		else {
			pErrorMessage(WRONG_INSTRUCTION);
			exit(1);
		}
	}

}
