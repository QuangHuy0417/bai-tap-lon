/*#include<iostream>
#include<string>
#include<SDL.h>
#include<SDL_image.h>
#include<stdio.h>
using namespace std;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;


class LTexture
{
	public:
		LTexture();
		~LTexture();
		bool loadFromFile(string path);
		void free();
		void render(int x,int y,SDL_Rect* clip=NULL);
		void setColor(Uint8 red, Uint8 green, Uint8 blue);
		int getWidth();
		int getHeight();
   private:
	   SDL_Texture* mTexture;
	   int mWidth;
	   int mHeight;
};

bool init();
bool loadMedia();
void close();

SDL_Renderer* gRenderer = NULL;
SDL_Window* gWindow = NULL;
LTexture gColorModulation;

LTexture::LTexture()
{
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}
LTexture::~LTexture()
{
	free();
}
bool LTexture::loadFromFile(string path)
{
	free();
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		cout << "Unable to load image!\n";
	}
	else
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 255, 255));
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			cout << "Unable to create newTexture!\n";
		}
		else
		{
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}
	mTexture = newTexture;
	return mTexture != NULL;
}
void LTexture::free()
{
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}
void LTexture::render(int x, int y, SDL_Rect* clip)
{
	SDL_Rect renderQuad = { x,y,mWidth,mHeight };
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad);
}
void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}
int LTexture::getWidth()
{
	return mWidth;
}
int LTexture::getHeight()
{
	return mHeight;
}

bool init()
{
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL couldn't initialize!\n";
		success = false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			cout << "Warning:Linear texture filtering not enable!\n";
		}
		else
		{
			gWindow = SDL_CreateWindow("ColorModulation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
			if (gWindow == NULL)
			{
				cout << "Window couldnt' be created!\n";
				success = false;
			}
			else
			{
				gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
				if (gRenderer == NULL)
				{
					cout << "Renderer couldn't be created!\n";
					success = false;
				}
				else
				{
					SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
					int imgFlags = IMG_INIT_PNG;
					if (!(IMG_Init(imgFlags) & imgFlags))
					{
						cout << "SDL_image couldn't initalize!\n";
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
	if (!gColorModulation.loadFromFile("colors.png"))
	{
		cout << "Failed to loadFromFile!\n";
		success = false;
	}
	return success;
}
void close()
{
	gColorModulation.free();
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	SDL_Quit();
	IMG_Quit();
}
int main(int argc, char* args[])
{
	if (!init())
	{
		cout << "failed to load initialzie!\n";
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
			Uint8 r = 255;
			Uint8 g = 255;
			Uint8 b = 255;
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
						switch (e.key.keysym.sym)
						{
						case SDLK_q:
							r += 32;
							break;
						case SDLK_w:
							g += 32;
							break;
						case SDLK_e:
							b += 32;
							break;
						case SDLK_a:
							r -= 32;
							break;
						case SDLK_s:
							g -= 32;
							break;
						case SDLK_d:
							b -= 32;
							break;

						}
					}
				}
				SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
				SDL_RenderClear(gRenderer);

				gColorModulation.setColor(r, g, b);
				gColorModulation.render(0, 0);
				SDL_RenderPresent(gRenderer);
			}
		}
	}
	close();
	return 0;
}*/