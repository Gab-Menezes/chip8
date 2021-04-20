#include "Instructions.h"
#include <memory.h>
#include <stdlib.h> 

//Despachamento de instrucoes
void Table0(Chip8* chip8)
{
	table0[chip8->opcode & 0x000Fu](chip8);
}

void Table8(Chip8* chip8)
{
	table8[chip8->opcode & 0x000Fu](chip8);
}

void TableE(Chip8* chip8)
{
	tableE[chip8->opcode & 0x000Fu](chip8);
}

void TableF(Chip8* chip8)
{
	tableF[chip8->opcode & 0x00FFu](chip8);
}


//Instrucoes
void OP_00E0(Chip8* chip8)
{
	//Limpamos o buffer da tela
	memset(chip8->screen, 0, sizeof(chip8->screen));
}

void OP_00EE(Chip8* chip8)
{
	//Voltamos um stack pointer
	chip8->sp--;
	//Pegamos o endereco que estava no stack pointer
	chip8->pc = chip8->stack[chip8->sp];
}

void OP_1nnn(Chip8* chip8)
{
	//0x0FFFu eh uma mascara de bit para obtemos o valor do endereco pegando os 3 ultimos byte do codigo
	uint16_t address = chip8->opcode & 0x0FFFu;
	//Fazemos o jump
	chip8->pc = address;
}

void OP_2nnn(Chip8* chip8)
{
	//0x0FFFu eh uma mascara de bit para obtemos o valor do endereco pegando os 3 ultimos byte do codigo
	uint16_t address = chip8->opcode & 0x0FFFu;

	//Adicionanos o program counter na stack e incrementeamos o stack pointer
	chip8->stack[chip8->sp] = chip8->pc;
	chip8->sp++;
	chip8->pc = address;
}

void OP_3xkk(Chip8* chip8)
{
	//Pegamos Vx (2° byte) e fazemos o shift em 8 casas Ex: F00 -> 00F
	uint8_t vx = (chip8->opcode & 0x0F00u) >> 8u;
	//Pegamos kk (3° e 4° bytes)
	uint8_t val = (chip8->opcode & 0x00FFu);
	if (chip8->registers[vx] == val) chip8->pc += 2;
}

void OP_4xkk(Chip8* chip8)
{
	//Pegamos Vx (2° byte) e fazemos o shift em 8 casas Ex: F00 -> 00F
	uint8_t vx = (chip8->opcode & 0x0F00u) >> 8u;
	//Pegamos kk (3° e 4° bytes)
	uint8_t val = (chip8->opcode & 0x00FFu);

	//Pulamos a proxima instrucao
	if (chip8->registers[vx] != val) chip8->pc += 2;
}

void OP_5xy0(Chip8* chip8)
{
	//Pegamos Vx (2° byte) e fazemos o shift em 8 casas Ex: F00 -> 00F
	uint8_t vx = (chip8->opcode & 0x0F00u) >> 8u;
	//Pegamos Vx (3° byte) e fazemos o shift em 4 casas Ex: 0F0 -> 00F
	uint8_t vy = (chip8->opcode & 0x00F0u) >> 4u;
	if (chip8->registers[vx] == chip8->registers[vy]) chip8->pc += 2;
}

void OP_6xkk(Chip8* chip8)
{
	//Pegamos Vx (2° byte) e fazemos o shift em 8 casas Ex: F00 -> 00F
	uint8_t vx = (chip8->opcode & 0x0F00u) >> 8u;
	//Pegamos kk (3° e 4° bytes)
	uint8_t val = (chip8->opcode & 0x00FFu);
	chip8->registers[vx] = val;
}

void OP_7xkk(Chip8* chip8)
{
	//Pegamos Vx (2° byte) e fazemos o shift em 8 casas Ex: F00 -> 00F
	uint8_t vx = (chip8->opcode & 0x0F00u) >> 8u;
	//Pegamos kk (3° e 4° bytes)
	uint8_t val = (chip8->opcode & 0x00FFu);
	chip8->registers[vx] += val;
}

void OP_8xy0(Chip8* chip8)
{
	//Pegamos Vx (2° byte) e fazemos o shift em 8 casas Ex: F00 -> 00F
	uint8_t vx = (chip8->opcode & 0x0F00u) >> 8u;
	//Pegamos Vy (3° byte) e fazemos o shift em 4 casas Ex: 0F0 -> 00F
	uint8_t vy = (chip8->opcode & 0x00F0u) >> 4u;
	chip8->registers[vx] = chip8->registers[vy];
}

void OP_8xy1(Chip8* chip8)
{
	//Pegamos Vx (2° byte) e fazemos o shift em 8 casas Ex: F00 -> 00F
	uint8_t vx = (chip8->opcode & 0x0F00u) >> 8u;
	//Pegamos Vy (3° byte) e fazemos o shift em 4 casas Ex: 0F0 -> 00F
	uint8_t vy = (chip8->opcode & 0x00F0u) >> 4u;
	chip8->registers[vx] |= chip8->registers[vy];
}

