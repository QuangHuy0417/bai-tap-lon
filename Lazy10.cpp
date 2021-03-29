#include<iostream>
#include<string>
#include<SDL.h>
#include<SDL_image.h>
#include<stdio.h>
using namespace std;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class LTexture
{
public:
	LTexture();
	~LTexture();
	bool loadFromFile(string path);
	void render(int x,int y);
	void free();
	int getWidth();
	int getHeight();
private:
	SDL_Texture* mTexture ;
	int mWidth;
	int mHeight;
};

bool init();
bool loadMedia();
void close();

SDL_Renderer* gRenderer = NULL;
SDL_Window* gWindow = NULL;
LTexture gFooTexture;
LTexture gBackgroundTexture;

LTexture:: LTexture()
{
	mTexture=NULL;
	mWidth = 0;
	mHeight = 0;
}
LTexture::~LTexture()
{
	free();
}
void LTexture::render(int x,int y)
{	
	SDL_Rect renderQuad = { x,y,mWidth,mHeight };
	SDL_RenderCopy(gRenderer, mTexture, NULL, &renderQuad);
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
	return mTexture!=NULL;
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
		cout << "SDL could not initialize!\n";
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
			gWindow = SDL_CreateWindow("Color Keying", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
					SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
					int imgFlags = IMG_INIT_PNG;
					if (!(IMG_Init(imgFlags) & imgFlags))
					{
						cout << "SDL_image could not initialize!\n";
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
	if (!gFooTexture.loadFromFile("foo.png"))
	{
		cout<<"Failed to load Foo image!\n";
			success=false;
	}
	if (!gBackgroundTexture.loadFromFile("background.png"))
	{
		cout << "Failed to load Background image!\n";
		success = false;
	}
	return success;
}
void close()
{
	gFooTexture.free();
	gBackgroundTexture.free();
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	IMG_Quit();
	SDL_Quit();
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

				gBackgroundTexture.render(0, 0);
				gFooTexture.render(240, 190);
				SDL_RenderPresent(gRenderer);
			}
		}
	}
	close();
	return 0;
}
