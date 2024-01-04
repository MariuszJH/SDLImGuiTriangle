#pragma once

namespace SDLImGui
{

class OpenGLContext;
class ImGuiFonts;

class ImGuiView final
{
public:
    ImGuiView(ImGuiFonts& imGuiFonts);

    void DrawView1(OpenGLContext* openGLContext);

private:
    void MaximiseView1();
    void SetInitialLayoutView1();
    void MenuBarForView1();

    void DrawSettingsView2();
    
    void HandleActionsOfView1();
    void HandleActionsOfSettingsView2();

private:
    bool isShowImGuiDemo {false};
    bool isShowSettingsView {false};
    ImGuiFonts& imGuiFonts;
};

} // ~namespace SDLImGui
