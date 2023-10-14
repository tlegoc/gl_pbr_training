#include <iostream>

#define SDL_MAIN_HANDLED

#include <SDL.h>
#include <GL/glew.h>

#include "src/imgui.h"
#include "src/imgui_impl_sdl2.h"
#include "src/imgui_impl_opengl3.h"

#include "src/RenderGraph.h"
#include "src/Passes/PBRPrePass.h"
#include "src/Passes/PBRDeferredPass.h"
#include "src/Camera.h"
#include "src/Model.h"
#include "src/Shader.h"
#include "src/Skybox.h"

#define WIDTH 1600
#define HEIGHT 900

int main() {
    SDL_Init(SDL_INIT_VIDEO);


    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); //OpenGL core profile
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);

    SDL_Window *window;

    window = SDL_CreateWindow("GL_PBR_TRAINING", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT,
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

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(window, glContext);
    ImGui_ImplOpenGL3_Init("#version 450");


    // If you want to use #include in your shaders
//    Shader::buildGLIncludes();

    Camera camera;
    camera.init(WIDTH, HEIGHT);
//    camera.m_fov = M_PI / 4.0f;
    camera.m_position = glm::vec3(0.0f, 3.0f, 3.0f);
    camera.m_direction = glm::normalize(glm::vec3(0.0, -1.0, -1.0));
    camera.updateView();
    camera.updateProjection();

    Skybox::CubemapInfo c_info{
            "assets/textures/nx.png",
            "assets/textures/ny.png",
            "assets/textures/nz.png",
            "assets/textures/px.png",
            "assets/textures/py.png",
            "assets/textures/pz.png"
    };
    Skybox skybox = Skybox::load(c_info);

    Shader shader = Shader::load("shaders/core/base.vert", "shaders/core/PBR/untextured.frag");

    Material mat;
    mat.setShader(shader);
    glm::vec4 base_color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    mat.setParameter("ubase_color", base_color);
    float metallic = 0.0f;
    mat.setParameter("umetallic", metallic);
    float roughness = 1.0f;
    mat.setParameter("uroughness", roughness);
    float reflectance = 0.5f;
    mat.setParameter("ureflectance", reflectance);
    glm::vec3 emissive = glm::vec3(0.0f, 0.0f, 0.0f);
    mat.setParameter("uemissive", emissive);

    Model model = Model();
    model.load("assets/material_ball.obj");
//    model.m_scale = glm::vec3(1.5f);
//    model.m_rotation.x += 3.0f;
    model.m_position = glm::vec3(0.0f, -0.5f, 0.0f);
    model.updateModelMatrix();
    model.setMaterial(mat);

    RenderGraph rg = RenderGraph();
    PBRPrePass pbrPrepass = PBRPrePass();
    PBRDeferredPass pbrDeferredPass = PBRDeferredPass();

    // First PBR pass, outputs all data (base color, roughness...) to a framebuffer
    pbrPrepass.init(WIDTH, HEIGHT);
    pbrPrepass.setCamera(&camera);
    pbrPrepass.addModel(&model);

    // Combine pass
    pbrDeferredPass.init(WIDTH, HEIGHT);
    // Link framebuffer
    pbrDeferredPass.setInputFramebuffer(pbrPrepass.getOutputFramebuffer());
    pbrDeferredPass.setSkybox(&skybox);
    pbrDeferredPass.setCamera(&camera);

    // Order matters
    rg.addPass(&pbrPrepass);
    rg.addPass(&pbrDeferredPass);

    uint64_t time = 0;
    uint64_t last_time = 0;
    auto quit = false;
    float camera_distance = 3.0f;
    bool camera_auto_rotate = true;
    GLuint fullscreen_text = -1;
    while (!quit) {
        last_time = time;
        time = SDL_GetTicks64();
        float delta_time = (time - last_time) / 1000.0f;
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);

            if (event.type == SDL_QUIT) {
                quit = true;
            }

            if (event.type == SDL_MOUSEWHEEL) {
                camera.m_fov -= event.wheel.y * 0.1f;
                camera.m_fov = glm::clamp(camera.m_fov, (float) M_PI / 32.0f, (float) M_PI / 1.01f);
            }

            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_UP) {
                    camera_distance -= 0.1f;
                }
                if (event.key.keysym.sym == SDLK_DOWN) {
                    camera_distance += 0.1f;
                }
            }
        }

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        // UI

        ImGui::Begin("Settings");
        ImGui::Text("FPS: %f", 1.0f / delta_time);

        ImGui::Text("Camera settings");
        ImGui::Checkbox("Auto rotate camera", &camera_auto_rotate);
        ImGui::DragFloat("Camera distance", &camera_distance, 0.1f, 0.0f, 100.0f);
        ImGui::DragFloat("Camera FOV", &camera.m_fov, 0.1f, (float) M_PI / 32.0f, (float) M_PI / 1.01f);

        ImGui::Text("Model settings");
        ImGui::ColorEdit4("Base color", &base_color.x);
        ImGui::DragFloat("Metallic", &metallic, 0.01f, 0.0f, 1.0f);
        ImGui::DragFloat("Roughness", &roughness, 0.01f, 0.0f, 1.0f);
        ImGui::DragFloat("Reflectance", &reflectance, 0.01f, 0.0f, 1.0f);
        ImGui::ColorEdit3("Emissive", &emissive.x);

        // Yes this is very bad
        // Don't do this at home
        mat.setParameter("ubase_color", base_color);
        mat.setParameter("umetallic", metallic);
        mat.setParameter("uroughness", roughness);
        mat.setParameter("ureflectance", reflectance);
        mat.setParameter("uemissive", emissive);

        int size_x = ImGui::GetContentRegionAvail().x / 2;
        float ratio = (float) WIDTH / (float) HEIGHT;
        int size_y = size_x / ratio;
        ImGui::BeginGroup();
        ImGui::Text("Color");
        ImGui::Image((void *) (intptr_t) pbrPrepass.getOutputFramebuffer()->getTexture(0), ImVec2(size_x, size_y));
        ImGui::EndGroup();
        ImGui::SameLine();
        ImGui::BeginGroup();
        ImGui::Text("Metallic/Roughness/Reflectance");
        ImGui::Image((void *) (intptr_t) pbrPrepass.getOutputFramebuffer()->getTexture(1), ImVec2(size_x, size_y));
        ImGui::EndGroup();
        ImGui::BeginGroup();
        ImGui::Text("Emissive");
        ImGui::Image((void *) (intptr_t) pbrPrepass.getOutputFramebuffer()->getTexture(2), ImVec2(size_x, size_y));
        ImGui::EndGroup();
        ImGui::SameLine();
        ImGui::BeginGroup();
        ImGui::Text("Normal");
        ImGui::Image((void *) (intptr_t) pbrPrepass.getOutputFramebuffer()->getTexture(3), ImVec2(size_x, size_y));
        ImGui::EndGroup();
        ImGui::BeginGroup();
        ImGui::Text("Position");
        ImGui::Image((void *) (intptr_t) pbrPrepass.getOutputFramebuffer()->getTexture(4), ImVec2(size_x, size_y));
        ImGui::EndGroup();
        ImGui::SameLine();
        ImGui::BeginGroup();
        ImGui::Text("Occlusion/Clearcoat/Clearcoat Roughness");
        ImGui::Image((void *) (intptr_t) pbrPrepass.getOutputFramebuffer()->getTexture(5), ImVec2(size_x, size_y));
        ImGui::EndGroup();
        ImGui::End();

        ImGui::Render();

        if (camera_auto_rotate) {
            camera.m_position = glm::vec3(glm::cos(time / 1000.0f) * camera_distance,
                                          0, //glm::cos(time / 10000.0f) * camera_distance,
                                          glm::sin(time / 1000.0f) * camera_distance);
            camera.m_direction = glm::normalize(-camera.m_position);
        }
        camera.updateView();
        camera.updateProjection();

        rg.execute();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
