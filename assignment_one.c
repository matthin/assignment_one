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
#define REG_ACCUM       0
#define REG_COUNTER     1
#define REG_INSTRUCTION 2
#define REG_OPCODE      3
#define REG_OPERAND     4
#define REG_VALID       5

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
  int opcode, operand, done = true, instruction_counter = 0;

  while (!done) {
    opcode = words[instruction_counter] / 1000;
    operand = words[instruction_counter] % 1000;

    switch (opcode) {
    case READ:
      break;
    case SAVE:
      break;
    case HALT:
      done = 1;
      break;
    default:
      dump(1);
    }

    if (!done) {
      instruction_counter++;
    }
  }
}

void dump(const int status) {
  int i = 0;

  puts("REGISTERS:");
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
