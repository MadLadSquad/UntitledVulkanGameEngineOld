#include "KeybindSettings.hpp"
#include "Renderer/Window/Window.hpp"
#include "Core/Interfaces/SettingsManager.hpp"
#include <imgui.h>
#include <cpp/imgui_stdlib.h>

void UVK::KeybindSettingsWidget::displayKeybindsEditor(bool& bReturn, bool& bOpen) noexcept
{
    int i = 0;
    for (auto& a : UVK::Input::getActions())
    {
        if (a.name.find("editor-") != UVK::FString::npos)
        {
            ImGui::TextWrapped("%s", a.name.c_str());

            ImGui::TextWrapped("Name");
            ImGui::SameLine();
            if (ImGui::InputText(("##Name##" + a.name + FString(std::to_string(a.keyCode))).c_str(), &a.name) || ImGui::IsItemActive())
                bReturn = true;
            ImGui::TextWrapped("Keycode");
            ImGui::SameLine();
            showKeySelect(static_cast<UVK::FString>("##Name##" + a.name + UVK::FString(std::to_string(a.keyCode) + std::to_string(i))).c_str(), a.keyCode);
            ImGui::Separator();
            i++;
        }
    }

    if (ImGui::Button("Close"))
        bOpen = false;
    ImGui::SameLine();
    if (ImGui::Button("Save"))
        UVK::SettingsManager::saveEditorKeybindSettings();
    ImGui::EndPopup();
}

void UVK::KeybindSettingsWidget::displayKeybindsGame(bool& bReturn, bool& bOpen) noexcept
{
    ImGui::BeginMenuBar();
    bool bDestroy = false;

    if (ImGui::MenuItem("+ Add Keybind##scn"))
    {
        UVK::InputAction action;
        static int newact = 0;
        action.name = "NewAction" + std::to_string(newact);
        action.keyCode = 0;

        UVK::Input::getActions().push_back(action);
        ++newact;
    }
    if (ImGui::MenuItem("- Remove Keybind##scn")) bDestroy = true;

    ImGui::EndMenuBar();

    int j = 0;
    for (int i = 0; i < UVK::Input::getActions().size(); i++)
    {
        if (UVK::Input::getActions()[i].name.find("editor-") == UVK::FString::npos)
        {
            if (bDestroy)
            {
                UVK::Input::getActions().erase(UVK::Input::getActions().begin() + i);
                bDestroy = false;
            }
            else
            {
                ImGui::TextWrapped("%s", UVK::Input::getActions()[i].name.c_str());

                ImGui::TextWrapped("Name");
                ImGui::SameLine();
                if (ImGui::InputText(static_cast<UVK::FString>("##Name##" + UVK::FString(UVK::Input::getActions()[i].name + std::to_string(UVK::Input::getActions()[i].keyCode))).c_str(), &UVK::Input::getActions()[i].name) || ImGui::IsItemActive())
                    bReturn = true;

                ImGui::TextWrapped("Keycode");
                ImGui::SameLine();
                showKeySelect(("##Keycode##" + UVK::Input::getActions()[i].name + UVK::FString(std::to_string(UVK::Input::getActions()[i].keyCode) + std::to_string(j))).c_str(), UVK::Input::getActions()[i].keyCode);
                ImGui::Separator();
                j++;
            }
        }
    }

    if (ImGui::Button("Close"))
    {
        bOpen = false;
    }
    ImGui::SameLine();
    if (ImGui::Button("Save"))
    {
        UVK::SettingsManager::saveKeybindSettings();
    }
    ImGui::EndPopup();
}

