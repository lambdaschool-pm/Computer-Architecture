#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpu.h"

unsigned char cpu_ram_read(CPU *cpu, unsigned char MAR)
{
  return cpu->ram[MAR];
}

unsigned char cpu_ram_write(CPU *cpu, unsigned char MAR, unsigned char MDR)
{
  return cpu->ram[MAR] = MDR;
}

unsigned char cpu_pop(CPU *cpu)
{
  unsigned char val = cpu_ram_read(cpu, cpu->reg[SP]);
  cpu->reg[SP]++;

  return val;
}

void cpu_push(CPU *cpu, unsigned char val)
{
  cpu->reg[SP]--;
  cpu_ram_write(cpu, cpu->reg[SP], val);
}

/**
 * Load the binary bytes from a .ls8 source file into a RAM array
 */
void cpu_load(CPU *cpu, char *filename)
{
  FILE *fp = fopen(filename, "r");
  char line[256];
  int address = ADDR_PROGRAM_ENTRY;

  // open file
  if (fp == NULL)
  {
    fprintf(stderr, "Can not open file %s\n", filename);
    exit(2);
  }

  // Read all the lines and store them in RAM
  while (fgets(line, sizeof line, fp) != NULL)
  {
    /*
    if (line[strlen(line) - 1] != '\n')
    {
      fprint(stderr, "Line was too long");
      exit(3);
    }
    */
    // convert string to a number
    char *endchar;

    unsigned char byte = strtol(line, &endchar, 2);

    // Ingnore empty lines
    if (endchar == line)
    {
      continue;
    }
    // Store in ram
    //cpu->ram[address++] = byte;
    cpu_ram_write(cpu, address++, byte);
  }
  /*
  const int DATA_LEN = 6;
  char data[DATA_LEN] = {
      // From print8.ls8
      0b10000010, // LDI R0,8
      0b00000000,
      0b00001000,
      0b01000111, // PRN R0
      0b00000000,
      0b00000001 // HLT
  };
  
  //int address = 0;

  for (int i = 0; i < DATA_LEN; i++)
  {
    cpu->ram[address++] = data[i];
  }
*/
  // TODO: Replace this with something less hard-coded
}

/**
 * ALU
 */
void alu(CPU *cpu, enum alu_op op, unsigned char regA, unsigned char regB)
{
  switch (op)
  {
  case ALU_ADD:
    // TODO
    cpu->reg[regA] += cpu->reg[regB];
    break;

  case ALU_DIV:
    // TODO
    cpu->reg[regA] /= cpu->reg[regB];
    break;

  case ALU_MUL:
    // TODO
    cpu->reg[regA] *= cpu->reg[regB];
    break;

    // TODO: implement more ALU ops

  case ALU_SUB:
    // TODO
    cpu->reg[regA] -= cpu->reg[regB];
    break;
  }
}
/**
 * Run the CPU
 */
void cpu_run(CPU *cpu)
{
  int running = 1; // True until we get a HLT instruction

  while (running)
  {
    // TODO
    // 1. Get the value of the current instruction (in address PC).
    // 2. switch() over it to decide on a course of action.
    // 3. Do whatever the instruction should do according to the spec.
    // 4. Move the PC to the next instruction.

    // Instructions
    unsigned char IR = cpu_ram_read(cpu, cpu->pc);

    // OP Code
    unsigned char operandA = cpu_ram_read(cpu, cpu->pc + 1);
    unsigned char operandB = cpu_ram_read(cpu, cpu->pc + 2);

    switch (IR)
    {
    case ADD:
      alu(cpu, ALU_ADD, operandA, operandB);
      break;

    case CALL:
      // TODO
      cpu_push(cpu, cpu->pc + 2); // the return programing is two instructions from the current Program Counter
      cpu->pc = cpu->reg[operandA];
      break;

    case DIV:
      // TODO
      alu(cpu, ALU_DIV, operandA, operandB);
      break;

    case HLT:
      running = 0;
      break;

    case LDI:
      cpu->reg[operandA] = operandB;
      break;

    case MUL:
      alu(cpu, ALU_MUL, operandA, operandB);
      break;

    case POP:
      // TODO
      cpu->reg[operandA] = cpu_pop(cpu);
      break;

    case PRA:
      printf("%c\n", cpu->reg[operandA]);
      break;

    case PRN:
      printf("%d\n", cpu->reg[operandA]);
      break;

    case PUSH:
      // TODO
      cpu_push(cpu, cpu->reg[operandA]);
      break;

    case RET:
      // TODO
      cpu->pc = cpu_pop(cpu);
      break;

    case SUB:
      // TODO
      alu(cpu, 3, operandA, operandB);
      break;

    default:
      printf("Unknown instruction at %02x: %02x\n", cpu->pc, IR);
      exit(2);
    }

    cpu->pc += ((IR >> 6) & 0x3) + 1;
  }
}

/**
 * Initialize a CPU struct
 */
void cpu_init(CPU *cpu)
{
  // TODO: Zero registers and RAM
  memset(cpu->reg, 0, sizeof cpu->reg);
  memset(cpu->ram, 0, sizeof cpu->ram);

  // TODO: Initialize the PC and other special registers
  cpu->pc = ADDR_PROGRAM_ENTRY;
  cpu->reg[SP] = ADDR_EMPTY_STACK;
}
