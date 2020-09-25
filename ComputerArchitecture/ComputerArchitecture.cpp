#include <iostream>
#include <String>
#include <vector>
#include "pch.h"
#include "InstructionFetch.h"
#include "InstructionDecoder.h"
#include "ALU.h"
#include "MEM.h"
#include "init.h"

using namespace std;

void basicOperation(int insNum, int singleflag);

int main() {
	int InsNum = 0, DataNum = 0;
	int ch, n;
	int Osize = 0;
	int Dsize = 0;
	bool quit = false;
	char fileName[50];
	while (!quit) {
		string command;
		int singleflag = 0;
		PC = 0x400000;
		SYSCALLflag = false;
		cout << "=========================================" << endl;
		cout << "l:load file\nj:jump PC\nb:Break point setting\ng:program excute\n"
			"m:view memory\nr:view register\nsm:set memory\nsr:set register/init register\nc:clear ui\nx:quit program" << endl;
		cout << "Select Instruction(l,j,b,g,s,m,r,sm,sr,x)" << endl;
		fflush(stdout);
		cin >> command;
		if (command == "l") {
			InitMEM(InsNum, DataNum);
			InitREG();
			InitBreakPoint();
			/*초기화 해야될것: 메모리,레지스터,브레이크포인트,각종변수등등*/
			Osize = 0;
			Dsize = 0;
			InsNum = 0;
			DataNum = 0;
			int Inspow = 6, Datapow = 6;
			cout << "open할 파일 명:";
			cin >> fileName;
			FILE *in;
			if ((in = fopen(fileName, "rb")) == NULL) {
				fputs("존재 하지 않는 파일입니다!\n", stderr);
				fflush(stderr);
			}
			//불러온 바이너리 파일 데이터와 명령어에 따라 적재
			while ((ch = fgetc(in)) != EOF) {
				//명령어의 갯수를 샌다.
				if (Osize >= 0 && Osize <= 3) {
					InsNum += ch * pow(16, Inspow);
					Inspow -= 2;
				}
				//데이터의 갯수를 샌다.
				else if (Osize >= 4 && Osize <= 7) {
					DataNum += ch * pow(16, Datapow);
					Datapow -= 2;
				}
				//명령어의 갯수만큼 progMEM에 저장
				else if (Osize >= 8 && Osize <= InsNum * 4 + 7) {
					MEM(progMEMaddr + Osize - 8, ch, MEMWRITE, WORD);
				}
				//데이터의 갯수만큼 dataMEM에 저장
				else {
					MEM(dataMEMaddr + Dsize, ch, MEMWRITE, WORD);
					Dsize++;
				}
				Osize++;
			}
			fclose(in);
			cout << "PC       Instruction" << endl;
			for (int i = 0; i < InsNum; i++) {
				MEM(PC, 0, MEMREAD, WORD);
				InsFetch(Cbin1, Cbin2, Cbin3, Cbin4);
				cout << hex << "0x" << PC << dec << " ";
				if ((n = InsDecode()) < 0)
					pErrorMessage(n);
				PC += 4;
			}
		}
		else if (command == "g") {
			basicOperation(InsNum, singleflag);
		}
		else if (command == "s") {
			singleflag = 1;
			basicOperation(InsNum, singleflag);
		}
		else if (command == "j") {
			string jPC;
			string com;
			cout << hex << "현재 PC값" << PC << endl;
			cout << "점프할 PC값을 입력하시오: 0x";
			cin >> jPC;
			if (dTOh(jPC) < 0x400000 || dTOh(jPC) > 0x400000 + InsNum * 4 - 4) {
				pErrorMessage(J_INS_ERROR_OUT_OF_BOUND);
				continue;
			}
			if (dTOh(jPC) % 4 != 0) {
				pErrorMessage(J_INS_ERROR_WRONG_PC);
				continue;
			}
			PC = dTOh(jPC);
			cout << "변경된 PC값" << hex << PC << endl;
			singleflag = 1;
			basicOperation(InsNum, singleflag);
		}
		else if (command == "b") {//breakPoint 지정 또는 해제
			string bp, com;
			cout << "s:Break Point 주소 지정\nr:Break Point 해제 \nSelect Instruction(s,r)";
			cin >> com;
			if (com == "s") {
				cout << "Break Point 주소:0x";
				cin >> bp;
				if (dTOh(bp) < 0x400000 || dTOh(bp) > 0x400000 + InsNum * 4 - 4) {
					pErrorMessage(B_INS_ERROR_OUT_OF_BOUND);
					continue;
				}
				else if (dTOh(bp) % 4 != 0) {
					pErrorMessage(B_INS_ERROR_WRONG_ADDRESS);
					continue;
				}
				setBreakPoint(dTOh(bp));
			}
			else if (com == "r") {
				cout << "Break Point 주소:0x";
				cin >> bp;
				if (dTOh(bp) < 0x400000 || dTOh(bp) > 0x400000 + InsNum * 4 - 4) {
					pErrorMessage(B_INS_ERROR_OUT_OF_BOUND);
				}
				else if (dTOh(bp) % 4 != 0) {
					pErrorMessage(B_INS_ERROR_WRONG_ADDRESS);
				}
				if (releaseBP(dTOh(bp)) < 0) pErrorMessage(B_INS_ERROR_NOT_EXIST);
			}
		}
		else if (command == "r") {
			viewReg();
		}
		else if (command == "m") {
			string smPCstart, smPCend;
			int imPCstart, imPCend;
			cout << "보고 싶은 메모리의 PC값의 시작점을 입력하시오: 0x";
			cin >> smPCstart;
			imPCstart = dTOh(smPCstart);
			if (dTOh(smPCstart) % 4 != 0) {
				pErrorMessage(M_INS_ERROR_WRONG_ADDRESS);
				continue;
			}
			cout << "보고 싶은 메모리의 PC값의 끝점을 입력하시오  : 0x";
			cin >> smPCend;
			imPCend = dTOh(smPCend);
			if (dTOh(smPCend) % 4 != 0) {
				pErrorMessage(M_INS_ERROR_WRONG_ADDRESS);
				continue;
			}
			if (imPCend < imPCstart) {
				pErrorMessage(MEM_NOMEM_ERROR);
				continue;
			}

			for (int i = imPCstart; i <= imPCend; i += 4) {
				MEM(i, 0, MEMREAD, WORD);
				cout << hex << "0x" << i << " : ";
				for (int i = 0; i < 8; i++)
					cout << Cbin1[i];
				for (int i = 0; i < 8; i++)
					cout << Cbin2[i];
				for (int i = 0; i < 8; i++)
					cout << Cbin3[i];
				for (int i = 0; i < 8; i++)
					cout << Cbin4[i];
				cout << endl;
			}
		}
		else if (command == "sr") {
			string s, com;
			int val, i = 0;
			cout << "s: set register i:init register\nSelect Instruction(s,i)";
			cin >> com;
			if (com == "s") {
				cout << "변경할 레지스터 입력 :$";
				cin >> s;//a1,10
				cout << "값:";
				cin >> val;
				for (i = 0; i < 32; i++) {
					if ("$" + s == regName[i]) {
						reg[i] = val;
						break;
					}
				}
				if (i == 32) pErrorMessage(SR_INS_ERROR);
				cout << "$" + s << "값 변경 성공!" << endl;
			}
			else if (com == "i") {
				cout << "레지스터가 초기화 되었습니다." << endl;
				InitREG();
			}
		}
		else if (command == "sm") {
			string smPC;
			int iPC, setV;
			cout << "값을 바꿀 PC값을 입력하시오: 0x";
			cin >> smPC;
			iPC = dTOh(smPC);
			cout << "값을 입력하시오: ";
			cin >> setV;
			MEM(iPC, setV, MEMWRITE, WORD);
			cout << "0x" << smPC << "에 " << setV << "가 저장되었습니다." << endl;
		}
		else if (command == "c") {
			system("cls");
		}
		else if (command == "x") {
			cout << "프로그램을 종료합니다..." << endl;
			quit = true;
		}
		else {
			cout << "잘못된 명령어 입니다.." << endl;
		}
	}//end while(1)
	return 0;
}


