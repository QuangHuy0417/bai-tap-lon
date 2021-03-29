#include<iostream>
#include<string>
#include<SDL.h>
#include<SDL_image.h>
#include<stdio.h>
using namespace std;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
bool loadMedia();
void close();

SDL_Texture* loadTexture(string path);
SDL_Window* gWindow = NULL;
SDL_Texture* gTexture = NULL;
SDL_Renderer* gRenderer = NULL;

bool init()
{
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL couldn't to initialized!\n";
		success = false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1"))
		{
			cout<<"Warning: Linear texture filter not enalble!\n";
		}
		else
		{
			gWindow = SDL_CreateWindow("LAZY7", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH, SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
				if (gWindow == NULL)
				{
					cout << "Window no be created!\n";
						success = false;
				}
				else
				{
					gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
					if (gRenderer == NULL)
					{
						cout << "Renderer not be created!\n";
						success = false;
					}
					else
					{
						SDL_SetRenderDrawColor(gRenderer, 0,255,255,255);
						int imgFlags=IMG_INIT_PNG;
						if (!(IMG_Init(imgFlags) & imgFlags))
						{
							cout << "SDL_image couldn't initialized!\n";
							success = false;
						}

					}
				}
		}
	}
	return success;
}

bool loadMedia()
{
	bool success = true;
	gTexture = loadTexture("texture.png");
	if (gTexture == NULL)
	{
		cout << "Failed to load texture img!\n";
		success = false;
	}
	return success;
}

void close()
{
	SDL_DestroyTexture(gTexture);
	gTexture = NULL;
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* loadTexture(string path)
{
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		cout << "Unable load image!\n";
	}
	else
	{
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			cout << "Unable to create newTexture!\n";
		}
		SDL_FreeSurface(loadedSurface);
	}
	return newTexture;
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
					else if (e.type == SDL_KEYDOWN)
					{
						quit = true;
					}
				}
				SDL_RenderClear(gRenderer);
				SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);
				SDL_RenderPresent(gRenderer);
			}
		}
	}
	close();
	return 0;
}