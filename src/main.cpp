#include <iostream>
#include <stdexcept>
#include <string.h>
#include <random>
#include <cmath>
using namespace std;

//Statically compile GLEW
#define GLEW_STATIC
#include <GL/glew.h>
//SDL
#include <SDL.h>
#include <SDL_opengl.h>
#ifdef _WIN32
#undef main
#endif

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "basicshaders.h"
#include "basicshapes.h"
#include "shaders.h"
#include "engine.h"
#include "mesh.h"
#include "types.h"

int main(int argc, char** argv) {
    if(argc > 1) {
        if(strcmp(argv[1], "shrine-s6zux") == 0) {
            cout << "TRIGGERING SHRINE MODE..." << endl;
        }
    }
    Engine engine;

    SDL_Init(SDL_INIT_VIDEO);

    // Require opengl 3.1
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    // Anti-aliasing
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);

    // Check for vsync
    if(SDL_GL_SetSwapInterval(1) != 0) {
        cerr << "VSync is not supported." << endl;
    }

    // Creates a window
    SDL_Window* window = SDL_CreateWindow("SDL2 Enten4",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          1280,
                                          768,
                                          SDL_WINDOW_OPENGL);

    // Attach openGL context to window
    SDL_GLContext glContext = SDL_GL_CreateContext(window);

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK) {
        cerr << "Failed opening GLEW." << endl;
        return -1;
    }

    auto meshVerts = basicmesh::cube;
    std::vector<std::vector<Mesh*>> meshes(4);
    for(uint i = 0; i < meshes.size(); i++) {
        meshes[i].resize((i+1)*(i+1));
        for(uint j = 0; j < (i+1)*(i+1); j++) {
            std::vector<float> colors(meshVerts.size());
            for(uint u = 0; u < colors.size(); u++) {
                colors[u] = ((double)rand()) / RAND_MAX;
            }

            meshes[i][j] = new Mesh(meshVerts, colors);
        }
    }

    std::vector<float> planeColor(basicmesh::meshPlane.size());
    for(uint u = 0; u < planeColor.size(); u++) {
        planeColor[u] = ((double)rand()) / RAND_MAX;
    }
    Mesh plane(basicmesh::meshPlane, planeColor);

    GLuint shaderID;
    try {
        shaderID = createVertFragShader(vertexShader2D, whiteFragment);
    } catch (std::logic_error compileError) {
        cerr << compileError.what();
        return -1;
    }

    glClearColor(0.3f, 0.3f, 0.7f, 1); // Background color
    glEnable(GL_CULL_FACE); // Disable rendering of faces viewed backwards
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    SDL_Event windowEvent;
    SDL_SetRelativeMouseMode(SDL_TRUE);
    bool running = true;

    glm::vec3 position(4.f, 4.f, 3.f);
    glm::vec3 direction(-1, 0, -1);
    glm::vec3 movement;

    while(running) {
        while(SDL_PollEvent(&windowEvent)) {
            if(windowEvent.type == SDL_KEYDOWN) {
                switch(windowEvent.key.keysym.sym) {
                case SDLK_w:
                    movement.y = 1;
                    break;
                case SDLK_s:
                    movement.y = -1;
                    break;
                }
            } else if(windowEvent.type == SDL_KEYUP) {
                switch(windowEvent.key.keysym.sym) {
                case SDLK_w:
                    if(movement.y > 0)
                        movement.y = 0;
                    break;
                case SDLK_s:
                    if(movement.y < 0)
                        movement.y = 0;
                    break;
                }
            }


            switch(windowEvent.type) {
            case SDL_KEYUP:
                if(windowEvent.key.keysym.sym != SDLK_ESCAPE) break;
            case SDL_QUIT:
                running = false;
                break;
            case SDL_MOUSEMOTION:
                direction = glm::rotate(direction, -windowEvent.motion.xrel * 0.005f, glm::vec3(0, 1, 0));
                direction.y -= windowEvent.motion.yrel * 0.005f;
                break;
            default:
                break;
            }
        }

        position += movement.y * direction * 0.1f;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shaderID);

        glm::mat4 projection = glm::perspective((float) (M_PI / 3.f), 16.f / 9.f, 0.1f, 100.f);
        glm::mat4 view = glm::lookAt(
                    position,
                    position + direction,
                    glm::vec3(0, 1, 0)
        );

        // This will all be deleted
        for(uint i = 0; i < meshes.size(); i++) {
            for(uint j = 0; j < (i+1)*(i+1); j++) {
                glm::mat4 model(1.0f);

                int level = i+1;
                int index = j;
                int signedI = i;

                float x = floor((index) / level);
                float y = index % level;

                model = glm::translate(model, glm::vec3(x*3 - (signedI * 1.5f), 5 -(signedI * 3), 3 * y - 1.5*signedI));
                model = glm::rotate(model, (float)SDL_GetTicks() / 1000, glm::vec3(0, 1, 0));

                glm::mat4 MVP = projection * view * model;

                GLint location = glGetUniformLocation(shaderID, "MVP");
                glUniformMatrix4fv(location, 1, GL_FALSE, &MVP[0][0]);

                meshes[i][j]->draw();
            }
        }

        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(0, -10, 0));
        model = glm::scale(model, glm::vec3(10, 10, 10));
        glm::mat4 MVP = projection * view * model;
        GLint location = glGetUniformLocation(shaderID, "MVP");
        glUniformMatrix4fv(location, 1, GL_FALSE, &MVP[0][0]);
        plane.draw();

        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(glContext);
    SDL_Quit();
    return 0;
}
