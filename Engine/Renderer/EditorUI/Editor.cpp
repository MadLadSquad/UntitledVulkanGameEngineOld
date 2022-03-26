#include "Editor.hpp"
#ifndef PRODUCTION
#include <Renderer/EditorUI/Widgets/Windows/SceneHierarchy.hpp>
#include <Renderer/EditorUI/Widgets/Windows/DetailsPanel.hpp>
#include <Renderer/EditorUI/Widgets/Windows/Statistics.hpp>
#include <Renderer/EditorUI/Widgets/Windows/WorldSettings.hpp>
#include <Renderer/EditorUI/Widgets/Windows/MemoryEditor.hpp>
#include <Renderer/EditorUI/Widgets/Windows/TopToolbar.hpp>
#include <Renderer/EditorUI/Widgets/Windows/TerminalEmulator.hpp>
#include <Renderer/EditorUI/Widgets/Windows/Filesystem.hpp>
#include <Renderer/EditorUI/Widgets/Windows/Tools.hpp>
#include <Renderer/EditorUI/Widgets/Windows/EditorViewport.hpp>

#include <Renderer/EditorUI/Widgets/Prompts/SaveLevel.hpp>
#include <Renderer/EditorUI/Widgets/Prompts/CreateFile.hpp>
#include <Renderer/EditorUI/Widgets/Prompts/OpenLevelWidget.hpp>
#include <Renderer/EditorUI/Widgets/Prompts/NewLevel.hpp>
#include <Renderer/EditorUI/Widgets/Prompts/Ship.hpp>
#include <Renderer/EditorUI/Widgets/Prompts/Warnings.hpp>
#include <Renderer/EditorUI/Widgets/Prompts/RemoveFile.hpp>

#include <Renderer/EditorUI/Widgets/Info/Help.hpp>
#include <Renderer/EditorUI/Widgets/Info/About.hpp>
#include <Renderer/EditorUI/Widgets/Settings/Settings.hpp>

#include <Renderer/EditorUI/EditorUtils/Resources.hpp>
#include <Renderer/EditorUI/EditorUtils/Settings.hpp>
#include <Renderer/EditorUI/EditorUtils/GUI.hpp>

#include <UVKBuildTool/src/Utility.h>

#include <imguiex/imguizmo/ImGuizmo.h>
#include <GameFramework/GameplayClasses/Level/Level.hpp>
#include <imgui_impl_vulkan.h>

void UVK::Editor::initEditor() noexcept
{
    // Set the UVKBuildTool path
    UBT::setPath("../");

    Timer tm;
    tm.startRecording();
    EditorResources::loadConfigs(*this);
#ifdef __MINGW32__
    EditorResources::loadResources(*this);
#else
    pt = UVK_CONTENT_PATH;
    EditorResources::loadResources(*this, pt);
#endif
    EditorUtilSettings::loadImGuiSettings(*this, strings.colTheme);

    tm.stopRecording();
    frameTimeData[0] = tm.getDuration();
    bools.bEditorUsingTextbox = false;

    logger.consoleLog("Starting the renderer took: ", UVK_LOG_TYPE_NOTE, tm.getDuration(), "ms!");
}

void UVK::Editor::runEditor(FVector4& colour, GLFrameBuffer& fb, Camera& camera, UVK::Level* lvl, const float& deltaTime) noexcept
{
#ifndef PRODUCTION
    EditorUtilSettings::setImGuiSettings(*this);
    displayEditor(colour, fb, camera, lvl, deltaTime);
    EditorUtilSettings::finishImGuiRender(*this);
}

