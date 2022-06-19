#include "simulator.h"

void main(int argc,char **argv){
	FILE *machp, *fopen();
	int instCount;
	int PC = 0;
	int used_memory = 0;
	bool registers_flag[16] = { false };	// True if the register is used. otherwise False
	struct instructionMemory *IM;
	struct ALU *alu;
	struct Mux *jmpAdd_mux_1, *branch_mux_2, *jalrPC_mux_3, 
		*regDst_mux_4, *ALUSrc_mux_5, *memtoReg_mux_6,
		*jalrMem_mux_7, *writeData_mux_8;
	struct registerFile *RF;
	struct DataMemory *memory;
	struct controlUnit *ctrUnit;
	
	if(argc < 2){
		printf("***** Please run this program as follows:\n");
		printf("***** %s ./output.exe machprog.mc\n",argv[0]);
		printf("***** where machprog.mc will be your machine code.\n");
		exit(1);
	}
	if((machp=fopen(argv[1],"r")) == NULL){
		printf("%s cannot be openned\n",argv[1]);
		exit(1);
	}

	IM = (struct instructionMemory *)malloc(sizeof(struct instructionMemory));
	jmpAdd_mux_1 = (struct Mux *)malloc(sizeof(struct Mux));
	branch_mux_2 = (struct Mux *)malloc(sizeof(struct Mux));
	jalrPC_mux_3 = (struct Mux *)malloc(sizeof(struct Mux));
	regDst_mux_4 = (struct Mux *)malloc(sizeof(struct Mux));
	ALUSrc_mux_5 = (struct Mux *)malloc(sizeof(struct Mux));
	memtoReg_mux_6 = (struct Mux *)malloc(sizeof(struct Mux));
	jalrMem_mux_7 = (struct Mux *)malloc(sizeof(struct Mux));
	writeData_mux_8 = (struct Mux *)malloc(sizeof(struct Mux));
	RF = (struct registerFile *)malloc(sizeof(struct registerFile));
	alu = (struct ALU *)malloc(sizeof(struct ALU));
	RF->registers[0] = 0;
	memory = (struct DataMemory *)malloc(sizeof(struct DataMemory));
	ctrUnit = (struct controlUnit *)malloc(sizeof(struct controlUnit));

	// Allocating memory to instructions array
	instCount = findInstructionsCount(machp);
	IM->instructions = malloc(instCount * sizeof(char *));
	for(int i=0; i<instCount; i++){
		IM->instructions[i] = malloc(33 * sizeof(char));
	}

	// Filling Instruction memory & Data memory
	fillInstructionAndDataMemory(IM, memory, &used_memory, machp);
	// char x[17];
	// strcpy(x, "1111111111111101");
	// printf("_____Test: %d __________________\n\n\n", bin2Dec(x, 16, 0));
										  
	while(PC < instCount){
		char opCode[5], rs[5], rt[5], rd[5], offset[17];

		// Convert instruction to binary
		int2CharBinary(atoi(IM->instructions[PC]), IM->instruction, 32);
		strncpy(opCode, &IM->instruction[4], 4);			 // 27 - 24 || Opcode
		opCode[4] = '\0';

		strncpy(rs, &IM->instruction[8], 4);   // 23 - 20 || Rs
		rs[4] = '\0';
		strncpy(rt, &IM->instruction[12], 4);  // 19 - 16 || Rt
		rt[4] = '\0';		
		strncpy(rd, &IM->instruction[16], 4);  // 15 - 12 || Rd
		rd[4] = '\0';
		strncpy(offset, &IM->instruction[16], 16);// 15 - 0 || Imm
		offset[16] = '\0';
		
		int rsDec = bin2Dec(rs, 4, 0);
		int rtDec = bin2Dec(rt, 4, 0);
		int rdDec = bin2Dec(rd, 4, 0);
		int offsetDec = bin2Dec(offset, 16, 1);

		// Register File
		RF->readRegister1 = rsDec;
		RF->readRegister2 = rtDec;

		// Codes in common between instructions ...
		setControls(ctrUnit, opCode);

		// Add
		if(strcmp(opCode, "0000") == 0){
			// // RegDst MUX
			// regDst_mux_4->signal = ctrUnit->RegDst;
			// regDst_mux_4->input1 = RF->readRegister2;
			// regDst_mux_4->input2 = bin2Dec(rd, 4);


			// RF->writeRegister = Mux_getOutput(regDst_mux_4);

			// // R[rs] & R[rt]
			// RF->readData1 = RF->registers[RF->readRegister1];
			// RF->readData2 = RF->registers[RF->readRegister2];
			
			// ALUSrc_mux_5->input1 = RF->readData2;
			// ALUSrc_mux_5->input2 = bin2Dec(offset, 16); 	// ************** THIS NEED TO BE CORRECTED
			// ALUSrc_mux_5->signal = ctrUnit->ALUSrc;

			// // ALU
			// alu->input1 = RF->readData1;
			// alu->input2 = Mux_getOutput(ALUSrc_mux_5);
			// alu->signal = ADD;


			// memtoReg_mux_6->input1 = ALU_getoutput(alu);
			// memtoReg_mux_6->signal = ctrUnit->MemtoReg;

			// jalrMem_mux_7->input1 = Mux_getOutput(memtoReg_mux_6);
			// jalrMem_mux_7->input2 = PC + 1;
			// jalrMem_mux_7->signal = ctrUnit->JalrCtr;

			// writeData_mux_8->input1 = Mux_getOutput(jalrMem_mux_7);
			// writeData_mux_8->input2 = bin2Dec(offset, 16) << 16; // ************** THIS NEED TO BE CORRECTED
			// writeData_mux_8->signal = ctrUnit->LUICtr;

			// RF->writeData = Mux_getOutput(writeData_mux_8);

			// // ********* HERE ********
			// RF->registers[RF->writeRegister] = alu->output;
			// registers_flag[rdDec] = true;

			// // ********* PC *********
			// PC = PC + 1;
			// char charPC[33], PC16UpBits[17], jumpAddress[33];
			// int2CharBinary(PC, charPC, 32);

			// strncpy(PC16UpBits, &charPC[0], 16); // 31 - 16
			// PC16UpBits[16] = '\0';
			// strcat(jumpAddress, PC16UpBits);
			// strcat(jumpAddress, offset);



			// jmpAdd_mux_1->input1 = PC;
			// // jmpAdd_mux_1->input2 = ALU_getoutput(alu);
			// jmpAdd_mux_1->signal = ctrUnit->Branch && alu->zero;


			// branch_mux_2->input1 = Mux_getOutput(jmpAdd_mux_1);
			// branch_mux_2->input2 = bin2Dec(jumpAddress, 32);
			// branch_mux_2->signal = ctrUnit->Jump;

			// jalrPC_mux_3->input1 = Mux_getOutput(branch_mux_2);
			// jalrPC_mux_3->input2 = RF->readData1;
			// jalrPC_mux_3->signal = ctrUnit->JalrCtr;

			// PC = Mux_getOutput(jalrPC_mux_3);


			RF->registers[rdDec] = RF->registers[rsDec] + RF->registers[rtDec];
			registers_flag[rsDec] = registers_flag[rtDec] = registers_flag[rdDec] = true;
			PC = PC + 1;
		}

		// Sub
		else if(strcmp(opCode, "0001") == 0){
			RF->registers[rdDec] = RF->registers[rsDec] - RF->registers[rtDec];
			registers_flag[rsDec] = registers_flag[rtDec] = registers_flag[rdDec] = true;
			PC = PC + 1;
		}

		// Slt
		else if(strcmp(opCode, "0010") == 0){
			if(RF->registers[rsDec] < RF->registers[rtDec]){
				RF->registers[rdDec] = 1;
			}
			else{
				RF->registers[rdDec] = 0;
			}
			registers_flag[rsDec] = registers_flag[rtDec] = registers_flag[rdDec] = true;
			PC = PC + 1;
		}

		// Or
		else if(strcmp(opCode, "0011") == 0){
			char or1[33], or2[33], res[33];
			long long bin = int2Binary(RF->registers[rsDec]);
			strcpy(or1, binaryExtend(bin, 32, '0'));
			bin = int2Binary(RF->registers[rtDec]);
			strcpy(or2, binaryExtend(bin, 32, '0'));
			for(int i=0; i<32; i++){
				if(or1[i] == '1' || or2[i] == '1'){
					res[i] = '1';
				}
				else{
					res[i] = '0';  
				}
			}
			RF->registers[rdDec] = bin2Dec(res, 32, 0);
			registers_flag[rsDec] = registers_flag[rtDec] = registers_flag[rdDec] = true;
			PC = PC + 1;
		}

		// And
		else if(strcmp(opCode, "0100") == 0){
			char and1[33], and2[33], res[33];
			long long bin = int2Binary(RF->registers[rsDec]);
			strcpy(and1, binaryExtend(bin, 32, '0'));
			bin = int2Binary(RF->registers[rtDec]);
			strcpy(and2, binaryExtend(bin, 32, '0'));
			for(int i=0; i<32; i++){
				if(and1[i] == '1' && and2[i] == '1'){
					res[i] = '1';
				}
				else{
					res[i] = '0';  
				}
			}
			RF->registers[rdDec] = bin2Dec(res, 32, 0);
			registers_flag[rsDec] = registers_flag[rtDec] = registers_flag[rdDec] = true;
			PC = PC + 1;
		}

		// Addi
		else if(strcmp(opCode, "0101") == 0){
			RF->registers[rtDec] = RF->registers[rsDec] + offsetDec;
			registers_flag[rtDec] = true;
			registers_flag[rsDec] = registers_flag[rtDec] = true;
			PC = PC + 1;
		}

		// Slti
		else if(strcmp(opCode, "0110") == 0){
			if(RF->registers[rsDec] < offsetDec){
				RF->registers[rtDec] = 1;
			}
			else{
				RF->registers[rtDec] = 0;
			}
			registers_flag[rsDec] = registers_flag[rtDec] = true;
			PC = PC + 1;
		}

		// Ori
		else if(strcmp(opCode, "0111") == 0){
			char or1[33], or2[33], res[33];
			long long bin = int2Binary(RF->registers[rsDec]);
			strcpy(or1, binaryExtend(bin, 32, '0'));
			offsetDec = bin2Dec(offset, 16, 0);
			bin = int2Binary(offsetDec);
			strcpy(or2, binaryExtend(bin, 32, '0'));
			for(int i=0; i<32; i++){
				if(or1[i] == '1' || or2[i] == '1'){
					res[i] = '1';
				}
				else{
					res[i] = '0';  
				}
			}
			RF->registers[rtDec] = bin2Dec(res, 32, 0);
			registers_flag[rsDec] = registers_flag[rtDec] = true;
			PC = PC + 1;
		}

		// Lui
		else if(strcmp(opCode, "1000") == 0){
			RF->registers[rtDec] = offsetDec << 16;
			registers_flag[rtDec] = true;
			PC = PC + 1;
		}

		// LW
		else if(strcmp(opCode, "1001") == 0){
			int address = offsetDec + RF->registers[rsDec];
			RF->registers[rtDec] = memory->data[address];
			registers_flag[rsDec] = registers_flag[rtDec] = true;
			PC = PC + 1;
		}

		// SW
		else if(strcmp(opCode, "1010") == 0){
			int address = offsetDec + RF->registers[rsDec];
			memory->data[address] = RF->registers[rtDec];
			registers_flag[rsDec] = registers_flag[rtDec] = true;
			PC = PC + 1;
		}

		// Beq
		else if(strcmp(opCode, "1011") == 0){
			if(RF->registers[rsDec] == RF->registers[rtDec]){
				PC = PC + 1 + offsetDec;
			}
			else{
				PC = PC + 1;
			}
			registers_flag[rsDec] = registers_flag[rtDec] = true;
		}

		// Jalr
		else if(strcmp(opCode, "1100") == 0){
			RF->registers[rtDec] = PC + 1;
			PC = RF->registers[rsDec];
			registers_flag[rsDec] = registers_flag[rtDec] = true;
		}

		// J
		else if(strcmp(opCode, "1101") == 0){
			offsetDec = bin2Dec(offset, 16, 0);
			PC = offsetDec;
		}

		// Halt
		else if(strcmp(opCode, "1110") == 0){
			displayResults(RF, instCount, used_memory, registers_flag);
			PC = PC + 1;
			break;
		}

		// Display registers for all instructions except halt
		if(strcmp(opCode, "1110") != 0){
			printf("\n>> Registers: \n");
			displayRegsiters(RF); 
		}

		// sleep(3);
	}

	fclose(machp);
	exit(0);
}

