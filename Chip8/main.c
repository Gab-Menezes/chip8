#include <stdlib.h> 
#include <time.h>
#include <stdio.h>
#include "src/Chip8.h";
#include "src/Context.h";

//Referencias:
//https://austinmorlan.com/posts/chip8_emulator/
//https://github.com/cookerlyk/Chip8
//https://github.com/gsamokovarov/chip8.c

int main()
{	
	//Numeros aleatorios a cada inicializacao do programa
	srand(time(NULL));

	printf("Bem vindo(a)\n\n");
	printf("-> Este programa eh um emulador de chip8 (um famoso intepretador de codigo).\n-> Para utiliza-lo eh necessario ter uma ROM (.ch8) de algum programa/jogo.\n-> Sera perguntado a escala de resoluca, este numero sera utilizado para redimensionar o tamanho da tela para monitores atuais, qualquer numero entre 5 e 20 deve ser o suficiente\n-> Sera perguntado o delay este numero pode variar de ROM para ROM entao va alterando ate o que achar melhpr (Normalmente entre 1ms e 10ms)\n\nDivita-se!!\n\n");

	//Nome do arquivo a ser carregado
	const char* rom[256];
	printf("Insira o nome do arquivo: ");
	scanf("%s", rom);
	//Escala de video, necessario devido aos monitores atuais
	int scale;
	printf("Insira a escala de resolucao: ");
	scanf("%i", &scale);
	//Delay em ms de cada ciclo
	int delay;
	printf("Insira o delay em ms: ");
	scanf("%i", &delay);
	printf("\n\n");


	//Criacao do contexo
	Context context; 
	init_context(&context, "Emulador CHIP-8", WIDTH * scale, HEIGHT * scale);

	//Criacao do chip8 e carregamento da ROM
	Chip8 chip8;
	init_chip8(&chip8);
	load_rom(&chip8, rom);

	//Numero de bytes em sequencia
	int videoPitch = sizeof(chip8.screen[0]) * WIDTH;

	//Emulacao do clock
	clock_t begin = clock();

	//Loop principal
	int quit = 0;
	while (!quit)
	{
		//Inputs do usuario
		quit = input_context(&context, &chip8.keyboard);

		//Update na emulacao do clock
		clock_t end = clock();
		float dt = (end - begin) / (CLOCKS_PER_SEC / 1000.f);

		//Assim que dt for maior do que o delay executamos o codigo, assim emulando um ciclo
		if (dt > delay)
		{
			//Update no tempo, preparando para o proximo ciclo
			begin = end;

			//Ciclo do chip8
			cycle(&chip8);

			//Update visual
			update_context(&context, chip8.screen, videoPitch);
		}
	}

	//Destruimos o contexto para evitar vazamento de memoria
	destroy_context(&context);

	return 0;
}