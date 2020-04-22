#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>


int main(void) {
    const char *win_title = "SDL Window Title";
    const int WIN_WIDTH = 640;
    const int WIN_HEIGHT = 560;

    SDL_Window *win = NULL;
    SDL_Surface *surface = NULL;

    win = SDL_CreateWindow(win_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_RESIZABLE);
    if( win == NULL ) {
        printf("SDL Error: %s\n", SDL_GetError());
    }
    
    surface = SDL_GetWindowSurface(win);
    if( surface == NULL ) {
        printf("SDL Error: %s\n", SDL_GetError());
    }

    SDL_FillRect(surface, NULL, 0xFFFF33);

    SDL_UpdateWindowSurface(win);

    bool event_flag = false;
    SDL_Event e;

    while( !event_flag ) {
        while( SDL_PollEvent(&e) ) {
            if( e.type == SDL_QUIT ) {
                event_flag = true;
            }
        }
    }

    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}
