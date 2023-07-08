#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

void disassemble_chip8_op(unsigned char* code_buffer, int pc)
{
  uint8_t *code = code_buffer + pc;
  uint8_t first_nib = *(code + 0) >> 4;

  printf("%04x %02x %02x ", pc, *(code + 0), *(code + 1));

  switch (first_nib)
  {
    case 0x00:
      {
        uint8_t second_byte = *(code + 1);
        switch (second_byte)
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
      }
      break;

    case 0x01:
      {
        uint8_t addr_p1 = *(code + 0) & 0x0f;
        uint8_t addr_p2 = *(code + 1);
        printf("%-10s $%01x%02x", "JUMP", addr_p1, addr_p2);
      }
      break;

    case 0x02:
      {
        uint8_t subrout_p1 = *(code + 0) & 0x0f;
        uint8_t subrout_p2 = *(code + 1);
        printf("%-10s $%01x%02x", "CALL", subrout_p1, subrout_p2);
      }
      break;

    case 0x03:
      {
        uint8_t reg = *(code + 0) & 0x0f;
        uint8_t const8 = *(code + 1);
        printf("%-10s V%01X,#$%02x", "SKIP.EQ", reg, const8);
      }
      break;

    case 0x04:
      {
        uint8_t reg = *(code + 0) & 0x0f;
        uint8_t const8 = *(code + 1);
        printf("%-10s V%01X,#$%02x", "SKIP.NE", reg, const8);
      }
      break;

    case 0x05:
      {
        uint8_t reg_1 = *(code + 0) & 0x0f;
        uint8_t reg_2 = *(code + 1) >> 4;
        uint8_t last_nib = *(code + 1) & 0x0f;
        switch (last_nib)
        {
          case 0:
            printf("%-10s V%01X,V%01X", "SKIP.EQ", reg_1, reg_2);
            break;
          default:
            printf("UNKNOWN 5");
            break;
          
        }
      }
      break;

    case 0x06:
      {
        uint8_t reg = *(code + 0) & 0x0f;
        uint8_t const8 = *(code + 1);
        printf("%-10s V%01X,#$%02x", "MVI", reg, const8);
      }
      break;

    case 0x07:
      {
        uint8_t reg = *(code + 0) & 0x0f;
        uint8_t const8 = *(code + 1);
        printf("%-10s V%01X,#$%02x", "ADI", reg, const8);
      }
      break;

    case 0x08:
      {
        {
          uint8_t reg_1 = *(code + 0) & 0x0f;
          uint8_t reg_2 = *(code + 1) >> 4;
          uint8_t last_nib = *(code + 1) & 0x0f;
          switch (last_nib)
          {
            case 0:
              printf("%-10s V%01X,V%01X", "MOV", reg_1, reg_2);
              break;
            case 1:
              printf("%-10s V%01X,V%01X", "OR", reg_1, reg_2);
              break;
            case 2:
              printf("%-10s V%01X,V%01X", "AND", reg_1, reg_2);
              break;
            case 3:
              printf("%-10s V%01X,V%01X", "XOR", reg_1, reg_2);
              break;
            case 4:
              printf("%-10s V%01X,V%01X", "ADD.", reg_1, reg_2);
             break;
            case 5:
              printf("%-10s V%01X,V%01X", "SUB.", reg_1, reg_2);
              break;
            case 6:
              printf("%-10s V%01X", "SHR.", reg_1);
              break;
            case 7:
              printf("%-10s V%01X,V%01X", "SUBB.", reg_1, reg_2);
              break;
            case 0xe0:
              printf("%-10s V%01X", "SHL.", reg_1);
              break;
            default:
              printf("UNKNOWN 8");
              break;
          }
        }
      }
      break;

    case 0x09:
      {
        uint8_t reg_1 = *(code +0) & 0x0f;
        uint8_t reg_2 = *(code + 1) >> 4;
        uint8_t last_nib = *(code + 1) & 0x0f;
        switch (last_nib) 
        {
          case 0:
            printf("%-10s V%01X,V%01X", "SKIP.NE", reg_1, reg_2);
            break;
          default:
            printf("UNKNOWN 9");
            break;
        }
      }
      break;

    case 0x0a:
      {
        uint8_t addr_p1 = *(code + 0) & 0x0f;
        uint8_t addr_p2 = *(code + 1);
        printf("%-10s I,#$%01x%02x", "MVI", addr_p1, addr_p2);
      }
      break;
      
    case 0x0b:
      {
        uint8_t addr_p1 = *(code + 0) & 0x0f; 
        uint8_t addr_p2 = *(code + 1);
        printf("%-10s $%01x,#%02x(V0)", "JUMP", addr_p1, addr_p2);
      }
      break;

    case 0x0c:
      {
        uint8_t reg = *(code + 0) & 0x0f;
        uint8_t const8 = *(code + 1);
        printf("%-10s V%01X,#$%02X", "RNDMSK", reg, const8);
      }
      break;

    case 0x0d:
      {
        uint8_t reg_1 = *(code + 0) & 0x0f;
        uint8_t reg_2 = *(code + 1) >> 4;
        uint8_t const4 = *(code + 1) & 0x0f;
        printf("%-10s V%01X,V%01X,#$%01x", "SPRITE", reg_1, reg_2, const4);
      }
      break;

    case 0x0e:
      {
        uint8_t reg = *(code + 0) &0x0f;
        uint8_t second_byte = *(code + 1);
        switch (second_byte)
        {
          case 0x9e:
            printf("%-10s V%01X", "STRIP.KEY", reg);
            break;

          case 0xa1:
            printf("%-10s V%01X", "STRIP.NOKEY", reg);
            break;

          default:
            printf("UNKNOWN E");
            break;
        }
      }
      break;

    case 0x0f:
      {
        uint8_t reg = *(code + 0) & 0x0f;
        uint8_t second_byte = *(code + 1);
        switch (second_byte)
        {
          case 0x07:
            printf("%-10s V%01X,%s", "MOV", reg, "DELAY");
            break;
          case 0x0a:
            printf("%-10s V%01X", "WAITKEY", reg);
            break;
          case 0x15:
            printf("%-10s %s,V%01X", "MOV", "DELAY", reg);
            break;
          case 0x18:
            printf("%-10s %s,V%01X", "MOV", "SOUND", reg);
            break;
          case 0x1e:
            printf("%-10s %s,V%01X", "ADD", "I", reg);
            break;
          case 0x29:
            printf("%-10s V%01X", "SPRITECHAR", reg);
            break;
          case 0x33:
            printf("%-10s V%01X", "MOVBCD", reg);
            break;
          case 0x55:
            printf("%-10s (%s),V%01X-V%01X", "MOVM", "I", 0x00, reg);
            break;
          case 0x65:
            printf("%-10s V%01X-V%01X,(%s)", "MOVM", 0x00, reg, "I");
            break;
          default:
            printf("UNKNOWN F");
            break;
        }
      }
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

