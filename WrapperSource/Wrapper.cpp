#include "Wrapper.hpp"
#include <UVKLog.h>

void Wrapper::wbegin()
{
#ifdef UVK_COMPILING_WITH_MODS
    std::cout << "begin modded" << std::endl;
#else
    std::cout << "begin regular" << std::endl;
#endif
}

void Wrapper::wend()
{
#ifdef UVK_COMPILING_WITH_MODS
    std::cout << "end modded" << std::endl;
#else
    std::cout << "end regular" << std::endl;
#endif
}