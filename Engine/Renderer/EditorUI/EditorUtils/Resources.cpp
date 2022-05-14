#include "Resources.hpp"
#include <Core/Core/Global.hpp>
#include <GameFramework/GameplayClasses/GameInstance.hpp>
#include <Renderer/EditorUI/Editor.hpp>

void UVK::EditorResources::loadConfigs(Editor& editor) noexcept
{
    // Assign the global editor instance to the current editor instance
    global.instance->editor = &editor;
    // Open the editor locale config
    global.localeManager.openLocaleConfig(true);

    // Get the short key string for the SHIFT and CTRL actions
    auto bindText = Utility::keyToText(Input::getAction("editor-bind-modifier").keyCode, false);
    auto shiftText = Utility::keyToText(Input::getAction("editor-shift").keyCode, false);

    // Assign the strings in the EditorKeys struct, this struct contains keycode combinations strings that are used as hints on menu items
    editor.keys = EditorKeys
    {
        .editor_level_save = bindText + "+" + Utility::keyToText(Input::getAction("editor-level-save").keyCode, false),
        .editor_level_new = bindText + "+" + Utility::keyToText(Input::getAction("editor-level-new").keyCode, false),
        .editor_level_saveas = bindText + "+" + shiftText + "+" + Utility::keyToText(Input::getAction("editor-level-saveas").keyCode, false),
        .editor_level_open = bindText + "+" + Utility::keyToText(Input::getAction("editor-level-open").keyCode, false),
        .editor_new_file = bindText + "+" + shiftText + "+" + Utility::keyToText(Input::getAction("editor-new-file").keyCode, false),
        .editor_undo = bindText + "+" + Utility::keyToText(Input::getAction("editor-undo").keyCode, false),
        .editor_redo = bindText + "+" + Utility::keyToText(Input::getAction("editor-redo").keyCode, false),
    };

    // Open the project config file
    YAML::Node file;
    try
    {
        file = YAML::LoadFile(UVK::FString(UVK_CONFIG_PRJ_PATH) + "uvproj.yaml");
    }
    catch (YAML::BadFile&)
    {
        logger.consoleLog("Could not find uvproj.yaml file", UVK_LOG_TYPE_ERROR);
        std::terminate();
    }

    if (file["engine-version"] && file["name"] && file["version"] && file["startup-level"])
    {
        // Assign the version, engine version, name and startup level strings to the EditorStrings struct. They are used to enable editing in editor
        editor.strings.engineVersion = file["engine-version"].as<std::string>();
        editor.strings.projectVersion = file["version"].as<std::string>();
        editor.strings.projectName = file["name"].as<std::string>();
        editor.strings.startupLevel = file["startup-level"].as<std::string>();
    }

    try
    {
        // Open the editor config file to assign settings to be changed later
        file = YAML::LoadFile(UVK::FString(UVK_CONFIG_SETTINGS_PATH) + "Editor.yaml");
    }
    catch (YAML::BadFile&)
    {
        logger.consoleLog("Could not open the Config/Settings/Editor.yaml file! Switching to default settings!", UVK_LOG_TYPE_ERROR);
    }

    if (file["filesystem-file-padding"])
        editor.settings.fsdata.padding = file["filesystem-file-padding"].as<float>();
    if (file["filesystem-file-thumbnail-size"])
        editor.settings.fsdata.imageSize = file["filesystem-file-thumbnail-size"].as<float>();
    if (file["filesystem-using-previews"])
        editor.settings.fsdata.bUsePreviews = file["filesystem-using-previews"].as<bool>();
    if (file["filesystem-max-preview-files"])
        editor.settings.fsdata.maxFileNum = file["filesystem-max-preview-files"].as<uint32_t>();
    if (file["max-saved-transactions"])
    {
        auto i = file["max-saved-transactions"].as<uint32_t>();
        editor.settings.maxSavedTransactions = i <= 5 ? 100 : i;
    }
    if (file["editor-layout-location"])
        editor.settings.editorLayoutLocation = UVK_CONFIG_SETTINGS_PATH + file["editor-layout-location"].as<std::string>();
    global.instance->stateTracker.init();
}

