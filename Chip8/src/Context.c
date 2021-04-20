#include "Context.h"
#include "Chip8.h"

void init_context(Context* context, const char* title, int width, int height)
{
	//Inicializacao do video do SDL
	SDL_Init(SDL_INIT_VIDEO);

	//Criacao de uma janela, renderer e textura
	context->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	context->renderer = SDL_CreateRenderer(context->window, -1, SDL_RENDERER_ACCELERATED);
	context->texture = SDL_CreateTexture(context->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
}

void destroy_context(Context* context)
{
	//Exclusao da janela, renderer e textura
	SDL_DestroyTexture(context->texture);
	SDL_DestroyRenderer(context->renderer);
	SDL_DestroyWindow(context->window);
	SDL_Quit();
}

void update_context(Context* context, const void* buffer, int pitch)
{
	//Update na textura
	SDL_UpdateTexture(context->texture, NULL, buffer, pitch);
	//Limpamos o estado atual do renderer
	SDL_RenderClear(context->renderer);
	//Copiamos os dados da textura para o renderer
	SDL_RenderCopy(context->renderer, context->texture, NULL, NULL);
	//Mostramos na tela
	SDL_RenderPresent(context->renderer);
}

int input_context(Context* context, uint8_t* keys)
{
	int quit = 0;

	//Criamos uma nova instancia de eventos e verificamos se algo foi pressionado pelo usuario
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			//Caso a janela seja fechada
			case SDL_QUIT:
				quit = 1;
			break;

			//Caso uma tela seja pressionada
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						quit = 1;
					break;
					case SDLK_x:
						keys[0] = 1;
					break;
					case SDLK_1:
						keys[1] = 1;
					break;
					case SDLK_2:
						keys[2] = 1;
					break;
					case SDLK_3:
						keys[3] = 1;
					break;
					case SDLK_q:
						keys[4] = 1;
					break;
					case SDLK_w:
						keys[5] = 1;
					break;
					case SDLK_e:
						keys[6] = 1;
					break;
					case SDLK_a:
						keys[7] = 1;
					break;
					case SDLK_s:
						keys[8] = 1;
					break;
					case SDLK_d:
						keys[9] = 1;
					break;
					case SDLK_z:
						keys[0xA] = 1;
					break;
					case SDLK_c:
						keys[0xB] = 1;
					break;
					case SDLK_4:
						keys[0xC] = 1;
					break;
					case SDLK_r:
						keys[0xD] = 1;
					break;
					case SDLK_f:
						keys[0xE] = 1;
					break;
					case SDLK_v:
						keys[0xF] = 1;
					break;
				}
			break;

			//Caso uma tecla seja liberada
			case SDL_KEYUP:
				switch (event.key.keysym.sym)
				{
					case SDLK_x:
						keys[0] = 0;
					break;
					case SDLK_1:
						keys[1] = 0;
					break;
					case SDLK_2:
						keys[2] = 0;
					break;
					case SDLK_3:
						keys[3] = 0;
					break;
					case SDLK_q:
						keys[4] = 0;
					break;
					case SDLK_w:
						keys[5] = 0;
					break;
					case SDLK_e:
						keys[6] = 0;
					break;
					case SDLK_a:
						keys[7] = 0;
					break;
					case SDLK_s:
						keys[8] = 0;
					break;
					case SDLK_d:
						keys[9] = 0;
					break;
					case SDLK_z:
						keys[0xA] = 0;
					break;
					case SDLK_c:
						keys[0xB] = 0;
					break;
					case SDLK_4:
						keys[0xC] = 0;
					break;
					case SDLK_r:
						keys[0xD] = 0;
					break;
					case SDLK_f:
						keys[0xE] = 0;
					break;
					case SDLK_v:
						keys[0xF] = 0;
					break;
				}
			break;
		}
	}

	return quit;
}

