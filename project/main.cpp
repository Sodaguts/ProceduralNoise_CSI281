#include <SDL2/SDL.h>
#include "shader.h"
#include <stdio.h>


#define SCREEN_WIDTH 640 
#define SCREEN_HEIGHT 480

void render();
void init();
void input();
void cleanup();

SDL_Window* window = nullptr;
SDL_GLContext context = nullptr;

bool running = true;

float vertices[] = 
{
     1.0,  1.0, 0.0, 1.0, 0.0, 0.0, 1.0,
     1.0, -1.0, 0.0, 0.0, 1.0, 0.0, 1.0,
    -1.0, -1.0, 0.0, 0.0, 0.0, 1.0, 1.0,
    -1.0,  1.0, 0.0, 0.0, 0.0, 0.0, 1.0         
};

unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
};

unsigned int vbo;
unsigned int vao;
unsigned int ebo;
unsigned int shaderProgram;


Shader m_shader;
float gridSize = 15.0;


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

    //create vbo
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //create vao
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glGenBuffers(1,&ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, sizeof(float) * 7, (const void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (const void*)(sizeof(float)*3));
    glEnableVertexAttribArray(1);

    //create shader
    m_shader.createShader("project/shader.vs","project/shader.fs");
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

//====================================================================
//==========================
//=        RENDER          =
//==========================

void render()
{
    // Do setup / math up here
    float time = (float)SDL_GetTicks() / 1000.0;

    // clear screen to start
    glClearColor(0.95, 0.75, 0.87, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

    //render loop actual
    //glUseProgram(shaderProgram);
    m_shader.use();
    m_shader.setVec2("_iResolution", SCREEN_WIDTH, SCREEN_HEIGHT);
    m_shader.setFloat("_gridSize", gridSize);
    m_shader.setFloat("_iTime", time);
    //glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    //glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    SDL_GL_SwapWindow(window);
    //SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
    //SDL_RenderClear(renderer);

    //SDL_RenderPresent(renderer); // use if SDL Renderer
}
//====================================================================


//==========================
//=        CLEANUP         =
//==========================
void cleanup()
{
    //cleanup pointers or other objects and quit the application
    SDL_DestroyWindow(window);
    SDL_Quit(); 
}

//==========================
//=        MAIN            =
//==========================

int main(int argc, char** argv){

    init();

    while(running)
    {
        input();

        render();
        
    }

    cleanup();
    return 0;
}