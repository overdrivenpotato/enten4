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

#include <SOIL.h>

#include "basicshaders.h"
#include "basicshapes.h"
#include "shaders.h"
#include "engine.h"
#include "mesh.h"
#include "types.h"
#include "camera.h"

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
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    // Anti-aliasingf
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

    // Creates a window
    SDL_Window* window = SDL_CreateWindow("SDL2 Enten4",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          1280, 768,
//                                          1600, 900,
                                          SDL_WINDOW_OPENGL);

    // Attach openGL context to window
    SDL_GLContext glContext = SDL_GL_CreateContext(window);

    // Enable vsync
    if(SDL_GL_SetSwapInterval(1) != 0) {
        cerr << "VSync is not supported: " << SDL_GetError() << endl;
    }

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK) {
        cerr << "Failed opening GLEW." << endl;
        return -1;
    }

    // Please exterminate
    auto meshVerts = basicmesh::cube;
    std::vector<std::vector<Mesh*>> meshes(4);
    for(uint i = 0; i < meshes.size(); i++) {
        meshes[i].resize((i+1)*(i+1));
        for(uint j = 0; j < (i+1)*(i+1); j++) {
            std::vector<float> colors(meshVerts.size());
            for(uint u = 0; u < colors.size(); u++) {
                colors[u] = ((double)rand()) / RAND_MAX;
            }

            meshes[i][j] = new Mesh(meshVerts, colors, basicmesh::cubeUV);
        }
    }

    std::vector<float> planeColor(basicmesh::meshPlane.size());
    for(uint u = 0; u < planeColor.size(); u++) {
        planeColor[u] = ((double)rand()) / RAND_MAX;
    }
    Mesh plane(basicmesh::meshPlane, planeColor, basicmesh::planeUV);

    GLuint shaderID;
    try {
        shaderID = createVertFragShader(vertexShader2D, whiteFragment);
    } catch (std::logic_error compileError) {
        cerr << compileError.what();
        return -1;
    }

    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    int width, height;
    unsigned char* image = SOIL_load_image("res/crate.jpg", &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glClearColor(0.3f, 0.3f, 0.7f, 1); // Background color
    glEnable(GL_CULL_FACE); // Disable rendering of faces viewed backwards
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    SDL_Event windowEvent;
    SDL_SetRelativeMouseMode(SDL_TRUE);
    bool running = true;

    glm::vec3 cameraVelocity;
    const float camSpeed = 0.2f;
    CameraFP camera(glm::vec3(8.f, -7.5f, 8.f), glm::vec3(-1, 0, -1));

    int frame = 0;
    Uint32 lastTime = SDL_GetTicks();

    while(running) {
        frame++;
        Uint32 passed = SDL_GetTicks();
        if(passed - lastTime > 1000) {
            cout << "FPS: " << frame << endl;
            lastTime = passed;
            frame = 0;
        }
        while(SDL_PollEvent(&windowEvent)) {
            if(windowEvent.type == SDL_KEYDOWN) {
                switch(windowEvent.key.keysym.sym) {
                case SDLK_w:
                    cameraVelocity.z = camSpeed;
                    break;
                case SDLK_s:
                    cameraVelocity.z = -camSpeed;
                    break;
                case SDLK_a:
                    cameraVelocity.x = camSpeed;
                    break;
                case SDLK_d:
                    cameraVelocity.x = -camSpeed;
                    break;
                case SDLK_SPACE:
                    cameraVelocity.y = camSpeed;
                    break;
                case SDLK_LSHIFT:
                    cameraVelocity.y = -camSpeed;
                    break;
                }
            } else if(windowEvent.type == SDL_KEYUP) {
                switch(windowEvent.key.keysym.sym) {
                case SDLK_w:
                    if(cameraVelocity.z > 0)
                        cameraVelocity.z = 0;
                    break;
                case SDLK_s:
                    if(cameraVelocity.z < 0)
                        cameraVelocity.z = 0;
                    break;
                case SDLK_a:
                    if(cameraVelocity.x > 0)
                        cameraVelocity.x = 0;
                    break;
                case SDLK_d:
                    if(cameraVelocity.x < 0)
                        cameraVelocity.x = 0;
                    break;
                case SDLK_SPACE:
                    if(cameraVelocity.y > 0)
                        cameraVelocity.y = 0;
                    break;
                case SDLK_LSHIFT:
                    if(cameraVelocity.y < 0)
                        cameraVelocity.y = 0;
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
                if(windowEvent.motion.xrel != 0) {
                    camera.rotateYaw(-windowEvent.motion.xrel * 0.005f);
                }
                if(windowEvent.motion.yrel != 0) {
                    camera.rotatePitch(windowEvent.motion.yrel * 0.005f);
                }
                break;
            default:
                break;
            }
        }


        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shaderID);

        camera.translateRelative(cameraVelocity);

        glm::mat4 projection = glm::perspective((float) (M_PI / 3.f), 16.f / 9.f, 0.1f, 100.f);
        glm::mat4 view = camera.getViewMatrix();

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
