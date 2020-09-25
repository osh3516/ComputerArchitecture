#ifndef ERROR_H_
#define ERROR_H_

#include <iostream>


using namespace std;


/*********ALU ERROR CODE*********/
#define ALU_LOGIC_ERROR -1
#define ALU_ADDSUB_ERROR -2
#define ALU_SHIFTOP_ERROR -3
#define ALU_OPERATE_ERROR -4
/*********Instruction Decode ERROR CODE***********/
#define WRONG_INSTRUCTION -11
/*********Memory ERROR CODE**********/
#define MEM_NOMEM_ERROR -21
#define MEM_ISNOTHW_ERROR -22
#define MEM_ISNOTW_ERROR -23
/*********Main Instruction ERROR CODE***********/
#define J_INS_ERROR_OUT_OF_BOUND -31
#define J_INS_ERROR_WRONG_PC -32
#define SR_INS_ERROR -33
#define B_INS_ERROR_OUT_OF_BOUND -34
#define B_INS_ERROR_WRONG_ADDRESS -35
#define B_INS_ERROR_NOT_EXIST -36
#define M_INS_ERROR_WRONG_ADDRESS -37

void pErrorMessage(int eCode) {
	switch (eCode) {
	case ALU_LOGIC_ERROR:
		cout << "error in logic operation\n" << endl;
		break;
	case ALU_ADDSUB_ERROR:
		cout << "error in add/subtract operation\n" << endl;
		break;
	case ALU_SHIFTOP_ERROR:
		cout << "error in shift operation\n" << endl;
		break;
	case ALU_OPERATE_ERROR:
		cout << " ALU_OPERATE_ERROR" << endl;
		break;
	case WRONG_INSTRUCTION:
		cout << "�߸��� ��ɾ��Դϴ�." << endl;
		break;
	case MEM_NOMEM_ERROR:
		cout << "�߸��� �޸� �����Դϴ�." << endl;
		break;
	case MEM_ISNOTHW_ERROR:
		cout << "is not half word" << endl;
		break;
	case MEM_ISNOTW_ERROR:
		cout << "is not word" << endl;
		break;
	case J_INS_ERROR_OUT_OF_BOUND:
		cout << "�߸��� �Է��Դϴ�.\n�Է��� 16�����Դϴ�. " << endl;
		break;
	case J_INS_ERROR_WRONG_PC:
		cout << "PC���� 4�� ����� �Է��ϼ���." << endl;
		break;
	case SR_INS_ERROR:
		cout << "���� �������� ���߽��ϴ�.\n �Է� ���� ��:s1 10 ==> $s1���� 10���� ����" << endl;
		break;
	case B_INS_ERROR_OUT_OF_BOUND:
		cout << "�߸��� �Է��Դϴ�.\n�Է��� 16�����Դϴ�." << endl;
		break;
	case B_INS_ERROR_WRONG_ADDRESS:
		cout << "�ּҸ� 4�� ����� �Է��ϼ���." << endl;
		break;
	case B_INS_ERROR_NOT_EXIST:
		cout << "�������� �ʴ� Break point �Դϴ�." << endl;
		break;
	case M_INS_ERROR_WRONG_ADDRESS:
		cout << "�޸� �ּҸ� 4�� ����� �Է��ϼ���" << endl;
		break;
	}
}
#endif /* ASD_H_ */
