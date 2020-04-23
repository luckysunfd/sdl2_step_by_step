#include <stdio.h>
#include <stdbool.h>
#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>


int main(void) {
    bool success_flag = false;

    const char *SDL_WIN_TITLE = "SDL event demo1";
    const int WIN_WIDTH = 640;
    const int WIN_HEIGHT = 580;

    SDL_Window *win = NULL;
    SDL_Surface *surface = NULL;
    SDL_Event e;
    
    if( SDL_Init(SDL_INIT_VIDEO) != 0 ) {
        fprintf(stderr, "SDL initialize error: %s\n", SDL_GetError());
        exit(-1);
    }

    win = SDL_CreateWindow(SDL_WIN_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_RESIZABLE);
    if(win == NULL) {
       fprintf(stderr, "SDL create window error: %s\n", SDL_GetError());
    }

    surface = SDL_GetWindowSurface(win);
    if(surface == NULL) {
        fprintf(stderr, "SDL get window surface error: %s\n", SDL_GetError());
    }

    SDL_FillRect(surface, NULL, 0xFFFF32);
    SDL_UpdateWindowSurface(win);

    while( !success_flag ) {
        while( SDL_PollEvent(&e) ) {
            switch( e.type )
            {
                case SDL_QUIT:
                    success_flag = true;
                    break;
                case SDL_KEYDOWN:
                    success_flag = true;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    success_flag = true;
                    break;
            }
        }
    }

    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}
