#pragma once
#include <Generated/BuildDef.hpp>
#ifndef PRODUCTION
#include <iostream>
#include <Renderer/Textures/Texture.hpp>
#include <imgui.h>


namespace CreateFile
{
    // Creates a file
    bool display(UVK::FString& fileOutLocation, bool& bShowCreateFile1, const UVK::FString& prjname) noexcept;
}
#endif