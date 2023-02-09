#include <iostream>
#include<SDL.h>
#undef main

#include<SDL_image.h>

SDL_Window* gWindow;
SDL_Renderer* gRenderer;
SDL_Surface* srfImg;
SDL_Texture* srfTex;
SDL_Surface* srfSprite;
SDL_Texture* texSprite;
SDL_Event evt;


const int FPS = 60;
const int FRAME_DELAY = 1000 / FPS;

bool isRunning;

int main()
{
	SDL_Rect src, dst;
	src.x = src.y = 0;
	src.w = src.h = 230;
	dst.x = dst.y = 0;
	dst.w = dst.h = 230;

	isRunning = true;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		gWindow = SDL_CreateWindow("random title", 100, 100, 1024, 768, 0);
		if (!gWindow) {
			isRunning = false;
		}
		gRenderer = SDL_CreateRenderer(gWindow, -1, 0);
		if (!gRenderer) {
			isRunning = false;
		}
		srfImg = IMG_Load("assets/player.png");
		srfTex = SDL_CreateTextureFromSurface(gRenderer, srfImg);
		SDL_FreeSurface(srfImg);

		srfSprite = IMG_Load("assets/sprite.png");
		texSprite = SDL_CreateTextureFromSurface(gRenderer, srfSprite);
		SDL_FreeSurface(srfSprite);

		int counter=0;
		while (isRunning) {
			int A = SDL_GetTicks();
			//
			SDL_PollEvent(&evt);
			switch (evt.type) {
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_KEYDOWN:
				// std::cout << "code = " << evt.key.keysym.sym << " key name = " <<  SDL_GetKeyName(evt.key.keysym.sym) << "\n";
				if (evt.key.keysym.sym == 27)
				{
					isRunning = false;
				}
				if (evt.key.keysym.sym == 1073741903) {
					dst.x += 32;
				}
				if (evt.key.keysym.sym == 1073741904) {
					dst.x -= 32;
				}
				if (evt.key.keysym.sym == 1073741906) {
					dst.y -= 32;
				}
				if (evt.key.keysym.sym == 1073741905) {
					dst.y += 32;
				}
				break;
			default:
				break;
			}

			SDL_RenderClear(gRenderer);
			SDL_RenderCopy(gRenderer, srfTex, &src, &dst);

			SDL_Rect src2, dst2;
			src2.x = (counter%8)*32;
			src2.y = 0;
			src2.w = src2.h = 32;
			dst2.x = dst2.y = 400;
			dst2.w = dst2.h = 230;
			SDL_RenderCopy(gRenderer, texSprite, &src2, &dst2);

			SDL_RenderPresent(gRenderer);

			//
			int B = SDL_GetTicks();
			int timeTaken = B - A;
			if (timeTaken < FRAME_DELAY) {
				SDL_Delay(FRAME_DELAY - timeTaken);
			}
			counter++;
		}		
	}

	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);

	std::cout << "sdl window closed\n";
	system("pause");

	return 0;
}