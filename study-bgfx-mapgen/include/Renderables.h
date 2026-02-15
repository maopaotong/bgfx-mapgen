#pragma once
#include <vector>
#include "renderable/Renderable.h"
#include "Entity00.h"
#include "Entity01.h"
#include "Entity02.h"

namespace mg
{

    struct Renderables
    {

        Entity00 r00;
        Entity01 r01;
        Entity02 r02;

        int init()
        {
            int err0 = r00.init();
            int err1 = r01.init();
            int err2 = r02.init();
            return (err0 && err1 && err2) ? -1 : 0;
        }

        void submit()
        {
            r00.submit();
            r01.submit();
            r02.submit();
        }
        void destroy()
        {
            r00.destroy();
            r01.destroy();
            r02.destroy();
        }
    };
};