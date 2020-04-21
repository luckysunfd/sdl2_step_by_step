/*
 * 一个简单的sdl窗口，无贴图
 *
 * @date: 2020.5.21 PM 
 */
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>


int main(int argc, char **argv) {
    // The window we'll be rendering to
    SDL_Window *win = NULL;
    
    // Initialize SDL2 video subsystem 
    if( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        printf("SDL could not Initialize! SDL_Error: %s\n", SDL_GetError());
    }else{
        // Create window 
        win = SDL_CreateWindow(
                    "my window",  // window title
                    0, 0,         // window position
                    640, 320,     // window size
                    SDL_WINDOW_SHOWN  // window property
                );
        if( win == NULL ) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }
        // todo surface 
    }
    
    /* 消息循环 -- 暂时略过这段代码，后面解释，运行后，点击关闭窗口按钮或者点击鼠标或者按下任意键即自动退出 */
    SDL_Event e;
    bool quit = false;

    while( !quit ) {
        while( SDL_PollEvent(&e) ) {
            if( e.type == SDL_QUIT ) {
                quit = true;
            }
            if( e.type == SDL_KEYDOWN ) {
                quit = true;
            }
            if( e.type == SDL_MOUSEBUTTONDOWN ) {
                quit = true;
            }
        }
    }

    // Destroy window
    SDL_DestroyWindow(win);
    // Quit SDL 
    SDL_Quit();
    return 0;
}
