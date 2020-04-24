#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>


int main(void) {
    bool quit_flag = false;
    const char win_title[] = "SDL window title";
    const int WIN_WIDTH = 640;
    const int WIN_HEIGHT = 580;

    int mX, mY; // 当前鼠标所在位置的窗口坐标

    int x = 288;
    int y = 208;

    SDL_Window *win = NULL;
    SDL_Surface *surface = NULL;
    SDL_Surface *img = NULL;
    SDL_Event e;

    if( SDL_Init(SDL_INIT_VIDEO) != 0 ) {
        fprintf(stderr, "could not initialize sdl2, error: %s\n", SDL_GetError());
        exit(-1);
    }

    win = SDL_CreateWindow(win_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_RESIZABLE);
    if( win == NULL ) {
        fprintf(stderr, "SDL create window error: %s\n", SDL_GetError());
        SDL_Quit();
        exit(-1);
    }

    img = SDL_LoadBMP("./spaceship.bmp");
    if( img == NULL ) {
        fprintf(stderr, "sdl load bmp file error: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        exit(-1);
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, 0);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, img);

    SDL_FreeSurface(img);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    while( !quit_flag ) {
        while( SDL_PollEvent(&e) ) {
            switch( e.type )
            {
                case SDL_QUIT:
                    quit_flag = true;
                    break;
                case SDL_KEYDOWN:
                    switch( e.key.keysym.sym )
                    {
                        case SDLK_LEFT:     x--; break;
                        case SDLK_RIGHT:    x++; break;
                        case SDLK_UP:       y--; break;
                        case SDLK_DOWN:  y++; break;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    switch( e.button.button )
                    {
                        case SDL_BUTTON_LEFT:
                            SDL_ShowSimpleMessageBox(0, "Mouse events", "Left button was pressed!", win);
                            break;
                        case SDL_BUTTON_RIGHT:
                            SDL_ShowSimpleMessageBox(0, "Mouse events", "Right button was pressed!", win);
                            break;
                        default:
                            SDL_ShowSimpleMessageBox(0, "Mouse events", "Some other button was pressed!", win);
                            break;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    //int mX = e.motion.x; // 变量不能定义在这里
                    //int mY = e.motion.y;
                    //printf(" y%d\n", mY);
                    SDL_GetMouseState(&mX, &mY);
                    printf("Mouse motion events X: %d, Y: %d \n", mX, mY);
                    break;
            }

            SDL_Rect dstrect = {x, y, 64, 64};
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, texture, NULL, &dstrect);
            SDL_RenderPresent(renderer);
        }
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}
