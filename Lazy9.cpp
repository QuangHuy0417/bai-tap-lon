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
		cout << "SDL could not initialize!\n";
		success = false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1"))
		{
			cout << "Warning: Linear Texture filtering not enabled!\n";
		}
		else
		{
			gWindow = SDL_CreateWindow("LAZY9", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
					SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
					int imgFlags = IMG_INIT_PNG;
					if (!(IMG_Init(imgFlags)&imgFlags))
					{
						cout << "SDL_image could not initialize!\n";
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
	gTexture = loadTexture("viewport.png");
	if (gTexture == NULL)
	{
		cout << "Unalble to load image!\n";
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
	SDL_Quit();
	IMG_Quit();
}

SDL_Texture* loadTexture(string path)
{
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		cout << "Failed to loadImg!\n";
	}
	else
	{
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			cout << "Unable create newTexture!\n";
		}
		SDL_FreeSurface(loadedSurface);
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
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				SDL_Rect leftViewPort;
				leftViewPort.x = 0;
				leftViewPort.y = 0;
				leftViewPort.w = SCREEN_WIDTH / 2;
				leftViewPort.h = SCREEN_HEIGHT / 2;
				SDL_RenderSetViewport(gRenderer, &leftViewPort);
				SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

				SDL_Rect rightViewPort;
				rightViewPort.x = SCREEN_WIDTH / 2;
				rightViewPort.y = 0;
				rightViewPort.w = SCREEN_WIDTH / 2;
				rightViewPort.h = SCREEN_HEIGHT / 2;
				SDL_RenderSetViewport(gRenderer, &rightViewPort);
				SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

				SDL_Rect bottomViewPort;
				bottomViewPort.x = 0;
				bottomViewPort.y = SCREEN_HEIGHT / 2;
				bottomViewPort.w = SCREEN_WIDTH;
				bottomViewPort.h = SCREEN_HEIGHT / 2;
				SDL_RenderSetViewport(gRenderer, &bottomViewPort);
				SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);
				SDL_RenderPresent(gRenderer);
			}
		}
	}
	close();
	return 0;
}