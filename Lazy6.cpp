#include<iostream>
#include<string>
#include<SDL.h>
#include<stdio.h>
#include<SDL_image.h>
using namespace std;
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 800;

bool init();
bool loadMedia();
void close();

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* loadSurface(string path);
SDL_Surface* gPNGSurface = NULL;

bool init()
{
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL couldn't to initialize!\n";
		success = false;
	}
	else
	{
		gWindow = SDL_CreateWindow("PNGLoaded", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			cout << "Window not be created!\n";
			success = false;
		}
		else
		{
			int imgFlags =IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags))
			{
				cout << "SDL_image couldn't initialized!\n";
				success = false;
			}
			else
			{
				gScreenSurface = SDL_GetWindowSurface(gWindow);
			}
		}
	}
	return success;
}

bool loadMedia()
{
	bool success = true;
	gPNGSurface = loadSurface("loaded.png");
	if (gPNGSurface == NULL)
	{
		cout << "Failed to load PNGimage!\n";
		success = false;
	}
	return success;
}

void close()
{
	SDL_FreeSurface(gPNGSurface);
	gPNGSurface = NULL;
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	IMG_Quit;
	SDL_Quit;
}

SDL_Surface* loadSurface(string path)
{
	SDL_Surface* optimizedSurface = NULL;
	SDL_Surface* loadSurface = IMG_Load(path.c_str());
	if (loadSurface == NULL)
	{
		cout << "Unable load image!\n";
	}
	else
	{
		optimizedSurface = SDL_ConvertSurface(loadSurface, gScreenSurface->format, 0);
		if (optimizedSurface == NULL)
		{
			cout << "Unable to optimize image!\n";
		}
		SDL_FreeSurface(loadSurface);
	}
	return optimizedSurface;
}

int main(int argc, char* args[])
{
	if (!init())
	{
		cout << "failed to initalize!\n";
	}
	else
	{
		if (!loadMedia())
		{
			cout << "failed to loadMedia!\n";
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
					else if (e.type == SDL_MOUSEBUTTONDOWN)
					{
						if (e.button.button == SDL_BUTTON_RIGHT)
						{
							quit = true;
						}
					}
				}
				SDL_Rect stretchedRect;
				stretchedRect.x = 0;
				stretchedRect.y = 0;
				stretchedRect.w = SDL_WIDTH;
				stretchedRect.h = SDL_HIGH;
				SDL_BlitSurface(gPNGSurface, NULL, gScreenSurface, NULL);
				SDL_BlitScaled(gPNGSurface, NULL, gScreenSurface, NULL);
				SDL_UpdateWindowSurface(gWindow);
			}
		}
	}
	close();
	return 0;
}