void OP_8xy2(Chip8* chip8)
{
	//Pegamos Vx (2° byte) e fazemos o shift em 8 casas Ex: F00 -> 00F
	uint8_t vx = (chip8->opcode & 0x0F00u) >> 8u;
	//Pegamos Vy (3° byte) e fazemos o shift em 4 casas Ex: 0F0 -> 00F
	uint8_t vy = (chip8->opcode & 0x00F0u) >> 4u;
	chip8->registers[vx] &= chip8->registers[vy];
}

void OP_8xy3(Chip8* chip8)
{
	//Pegamos Vx (2° byte) e fazemos o shift em 8 casas Ex: F00 -> 00F
	uint8_t vx = (chip8->opcode & 0x0F00u) >> 8u;
	//Pegamos Vy (3° byte) e fazemos o shift em 4 casas Ex: 0F0 -> 00F
	uint8_t vy = (chip8->opcode & 0x00F0u) >> 4u;
	chip8->registers[vx] ^= chip8->registers[vy];
}

void OP_8xy4(Chip8* chip8)
{
	//Pegamos Vx (2° byte) e fazemos o shift em 8 casas Ex: F00 -> 00F
	uint8_t vx = (chip8->opcode & 0x0F00u) >> 8u;
	//Pegamos Vy (3° byte) e fazemos o shift em 4 casas Ex: 0F0 -> 00F
	uint8_t vy = (chip8->opcode & 0x00F0u) >> 4u;
	
	//Fazemos a soma dos registros
	uint16_t sum = chip8->registers[vx] + chip8->registers[vy];
	//Setamos o flag byte de for maior do que 255
	chip8->registers[FLAG_LOCATION] = sum > 255u ? 1 : 0;
	//Matemos os 2 ultimos bytes da soma
	chip8->registers[vx] = sum & 0xFFu;
}

void OP_8xy5(Chip8* chip8)
{
	//Pegamos Vx (2° byte) e fazemos o shift em 8 casas Ex: F00 -> 00F
	uint8_t vx = (chip8->opcode & 0x0F00u) >> 8u;
	//Pegamos Vy (3° byte) e fazemos o shift em 4 casas Ex: 0F0 -> 00F
	uint8_t vy = (chip8->opcode & 0x00F0u) >> 4u;

	//Setamos o flag byte de for maior do que 255
	chip8->registers[FLAG_LOCATION] = chip8->registers[vx] > chip8->registers[vy] ? 1 : 0;
	//Fazemos a subtracao
	chip8->registers[vx] -= chip8->registers[vy];
}

void OP_8xy6(Chip8* chip8)
{
	//Pegamos Vx (2° byte) e fazemos o shift em 8 casas Ex: F00 -> 00F
	uint8_t vx = (chip8->opcode & 0x0F00u) >> 8u;

	//Setamos o flag byte se o ultimo bit de for 1;
	chip8->registers[FLAG_LOCATION] = chip8->registers[vx] & 0x1u;
	//Fazemos o shift right
	chip8->registers[vx] >>= 1;
}

void OP_8xy7(Chip8* chip8)
{
	//Pegamos Vx (2° byte) e fazemos o shift em 8 casas Ex: F00 -> 00F
	uint8_t vx = (chip8->opcode & 0x0F00u) >> 8u;
	//Pegamos Vy (3° byte) e fazemos o shift em 4 casas Ex: 0F0 -> 00F
	uint8_t vy = (chip8->opcode & 0x00F0u) >> 4u;

	//Setamos o flag byte de for maior do que 255
	chip8->registers[FLAG_LOCATION] = chip8->registers[vy] > chip8->registers[vx] ? 1 : 0;
	//Fazemos a subtracao
	chip8->registers[vx] = chip8->registers[vy] - chip8->registers[vx];
}

void OP_8xyE(Chip8* chip8)
{
	//Pegamos Vx (2° byte) e fazemos o shift em 8 casas Ex: F00 -> 00F
	uint8_t vx = (chip8->opcode & 0x0F00u) >> 8u;

	//Setamos o flag byte se o primeiro bit for 1
	chip8->registers[FLAG_LOCATION] = (chip8->registers[vx] & 0x80u) >> 7u;
	//Fazemos o shift left
	chip8->registers[vx] <<= 1;
}

void OP_9xy0(Chip8* chip8)
{
	//Pegamos Vx (2° byte) e fazemos o shift em 8 casas Ex: F00 -> 00F
	uint8_t vx = (chip8->opcode & 0x0F00u) >> 8u;
	//Pegamos Vy (3° byte) e fazemos o shift em 4 casas Ex: 0F0 -> 00F
	uint8_t vy = (chip8->opcode & 0x00F0u) >> 4u;

	//Pulamos a proxima instrucao
	if (chip8->registers[vx] != chip8->registers[vy]) chip8->pc += 2;
}

