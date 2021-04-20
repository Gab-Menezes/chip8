#ifndef CONTEXT_H
#define CONTEXT_H

#include <SDL.h>

typedef struct
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* texture;
} Context;

void init_context(Context* context, const char* title, int width, int height); //Inicializacao do contexto
void destroy_context(Context* context); //Exclusao do contexto
void update_context(Context* context, const void* buffer, int pitch); //Update visual
int input_context(Context* context, uint8_t* keys); //Inputs do usuario

#endif // !CONTEXT_H