void UVK::Editor::displayEditor(FVector4& colour, GLFrameBuffer& fb, Camera& camera, UVK::Level* lvl, const float& deltaTime) noexcept
{
    accumulateUndoRedo += deltaTime;
    EditorGUIUtils::switchKeybinds(*this);
    EditorGUIUtils::renderMenubar(*this);
    ImGuiStyle& style = ImGui::GetStyle();

    if (bools.bShowDirectSaveWarning)
        Warnings::displaySaveWarning(bools.bShowDirectSaveWarning);
    if (bools.bShowExitWarning)
        Warnings::displayExitWarning(bools.bShowExitWarning);
    if (bools.bShowGenerateWarning)
        Warnings::displayGenerateWarning(bools.bShowGenerateWarning);
    if (bools.bShowSaveWarning)
        NewLevel::display(bools.bShowSaveWarning);
    if (bools.bShowSaveLevelWidget)
        bools.bEditorUsingTextbox = SaveLevel::display(bools.bShowSaveLevelWidget, strings.location, colour) || bools.bEditorUsingTextbox;
    if (bools.bShowOpenLevelWidget)
        bools.bEditorUsingTextbox = OpenLevelWidget::display(strings.openLevel, bools.bShowOpenLevelWidget, frameTimeData[1], colour) || bools.bEditorUsingTextbox;
    if (bools.bShowCreateFile1)
        bools.bEditorUsingTextbox = CreateFile::display(strings.fileOutLocation, bools.bShowCreateFile1, strings.projectName) || bools.bEditorUsingTextbox;
    if (bools.bShowDetailsPanel)
        bools.bEditorUsingTextbox = DetailsPanel::display(selectedEntity, lvl, bools.bShowDetailsPanel, moduleManager, bools.bDestroyEntity) || bools.bEditorUsingTextbox;
    if (bools.bShowSceneHierarchy)
        bools.bEditorUsingTextbox = SceneHierarchy::display(selectedEntity, entNum, bools.bShowSceneHierarchy, currentLevelFolders) || bools.bEditorUsingTextbox;
    if (bools.bShowViewport)
    {
        style.WindowPadding = ImVec2(0.0f, 0.0f);
        EditorViewport::display(fb, viewportWidth, viewportHeight, bools.bShowViewport, camera, selectedEntity, UVK::Level::getPawn(lvl)->camera.projection().data(), bools.bEditorViewportFocused);
        style.WindowPadding = ImVec2(8.0f, 8.0f);
    }
#ifndef __MINGW32__
    if (bools.bShowFilesystem)
        bools.bEditorUsingTextbox = Filesystem::display(pt, textures.fileTextures, settings.fsdata, bools.bShowFilesystem) || bools.bEditorUsingTextbox;
#endif
    if (bools.bShowToolbar)
    {
        style.WindowPadding = ImVec2(0.0f, 0.0f);
        bools.bEditorUsingTextbox = TopToolbar::display(textures.play, strings.projectName, moduleManager, bools.bShowToolbar, textures.restart, textures.stop) || bools.bEditorUsingTextbox;
        style.WindowPadding = ImVec2(8.0f, 8.0f);
    }
    if (bools.bShowTools)
        bools.bEditorUsingTextbox = Tools::display(moduleManager, bools.bShowTools) || bools.bEditorUsingTextbox;
    if (bools.bShowTerminalEmulator)
        bools.bEditorUsingTextbox = TerminalEmulator::display(strings.terminalCommand, bools.bFinalisedCommand, bools.bShowTerminalEmulator) || bools.bEditorUsingTextbox;
    if (bools.bShowMemoryEditor)
        ImGuiMemoryEditor::display(bools.bShowMemoryEditor);
    if (bools.bShowStatistics)
        Statistics::display(frameTimeData, bools.bShowStatistics);
    if (bools.bShowWorldSettings)
        bools.bEditorUsingTextbox = WorldSettings::display(colour, global.ambientLight, global.levelName, bools.bShowWorldSettings) || bools.bEditorUsingTextbox;
    if (bools.bShowAboutUs)
        About::display(strings.engineVersion, strings.projectName, strings.projectVersion, textures.logoTxt, bools.bShowAboutUs);
    if (bools.bShowHelp)
        Help::display(bools.bShowHelp);
    if (bools.bShowRemoveFile)
        bools.bEditorUsingTextbox = RemoveFile::display(bools.bShowRemoveFile) || bools.bEditorUsingTextbox;
    if (bools.bShowShip)
        bools.bEditorUsingTextbox = Shipping::display(bools.bShowShip, strings.projectName) || bools.bEditorUsingTextbox;
    if (bools.bShowWindowSettings)
        bools.bEditorUsingTextbox = UVK::SettingsWidgets::displayWindow(bools.bShowWindowSettings) || bools.bEditorUsingTextbox;
    if (bools.bShowRendererSettings)
        bools.bEditorUsingTextbox = UVK::SettingsWidgets::displayRenderer(bools.bShowRendererSettings, *this) || bools.bEditorUsingTextbox;
    if (bools.bShowKeybindSettings)
        bools.bEditorUsingTextbox = UVK::SettingsWidgets::displayKeybindEditor(bools.bShowKeybindSettings) || bools.bEditorUsingTextbox;
    if (bools.bShowGameKeybinds)
        bools.bEditorUsingTextbox = UVK::SettingsWidgets::displayKeybindGame(bools.bShowGameKeybinds) || bools.bEditorUsingTextbox;
    if (bools.bShowThemeSettings)
        bools.bEditorUsingTextbox = UVK::SettingsWidgets::displayThemeEditor(bools.bShowThemeSettings) || bools.bEditorUsingTextbox;
    if (bools.bShowGameSettings)
        bools.bEditorUsingTextbox = UVK::SettingsWidgets::displayProjectSettings(strings.projectName, strings.projectVersion, strings.engineVersion, strings.startupLevel, bools.bShowGameSettings) || bools.bEditorUsingTextbox;
    if (bools.bShowEditorSettings)
        bools.bEditorUsingTextbox = UVK::SettingsWidgets::displayEditorSettings(bools.bShowEditorSettings, *this);
    if (bools.bShowDeveloperConsole)
        loggerwidget.displayFull(bools.bShowDeveloperConsole, bools.bEditorUsingTextbox);
    moduleManager.renderIndependentModule(bools.bEditorUsingTextbox);
#endif
}

void UVK::Editor::beginFrame() noexcept
{
    if (global.bUsesVulkan)
        ImGui_ImplVulkan_NewFrame();
    else
        ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGuizmo::BeginFrame();
}

void UVK::Editor::destroyContext() noexcept
{
    ImGui::SaveIniSettingsToDisk((settings.editorLayoutLocation + ".ini").c_str());
    textures.play.destroy();
    textures.logoTxt.destroy();
    for (auto& a : textures.fileTextures)
        a.destroy();

    if (global.bUsesVulkan)
        ImGui_ImplVulkan_Shutdown();
    else
        ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
#ifndef PRODUCTION
    ImPlot::DestroyContext();
#endif
    //ImTTY::Terminal.DestroyContext();
    global.window.destroyWindow();
}

UVK::EditorPointer::EditorPointer() noexcept
{
    ptr = global.instance->editor;
}

UVK::Editor* UVK::EditorPointer::data() noexcept
{
    return ptr;
}

UVK::Texture* UVK::EditorPointer::fsicons() noexcept
{
    return ptr->textures.fileTextures;
}

#else
UVK::Editor::Editor() noexcept
{
//    global.instance->editor = this;
}

UVK::EditorPointer::EditorPointer() noexcept
{

}

UVK::Editor* UVK::EditorPointer::data() noexcept
{
    return nullptr;
}
#endif


