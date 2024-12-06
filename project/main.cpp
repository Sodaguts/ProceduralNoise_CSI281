#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <stdio.h>
#include <iostream>

#define SCREEN_WIDTH 640 
#define SCREEN_HEIGHT 480

void render();

void init();

void cleanup();

SDL_Window* window = nullptr;
SDL_GLContext context = nullptr;


int main(int argc, char** argv){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("Error: SDL failed to initialize\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("Noise Project", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    if(window == nullptr)
    {
        printf("Error: SDL window failed to initialize\nSDL Error:'%s'\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer){
        printf("Error: Failed to create renderer\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }

    //Set OpenGL attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);


    context = SDL_GL_CreateContext(window);
    if(context == nullptr)
    {
        printf("Error: Failed to create OpenGL context\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }

        //init GLAD
    if(!gladLoadGLLoader(SDL_GL_GetProcAddress))
    {
        printf("Glad was not initialized !!!");
        return 1;
    }

    bool running = true;
    while(running){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            running = false;
                            break;
                    }
                    break;

                default:
                    break;
            }
        }

        glClearColor(0.95, 0.75, 0.87, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // causes program to crash?

        SDL_GL_SwapWindow(window);
        //SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
        //SDL_RenderClear(renderer);

        //SDL_RenderPresent(renderer);
    }


    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

void init()
{
    //init openGL and SDL     
}

void render()
{
    // render loop logic here ig    
}

void cleanup()
{
    //cleanup pointers and stuff   
}