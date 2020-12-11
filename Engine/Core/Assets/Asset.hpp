// Asset.hpp
// Last update 12/7/2020 by Stanislav Vasilev(Madman10K)
#pragma once
#include <Core.hpp>

namespace UVK
{
    UVK_API struct AssetReference
    {
        String Name;
        String Location;
        int Type;
    };

    UVK_API class Asset
    {
    public:
        AssetReference AddAsset(int type, String location, String name)
        {
            AssetReference ref;

            ref.Location = location;
            ref.Name = name;
            ref.Type = type;
/*
            switch (type)
            {
                case 0:

                case 1:

                case 2:

                case 3:

                case 4:

                default:

            }
*/
            return ref;

        }


    private:
    };
}