void OP_Annn(Chip8* chip8)
{
	//0x0FFFu eh uma mascara de bit para obtemos o valor do endereco pegando os 3 ultimos byte do codigo
	uint16_t address = chip8->opcode & 0x0FFFu;
	chip8->index = address;
}

void OP_Bnnn(Chip8* chip8)
{
	//0x0FFFu eh uma mascara de bit para obtemos o valor do endereco pegando os 3 ultimos byte do codigo
	uint16_t address = chip8->opcode & 0x0FFFu;
	chip8->pc = chip8->registers[0] + address;
}

void OP_Cxkk(Chip8* chip8)
{
	//Pegamos Vx (2° byte) e fazemos o shift em 8 casas Ex: F00 -> 00F
	uint8_t vx = (chip8->opcode & 0x0F00u) >> 8u;
	//Pegamos kk (3° e 4° bytes)
	uint8_t val = (chip8->opcode & 0x00FFu);
	//Geramos um numero aleatorio
	uint8_t random = rand() % 256;

	chip8->registers[vx] = val & random;
}

void OP_Dxyn(Chip8* chip8)
{
	//Pegamos Vx (2° byte) e fazemos o shift em 8 casas Ex: F00 -> 00F
	uint8_t vx = (chip8->opcode & 0x0F00u) >> 8u;
	//Pegamos Vy (3° byte) e fazemos o shift em 4 casas Ex: 0F0 -> 00F
	uint8_t vy = (chip8->opcode & 0x00F0u) >> 4u;
	//Pegamos n  (4° byte) (altura do sprite)
	uint8_t n =  (chip8->opcode & 0x000Fu);

	//Caso usamos o modulo para garantir queo valor sempre estara dentro da tela
	uint8_t x_pos = chip8->registers[vx] % WIDTH;
	uint8_t y_pos = chip8->registers[vy] % HEIGHT;

	//Flag byte = 0
	chip8->registers[FLAG_LOCATION] = 0;
	for (int y = 0; y < n; y++) 
	{
		//Pegamos o sprite que desejamos desenhar da memoria
		uint8_t sprite = chip8->memory[chip8->index + y];
		for (int x = 0; x < 8; x++) 
		{
			//Verificamos se o pixel deve ser desenhado
			if (sprite & (0x80u >> x))
			{
				//Pegamos o pixel atual da tela
				uint32_t* screenPixel = &chip8->screen[(y_pos + y) * WIDTH + (x_pos + x)];
				
				//Verificamos se o pixel atual da tela esta ligado (branco), se estiver o flag byte = 1
				if (*screenPixel == 0xFFFFFFFF) chip8->registers[FLAG_LOCATION] = 1;

				//Fazemos o xor do do pixel da tela com ele mesmo
				*screenPixel ^= 0xFFFFFFFF;
			}
		}
	}
}

void OP_Ex9E(Chip8* chip8)
{
	//Pegamos Vx (2° byte) e fazemos o shift em 8 casas Ex: F00 -> 00F
	uint8_t vx = (chip8->opcode & 0x0F00u) >> 8u;
	//Pegamos o valor da tecla que queremos verificar
	uint8_t key = chip8->registers[vx];
	if (chip8->keyboard[key]) chip8->pc += 2;
}

void OP_ExA1(Chip8* chip8)
{
	//Pegamos Vx (2° byte) e fazemos o shift em 8 casas Ex: F00 -> 00F
	uint8_t vx = (chip8->opcode & 0x0F00u) >> 8u;
	//Pegamos o valor da tecla que queremos verificar
	uint8_t key = chip8->registers[vx];
	if (!chip8->keyboard[key]) chip8->pc += 2;
}

void OP_Fx07(Chip8* chip8)
{
	//Pegamos Vx (2° byte) e fazemos o shift em 8 casas Ex: F00 -> 00F
	uint8_t vx = (chip8->opcode & 0x0F00u) >> 8u;
	chip8->registers[vx] = chip8->delay_timer;
}

