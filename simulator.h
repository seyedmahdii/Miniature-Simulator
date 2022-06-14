#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

struct instructionMemory{
	int readAddress;
	int instruction;
};

struct controlUnit{
	int RegDst;	// 1 for rd and 0 for rt
	int Jump;
	int Branch;
	int MemRead;
	int MemtoReg;
	int ALUOp;
	int MemWrite;
	int ALUSrc;	// 0 for rt and 1 for imm
	int RegWrite;
	int ExOp;	// 0 for ZE and 1 for SE
	int JalrCtr;
	int LUICtr;
};

struct mux{
	int input1;
	int input2;
	int signal;
	int output;

	// int decideOutput(){
	// 	if(signal == 0){
	// 		output = input1;
	// 		return 1;
	// 	}
	// 	else{
	// 		output = input2;
	// 		return 2;
	// 	}
	// }
};

struct ALU{
	int input1;
	int input2;
	int output;
	int signal;
	int zero;
};

struct registerFile{
	int input1;
	int input2;
	int output1;
	int output2;
	int writeRegister;
	int writeData;
};

char *getNthLine(FILE *, int);
long long int2Binary(int dec);	// Converts decimal to binary
char *binaryExtend(long long bin, int len, char sign);	// Etxends binary
long long bin2Dec(char *, int);
long long complement2s(long long bin);