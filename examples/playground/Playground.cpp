#include <GraphicsHandler.h>
#include <imgui.h>
#include <implot.h>
#include <Image.h>

int main() {

    GraphicsHandler handler{"DISP - Playground"};

    Image img{"assets/lena.png"};

    handler.add_render_callback([&img]{
        ImGui::ShowDemoWindow();
        ImPlot::ShowDemoWindow();
        img.draw();
        img.plot("Lena");
    });

    handler.run();

}