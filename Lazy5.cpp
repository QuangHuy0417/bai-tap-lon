#include<iostream>
#include<string>
#include<SDL.h>
#include<stdio.h>
using namespace std;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* loadSurface(string path);
SDL_Surface* gStretchedSurface = NULL;

bool init();
bool loadMedia();
void close();

bool init()
{
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL COULDN'T TO INITIALIZE!\n";
		success = false;
	}
	else
	{
		gWindow = SDL_CreateWindow("LAZYFOO5", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			cout << "Window couldn't to be created!\n";
			success = false;
		}
		else
		{
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}
	return success;
}

bool loadMedia()
{
	bool success = true;
	gStretchedSurface = SDL_LoadBMP("stretch.bmp");
	if (gStretchedSurface == NULL)
	{
		cout << "error to open image!\n";
		success = false;
	}
	return success;
}

void close()
{
	SDL_FreeSurface(gStretchedSurface);
	gStretchedSurface = NULL;
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	SDL_Quit();
}

SDL_Surface* loadSurface (string path)
{
	SDL_Surface* optimizedSurface = NULL;
	SDL_Surface* loadSurface = SDL_LoadBMP(path.c_str());
	if (loadSurface == NULL)
	{
		cout << "Unable to load Media!\n";
	}
	else
	{
		optimizedSurface = SDL_ConvertSurface(loadSurface, gScreenSurface->format, 0);
		if (optimizedSurface == NULL)
		{
			cout << "Unable to optimized image!\n";
		}
		SDL_FreeSurface(loadSurface);
	}
	return optimizedSurface;
}

int main(int argc, char* args[])
{
	if (!init())
	{
		cout << "Failed to initialized!\n";
	}
	else
	{
		if (!loadMedia())
		{
			cout << "Failed to loadMedia!\n";
		}
		else
		{
			bool quit = false;
			SDL_Event e;
			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
				}
				SDL_Rect strecthRect;
				strecthRect.x = 0;
				strecthRect.y = 0;
				strecthRect.w = 640;
				strecthRect.h = 480;
				SDL_BlitScaled(gStretchedSurface, NULL, gScreenSurface, NULL);
				SDL_UpdateWindowSurface(gWindow);
			}
		}
	}
	close();
	return 0;
}