#include <iostream>

#include "imgui.h"

#include "ImGuiView.hpp"
#include "OpenGLContext.hpp"
#include "ImGuiFonts.hpp"

namespace SDLImGui
{

ImGuiView::ImGuiView(ImGuiFonts& imGuiFonts)
    : imGuiFonts(imGuiFonts)
{}

void ImGuiView::MaximiseView1()
{
    static const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size, ImGuiCond_Appearing);
    // ImGui::SetNextWindowSize(viewport->Size, ImGuiCond_Always);
}

void ImGuiView::SetInitialLayoutView1()
{
    static const ImGuiViewport* viewport = ImGui::GetMainViewport();
    // ImGui::SetNextWindowPos(ImVec2(viewport->WorkPos.x + 0, viewport->WorkPos.y + 0), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowPos(viewport->Pos, ImGuiCond_Appearing);
    // ImGui::SetNextWindowPos(viewport->Pos, ImGuiCond_Always);
    // ImGui::SetNextWindowPos(viewport->Pos, ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2(viewport->WorkSize.x / 3.5, viewport->WorkSize.y / 4.0), ImGuiCond_Appearing);
    // ImGui::SetNextWindowSize(ImVec2(viewport->WorkSize.x / 3.5, viewport->WorkSize.y / 4.0), ImGuiCond_Always);
    // ImGui::SetNextWindowSize(ImVec2(viewport->WorkSize.x / 3.5, viewport->WorkSize.y / 4.0), ImGuiCond_Once);
}

void ImGuiView::MenuBarForView1()
{
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Settings"))
        {
            ImGui::MenuItem("Adjust Style and Fonts", nullptr, &isShowSettingsView);
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }
}

void ImGuiView::DrawView1(OpenGLContext* openGLContext)
{
    // MaximiseView1();
    SetInitialLayoutView1();

    imGuiFonts.PushSelectedFont();

    static bool isShowView1 {false};
    ImGuiWindowFlags windowFlags {0};
    // windowFlags |= ImGuiWindowFlags_NoTitleBar;
    windowFlags |= ImGuiWindowFlags_MenuBar;
    // windowFlags |= ImGuiWindowFlags_NoMove;
    // windowFlags |= ImGuiWindowFlags_NoResize;
    // windowFlags |= ImGuiWindowFlags_NoCollapse;

    if (!ImGui::Begin("ImGui View 1", &isShowView1, windowFlags))
    {
        ImGui::End();
        ImGui::PopFont();
        return;
    }

    MenuBarForView1();


    ImGui::Checkbox("Show Triangle", &openGLContext->isShowTriangle);
    ImGui::SameLine();
    ImGui::SetNextItemWidth(180);
    ImGui::SliderFloat("Traingle size", &openGLContext->rescaleSize, 0.0F, 5.0F, "%.1F (Rescale)");
    ImGui::SliderFloat2("Shift (x, y)", openGLContext->triangleShift, -1.0, 1.0, "%.2f");
    ImGui::SliderFloat("Rotate", &openGLContext->rotationAngleDeg, -360.0F, 360.0F, "%.0F (deg)");

    ImGui::ColorEdit3("Triangle Colour", openGLContext->triangleColour);
    
    if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal))
            ImGui::SetTooltip("Ctrl+click on individual component to input value.\nClick on the color square to open a color picker.\nClick and hold to use drag and drop.");
    

    ImGui::End();
    HandleActionsOfView1();
    ImGui::PopFont();
}

void ImGuiView::HandleActionsOfView1()
{
    if (isShowSettingsView)
        DrawSettingsView2();
}

void ImGuiView::DrawSettingsView2()
{
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    // ImGui::SetNextWindowPos(ImVec2(viewport->WorkPos.x + 550, viewport->WorkPos.y + 50), ImGuiCond_Always);
    // ImGui::SetNextWindowSize(ImVec2(viewport->WorkSize.x / 2.1, viewport->WorkSize.y / 3.5), ImGuiCond_Appearing);
    ImGui::SetNextWindowPos(ImVec2(viewport->WorkPos.x + 550, viewport->WorkPos.y + 50), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(viewport->WorkSize.x / 2.1, viewport->WorkSize.y / 3.5), ImGuiCond_FirstUseEver);

    imGuiFonts.PushSelectedFont();

    if (!ImGui::Begin("Style and Fonts", &isShowSettingsView))
    {
        ImGui::End();
        ImGui::PopFont();
        return;
    }

    static int themeStyleIndex {0};
    ImGui::RadioButton("Dark", &themeStyleIndex, 0); ImGui::SameLine();
    ImGui::RadioButton("Light", &themeStyleIndex, 1); ImGui::SameLine();
    ImGui::RadioButton("Classic", &themeStyleIndex, 2);

    switch (themeStyleIndex)
    {
    case 0: ImGui::StyleColorsDark(); break;
    case 1: ImGui::StyleColorsLight(); break;
    case 2: ImGui::StyleColorsClassic(); break;
    }

    ImGui::SameLine();

    ImGui::Checkbox("ImGui Demo Window", &isShowImGuiDemo);

    ImGui::SetNextItemWidth(250);
    ImGui::Combo("Font  ", &imGuiFonts.selectedFontNameIndex, imGuiFonts.pFontNameItems.get(), imGuiFonts.availableFontNames.size());

    ImGui::SameLine();

    ImGui::SetNextItemWidth(100);
    ImGui::Combo("Font Size", &imGuiFonts.selectedFontSizeIndex, imGuiFonts.pFontSizeItems.get(), imGuiFonts.fontSizesStr.size());

    ImGui::End();
    HandleActionsOfSettingsView2();
    ImGui::PopFont();
}

void ImGuiView::HandleActionsOfSettingsView2()
{
    if (isShowImGuiDemo)
        ImGui::ShowDemoWindow(&isShowImGuiDemo);
}
    
} // ~namespace SDLImGui