long long int2Binary(long long num){
	long long bin = 0;
	int rem, i = 1;

	while (num != 0){
		rem = num % 2;
		num /= 2;
		bin += rem * i;
		i *= 10;
	}
	return bin;
}

char *binaryExtend(long long bin, int len, char sign){
	char cBin[33], *final;
	final = (char *)malloc(33);
	sprintf(cBin, "%d", bin);

	int diff = len - strlen(cBin);
	for(int i=0; i<diff; i++){
		final[i] = sign;
	}
	final[diff] = '\0';  // End of character array
	strcat(final, cBin);
	return (char *)final;
}

long long bin2Dec(char *binary, int len, int sign){
	char  bin[len+1];
	strcpy(bin, binary);
	bool negative = false;

	// For negative binaries(sign bit = 1)
	if(sign == 1 && binary[0] == '1'){
		negative = true;
		strcpy(bin, complement2s(binary, len));
	}

	long long decimal = 0;
	int position = 0;
	int i = len - 1;

	// Skip the 0s before the first 1 (000101 => 101)
	int k = 0;
	while(bin[k] == '0'){
		k++;
	}

	while(i - k >= 0){
		decimal = decimal + (bin[i] - 48) * pow(2, position);
		i--;
		position++;
	}

	if(negative){
		return -1 * decimal;
	}
	else{
		return decimal;
	}
}

