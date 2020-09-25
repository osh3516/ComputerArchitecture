#ifndef UTILS_H_
#define UTILS_H_

#include <String>
#include <math.h>
#include <map>

using namespace std;

void viewReg();//��� �������Ͱ��� ����Ѵ�.

void setBreakPoint(int BP);//Break Point����
int releaseBP(int address);//Break Point����
bool isBreakPoint(int address);//Break Point���� �Ǵ�.

int dTOh(string dec);//10����->16����(10������ string���� �Է�)
int bTOd(string s, int bitsize);//2����->10����
int sbTOd(string s, int bitsize);//��ȣ�ִ� 2����->10����
string make2bosoo(string bits, int bitsize);//bits�� 2�� ���� ���Ѵ�. bits��ũ��� bitsize�̴�.
void dTOb(int ch, char bits[], int bitsize);//10���� ->2����
void fusion(char bits[], char cbits1[], char cbits2[], char cbits3[], char cbits4[], int bitsize);//4���� char�迭�� 1���� ��ģ��. (bitszie�� 4���� char�迭 ũ���� ��
void cutbit(char bits[], int bitSize, char cbits1[], char cbits2[], char cbits3[], char cbits4[]);//1���� char�迭�� 8bits������ �ڸ���. (bitsize�� ��ü �迭�� ũ��)


#define INT_MAX 2147483647
#define M_INT_MAX -2147483648

struct Rtype {
	int op;
	string rs;
	int Drs;
	string rt;
	int Drt;
	string rd;
	int Drd;
	string sh;
	int Dsh;
	string fcnt;
	int Dfcnt;
};
struct Itype {
	int op;
	string rs;
	int Drs;
	string rt;
	int Drt;
	string operand;
	int Doperand;
};
struct Jtype {
	int op;
	string address;
	int DAddress;
};



string regName[] = { "$r0","$at","$v0","$v1","$a0","$a1","$a2",
		"$a3","$t0","$t1","$t2","$t3","$t4","$t5","$t6","$t7","$s0","$s1",
		"$s2","$s3","$s4","$s5","$s6","$s7","$t8","$t9","$k0","$k1","$gp","$sp","$fp","$ra" };

int reg[] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0x7fffffff,0,0 };
int regHi = 0, regLo = 0;

Rtype rIns;
Jtype jIns;
Itype iIns;
int insType;//0 is R 1 is i 2 is j

int PC = 0x400000;
int ALUControl;
bool SYSCALLflag = false;

map<int, bool> breakPoint;

void viewReg() {
	for (int i = 0; i < 32; i++) {
		cout << regName[i] << ":" << dec << reg[i] << " ";
		if (i % 4 == 3) cout << endl;
	}
	cout << "HI:" << regHi << " LO:" << regLo << " PC:" << hex << PC << endl;
}

void setBreakPoint(int BP) {
	if (breakPoint.find(BP) == breakPoint.end()) {
		breakPoint.insert(pair<int, bool>(BP, true));
	}
	else breakPoint[BP] = true;
	cout << "Break Point��" << hex << BP << "�� ���� ����ϴ�. " << endl;
}
int releaseBP(int address) {
	if (breakPoint.find(address) == breakPoint.end()) {
		return -1;
	}
	else {
		breakPoint[address] = false;
	}
	return 0;
}
bool isBreakPoint(int address) {
	if (breakPoint.find(address) == breakPoint.end()) {
		return false;//address�� break point�� �ƴ�
	}
	else {
		return breakPoint[address];
	}
}

int dTOh(string dec) {
	int res = 0, hex = 0, val;
	for (int i = dec.length() - 1; i >= 0; i--) {
		if (dec[i] == 'a' || dec[i] == 'A') val = 10;
		else if (dec[i] == 'b' || dec[i] == 'B') val = 11;
		else if (dec[i] == 'c' || dec[i] == 'C') val = 12;
		else if (dec[i] == 'd' || dec[i] == 'D') val = 13;
		else if (dec[i] == 'e' || dec[i] == 'E') val = 14;
		else if (dec[i] == 'f' || dec[i] == 'F') val = 15;
		else val = dec[i] - 48;
		res += val * pow(16, hex);
		hex++;
		//cout<<"dec ["<<i<<"]:"<<dec[i]<<" res:"<<res<<" val :"<<val<<endl;
	}
	return res;
}


/******������ -> ������ ��ȯ******/
/**bTOd(������,��Ʈ��)**/
int bTOd(string s, int bitsize) {
	int ret = 0;
	int t = 1;
	for (int i = bitsize - 1; i >= 0; i--) {
		if (s[i] == '1') {
			ret += t;
		}
		t = t * 2;
	}
	return ret;
}

int sbTOd(string s, int bitsize) {
	int ret = 0, mflag = 1;
	int t = 1;
	if (s[0] == '1') {
		s = make2bosoo(s, bitsize);
		mflag = -1;
	}
	for (int i = bitsize - 1; i >= 0; i--) {
		if (s[i] == '1') {
			ret += t;
		}
		t = t * 2;
	}
	return ret * mflag;
}
/*bits�� 2�� ���� ���Ѵ�. bits��ũ��� bitsize�̴�.*/
string make2bosoo(string bits, int bitsize) {
	int i, flag = 0;
	for (i = bitsize - 1; i >= 0; i--) {
		if (flag == 0) {
			if (bits[i] == '0') {
				bits[i] = '0';
			}
			else if (bits[i] == '1') {
				bits[i] = '1';
				flag = 1;
				continue;
			}
		}
		else if (flag == 1) {
			if (bits[i] == '0') bits[i] = '1';
			else bits[i] = '0';
		}
	}
	return bits;
}
void dTOb(int ch, char bits[], int bitsize) {
	int i = 0, flag = 0;
	if (ch < 0) {
		ch = ch * (-1);
		flag = 1;
	}
	for (i = 0; i < bitsize; i++) {
		if (ch % 2 == 0) {
			bits[bitsize - 1 - i] = '0';
		}
		else if (ch % 2 == 1) {
			bits[bitsize - 1 - i] = '1';
		}
		ch = ch / 2;
	}
	if (flag == 1) make2bosoo(bits, bitsize);
}

void fusion(char bits[], char cbits1[], char cbits2[], char cbits3[], char cbits4[], int bitsize) {
	int i;
	for (i = 0; i < bitsize; i++) {
		if (i < 8) bits[i] = cbits1[i];
		else if (i < 16) bits[i] = cbits2[i - 8];
		else if (i < 24) bits[i] = cbits3[i - 16];
		else if (i < 32) bits[i] = cbits4[i - 24];
	}
}
void cutbit(char bits[], int bitSize, char cbits1[], char cbits2[], char cbits3[], char cbits4[]) {
	int i = 0;
	for (i = 0; i < bitSize; i++) {
		if (i / 8 == 3) cbits4[i - 24] = bits[i];
		else if (i / 8 == 2) cbits3[i - 16] = bits[i];
		else if (i / 8 == 1) cbits2[i - 8] = bits[i];
		else cbits1[i] = bits[i];
	}
	cbits1[8] = '\0';
	cbits2[8] = '\0';
	cbits3[8] = '\0';
	cbits4[8] = '\0';
}

#endif /* UTILS_H_ */
