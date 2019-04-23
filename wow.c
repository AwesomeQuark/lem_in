#include "/Users/conoel/.brew/include/SDL2/SDL.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#define WINDOW_W 800
#define WINDOW_H 800
#define PRECISION 0.001
#define PI 3.14159265
#define LINES 2000

static int		sdl_start(SDL_Window **win, SDL_Renderer **ren)
{
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		printf("Erreur d'initialisation de la SDL : %s",SDL_GetError());
		return 0;
	}
	if (!(*win = SDL_CreateWindow("Mes couilles", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_W, WINDOW_H, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE )))
	{
		printf("Erreur de creation de fenetre de la SDL : %s",SDL_GetError());
		return 0;
	}
	if (!(*ren = SDL_CreateRenderer(*win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)))
	{
		printf("Erreur de creation de renderer de la SDL : %s",SDL_GetError());
		return 0;
	}
	SDL_SetRenderDrawColor(*ren, 255, 255, 255, 255);
	SDL_RenderClear(*ren);
	SDL_RenderPresent(*ren);
	return (1);
}

static void	draw(SDL_Window *fenetre, SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor(renderer,0,0,0,255);
	for(double i = 0.0; i < 360; i+= PRECISION)
		SDL_RenderDrawPoint(renderer,WINDOW_W /2 - cos(i)*WINDOW_W / 2,WINDOW_H / 2 - sin(i)* WINDOW_H / 2);
	srand(time(NULL));
	SDL_Point octogone[LINES];
	for(int i = 0; i < LINES; i++)
	{
		int a = rand();
		octogone[i].x = WINDOW_W /2 - cos(a*45*PI/180)*WINDOW_W / 2;
		octogone[i].y = WINDOW_H /2 - sin(a*45*PI/180)*WINDOW_H / 2;
	}
	if ( SDL_RenderDrawLines(renderer, octogone, LINES)<0)
	{
		printf("Erreur dans le tracé de l'octogone : %s",SDL_GetError());
		exit(EXIT_FAILURE);
	}
	SDL_RenderPresent(renderer);
}

int main(int argc, char *argv[])
{
	SDL_Window* fenetre;
	SDL_Renderer* renderer;

	sdl_start(&fenetre, &renderer);
	draw(fenetre, renderer);

}