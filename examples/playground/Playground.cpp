#include <GraphicsHandler.h>
#include <imgui.h>
#include <implot.h>

int main() {

    GraphicsHandler handler{"DISP - Playground"};

    handler.add_render_callback([]{
        ImGui::ShowDemoWindow();
        ImPlot::ShowDemoWindow();
    });

    handler.run();

}