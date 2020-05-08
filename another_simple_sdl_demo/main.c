#include <stdio.h>
#include <stdlib.h>
/* this line here tells sdl2 that we won't be needing any special entry point for our program.
 * we'll be handling the entry and library initiation our-selves within int main(int argc, char **argv);
 */
#define SDL_MAIN_HANDLED
/* this line provides references to all the SDL2 functions and variables we will be using.  */
#include "SDL2/SDL.h"


void My_SDL_Init(void);
void My_SDL_Quit(void);

/* this provides us with a global defined custom object which will used to house all persistent relation information. doing things this way will help cut down on function parameters. which can easily get out-of-hand if not kept in check  */
static struct {
    /* define "attributes" */
    SDL_bool running;

    /* define "methods" */
    void (*ptr_init_func)(void);
    void (*ptr_quit_func)(void);
} My_SDL = {
    SDL_FALSE,
    My_SDL_Init,
    My_SDL_Quit
};


/* 仅做sdl初始化以及设置 正在运行 标识状态 */
void My_SDL_Init(void) {
    puts("SDL init");

    /* 应该加一个是否初始化成功的判断, 并打印未初始化成功的原因，即是什么导致了sdl未初始化成功呢？ */
    if( SDL_Init(SDL_INIT_VIDEO) != 0 ) {
        fprintf(stderr, "SDL_ERROR -> %s\n", SDL_GetError());
        exit(1);
    }

    My_SDL.running = SDL_TRUE;
}

/* 不做资源的释放，在调用之前，需要自己释放占用的资源 */
void My_SDL_Quit(void) {
    puts("SDL quit");

    SDL_Quit();

    My_SDL.running = SDL_FALSE;
}




int main(int argc, char **argv) {
    My_SDL.ptr_init_func();

    printf("Running = %d\n", My_SDL.running);

    while( My_SDL.running ) {
        My_SDL.ptr_quit_func();
    }

    printf("Running = %d\n", My_SDL.running);

    return 0;
}
