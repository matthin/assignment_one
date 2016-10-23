/* PROGRAM:  assignment_one.c
   DATE:     23/10/2016
   TOPIC:    Simple Langauge Simulator
   PURPOSE:  A small program to simulate the operations of a very simple computer.   
*/

/**************************************************************************/
/* Declare include files
 **************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**************************************************************************/
/* Macro Defines
 **************************************************************************/
#define SIZE 1000

/*
 * Operation Codes
 */
#define READ 10
#define SAVE 11

#define LOAD  20
#define STORE 21

#define ADD       30
#define SUBSTRACT 31
#define DIVIDE    32
#define MULTIPLY  33

#define BRANCH     40
#define BRANCHNEG  41
#define BRANCHZERO 42
#define HALT       43

/*
 * Register Defines
 */
#define REG_ACCUM   0
#define REG_COUNTER 1
#define REG_INSTR   2
#define REG_OPCODE  3
#define REG_OPERAND 4
#define REG_VALID   5

/**************************************************************************/
/* Global variables
 **************************************************************************/
int words[SIZE];
int registers[6];
int maxAddress = 0;

/**************************************************************************/
/* Function prototypes
 **************************************************************************/
void initialization();
void load_sml();
void execute_sml();
void dump(int status);

/**************************************************************************
 * Main
 *    Calls methods initialization(), load_sml(), execute_sml() & dump()
 *    Returns 0 on success
 **************************************************************************/
int main() {
  initialization();
  load_sml();
  execute_sml();
  dump(0);
  return 0;
}

/**************************************************************************
 * initialization
 *      Upon execution it initilizes the words array up to the size with 
 *	50505 & registers array upto 6 with 0's.
 *      Return: 
 *           n/a
 *      Sets global variable words & registers
 **************************************************************************/
void initialization() {
  int i;

  for (i = 0; i < SIZE; ++i) {
    words[i] = 50505;
  }

  for (i = 0; i < 6; ++i) {
    registers[i] = 0;
  }
}

/**************************************************************************
 * load_sml
 *      Upon execution it takes input of word and error checks them while
	storing valid word in to words array. 
 *      Return: 
 *           n/a
 **************************************************************************/
void load_sml() {
  int i = 0, word;

  for (;;) {
    scanf("%d", &word);

    if (word == -999999) {
      break;
    }
    if(word >= 99999 || word <= -99999){
    	puts("                      *** ABEND: prg load: prg invalid word ***\n");
	puts("*********************************ABNORMAL TERMINATION****************************");
	dump(1);
	break;	
    }
    if(i>SIZE){
	puts("				*** ABEND: prg load: prg too big ***\n");
	puts("*********************************ABNORMAL TERMINATION****************************");
	dump(1);
	break;
    }
    words[i++] = word;   
  }
}

/**************************************************************************
 * execute_sml
 *      Upon execution it takes an word from the words array and splits them
 *	into Opcode and Operand, depending on valid opcode, it calls upon
 *	different cases to be executed. If invalid then error message it 
 * 	put and dump(1); is called upon.
 *      Return: 
 *           n/a
 **************************************************************************/
void execute_sml() {
  int done = false, tempData = 0;
  puts("*********************************START EXECUTION*********************************");
  
  while (!done) {
    registers[REG_OPCODE] = words[registers[REG_COUNTER]] / 1000;
    registers[REG_OPERAND] = words[registers[REG_COUNTER]] % 1000;
    
    switch (registers[REG_OPCODE]) {
    case READ:
      scanf("%d", &tempData);
      if(tempData > 99999 || tempData < -99999) {
        puts("                      *** ABEND: prg load: prg invalid word ***\n");
	puts("*********************************ABNORMAL TERMINATION****************************");
        dump(1);
	break;
      }
      words[registers[REG_OPERAND]] = tempData;
      printf("READ:  %+05d\n", words[registers[REG_OPERAND]]); 
      break;
    case SAVE:
      registers[REG_ACCUM] = words[registers[REG_OPERAND]];
      break;
    case LOAD:
      registers[REG_ACCUM] = words[registers[REG_OPERAND]];
      break;
    case STORE:
      words[registers[REG_OPERAND]] = registers[REG_ACCUM];
      printf("%+05d\n",  words[registers[REG_OPERAND]]); 
      break;
    case ADD:
      registers[REG_ACCUM] += words[registers[REG_OPERAND]]; 	    
      break;
    case SUBSTRACT:
      registers[REG_ACCUM] -= words[registers[REG_OPERAND]];
      break;
    case DIVIDE:  	
      if (words[registers[REG_OPERAND]] == 0) {
        puts("				 *** ABEND: attempted division by 0 ***\n");
        puts("*********************************ABNORMAL TERMINATION****************************");
        dump(1);
        break;
      }
      registers[REG_ACCUM] /= words[registers[REG_OPERAND]];
      break;
    case MULTIPLY:
      registers[REG_ACCUM] *= words[registers[REG_OPERAND]];
      break;
    case BRANCH:	
      registers[REG_COUNTER] = registers[REG_OPERAND];
      break;
    case BRANCHNEG:
      if (registers[REG_ACCUM] <= 0) {
        registers[REG_COUNTER] = registers[REG_OPERAND];
      }
      break;
    case BRANCHZERO:
      if (registers[REG_ACCUM] == 0) {
        registers[REG_COUNTER] = registers[REG_OPERAND];
      }
      break;
    case HALT:
      puts("*********************************END EXECUTION***********************************");	 
      dump(1);
      break;
    default:
      puts("\n             *** ABEND: Addressability error and/or Invalid Opcodeeexit ***\n");
      puts("*********************************ABNORMAL TERMINATION****************************");
      dump(1);
      break;
    }
    if(registers[REG_ACCUM] >= 99999){
        puts("				     *** ABEND: overflow ***\n");
        puts("*********************************ABNORMAL TERMINATION****************************");
        dump(1);
        break;
    }else if(registers[REG_ACCUM] <= -99999){
	puts("				     *** ABEND: underflow ***\n");
        puts("*********************************ABNORMAL TERMINATION****************************");
        dump(1);        
	break;
    } 
    if (!done) {
      registers[REG_COUNTER]++;	
    }
    
  }
}

/**************************************************************************
 * dump
 *      Prints out essential information of the registers and exits 
 *	with success or faliure using the status.
 *      Return: 
 *           n/a
 **************************************************************************/
void dump(const int status) {
  int i;
 
  puts("\nREGISTERS:");
  printf("accumulator           %+06d\n",    registers[REG_ACCUM]);
  printf("instructioncounter       %03d\n",  registers[REG_COUNTER]);
  printf("instructionregister   %+d\n",      words[registers[REG_COUNTER]]);
  printf("operationcode             %02d\n",   registers[REG_OPCODE]);
  printf("operand                  %03d\n",  registers[REG_OPERAND]);
  printf("ValidInstructions         %2d\n\n", ++registers[REG_COUNTER]);

  printf("MEMORY:\n");
  for (i = 0; i < SIZE; ++i) {
    if(words[i] == 50505)
      break;
    else if(i%10==0){
      printf("\n%3d ", i);;
    }
    printf("%+05d ", words[i]);
    
  }
  puts("");
  exit(status);
}
