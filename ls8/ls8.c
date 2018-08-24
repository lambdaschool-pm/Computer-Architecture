#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"

/**
 * Main
 */
int main(int argc, char *argv[])
{

  // init a  CPU struct
  CPU cpu;

  if (argc != 2)
  {
    fprintf(stderr, "Useage: ./ls8 file.ls8\n");
    exit(1);
  }

  char *filename = argv[1];

  cpu_init(&cpu);
  cpu_load(&cpu, filename);
  cpu_run(&cpu);

  return 0;
}