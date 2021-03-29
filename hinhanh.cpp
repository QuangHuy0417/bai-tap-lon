#include <SDL.h>
#include <SDL_image.h>
//#include<SDL_mixer.h>
//#include<SDL_ttf.h>

SDL_Window* g_windows = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* g_background = NULL;

bool loadImage() {
	g_background = IMG_Load("meo.jpg");
	if (g_background != NULL) return true;
	return false;
}
void close() {
	SDL_FreeSurface(g_background);
	g_background = NULL;
	SDL_DestroyWindow(g_windows);
	g_windows = NULL;
	SDL_Quit();
}
bool init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) {
		g_windows = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 720, 720, SDL_WINDOW_SHOWN);
		if (g_windows != NULL) {
			gScreenSurface = SDL_GetWindowSurface(g_windows);
		}
	}
	return true;
}
int main(int argc, char* argv[]) {
	if (init() == true) {
		if (loadImage()) {
			SDL_BlitSurface(g_background, NULL, gScreenSurface, NULL);
			SDL_UpdateWindowSurface(g_windows);
			SDL_Delay(10000);
		}
	}
	close();
	return 0;
}