void UVK::KeybindSettingsWidget::showKeySelect(const char* name, uint16_t& key) noexcept
{
    static UVK::FString text;
    UVK::Utility::keyToText(text, key, true);

    if (ImGui::BeginCombo(name, text.c_str()))
    {
        if (ImGui::MenuItem("Unknown Key")) key = Keys::UnknownKey;
        if (ImGui::MenuItem("Space")) key = Keys::Space;
        if (ImGui::MenuItem("Apostrophe")) key = Keys::Apostrophe;
        if (ImGui::MenuItem("Comma")) key = Keys::Comma;
        if (ImGui::MenuItem("Minus")) key = Keys::Minus;
        if (ImGui::MenuItem("Period")) key = Keys::Period;
        if (ImGui::MenuItem("Slash")) key = Keys::Slash;
        if (ImGui::MenuItem("Zero")) key = Keys::Zero;
        if (ImGui::MenuItem("One")) key = Keys::One;
        if (ImGui::MenuItem("Two")) key = Keys::Two;
        if (ImGui::MenuItem("Three")) key = Keys::Three;
        if (ImGui::MenuItem("Four")) key = Keys::Four;
        if (ImGui::MenuItem("Five")) key = Keys::Five;
        if (ImGui::MenuItem("Six")) key = Keys::Six;
        if (ImGui::MenuItem("Seven")) key = Keys::Seven;
        if (ImGui::MenuItem("Eight")) key = Keys::Eight;
        if (ImGui::MenuItem("Nine")) key = Keys::Nine;
        if (ImGui::MenuItem("Semicolon")) key = Keys::Semicolon;
        if (ImGui::MenuItem("Equal")) key = Keys::Equal;

        ImGui::Separator();

        if (ImGui::MenuItem("A")) key = Keys::A;
        if (ImGui::MenuItem("B")) key = Keys::B;
        if (ImGui::MenuItem("C")) key = Keys::C;
        if (ImGui::MenuItem("D")) key = Keys::D;
        if (ImGui::MenuItem("E")) key = Keys::E;
        if (ImGui::MenuItem("F")) key = Keys::F;
        if (ImGui::MenuItem("G")) key = Keys::G;
        if (ImGui::MenuItem("H")) key = Keys::H;
        if (ImGui::MenuItem("I")) key = Keys::I;
        if (ImGui::MenuItem("J")) key = Keys::J;
        if (ImGui::MenuItem("K")) key = Keys::K;
        if (ImGui::MenuItem("L")) key = Keys::L;
        if (ImGui::MenuItem("M")) key = Keys::M;
        if (ImGui::MenuItem("N")) key = Keys::N;
        if (ImGui::MenuItem("O")) key = Keys::O;
        if (ImGui::MenuItem("P")) key = Keys::P;
        if (ImGui::MenuItem("Q")) key = Keys::Q;
        if (ImGui::MenuItem("R")) key = Keys::R;
        if (ImGui::MenuItem("S")) key = Keys::S;
        if (ImGui::MenuItem("T")) key = Keys::T;
        if (ImGui::MenuItem("U")) key = Keys::U;
        if (ImGui::MenuItem("V")) key = Keys::V;
        if (ImGui::MenuItem("W")) key = Keys::W;
        if (ImGui::MenuItem("X")) key = Keys::X;
        if (ImGui::MenuItem("Y")) key = Keys::Y;
        if (ImGui::MenuItem("Z")) key = Keys::Z;

        ImGui::Separator();

        if (ImGui::MenuItem("Left Bracket")) key = Keys::LeftBracket;
        if (ImGui::MenuItem("Backslash")) key = Keys::Backslash;
        if (ImGui::MenuItem("Right Bracket")) key = Keys::RightBracket;
        if (ImGui::MenuItem("Grave Accent")) key = Keys::GraveAccent;
        if (ImGui::MenuItem("World One")) key = Keys::WorldOne;
        if (ImGui::MenuItem("World Two")) key = Keys::WorldTwo;
        if (ImGui::MenuItem("Escape")) key = Keys::Escape;
        if (ImGui::MenuItem("Enter")) key = Keys::Enter;
        if (ImGui::MenuItem("Tab")) key = Keys::Tab;
        if (ImGui::MenuItem("Backspace")) key = Keys::Backspace;
        if (ImGui::MenuItem("Insert")) key = Keys::Insert;
        if (ImGui::MenuItem("Delete")) key = Keys::Delete;

        ImGui::Separator();

        if (ImGui::MenuItem("Right Arrow")) key = Keys::RightArrow;
        if (ImGui::MenuItem("Left Arrow")) key = Keys::LeftArrow;
        if (ImGui::MenuItem("Down Arrow")) key = Keys::DownArrow;
        if (ImGui::MenuItem("Up Arrow")) key = Keys::UpArrow;

        ImGui::Separator();

        if (ImGui::MenuItem("Page Up")) key = Keys::PageUp;
        if (ImGui::MenuItem("Page Down")) key = Keys::PageDown;
        if (ImGui::MenuItem("Home")) key = Keys::Home;
        if (ImGui::MenuItem("End")) key = Keys::End;
        if (ImGui::MenuItem("Caps Lock")) key = Keys::CapsLock;
        if (ImGui::MenuItem("Scroll Lock")) key = Keys::ScrollLock;
        if (ImGui::MenuItem("Num Lock")) key = Keys::NumLock;
        if (ImGui::MenuItem("Print Screen")) key = Keys::PrintScreen;
        if (ImGui::MenuItem("Pause")) key = Keys::Pause;

        ImGui::Separator();

        if (ImGui::MenuItem("F1")) key = Keys::F1;
        if (ImGui::MenuItem("F2")) key = Keys::F2;
        if (ImGui::MenuItem("F3")) key = Keys::F3;
        if (ImGui::MenuItem("F4")) key = Keys::F4;
        if (ImGui::MenuItem("F5")) key = Keys::F5;
        if (ImGui::MenuItem("F6")) key = Keys::F6;
        if (ImGui::MenuItem("F7")) key = Keys::F7;
        if (ImGui::MenuItem("F8")) key = Keys::F8;
        if (ImGui::MenuItem("F9")) key = Keys::F9;
        if (ImGui::MenuItem("F10")) key = Keys::F10;
        if (ImGui::MenuItem("F11")) key = Keys::F11;
        if (ImGui::MenuItem("F12")) key = Keys::F12;
        if (ImGui::MenuItem("F13")) key = Keys::F13;
        if (ImGui::MenuItem("F14")) key = Keys::F14;
        if (ImGui::MenuItem("F15")) key = Keys::F15;
        if (ImGui::MenuItem("F16")) key = Keys::F16;
        if (ImGui::MenuItem("F17")) key = Keys::F17;
        if (ImGui::MenuItem("F18")) key = Keys::F18;
        if (ImGui::MenuItem("F19")) key = Keys::F19;
        if (ImGui::MenuItem("F20")) key = Keys::F20;
        if (ImGui::MenuItem("F21")) key = Keys::F21;
        if (ImGui::MenuItem("F22")) key = Keys::F22;
        if (ImGui::MenuItem("F23")) key = Keys::F23;
        if (ImGui::MenuItem("F24")) key = Keys::F24;
        if (ImGui::MenuItem("F25")) key = Keys::F25;

        ImGui::Separator();

        if (ImGui::MenuItem("Num Pad Zero")) key = Keys::NumPadZero;
        if (ImGui::MenuItem("Num Pad One")) key = Keys::NumPadOne;
        if (ImGui::MenuItem("Num Pad Two")) key = Keys::NumPadTwo;
        if (ImGui::MenuItem("Num Pad Three")) key = Keys::NumPadThree;
        if (ImGui::MenuItem("Num Pad Four")) key = Keys::NumPadFour;
        if (ImGui::MenuItem("Num Pad Five")) key = Keys::NumPadFive;
        if (ImGui::MenuItem("Num Pad Six")) key = Keys::NumPadSix;
        if (ImGui::MenuItem("Num Pad Seven")) key = Keys::NumPadSeven;
        if (ImGui::MenuItem("Num Pad Eight")) key = Keys::NumPadEight;
        if (ImGui::MenuItem("Num Pad Nine")) key = Keys::NumPadNine;
        if (ImGui::MenuItem("Num Pad Decimal")) key = Keys::NumPadDecimal;
        if (ImGui::MenuItem("Num Pad Divide")) key = Keys::NumPadDivide;
        if (ImGui::MenuItem("Num Pad Multiply")) key = Keys::NumPadMultiply;
        if (ImGui::MenuItem("Num Pad Subtract")) key = Keys::NumPadSubtract;
        if (ImGui::MenuItem("Num Pad Add")) key = Keys::NumPadAdd;
        if (ImGui::MenuItem("Num Pad Enter")) key = Keys::NumPadEnter;
        if (ImGui::MenuItem("Num Pad Equal")) key = Keys::NumPadEqual;

        ImGui::Separator();

        if (ImGui::MenuItem("Mouse Button 1/Left")) key = Keys::MouseButtonLeft;
        if (ImGui::MenuItem("Mouse Button 2/Right")) key = Keys::MouseButtonRight;
        if (ImGui::MenuItem("Mouse Button 3/Middle")) key = Keys::MouseButtonMiddle;
        if (ImGui::MenuItem("Mouse Button 4")) key = Keys::MouseButton4;
        if (ImGui::MenuItem("Mouse Button 5")) key = Keys::MouseButton5;
        if (ImGui::MenuItem("Mouse Button 6")) key = Keys::MouseButton6;
        if (ImGui::MenuItem("Mouse Button 7")) key = Keys::MouseButton7;
        if (ImGui::MenuItem("Mouse Button 8/Last")) key = Keys::MouseButtonLast;

        ImGui::EndCombo();
    }
}