void basicOperation(int insNum, int singleflag) {
	string com;
	int stopflag = 0;
	int n;
	while (!SYSCALLflag && PC < 0x400000 + 4 * insNum && PC >= 0x400000) {
		while (singleflag == 1) {
			cout << "\nf:stop c:continue s:single step r:view register\nSelect Instruction(f,c,s,r) ";
			cin >> com;
			cout << endl;
			if (com == "f") {
				stopflag = 1;
				break;
			}
			else if (com == "c") {
				singleflag = 0;
				break;
			}
			else if (com == "s") {
				singleflag = 1;
				break;
			}
			else if (com == "r") {
				viewReg();
			}
			else {
				cout << "잘못된 명령어 입니다!" << endl;
			}
		}
		while (isBreakPoint(PC)) {
			cout << "Execution stopped at breakPoint " << hex << PC << endl;
			cout << "f:stop c:continue s:single step r:view register\nSelect Instruction(f,c,s,r) ";
			cin >> com;
			cout << endl;
			if (com == "f") {
				stopflag = 1;
				break;
			}
			else if (com == "c") {
				break;
			}
			else if (com == "s") {
				singleflag = 1;
				break;
			}
			else if (com == "r") {
				viewReg();
			}
			else {
				cout << "잘못된 명령어 입니다!" << endl;
			}
		}
		if (stopflag == 1) {
			break;
		}
		MEM(PC, 0, MEMREAD, WORD);
		InsFetch(Cbin1, Cbin2, Cbin3, Cbin4);
		cout << hex << "0x" << PC << dec << " ";
		if ((n = InsDecode()) < 0)
			pErrorMessage(n);
		if ((n = ALUOperation()) < 0)
			pErrorMessage(n);
		PC += 4;
	}
}