void OP_Fx0A(Chip8* chip8)
{
	//Pegamos Vx (2° byte) e fazemos o shift em 8 casas Ex: F00 -> 00F
	uint8_t vx = (chip8->opcode & 0x0F00u) >> 8u;

	//Faz a leitura de uma tecla
	if      (chip8->keyboard[0])  chip8->registers[vx] = 0;
	else if (chip8->keyboard[1])  chip8->registers[vx] = 1;
	else if (chip8->keyboard[2])  chip8->registers[vx] = 2;
	else if (chip8->keyboard[3])  chip8->registers[vx] = 3;
	else if (chip8->keyboard[4])  chip8->registers[vx] = 4;
	else if (chip8->keyboard[5])  chip8->registers[vx] = 5;
	else if (chip8->keyboard[6])  chip8->registers[vx] = 6;
	else if (chip8->keyboard[7])  chip8->registers[vx] = 7;
	else if (chip8->keyboard[8])  chip8->registers[vx] = 8;
	else if (chip8->keyboard[9])  chip8->registers[vx] = 9;
	else if (chip8->keyboard[10]) chip8->registers[vx] = 10;
	else if (chip8->keyboard[11]) chip8->registers[vx] = 11;
	else if (chip8->keyboard[12]) chip8->registers[vx] = 12;
	else if (chip8->keyboard[13]) chip8->registers[vx] = 13;
	else if (chip8->keyboard[14]) chip8->registers[vx] = 14;
	else if (chip8->keyboard[15]) chip8->registers[vx] = 15;
	else chip8->pc -= 2; //Cria um loop infinito esperando um tecla ser clicada
}

void OP_Fx15(Chip8* chip8)
{
	//Pegamos Vx (2° byte) e fazemos o shift em 8 casas Ex: F00 -> 00F
	uint8_t vx = (chip8->opcode & 0x0F00u) >> 8u;
	chip8->delay_timer = chip8->registers[vx];
}

void OP_Fx18(Chip8* chip8)
{
	//Pegamos Vx (2° byte) e fazemos o shift em 8 casas Ex: F00 -> 00F
	uint8_t vx = (chip8->opcode & 0x0F00u) >> 8u;
	chip8->sound_timer = chip8->registers[vx];
}

void OP_Fx1E(Chip8* chip8)
{
	//Pegamos Vx (2° byte) e fazemos o shift em 8 casas Ex: F00 -> 00F
	uint8_t vx = (chip8->opcode & 0x0F00u) >> 8u;
	chip8->index += chip8->registers[vx];
}

void OP_Fx29(Chip8* chip8)
{
	//Pegamos Vx (2° byte) e fazemos o shift em 8 casas Ex: F00 -> 00F
	uint8_t vx = (chip8->opcode & 0x0F00u) >> 8u;
	uint8_t digit = chip8->registers[vx];
	//Fazemos o endereco base + 5 * digito, usamos 5, pois sabemos que cada caracter tem o tamanho de 5 bytes
	chip8->index = FONTSET_START_ADDRESS + (5 * digit);
}

void OP_Fx33(Chip8* chip8)
{
	//Pegamos Vx (2° byte) e fazemos o shift em 8 casas Ex: F00 -> 00F
	uint8_t vx = (chip8->opcode & 0x0F00u) >> 8u;
	uint8_t val = chip8->registers[vx];

	uint8_t index = chip8->index;

	//Digito da unidade
	chip8->memory[index + 2] = val % 10;
	val /= 10;

	//Digito da dezena
	chip8->memory[index + 1] = val % 10;
	val /= 10;

	//Digito da centena
	chip8->memory[index] = val % 10;
}

void OP_Fx55(Chip8* chip8)
{
	//Pegamos Vx (2° byte) e fazemos o shift em 8 casas Ex: F00 -> 00F
	uint8_t vx = (chip8->opcode & 0x0F00u) >> 8u;

	//Copiamos o conteudo do array de registros para a memoria, incluindo o registro passado, por isso o + 1
	for (uint8_t i = 0; i <= vx; i++)
		chip8->memory[chip8->index + i] = chip8->registers[i];
	//memcpy(&chip8->memory[chip8->index], chip8->registers, (vx + 1));
}

void OP_Fx65(Chip8* chip8)
{
	//Pegamos Vx (2° byte) e fazemos o shift em 8 casas Ex: F00 -> 00F
	uint8_t vx = (chip8->opcode & 0x0F00u) >> 8u;

	//Copiamos o conteudo do array de registros para a memoria, incluindo o registro passado, por isso o + 1
	//memcpy(chip8->registers, &chip8->memory[chip8->index], (vx + 1));
	for (uint8_t i = 0; i <= vx; i++)
		chip8->registers[i] = chip8->memory[chip8->index + i];
}


//Ciclo
void cycle(Chip8* chip8)
{
	//Fetch
	chip8->opcode = (chip8->memory[chip8->pc] << 8u) | chip8->memory[chip8->pc + 1];

	//Preparando o program counter para proxima instrucao
	chip8->pc += 2;

	//Decode e Execute
	//Despachamos para a tabela principal que em seguida ou sera executado ou despachado para outra tabela
	table[(chip8->opcode & 0xF000u) >> 12u](chip8);

	//Decrementa o delay e sound se foram setados pela instrucao executada
	if (chip8->delay_timer > 0) chip8->delay_timer--;
	if (chip8->sound_timer > 0) chip8->sound_timer--;
}
