#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>


// 初始化sdl以及创建一个sdl窗口, 成功返回true，失败返回false
bool Init_(void);

// 载入图片资源
bool Load_Image(void);

// 释放图片资源以及销毁sdl
void Close_(void); 


// 将要渲染的窗口
SDL_Window  *gWin = NULL;
// 窗口里容纳的表面
SDL_Surface *gScreenSurface = NULL;
// 将要装载以及显示在窗口中的图像
SDL_Surface *gHelloWorld = NULL;

//////////////////////////////////////////////////////////////

int main(int argc, char **argv) {
    
    if( !Init_() ) {
        puts("Failed to initialize!");
    }else{
        if( !Load_Image() ) {
            puts("Failed to load bmp image!");
        }else{
            // Apply the image 
            SDL_BlitSurface( gHelloWorld, NULL, gScreenSurface, NULL );
            // Update the surface 
            SDL_UpdateWindowSurface( gWin );
        }
    }
    
    SDL_Event e;
    bool quit = false;

    while( !quit ) {
        while( SDL_PollEvent(&e) ) {
            if( e.type == SDL_QUIT ) {
                quit = true;
            }
        }
    }

    Close_();
    return 0;
}


/////////////////////////////////////////////////////////////

// 初始化sdl以及创建一个sdl窗口, 成功返回true，失败返回false
bool Init_(void) {
    // sdl window title 
    const char *TITLE_WIN = "SDL Window Title";
    // sdl window width 
    const int  WIDTH_WIN = 640;
    // sdl window height
    const int  HEIGHT_WIN = 480;

    // 哨兵
    bool success_flag = true;
    if( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success_flag = false;
    }else{
        gWin = SDL_CreateWindow(
                    TITLE_WIN,
                    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                    WIDTH_WIN, HEIGHT_WIN,
                    SDL_WINDOW_SHOWN
                );

        if(gWin == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success_flag = false;
        }else{
            // Get window surface
            gScreenSurface = SDL_GetWindowSurface( gWin );
        }
    }

    return success_flag;
}


// 载入图片资源
bool Load_Image(void) {
    bool success_flag = true;

    // load image, 需要注意下路径问题，尤其是在不同os环境下
    gHelloWorld = SDL_LoadBMP("./hello_world.bmp");
    if(gHelloWorld == NULL) {
        printf("Unable to load image %s! SDL Error: %s\n", "./hello_world.bmp", SDL_GetError());
        success_flag = false;
    }

    return success_flag;
}


// 释放图片资源以及销毁sdl
void Close_(void) {
    // Dealloc surface 
    SDL_FreeSurface( gHelloWorld );
    gHelloWorld = NULL;
    // Destroy window
    SDL_DestroyWindow( gWin );
    gWin = NULL;
    // Quit SDL subsystem
    SDL_Quit();
}
