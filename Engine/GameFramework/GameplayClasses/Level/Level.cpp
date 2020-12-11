// Level.cpp
// Last update 12/8/2020 by Stanislav Vasilev(Madman10K)

#include "Level.hpp"

void UVK::Level::Serialise(String output)
{

}
void UVK::Level::Deserialise(AssetReference assetRef)
{
    if (assetRef.Type == 4)
    {
        std::cout << "A level asset was passed" << std::endl;
    }
    else
    {
        throw std::runtime_error("An invalid asset type was passed as level. If you are a user contact the developer of the application about this. If you are a developer use the ASSET_TYPE macros instead of plane integers and monitor what asset types you are passing to the given asset function!");
    }
}
