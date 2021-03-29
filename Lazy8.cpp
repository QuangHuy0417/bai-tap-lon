#include<iostream>
#include<string>
#include<SDL.h>
#include<SDL_image.h>
#include<stdio.h>
using namespace std;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

bool init();
bool loadMedia();
void close();

SDL_Texture* loadTexture(string path);
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

bool init()
{
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL couldn't iniyialize!\n";
		success = false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			cout << "Warning: Linear Texture filter not enable!\n";
		}
		else
		{
			gWindow = SDL_CreateWindow("8-GeometryRendering", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
			if (gWindow == NULL)
			{
				cout << "Window not be created!\n";
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
				    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
					int imgFlags = IMG_INIT_PNG;
					if (imgFlags == NULL)
					{
						cout << "SDL_image couldn't initialize!\n";
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
	return success;
}

void close()
{
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	SDL_Quit();
}

SDL_Texture* loadTexture(string path)
{
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadSurface = IMG_Load(path.c_str());
	if (loadSurface == NULL)
	{
		cout << "Failed to load image!\n";
	}
	else
	{
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadSurface);
		if (newTexture == NULL)
		{
			cout << "Unable create newTexture!\n";
		}
		SDL_FreeSurface(loadSurface);
	}
	return newTexture;
}

int main(int argc, char* args[])
{
	if (!init())
	{
		cout << "Failed to initialize!\n";
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
					else if (e.type == SDL_MOUSEBUTTONDOWN)
					{
						quit = true;
					}
				}
				SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
				SDL_RenderClear(gRenderer);

				SDL_Rect fillRect = { SCREEN_WIDTH / 4,SCREEN_HEIGHT / 4,SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2 };
				SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 50);
				SDL_RenderFillRect(gRenderer, &fillRect);

				SDL_Rect outlineRect = { SCREEN_WIDTH / 6,SCREEN_HEIGHT / 6,SCREEN_WIDTH *2/ 3,SCREEN_HEIGHT*2 / 3 };
				SDL_SetRenderDrawColor(gRenderer, 0, 255, 0, 0);
				SDL_RenderDrawRect(gRenderer, &outlineRect);

				SDL_SetRenderDrawColor(gRenderer, 0, 0, 255, 0);
				SDL_RenderDrawLine(gRenderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);

				SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
				for (int i = 0; i < SCREEN_HEIGHT; i =i+4)
				{
					SDL_RenderDrawPoint(gRenderer, SCREEN_WIDTH / 2, i);
				}

				SDL_RenderPresent(gRenderer);
			}
		}
	}
	close();
	return 0;
}