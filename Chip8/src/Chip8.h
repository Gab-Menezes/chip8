#ifndef CHIP8_H
#define CHIP8_H

#include "Instructions.h"

static void init_tables(Chip8* chip8); //Mapeamento de cada instrucao, para um index de alguns arrays
void init_chip8(Chip8* chip8); //Inicializacao do chip8
void load_rom(Chip8* chip8, const char* path); //Carregamento da ROM

#endif // !CHIP8_H
