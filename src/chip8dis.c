#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

void disassemble_chip8_op(uint8_t *code_buffer, int pc)
{
  uint8_t *code = code_buffer + pc;
  uint8_t first_nib = *(code + 0) >> 4;

  printf("%04x %02x %02x ", pc, *(code + 0), *(code + 1));

  switch (first_nib)
  {
    case 0x00:
      switch (*(code + 1))
      {
        case 0xe0:
          printf("%-10s", "CLS");
          break;

        case 0xee:
          printf("%-10s", "RTS");
          break;

        default:
          printf("UNKNOWN 0");
          break;
      }
      break;

    case 0x01:
      {
        printf("%-10s $%01x%02x", "JUMP", *(code + 0) & 0xf, *(code + 1));
      }
      break;

    case 0x02:
      {
        printf("%-10s $%01x%02x", "CALL", *(code + 0) & 0xf, *(code + 1));
      }
      break;

    case 0x03:
      printf("3 not handled yet");
      break;

    case 0x04:
      printf("4 not handled yet");
      break;

    case 0x05:
      printf("5 not handled yet");
      break;

    case 0x06:
      {
        uint8_t reg = *(code + 0) & 0x0f;
        printf("%-10s V%01X,#$%02x", "MVI", reg, *(code + 1));
      }
      break;

    case 0x07:
      printf("7 not handled yet");
      break;

    case 0x08:
      printf("8 not handled yet");
      break;

    case 0x09:
      printf("9 not handled yet");
      break;

    case 0x0a:
      {
        uint8_t addres_shi = *(code + 0) & 0x0f;
        printf("%-10s I,#$%01x%02x", "MVI", addres_shi, *(code + 1));
      }
      break;
      
    case 0x0b:
      printf("b not handled yet");
      break;

    case 0x0c:
      printf("c not handled yet");
      break;

    case 0x0d:
      printf("d not handled yet");
      break;

    case 0x0e:
      printf("e not handled yet");
      break;

    case 0x0f:
      printf("f not handled yet");
      break;
  }
}

int main(int argc, char** argv) {
  FILE *f = fopen(*(argv + 1), "rb");

  if (f == NULL)
  {
    printf("error: failed to open %s\n", *(argv + 1));
    exit(1);
  }

  fseek(f, 0L, SEEK_END);
  int fsize = ftell(f);
  fseek(f, 0L, SEEK_SET);

  unsigned char* buffer = malloc(fsize + 0x200);

  fread(buffer + 0x200, fsize, 1, f);

  fclose(f);

  int pc = 0x200;

  while (pc < (fsize + 0x200))
  {
    disassemble_chip8_op(buffer, pc);

    pc += 2;

    printf("\n");
  }

  return 0;
}

