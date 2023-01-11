#include "disp/GraphicsHandler.h"
#include <imgui.h>
#include <implot.h>
#include "disp/Image.h"

#include <disp/python.h>
#include <iostream>

// partial stb support for imgui
#include <misc/cpp/imgui_stdlib.h>

int main() {

    disp::py::scoped_interpreter guard{}; // start the interpreter and keep it alive

    disp::py::module_::import("disp");

    GraphicsHandler handler{"DISP - Playground"};

    //Image img{"assets/lena.png"};

    handler.add_render_callback([]{
        ImGui::ShowDemoWindow();
        ImPlot::ShowDemoWindow();
        //img.plot("Lena");



        if(ImGui::Begin("Python")) {
            std::string cmd;
            if(ImGui::InputText("##python", &cmd, ImGuiInputTextFlags_EnterReturnsTrue)) {
                try {
                    std::cout << cmd << std::endl;
                    disp::py::exec(cmd);
                } catch (std::exception &e) {
                    std::cerr << e.what() << std::endl;
                }
                
            }
        }
        ImGui::End();

    });

    handler.run();

}