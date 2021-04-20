#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "Chip8Def.h"

//Definicao das tabelas de mapeamento utilizando ponteiros para funcoes
void (*table[0xF + 1])(Chip8* chip8);
void (*table0[0xE + 1])(Chip8* chip8);
void (*table8[0xE + 1])(Chip8* chip8);
void (*tableE[0xE + 1])(Chip8* chip8);
void (*tableF[0x65 + 1])(Chip8* chip8);

void Table0(Chip8* chip8);
void Table8(Chip8* chip8);
void TableE(Chip8* chip8);
void TableF(Chip8* chip8);

//Emulacao das intrucoes do chip8
void OP_00E0(Chip8* chip8); //Cls
void OP_00EE(Chip8* chip8); //Ret
void OP_1nnn(Chip8* chip8); //Jump to nnn
void OP_2nnn(Chip8* chip8); //Call to nnn
void OP_3xkk(Chip8* chip8); //Skip if registers[Vx] == kk
void OP_4xkk(Chip8* chip8); //Skip if registers[Vx] != kk
void OP_5xy0(Chip8* chip8); //Skip if registers[Vx] == registers[Vy]
void OP_6xkk(Chip8* chip8); //Set registers[Vx] = kk
void OP_7xkk(Chip8* chip8); //Set registers[Vx] += kk
void OP_8xy0(Chip8* chip8); //Set registers[Vx] = registers[Vy]
void OP_8xy1(Chip8* chip8); //Set registers[Vx] |= registers[Vy]
void OP_8xy2(Chip8* chip8); //Set registers[Vx] &= registers[Vy]
void OP_8xy3(Chip8* chip8); //Set registers[Vx] ^= registers[Vy]
void OP_8xy4(Chip8* chip8); //Set registers[Vx] += registers[Vy], Set flag byte (sum > 255), Keep 2 lowests bytes
void OP_8xy5(Chip8* chip8); //Set registers[Vx] -= registers[Vy], Set flag byte (registers[Vx] > registers[Vy])
void OP_8xy6(Chip8* chip8); //Set registers[Vx] >>= 1, Set flag byte (registers[Vx] & 0x1u)
void OP_8xy7(Chip8* chip8); //Set registers[Vx] = registers[Vy] - registers[Vx], Set flag byte (registers[Vy] > registers[Vx])
void OP_8xyE(Chip8* chip8); //Set registers[Vx] <<= 1, Set flag byte (registers[Vx] & 0x80u) >> 7u)
void OP_9xy0(Chip8* chip8); //Skip if registers[Vx] != registers[Vy]
void OP_Annn(Chip8* chip8); //Set index = nnn
void OP_Bnnn(Chip8* chip8); //Jump to nnn + registers[0]
void OP_Cxkk(Chip8* chip8); //Set registers[Vx] = rendom number & kk
void OP_Dxyn(Chip8* chip8); //Draw
void OP_Ex9E(Chip8* chip8); //Skip if keyboard[registers[vx]] is pressed
void OP_ExA1(Chip8* chip8); //Skip if keyboard[registers[vx]] is not pressed
void OP_Fx07(Chip8* chip8); //Set registers[vx] = dalay_timer
void OP_Fx0A(Chip8* chip8); //Wait for key input, Set registers[vx] = key
void OP_Fx15(Chip8* chip8); //Set delay_timer = registers[vx]
void OP_Fx18(Chip8* chip8); //Set sound_timer = registers[vx]
void OP_Fx1E(Chip8* chip8); //Set index += registers[vx]
void OP_Fx29(Chip8* chip8); //Set index to be the sprite of registers[vx] (index = FONTSET_START_ADDRESS + (5 * digit))
void OP_Fx33(Chip8* chip8); //Set each digit of a number to a memory place (EX: 123, memory[index] = 1, memory[index + 1] = 2, memory[index + 2] = 3)
void OP_Fx55(Chip8* chip8); //Copy 0 to vx register into memory
void OP_Fx65(Chip8* chip8); //Copy memory to registers 0 to vx

//Emulacao de um ciclo do chip8 (fetch, decode, execute)
void cycle(Chip8* chip8);


#endif // !INSTRUCTIONS_H

