#pragma once
#include <vector>
#include "Renderable.h"
namespace mg
{

    struct ListRenderable : public Renderable
    {
        
        std::vector<Renderable *> list;

        int init() override
        {
            for (Renderable *r : list)
            {
                if (r->init())
                {
                    return -1;
                }
            }
            return 0;
        }
        void submit() override
        {
            for (Renderable *r : list)
            {
                r->submit();
            }
        }
        void destroy() override
        {
            for (Renderable *r : list)
            {
                r->destroy();
            }
        }
    };
};