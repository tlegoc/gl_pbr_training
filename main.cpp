#include <iostream>

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <GL/glew.h>

#include "src/RenderGraph.h"
#include "src/Passes/PBRPrePass.h"
#include "src/Passes/PBRDeferredPass.h"
#include "src/Camera.h"
#include "src/Model.h"
#include "src/Shader.h"

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); //OpenGL core profile
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);

    SDL_Window *window;

    window = SDL_CreateWindow("GL_PBR_TRAINING", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600,
                              SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    if (window == nullptr) {
        std::cout << "Failed to create window" << std::endl;
        return -1;
    }

    SDL_GLContext glContext = SDL_GL_CreateContext(window);

    if (glContext == nullptr) {
        std::cout << "Failed to create OpenGL context" << std::endl;
        return -1;
    }

    GLenum glewError = glewInit();

    if (glewError != GLEW_OK) {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    SDL_GL_SetSwapInterval(1);

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    Camera camera;
    camera.init();
    camera.m_position = glm::vec3(0.0f, 0.0f, 3.0f);
    camera.updateView();

    Shader shader = Shader::load("shaders/base.vert", "shaders/pbr_prepass_untextured.frag");

    Material mat;
    mat.setShader(shader);

    Model model = Model();
    model.load("assets/monkey.obj");
    model.updateModelMatrix();
    model.setMaterial(&mat);

    RenderGraph rg = RenderGraph();
    PBRPrePass pbrPrepass = PBRPrePass();
    PBRDeferredPass pbrDeferredPass = PBRDeferredPass();

    // First PBR pass, outputs all data (base color, roughness...) to a framebuffer
    pbrPrepass.init();
    pbrPrepass.setCamera(&camera);
    pbrPrepass.addModel(&model);

    // Combine pass
    pbrDeferredPass.init();
    pbrDeferredPass.setInputFramebuffer(pbrPrepass.getOutputFramebuffer());

    rg.addPass(&pbrPrepass);
    rg.addPass(&pbrDeferredPass);

    auto quit = false;
    while (!quit) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        rg.execute();

        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
