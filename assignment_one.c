#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
#define BRANCHING  41
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

/*
 * Globals
 */
int words[1000];
int registers[6];

/*
 * Function Definitions
 */
void initialization();
void load_sml();
void execute_sml();
void dump(int status);

int main() {
  initialization();
  load_sml();
  execute_sml();
  dump(0);

  return 0;
}

void initialization() {
  int i;

  for (i = 0; i < 1000; ++i) {
    words[i] = 50505;
  }

  for (i = 0; i < 6; ++i) {
    registers[i] = 0;
  }
}

void load_sml() {
  int i = 0, word;

  for (;;) {
    scanf("%d", &word);

    if (word == -999999) {
      break;
    }

    words[i++] = word;
  }
}

void execute_sml() {
  int done = false;

  while (!done) {
    registers[REG_OPCODE] = words[registers[REG_COUNTER]] / 1000;
    registers[REG_OPERAND] = words[registers[REG_COUNTER]] % 1000;

    printf("%d\n", registers[REG_OPCODE]);
    switch (registers[REG_OPCODE]) {
    case READ:
    case SAVE:
      scanf("%d", &words[registers[REG_OPERAND]]);
      break;
    case LOAD:
      scanf("%d", &registers[REG_ACCUM]);
      break;
    case HALT:
      done = 1;
      break;
    default:
      dump(1);
    }

    if (!done) {
      registers[REG_COUNTER]++;
    }
  }
}

void dump(const int status) {
  int i = 0;

  puts("REGISTERS:");
  printf("accumulator %d\n", registers[REG_ACCUM]);
  printf("instructioncounter %d\n", registers[REG_COUNTER]);
  printf("instructionregister %d\n", registers[REG_INSTR]);
  printf("operationcode %d\n", registers[REG_OPCODE]);
  printf("operand %d\n", registers[REG_OPERAND]);
  printf("ValidInstructions %d\n\n", registers[REG_VALID]);

  printf("MEMORY:\n\n");
  for (;;) {
    if (words[i] == 50505) {
      break;
    }

    printf("%+d ", words[i++]);
  }

  puts("");

  exit(status);
}