void int2CharBinary(long long num, char* binary, int len){
	int binaryNum[32];
	strcpy(binary, "00000000000000000000000000000000");
  
	// Converting to binary
    int i = 0;	
    while (num > 0) {
        binaryNum[i] = num % 2;
        num = num / 2;
        i++;
    }
  
	// Storing int binary int char* binary 
	for(int k=0; k<i; k++){
		binary[len - k - 1] = binaryNum[k] == 1 ? '1' : '0';
	}

	binary[len+1] = '\0';
}

void fillInstructionAndDataMemory(struct instructionMemory *IM, struct DataMemory *memory, int *memory_used, FILE *inputFile){
	int lineNo = 0;
	size_t lineSize;
	char *line;
	char *token;
	line = (char *)malloc(72);

	while(getline(&line, &lineSize, inputFile) != -1){
		token = strtok(line, "\n");
		strcpy(IM->instructions[lineNo], token);
		lineNo++;

		// 234881024 is halt instruction
		if(strcmp(token, "234881024") == 0){
			break;
		}
	}

	while(getline(&line, &lineSize, inputFile) != -1){
		token = strtok(line, "\n");
		memory->data[lineNo] = atoi(token);
		(*memory_used)++;
		lineNo++;
	}
	
	rewind(inputFile);
	free(line);
}

