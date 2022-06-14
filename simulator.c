#include "simulator.h"

void main(int argc,char **argv){
   FILE *machp, *fopen();
   int i, j, noInsts;
   size_t lineSize;
   char *line;
   char *token;
   int instCount = 0;

   i = 0;
   j = 0;
   line = (char *)malloc(72);

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

   while(getline(&line, &lineSize, machp) != -1){
      
   }

   fclose(machp);
   exit(0);
}

char *getNthLine(FILE *inputFile, int n){
   int count = 0;
   size_t lineSize;
   char *line;
   line = (char *)malloc(72);
   while(getline(&line, &lineSize, inputFile) != -1){
      count++;
      if(count == n){
         break;
      }
   }
   return (char *)line;
}

long long int2Binary(int num){
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

long long bin2Dec(char *binary, int len){
   long long decimal = 0;
   int position = 0;
   int i = len - 1;
   while(i >= 0){
      decimal = decimal + (binary[i] - 48) * pow(2, position);
      i--;
      position++;
   }
   return decimal;
}


long long complement2s(long long bin){
   char ones[33], twos[33];
   sprintf(ones, "%d", bin);

   int len = strlen(ones);

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
      char res[33];
      res[0] = '1';
      strcat(res, twos);
      return atoi(res);
   }
   return atoi(twos);
}