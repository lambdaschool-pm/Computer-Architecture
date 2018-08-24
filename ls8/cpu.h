#ifndef _CPU_H_
#define _CPU_H_

// Holds all information about the CPU
typedef struct cpu
{
  // TODO
  // PC
  // registers (array)
  // ram (array)
  unsigned char pc;
  unsigned char reg[8];
  unsigned char ram[256];
} CPU;

// Special register values
#define IM 5
#define IS 6
#define SP 7

// ALU operations
enum alu_op
{
  ALU_ADD,
  ALU_DIV,
  ALU_MUL,
  ALU_SUB
};

// Memory locations
#define ADDR_PROGRAM_ENTRY 0x00 // Where programs start getting loaded
#define ADDR_EMPTY_STACK 0xF4   // Where SP is on an empty stack

// Instructions

// These use binary literals. If these aren't available with your compiler, hex
// literals should be used.

// TODO: more instructions here. These can be used in cpu_run().
#define ADD 0b10100000
#define AND 0b10101000
#define CALL 0b01010000
#define CMP 0b10100111
#define DEC 0b01100110
#define DIV 0b10100011
#define HLT 0b00000001
#define INC 0b01100101
#define INT 0b01010010
#define IRET 0b00010011
#define JEQ 0b01010101
#define JGE 0b01011010
#define JGT 0b01010111
#define JLE 0b01011001
#define JLT 0b01011000
#define JMP 0b01010100
#define JNE 0b01010110
#define LD 0b10000011
#define LDI 0b10000010
#define MOD 0b10100100
#define MUL 0b10100010
#define NOP 0b00000000
#define NOT 0b01101001
#define OR 0b10101010
#define POP 0b01000110
#define PRA 0b01001000
#define PRN 0b01000111
#define PUSH 0b01000101
#define RET 0b00010001
#define SHL 0b10101100
#define SHR 0b10101101
#define ST 0b10000100
#define SUB 0b10100001
#define XOR 0b10101011
// Function declarations

extern void cpu_load(CPU *cpu, char *filename);
extern void cpu_init(CPU *cpu);
extern void cpu_run(CPU *cpu);

extern unsigned char cpu_ram_read(CPU *cpu, unsigned char index);
extern unsigned char cpu_ram_write(CPU *cpu, unsigned char MAR, unsigned char MDR);

#endif
