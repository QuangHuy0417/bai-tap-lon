#include<iostream>
#include<SDL.h>
using namespace std;
int main(int argc,char* args[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		cout << "Happy new year" << endl;
		cout << "Try to learn very well,my family is happy and heathy" << endl;
		cout << "Get scholarship in new year and fass subject and become a excellent developer" << endl;
	}
		return 0;
}