int findInstructionsCount(FILE *inputFile){
   	int count = 0;
	size_t lineSize;
	char *line;
	line = (char *)malloc(72);
	while(getline(&line, &lineSize, inputFile) != -1){
		if(line[0] == '\0');
		else{
			count++;
		}
	}
	rewind(inputFile);
	free(line);
	return count;
}

void displayRegsiters(struct registerFile *RF){
	system("clear"); // system("cls") for windows

	for(int i=0; i<16; i++){
		printf("R[%d] = %d \t", i, RF->registers[i]);
		if(i %2 == 1){
			printf("\n");
		}
	}

	printf("\n\n");
}

int Mux_getOutput(struct Mux* mux){
	if(mux->signal == 0){
		mux->output = mux->input1;
		return mux->input1;
	}
	else{
		mux->output = mux->input2;
		return mux->input2;
	}
}

int ALU_getoutput(struct ALU* alu){
	if(alu->signal == ADD){
		alu->output = alu->input1 + alu->input2;
	}
	else if(alu->signal == SUB){
		alu->output = alu->input1 - alu->input2;
		if(alu->output == 0){
			alu->zero = 1;
		}
		else{
			alu->zero = 0;
		}
	}
	else if(alu->signal == MUL){
		alu->output = alu->input1 * alu->input2;
	}
	else if(alu->signal == DIV){
		alu->output = alu->input1 / alu->input2;
	}
	else if(alu->signal == OR){
		
	}
	else if(alu->signal == AND){
		
	}
	else if(alu->signal == NAND){
		
	}
}

