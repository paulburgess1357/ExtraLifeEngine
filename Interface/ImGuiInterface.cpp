#include "ImGuiInterface.h"
#include "../ExternalResources/imgui/imgui_impl_glfw.h"
#include "../ExternalResources/imgui/imgui_impl_opengl3.h"
#include "../Utility/Print.h"
#include "../Utility/FatalError.h"
#include <glad/glad.h>

std::shared_ptr<ImGuiNS::InterfaceCameraData> ImGuiNS::ImGuiInterface::m_interface_camera_data = nullptr;
bool ImGuiNS::ImGuiInterface::m_display_interface = false;

void ImGuiNS::ImGuiInterface::initialize_window(std::shared_ptr<IWindow>& window){

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

void ImGuiNS::ImGuiInterface::initialize_camera_data(const Camera& camera){
    m_interface_camera_data = std::make_shared<InterfaceCameraData>(camera);
}


void ImGuiNS::ImGuiInterface::update() {
	if(m_display_interface){
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        debug_menu();
	}
}

void ImGuiNS::ImGuiInterface::debug_menu() {
    ImGui::Begin("Extra Life Debug");
    // TODO: Extremely old API for font scaling.  Update method to be correct
    ImGui::SetWindowFontScale(1.5);
    fps();

    check_camera_interface();
    m_interface_camera_data->display();
	
    globals();
    ImGui::End();
}

void ImGuiNS::ImGuiInterface::fps() {
    ImGui::Text("FPS: %.0f", ImGui::GetIO().Framerate);
}

void ImGuiNS::ImGuiInterface::globals() {

    // Lifetime Static
    static float clr_color[4]{ 0.08f, 0.08f, 0.08f, 1.0f };

    if (ImGui::CollapsingHeader("Global Settings")) {
        ImGui::ColorEdit3("clear color", clr_color);
    }

    // Set Lifetime Static Values
    glClearColor(clr_color[0], clr_color[1], clr_color[2], clr_color[3]);
}

void ImGuiNS::ImGuiInterface::render() {
	if(m_display_interface){
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}

void ImGuiNS::ImGuiInterface::destroy() {
    Print::print("Destroying ImGuiCLass Assets");
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void ImGuiNS::ImGuiInterface::check_camera_interface() {
	if(m_interface_camera_data == nullptr){
        FatalError::fatal_error("Camera data interface is null!  Unable to display camera data interface (called from ImGuiInterface::check_camera_interface())");
	}
}

void ImGuiNS::ImGuiInterface::toggle_interface(){
    m_display_interface = !m_display_interface;
}
