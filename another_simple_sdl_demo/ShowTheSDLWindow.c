#include <stdio.h>
#include <stdlib.h>

#define SDL_MAIN_HANDLED
#include "SDL2/SDL.h"


#define SCREEN_W 640
#define SCREEN_H 580
#define SCREEN_SCALE 1
#define WIN_TITLE "Play Play Play"


void Play_Init(void);
void Play_Quit(void);


struct {
    SDL_bool running;
    struct {
        unsigned int w;
        unsigned int h;
        const char *win_title;
        SDL_Window *win;
        SDL_Renderer *render;
    } screen;

    void (*ptr_init_func)(void);
    void (*ptr_quit_func)(void);
} Play = {
    SDL_FALSE,
    {
        SCREEN_SCALE*SCREEN_W,
        SCREEN_SCALE*SCREEN_H,
        WIN_TITLE,
        NULL,
        NULL
    },
    Play_Init,
    Play_Quit
};



int main(int argc, char **argv) {
    Play.ptr_init_func();

    SDL_Event event;

    while( Play.running ) {
        while( SDL_PollEvent(&event) ) {
            switch(event.type) 
            {
                case SDL_QUIT:
                    Play.running = SDL_FALSE;
                    break;
                default:
                    break;
            }
        }

        SDL_RenderClear(Play.screen.render);
        SDL_RenderPresent(Play.screen.render);
    }

    Play.ptr_quit_func();

    return 0;
}




void Play_Init(void) {
    puts("Init SDL2...");

    if( SDL_Init(SDL_INIT_VIDEO) != 0 ) {
        fprintf(stderr, "SDL Error: %s\n" , SDL_GetError());
        exit(1);
    }

    unsigned int win_width = Play.screen.w;
    unsigned int win_height = Play.screen.h;
    const char *win_title = Play.screen.win_title;

    Play.screen.win = SDL_CreateWindow(
                win_title,
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                win_width,
                win_height,
                SDL_WINDOW_SHOWN
            );

    Play.screen.render = SDL_CreateRenderer(
                Play.screen.win, -1,
                SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
            );

    Play.running = SDL_TRUE;
}


void Play_Quit(void) {
    puts("SDL_Quit...");
    SDL_DestroyRenderer(Play.screen.render);
    SDL_DestroyWindow(Play.screen.win);

    Play.screen.win = NULL;
    Play.screen.render = NULL;

    SDL_Quit();
}

