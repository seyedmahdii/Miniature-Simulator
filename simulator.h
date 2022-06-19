#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

// For sleep()
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

// MUX Signals
#define ZERO 0
#define ONE 1
#define X 2

// ALU Signals
#define ADD 0
#define SUB 1
#define MUL 2
#define DIV 3
#define OR  4
#define AND 5
#define NAND 6

struct instructionMemory{
	int readAddress;
	char instruction[33];
	char **instructions;
};

struct registerFile{
	int readRegister1;
	int readRegister2;
	int readData1;
	int readData2;
	int writeRegister;
	int writeData;
	int registers[16]; // It holds register values in decimal
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

struct Mux{
	int input1;
	int input2;
	int signal;
	int output;
};

struct ALU{
	int input1;
	int input2;
	int output;
	int signal;
	int zero;
};

struct DataMemory{
	int address;
	int writeData;
	int readData;
	int data[1 << 14];
};

long long int2Binary(long long dec);	// Converts decimal to binary
void int2CharBinary(long long dec, char* binary, int len);	// Converts decimal to char* binary
char *binaryExtend(long long bin, int len, char sign);	// Etxends binary
long long bin2Dec(char *, int, int sign);

int Mux_getOutput(struct Mux* mux);
int ALU_getoutput(struct ALU* alu);
void displayRegsiters(struct registerFile *);
void fillInstructionAndDataMemory(struct instructionMemory *, struct DataMemory *, int *memory_used, FILE *);
int findInstructionsCount(FILE *);
void setControls(struct controlUnit *, char *opCode);
void displayResults(struct registerFile *, int IC, int used_memory, bool registers_flag[16]);
char* complement2s(char *ones, int len);