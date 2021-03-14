#include "ImGuiInterface.h"
#include "../ExternalResources/imgui/imgui_impl_glfw.h"
#include "../ExternalResources/imgui/imgui_impl_opengl3.h"
#include "../Utility/Print.h"
#include <glad/glad.h>

void ImGui::ImGuiInterface::initialize(std::shared_ptr<IWindow>& window){

    // TODO query this:
    const char* glsl_version = "#version 330";

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window->get_glfw_ptr(), true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    ImGui::StyleColorsClassic();
}

void ImGui::ImGuiInterface::update() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    debug_menu();
}

void ImGui::ImGuiInterface::debug_menu() {
    ImGui::Begin("Extra Life Debug");
    // TODO: Extremely old API for font scaling.  Update method to be correct
    ImGui::SetWindowFontScale(1.5);
    fps();
    globals();
    ImGui::End();
}

void ImGui::ImGuiInterface::fps() {
    ImGui::Text("FPS: %.0f", ImGui::GetIO().Framerate);
}

void ImGui::ImGuiInterface::globals() {

    // Lifetime Static
    static float clr_color[4]{ 0.08f, 0.08f, 0.08f, 1.0f };

    if (ImGui::CollapsingHeader("Global Settings")) {
        ImGui::ColorEdit3("clear color", clr_color);
    }

    // Set Lifetime Static Values
    glClearColor(clr_color[0], clr_color[1], clr_color[2], clr_color[3]);
}

void ImGui::ImGuiInterface::render() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGui::ImGuiInterface::destroy() {
    Print::print("Destroying ImGuiCLass Assets");
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}