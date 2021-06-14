// GLEntityManager.hpp
// Last update 13/6/2021 by Madman10K
#pragma once


namespace UVK
{
    class GLCamera;

    class GLEntityManager
    {
    public:
        static void tick(GLCamera* camera);
        static void clean();
    private:
    };
}