void setControls(struct controlUnit *ctrUnit, char *opCode){
	// Add
	if(strcmp(opCode, "0000") == 0){
		ctrUnit->RegDst = ONE;
		ctrUnit->ALUSrc = ZERO;
		ctrUnit->MemtoReg = ZERO;
		ctrUnit->RegWrite = ONE;
		ctrUnit->MemRead = ZERO;
		ctrUnit->MemWrite = ZERO;
		ctrUnit->Branch = ZERO;
		ctrUnit->ALUOp = ADD;
		ctrUnit->LUICtr = ZERO;
		ctrUnit->JalrCtr = ZERO;
		ctrUnit->Jump = ZERO;
		ctrUnit->ExOp = X;
	}
	// Sub
	else if(strcmp(opCode, "0001") == 0){
		ctrUnit->RegDst = ONE;
		ctrUnit->ALUSrc = ZERO;
		ctrUnit->MemtoReg = ZERO;
		ctrUnit->RegWrite = ONE;
		ctrUnit->MemRead = ZERO;
		ctrUnit->MemWrite = ZERO;
		ctrUnit->Branch = ZERO;
		ctrUnit->ALUOp = SUB;
		ctrUnit->LUICtr = ZERO;
		ctrUnit->JalrCtr = ZERO;
		ctrUnit->Jump = ZERO;
		ctrUnit->ExOp = X;
	}
	// Slt
	else if(strcmp(opCode, "0010") == 0){
		ctrUnit->RegDst = ONE;
		ctrUnit->ALUSrc = ZERO;
		ctrUnit->MemtoReg = ZERO;
		ctrUnit->RegWrite = ONE;
		ctrUnit->MemRead = ZERO;
		ctrUnit->MemWrite = ZERO;
		ctrUnit->Branch = ZERO;
		ctrUnit->ALUOp = SUB;
		ctrUnit->LUICtr = ZERO;
		ctrUnit->JalrCtr = ZERO;
		ctrUnit->Jump = ZERO;
		ctrUnit->ExOp = X;
	}
	// Or
	else if(strcmp(opCode, "0011") == 0){
		ctrUnit->RegDst = ONE;
		ctrUnit->ALUSrc = ZERO;
		ctrUnit->MemtoReg = ZERO;
		ctrUnit->RegWrite = ONE;
		ctrUnit->MemRead = ZERO;
		ctrUnit->MemWrite = ZERO;
		ctrUnit->Branch = ZERO;
		ctrUnit->ALUOp = OR;
		ctrUnit->LUICtr = ZERO;
		ctrUnit->JalrCtr = ZERO;
		ctrUnit->Jump = ZERO;
		ctrUnit->ExOp = X;
	}
	// Nand
	else if(strcmp(opCode, "0100") == 0){
		ctrUnit->RegDst = ONE;
		ctrUnit->ALUSrc = ZERO;
		ctrUnit->MemtoReg = ZERO;
		ctrUnit->RegWrite = ONE;
		ctrUnit->MemRead = ZERO;
		ctrUnit->MemWrite = ZERO;
		ctrUnit->Branch = ZERO;
		ctrUnit->ALUOp = AND;
		ctrUnit->LUICtr = ZERO;
		ctrUnit->JalrCtr = ZERO;
		ctrUnit->Jump = ZERO;
		ctrUnit->ExOp = X;
	}
	// Addi
	else if(strcmp(opCode, "0101") == 0){
		ctrUnit->RegDst = ZERO;
		ctrUnit->ALUSrc = ONE;
		ctrUnit->MemtoReg = ZERO;
		ctrUnit->RegWrite = ONE;
		ctrUnit->MemRead = ZERO;
		ctrUnit->MemWrite = ZERO;
		ctrUnit->Branch = ZERO;
		ctrUnit->ALUOp = ADD;
		ctrUnit->LUICtr = ZERO;
		ctrUnit->JalrCtr = ZERO;
		ctrUnit->Jump = ZERO;
		ctrUnit->ExOp = ONE;
	}
	// Slti
	else if(strcmp(opCode, "0110") == 0){
		ctrUnit->RegDst = ZERO;
		ctrUnit->ALUSrc = ONE;
		ctrUnit->MemtoReg = ZERO;
		ctrUnit->RegWrite = ONE;
		ctrUnit->MemRead = ZERO;
		ctrUnit->MemWrite = ZERO;
		ctrUnit->Branch = ZERO;
		ctrUnit->ALUOp = SUB;
		ctrUnit->LUICtr = ZERO;
		ctrUnit->JalrCtr = ZERO;
		ctrUnit->Jump = ZERO;
		ctrUnit->ExOp = ONE;
	}
	// Ori
	else if(strcmp(opCode, "0111") == 0){
		ctrUnit->RegDst = ZERO;
		ctrUnit->ALUSrc = ONE;
		ctrUnit->MemtoReg = ZERO;
		ctrUnit->RegWrite = ONE;
		ctrUnit->MemRead = ZERO;
		ctrUnit->MemWrite = ZERO;
		ctrUnit->Branch = ZERO;
		ctrUnit->ALUOp = OR;
		ctrUnit->LUICtr = ZERO;
		ctrUnit->JalrCtr = ZERO;
		ctrUnit->Jump = ZERO;
		ctrUnit->ExOp = ZERO;
	}
	// Lui
	else if(strcmp(opCode, "1000") == 0){
		ctrUnit->RegDst = ZERO;
		ctrUnit->ALUSrc = X;
		ctrUnit->MemtoReg = X;
		ctrUnit->RegWrite = ONE;
		ctrUnit->MemRead = X;
		ctrUnit->MemWrite = ZERO;
		ctrUnit->Branch = ZERO;
		ctrUnit->ALUOp = X;
		ctrUnit->LUICtr = ZERO;
		ctrUnit->JalrCtr = ZERO;
		ctrUnit->Jump = ZERO;
		ctrUnit->ExOp = X;
	}
	// LW
	else if(strcmp(opCode, "1001") == 0){
		ctrUnit->RegDst = ZERO;
		ctrUnit->ALUSrc = ONE;
		ctrUnit->MemtoReg = ONE;
		ctrUnit->RegWrite = ONE;
		ctrUnit->MemRead = ONE;
		ctrUnit->MemWrite = ZERO;
		ctrUnit->Branch = ZERO;
		ctrUnit->ALUOp = ADD;
		ctrUnit->LUICtr = ZERO;
		ctrUnit->JalrCtr = ZERO;
		ctrUnit->Jump = ZERO;
		ctrUnit->ExOp = ONE;
	}
	// SW
	else if(strcmp(opCode, "1010") == 0){
		ctrUnit->RegDst = X;
		ctrUnit->ALUSrc = ONE;
		ctrUnit->MemtoReg = X;
		ctrUnit->RegWrite = ZERO;
		ctrUnit->MemRead = ZERO;
		ctrUnit->MemWrite = ONE;
		ctrUnit->Branch = ZERO;
		ctrUnit->ALUOp = ADD;
		ctrUnit->LUICtr = ZERO;
		ctrUnit->JalrCtr = ZERO;
		ctrUnit->Jump = ZERO;
		ctrUnit->ExOp = ONE;
	}
	// Beq
	else if(strcmp(opCode, "1011") == 0){
		ctrUnit->RegDst = X;
		ctrUnit->ALUSrc = ZERO;
		ctrUnit->MemtoReg = X;
		ctrUnit->RegWrite = ZERO;
		ctrUnit->MemRead = ZERO;
		ctrUnit->MemWrite = ONE;
		ctrUnit->Branch = ONE;
		ctrUnit->ALUOp = SUB;
		ctrUnit->LUICtr = ZERO;
		ctrUnit->JalrCtr = ZERO;
		ctrUnit->Jump = ZERO;
		ctrUnit->ExOp = ONE;
	}
	// Jalr
	else if(strcmp(opCode, "1100") == 0){
		ctrUnit->RegDst = ZERO;
		ctrUnit->ALUSrc = X;
		ctrUnit->MemtoReg = X;
		ctrUnit->RegWrite = ONE;
		ctrUnit->MemRead = ZERO;
		ctrUnit->MemWrite = ZERO;
		ctrUnit->Branch = ZERO;
		ctrUnit->ALUOp = X;
		ctrUnit->LUICtr = ZERO;
		ctrUnit->JalrCtr = ONE;
		ctrUnit->Jump = ZERO;
		ctrUnit->ExOp = X;
	}
	// J
	else if(strcmp(opCode, "1101") == 0){
		ctrUnit->RegDst = X;
		ctrUnit->ALUSrc = X;
		ctrUnit->MemtoReg = X;
		ctrUnit->RegWrite = ZERO;
		ctrUnit->MemRead = ZERO;
		ctrUnit->MemWrite = ZERO;
		ctrUnit->Branch = ZERO;
		ctrUnit->ALUOp = X;
		ctrUnit->LUICtr = ZERO;
		ctrUnit->JalrCtr = ZERO;
		ctrUnit->Jump = ONE;
		ctrUnit->ExOp = ZERO;
	}
	// Halt
	else if(strcmp(opCode, "1110") == 0){
		ctrUnit->RegDst = X;
		ctrUnit->ALUSrc = X;
		ctrUnit->MemtoReg = X;
		ctrUnit->RegWrite = X;
		ctrUnit->MemRead = X;
		ctrUnit->MemWrite = X;
		ctrUnit->Branch = X;
		ctrUnit->ALUOp = X;
		ctrUnit->LUICtr = X;
		ctrUnit->JalrCtr = X;
		ctrUnit->Jump = X;
		ctrUnit->ExOp = X;
	}
}

void displayResults(struct registerFile *RF, int IC, int used_memory, bool registers_flag[16]){
	int registers_used = 0;
	for(int i=0; i<16; i++){
		if(registers_flag[i]){
			registers_used++;
		}
	}

	printf("\n____________________RESULTS____________________\n");
	printf("\n>> Instruction count: %d instructions", IC);
	printf("\n>> Memory used: %d words", used_memory);
	printf("\n>> Registers used: %.2f%%", 1.0 * registers_used / 16 * 100);
	printf("\n>> Registers: \n");
	displayRegsiters(RF);
}

char* complement2s(char *ones, int len){
	char *twos = malloc (sizeof (char) * len+1);

	// ones complement
	for(int i=0; i<len; i++){
		ones[i] = (ones[i] == '1') ? '0' : '1';
	}

	strcpy(twos, ones);
	int i;
	for(i=len-1; i>=0; i--){
		if(ones[i] == '1'){
			twos[i] = '0';
		}
		else{
			twos[i] = '1';
			break;
		}
	}
	if(i == -1){
		char *res = malloc (sizeof (char) * len+1);
		res[0] = '1';
		strcat(res, twos);
		return res;
	}
   	return twos;
}