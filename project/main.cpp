#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <stdio.h>
#include <iostream>

#define SCREEN_WIDTH 640 
#define SCREEN_HEIGHT 480

void render();

void init();

void input();

void cleanup();

SDL_Window* window = nullptr;
SDL_GLContext context = nullptr;

bool running = true;

//==========================
//=        INIT            =
//==========================
void init()
{
    //init openGL and SDL    
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("Error: SDL failed to initialize\nSDL Error: '%s'\n", SDL_GetError());
        exit(1);
    }

    window = SDL_CreateWindow("Noise Project", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    if(window == nullptr)
    {
        printf("Error: SDL window failed to initialize\nSDL Error:'%s'\n", SDL_GetError());
        exit(1);
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer){
        printf("Error: Failed to create renderer\nSDL Error: '%s'\n", SDL_GetError());
        exit(1);
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
        exit(1);
    }

    //init GLAD
    //important to do this AFTER creating the context otherwise it will not work
    if(!gladLoadGLLoader(SDL_GL_GetProcAddress))
    {
        printf("Glad was not initialized !!!");
        exit(1);
    } 
}

//==========================
//=        RENDER          =
//==========================
void render()
{
    glClearColor(0.95, 0.75, 0.87, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

    //render loop actual

    SDL_GL_SwapWindow(window);
}

//==========================
//=        INPUT           =
//==========================
void input()
{
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case SDLK_ESCAPE:
                        running = false;
                        break;
                }
                break;
            default:
                break;
        }
    }
}

//==========================
//=        CLEANUP         =
//==========================
void cleanup()
{
    //cleanup pointers or other objects and quit the application
    SDL_DestroyWindow(window);
    SDL_Quit(); 
}

int main(int argc, char** argv){

    init();

    while(running)
    {
        input();

        render();
        //SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
        //SDL_RenderClear(renderer);

        //SDL_RenderPresent(renderer);
    }

    cleanup();
    return 0;
}