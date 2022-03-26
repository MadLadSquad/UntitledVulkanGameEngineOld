#include "GUI.hpp"
#include <imgui.h>
#include <GameFramework/GameplayClasses/Level/Level.hpp>
#include <Core/Global.hpp>
#include <Renderer/EditorUI/Editor.hpp>

void UVK::EditorGUIUtils::renderMenubar(Editor& editor) noexcept
{
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            // TODO: Change this for file indexing :D
            if (ImGui::MenuItem("Save Level", editor.keys.editor_level_save.c_str()))
                editor.bools.bShowDirectSaveWarning = true;
            if (ImGui::MenuItem("Save Level As", editor.keys.editor_level_saveas.c_str()))
                editor.bools.bShowSaveLevelWidget = true;
            if (ImGui::MenuItem("New Level", editor.keys.editor_level_new.c_str()))
                editor.bools.bShowSaveWarning = true;
            if (ImGui::MenuItem("Open Level", editor.keys.editor_level_open.c_str()))
                editor.bools.bShowOpenLevelWidget = true;
            if (ImGui::MenuItem("New File", editor.keys.editor_new_file.c_str()))
                editor.bools.bShowCreateFile1 = true;
            if (ImGui::MenuItem("Remove File"))
                editor.bools.bShowRemoveFile = true;
            if (ImGui::MenuItem("Regenerate files"))
                editor.bools.bShowGenerateWarning = true;
            if (ImGui::MenuItem("Ship Project"))
                editor.bools.bShowShip = true;
            if (ImGui::MenuItem("Exit"))
                editor.bools.bShowExitWarning = true;

            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Undo", editor.keys.editor_undo.c_str()))
                global.instance->stateTracker.undo();
            if (ImGui::MenuItem("Redo", editor.keys.editor_redo.c_str()))
                global.instance->stateTracker.redo();

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Settings"))
        {
            if (ImGui::MenuItem("Game Settings"))
                editor.bools.bShowGameSettings = true;
            if (ImGui::MenuItem("Editor Settings"))
                editor.bools.bShowEditorSettings = true;
            if (ImGui::MenuItem("Window Settings"))
                editor.bools.bShowWindowSettings = true;
            if (ImGui::MenuItem("Renderer Settings"))
                editor.bools.bShowRendererSettings = true;
            if (ImGui::MenuItem("Editor Keybind Settings"))
                editor.bools.bShowKeybindSettings = true;
            if (ImGui::MenuItem("Game Keybind Settings"))
                editor.bools.bShowGameKeybinds = true;
            if (ImGui::MenuItem("Theme Editor"))
                editor.bools.bShowThemeSettings = true;

            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("View"))
        {
            ImGui::Checkbox("Filesystem", &editor.bools.bShowFilesystem);
            ImGui::Checkbox("Statistics", &editor.bools.bShowStatistics);
            ImGui::Checkbox("Viewport", &editor.bools.bShowViewport);
            ImGui::Checkbox("Details Panel", &editor.bools.bShowDetailsPanel);
            ImGui::Checkbox("Terminal Emulator", &editor.bools.bShowTerminalEmulator);
            ImGui::Checkbox("Scene Hierarchy", &editor.bools.bShowSceneHierarchy);
            ImGui::Checkbox("World Settings", &editor.bools.bShowWorldSettings);
            ImGui::Checkbox("Toolbar", &editor.bools.bShowToolbar);
            ImGui::Checkbox("Tools", &editor.bools.bShowTools);
            ImGui::Checkbox("Memory Editor", &editor.bools.bShowMemoryEditor);
            ImGui::Checkbox("Developer Console", &editor.bools.bShowDeveloperConsole);

            if (!editor.moduleManager.getIndependentModules().empty())
            {
                ImGui::Separator();

                for (auto& a : editor.moduleManager.getIndependentModules())
                    ImGui::Checkbox(a.name, &a.bEnabled);
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("More"))
        {
            if (ImGui::MenuItem("About us"))
                editor.bools.bShowAboutUs = true;

            if (ImGui::MenuItem("Help"))
                editor.bools.bShowHelp = true;
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    ImGui::End();
    editor.bools.bEditorUsingTextbox = false;
}

void UVK::EditorGUIUtils::switchKeybinds(UVK::Editor& editor) noexcept
{
    if ((Input::getAction("editor-bind-modifier") == Keys::KeyPressed || Input::getAction("editor-bind-modifier") == Keys::KeyRepeat) && (Input::getAction("editor-shift") == Keys::KeyPressed || Input::getAction("editor-shift") == Keys::KeyRepeat) && (Input::getAction("editor-level-saveas") == Keys::KeyPressed || Input::getAction("editor-level-saveas") == Keys::KeyRepeat))
        editor.bools.bShowSaveLevelWidget = true;
    else if ((Input::getAction("editor-bind-modifier") == Keys::KeyPressed || Input::getAction("editor-bind-modifier") == Keys::KeyRepeat) && (Input::getAction("editor-level-save") == Keys::KeyPressed || Input::getAction("editor-level-save") == Keys::KeyRepeat))
    {
        // TODO: Change this for file indexing :D
        UVK::Level::save(global.levelLocation.c_str());
    }
    else if ((Input::getAction("editor-bind-modifier") == Keys::KeyPressed || Input::getAction("editor-bind-modifier") == Keys::KeyRepeat) && (Input::getAction("editor-shift") == Keys::KeyPressed || Input::getAction("editor-shift") == Keys::KeyRepeat) && (Input::getAction("editor-new-file") == Keys::KeyPressed || Input::getAction("editor-new-file") == Keys::KeyRepeat))
        editor.bools.bShowCreateFile1 = true;
    else if ((Input::getAction("editor-bind-modifier") == Keys::KeyPressed || Input::getAction("editor-bind-modifier") == Keys::KeyRepeat) && (Input::getAction("editor-level-new") == Keys::KeyPressed || Input::getAction("editor-level-new") == Keys::KeyRepeat))
        editor.bools.bShowSaveWarning = true;
    else if ((Input::getAction("editor-bind-modifier") == Keys::KeyPressed || Input::getAction("editor-bind-modifier") == Keys::KeyRepeat) && (Input::getAction("editor-level-open") == Keys::KeyPressed || Input::getAction("editor-level-open") == Keys::KeyRepeat))
        editor.bools.bShowOpenLevelWidget = true;
    else if (((Input::getAction("editor-bind-modifier") == Keys::KeyPressed || Input::getAction("editor-bind-modifier") == Keys::KeyRepeat) && Input::getAction("editor-undo") == Keys::KeyPressed) && editor.accumulateUndoRedo >= 0.3 && !editor.bools.bEditorUsingTextbox)
    {
        global.instance->stateTracker.undo();
        editor.accumulateUndoRedo = 0.0f;
    }
    else if (((Input::getAction("editor-bind-modifier") == Keys::KeyPressed || Input::getAction("editor-bind-modifier") == Keys::KeyRepeat) && Input::getAction("editor-redo") == Keys::KeyPressed) && !editor.bools.bEditorUsingTextbox && editor.accumulateUndoRedo >= 1.0)
    {
        global.instance->stateTracker.redo();
        editor.accumulateUndoRedo = 0.0f;
    }
}
