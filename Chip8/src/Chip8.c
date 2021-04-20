#include "Chip8.h"
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

extern void (*table[0xF + 1])(Chip8* chip8);
extern void (*table0[0xE + 1])(Chip8* chip8);
extern void (*table8[0xE + 1])(Chip8* chip8);
extern void (*tableE[0xE + 1])(Chip8* chip8);
extern void (*tableF[0x65 + 1])(Chip8* chip8);

static void init_tables(Chip8* chip8)
{
	table[0x0] = &Table0;
	table[0x1] = &OP_1nnn;
	table[0x2] = &OP_2nnn;
	table[0x3] = &OP_3xkk;
	table[0x4] = &OP_4xkk;
	table[0x5] = &OP_5xy0;
	table[0x6] = &OP_6xkk;
	table[0x7] = &OP_7xkk;
	table[0x8] = &Table8;
	table[0x9] = &OP_9xy0;
	table[0xA] = &OP_Annn;
	table[0xB] = &OP_Bnnn;
	table[0xC] = &OP_Cxkk;
	table[0xD] = &OP_Dxyn;
	table[0xE] = &TableE;
	table[0xF] = &TableF;

	table0[0x0] = &OP_00E0;
	table0[0xE] = &OP_00EE;

	table8[0x0] = &OP_8xy0;
	table8[0x1] = &OP_8xy1;
	table8[0x2] = &OP_8xy2;
	table8[0x3] = &OP_8xy3;
	table8[0x4] = &OP_8xy4;
	table8[0x5] = &OP_8xy5;
	table8[0x6] = &OP_8xy6;
	table8[0x7] = &OP_8xy7;
	table8[0xE] = &OP_8xyE;

	tableE[0x1] = &OP_ExA1;
	tableE[0xE] = &OP_Ex9E;

	tableF[0x07] = &OP_Fx07;
	tableF[0x0A] = &OP_Fx0A;
	tableF[0x15] = &OP_Fx15;
	tableF[0x18] = &OP_Fx18;
	tableF[0x1E] = &OP_Fx1E;
	tableF[0x29] = &OP_Fx29;
	tableF[0x33] = &OP_Fx33;
	tableF[0x55] = &OP_Fx55;
	tableF[0x65] = &OP_Fx65;
}

void init_chip8(Chip8* chip8)
{
	//Inicializacao
	chip8->pc = PROGRAM_COUNTER_START;
	chip8->opcode = 0;
	chip8->sp = 0;
	chip8->index = 0;

	//Timers
	chip8->delay_timer = 0;
	chip8->sound_timer = 0;

	//Limpa as memorias
	//Video
	memset(chip8->screen, 0, sizeof(chip8->screen));

	//Stack
	memset(chip8->stack, 0, sizeof(chip8->stack));

	//Memoria
	memset(chip8->memory, 0, sizeof(chip8->memory));

	//Registros
	memset(chip8->registers, 0, sizeof(chip8->registers));

	//Input do teclado
	memset(chip8->keyboard, 0, sizeof(chip8->keyboard));

	//Carrega o array de fonte na memoria
	memcpy(&chip8->memory[FONTSET_START_ADDRESS], fontset, sizeof(fontset));

	//Cria o mapeamento da operacao para funcao especifica
	init_tables(chip8);
}

void load_rom(Chip8* chip8, const char* file_name)
{
    //Abre o arquivo em mode de leitura de byte
	FILE* rom = fopen(file_name, "rb");
    if (rom != NULL) {
        //Vai para o final do arquivo e depois volta para descobrir o tamanho
        fseek(rom, 0, SEEK_END);
        long int rom_length = ftell(rom);
        rewind(rom);
		//Verifica se o tamanho da rom caberá na memoria
		if (PROGRAM_END - PROGRAM_START < rom_length)
		{
			fclose(rom);
			printf("ERRO: O arquivo eh muito grande\n");
			exit(EXIT_FAILURE);
		}

		//Aloca um buffer de tamanho necessario copia o conteudo do arquivo
        uint8_t* rom_buffer = (uint8_t*)malloc(sizeof(uint8_t) * rom_length);
        fread(rom_buffer, sizeof(uint8_t), rom_length, rom);

		//Copiamos o buffer para memoria do chip8
		//memcpy(chip8->memory[PROGRAM_COUNTER_START], rom_buffer, rom_length);
		for (int i = 0; i < rom_length; i++) 
            chip8->memory[PROGRAM_START + i] = rom_buffer[i];

		//fread(&chip8->memory[PROGRAM_COUNTER_START], sizeof(uint8_t), rom_length, rom);

		free(rom_buffer);
    }
    else 
	{
        printf("ERRO: Arquivo nao encontrado\n");
        exit(EXIT_FAILURE);
    }
    fclose(rom);
}