#ifndef __MINGW32__
void UVK::EditorResources::loadResources(Editor& editor, std_filesystem::path& pt) noexcept
{
    editor.textures.play = Texture(static_cast<UVK::FString>(pt.string() + "Engine/play.png"));
    editor.textures.play.loadImgui();

    editor.textures.logoTxt = Texture(static_cast<UVK::FString>(pt.string() + "Engine/logo.png"));
    editor.textures.logoTxt.loadImgui();

    editor.textures.fileTextures[UVK::EditorTextures::FS_ICON_AUDIO] = Texture(static_cast<UVK::FString>(pt.string() + "Engine/audio.png"));
    editor.textures.fileTextures[UVK::EditorTextures::FS_ICON_AUDIO].loadImgui();

    editor.textures.fileTextures[UVK::EditorTextures::FS_ICON_IMAGE] = Texture(static_cast<UVK::FString>(pt.string() + "Engine/image.png"));
    editor.textures.fileTextures[UVK::EditorTextures::FS_ICON_IMAGE].loadImgui();

    editor.textures.fileTextures[UVK::EditorTextures::FS_ICON_VIDEO] = Texture(static_cast<UVK::FString>(pt.string() + "Engine/video.png"));
    editor.textures.fileTextures[UVK::EditorTextures::FS_ICON_VIDEO].loadImgui();

    editor.textures.fileTextures[UVK::EditorTextures::FS_ICON_FOLDER] = Texture(static_cast<UVK::FString>(pt.string() + "Engine/folder.png"));
    editor.textures.fileTextures[UVK::EditorTextures::FS_ICON_FOLDER].loadImgui();

    editor.textures.fileTextures[UVK::EditorTextures::FS_ICON_FONT] = Texture(static_cast<UVK::FString>(pt.string() + "Engine/font.png"));
    editor.textures.fileTextures[UVK::EditorTextures::FS_ICON_FONT].loadImgui();

    editor.textures.fileTextures[UVK::EditorTextures::FS_ICON_MODEL] = Texture(static_cast<UVK::FString>(pt.string() + "Engine/obj.png"));
    editor.textures.fileTextures[UVK::EditorTextures::FS_ICON_MODEL].loadImgui();

    editor.textures.fileTextures[UVK::EditorTextures::FS_ICON_UNKNOWN] = Texture(static_cast<UVK::FString>(pt.string() + "Engine/unknown.png"));
    editor.textures.fileTextures[UVK::EditorTextures::FS_ICON_UNKNOWN].loadImgui();

    editor.textures.fileTextures[UVK::EditorTextures::FS_ICON_CODE] = Texture(static_cast<UVK::FString>(pt.string() + "Engine/code.png"));
    editor.textures.fileTextures[UVK::EditorTextures::FS_ICON_CODE].loadImgui();

    editor.textures.fileTextures[UVK::EditorTextures::FS_ICON_CLOSE] = Texture(static_cast<UVK::FString>(pt.string() + "Engine/close.png"));
    editor.textures.fileTextures[UVK::EditorTextures::FS_ICON_CLOSE].loadImgui();

    editor.textures.restart = Texture(static_cast<UVK::FString>(pt.string() + "Engine/refresh.png"));
    editor.textures.restart.loadImgui();

    editor.textures.stop = Texture(static_cast<UVK::FString>(pt.string() + "Engine/stop.png"));
    editor.textures.stop.loadImgui();
}
#else
void UVK::EditorResources::loadResources(Editor& editor) noexcept
{
    editor.textures.play = Texture(static_cast<UVK::FString>("../Content/Engine/play.png"));
    editor.textures.play.loadImgui();

    editor.textures.logoTxt = Texture(static_cast<UVK::FString>("../Content/Engine/logo.png"));
    editor.textures.logoTxt.loadImgui();

    editor.textures.fileTextures[0] = Texture(static_cast<UVK::FString>("../Content/Engine/audio.png"));
    editor.textures.fileTextures[0].loadImgui();

    editor.textures.fileTextures[1] = Texture(static_cast<UVK::FString>("../Content/Engine/image.png"));
    editor.textures.fileTextures[1].loadImgui();

    editor.textures.fileTextures[2] = Texture(static_cast<UVK::FString>("../Content/Engine/video.png"));
    editor.textures.fileTextures[2].loadImgui();

    editor.textures.fileTextures[3] = Texture(static_cast<UVK::FString>("../Content/Engine/folder.png"));
    editor.textures.fileTextures[3].loadImgui();

    editor.textures.fileTextures[4] = Texture(static_cast<UVK::FString>("../Content/Engine/font.png"));
    editor.textures.fileTextures[4].loadImgui();

    editor.textures.fileTextures[5] = Texture(static_cast<UVK::FString>("../Content/Engine/obj.png"));
    editor.textures.fileTextures[5].loadImgui();

    editor.textures.fileTextures[6] = Texture(static_cast<UVK::FString>("../Content/Engine/unknown.png"));
    editor.textures.fileTextures[6].loadImgui();

    editor.textures.fileTextures[7] = Texture(static_cast<UVK::FString>("../Content/Engine/code.png"));
    editor.textures.fileTextures[7].loadImgui();

    editor.textures.fileTextures[UVK::EditorTextures::FS_ICON_CLOSE] = Texture("../Content/Engine/close.png");
    editor.textures.fileTextures[UVK::EditorTextures::FS_ICON_CLOSE].loadImgui();

    editor.textures.restart = Texture("../Content/Engine/refresh.png");
    editor.textures.restart.loadImgui();

    editor.textures.stop = Texture("../Content/Engine/stop.png");
    editor.textures.stop.loadImgui();
}
#endif