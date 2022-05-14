#include "Locale.hpp"
#include <Core/Utility.hpp>
#include <Core/Global.hpp>

UVK::LocaleManager::~LocaleManager() noexcept
{
    for (auto& a : translations)
    {
        for (auto& f : a)
        {
            f.first.clear();
            f.second.clear();
        }
        a.clear();
    }
}

void UVK::LocaleManager::openLocaleConfig()
{
    YAML::Node node;
    try
    {
        node = YAML::LoadFile("../Config/Translations/translation-base.yaml");
    }
    catch (YAML::BadFile&)
    {
        logger.consoleLog("Couldn't open the translation base file!", UVK_LOG_TYPE_WARNING);
        return;
    }

    if (node["origin-locale"])
    {
        auto str = Utility::toLower(node["origin-locale"].as<std::string>().c_str());
        auto it = str.find('-');
        if (it != std::string::npos)
            str[it] = '_';

        defaultLayout = UVK::Locale::getLocaleID(str);
        if (defaultLayout == static_cast<UVK::LocaleTypes>(-1))
        {
            logger.consoleLog("A non-valid default layout string was submitted! String: ", UVK_LOG_TYPE_ERROR, str);
            return;
        }
        currentLayout = defaultLayout;
    }

    const auto& strings = node["strings"];
    if (strings)
        for (const auto& a : strings)
            translations[static_cast<int>(currentLayout)].push_back({ a.as<std::string>(), a.as<std::string>() });

    if (exists(std_filesystem::path("../Config/Translations/")))
    {
        YAML::Node node2;
        for (auto& a : std_filesystem::directory_iterator(std_filesystem::path("../Config/Translations/")))
        {
            if (a.path().filename() != "translation-base.yaml" && (a.path().extension().string() == ".yaml" || a.path().extension().string() == ".yml"))
            {
                try
                {
                    node2 = YAML::LoadFile(a.path().string());
                }
                catch (YAML::BadFile&)
                {
                    continue;
                }
                auto tmp = a.path().filename().string();
                tmp.erase(tmp.find_last_of('.'));
                auto id = Locale::getLocaleID(Utility::toLower(tmp.c_str()));
                if (node2["strings"])
                    for (const auto& f : node2["strings"])
                        if (f["string"] && f["translation"])
                            translations[static_cast<int>(id)].push_back({ f["string"].as<std::string>(), f["translation"].as<std::string>() });
            }
        }
    }
}

const UVK::FString& UVK::LocaleManager::getLocaleString(String original, UVK::LocaleTypes locale) noexcept
{
    auto& arr = translations[static_cast<int>(locale)];
    for (auto& a : arr)
        if (a.first == original)
            return a.second;
    logger.consoleLog("Couldn't find the translated string for locale ", UVK_LOG_TYPE_WARNING, UVK::Locale::getLocaleName(locale, true), ". Reverting to default layout ", UVK::Locale::getLocaleName(defaultLayout, true), "!");
    return emptyString;
}

constexpr const char* UVK::Locale::getLocaleName(UVK::LocaleTypes types, bool bShort) noexcept
{
    if (bShort)
        return UVK::LocaleManager::localeString[static_cast<int>(types)];
    return UVK::LocaleManager::localeStringFull[static_cast<int>(types)];
}

UVK::FString& UVK::Locale::getLocaleString(String original, UVK::LocaleTypes locale) noexcept
{
    for (auto& a : global.localeManager.translations[static_cast<int>(locale)])
        if (a.first == original)
            return a.second;
    logger.consoleLog("Couldn't find string in locale ", UVK_LOG_TYPE_WARNING, Locale::getLocaleName(locale, true), "! Reverting to original layout!");
    for (auto& a : global.localeManager.translations[static_cast<int>(locale)])
        if (a.first == original)
            return a.second;
    return global.localeManager.emptyString;
}

UVK::LocaleTypes& UVK::Locale::getCurrentLayout() noexcept
{
    return global.localeManager.currentLayout;
}

UVK::LocaleTypes& UVK::Locale::getFallbackLayout() noexcept
{
    return global.localeManager.defaultLayout;
}

UVK::LocaleTypes UVK::Locale::getLocaleID(const FString& str) noexcept
{
    for (size_t ret = 0; ret < 229; ret++)
        if (UVK::LocaleManager::localeString[ret] == str)
            return static_cast<UVK::LocaleTypes>(ret);
    return static_cast<UVK::LocaleTypes>(-1);
}
