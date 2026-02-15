#pragma once
#include <vector>
#include "renderable.h"
#include "Entity00.h"
#include "Entity01.h"
#include "Entity02.h"

namespace mg
{

    struct AllRenderables : public RenderableTuple<Entity00, Entity01, Entity02>
    {
        INJECT(AllRenderables(Entity00 *e0, Entity01 *e1, Entity02 *e2)) : RenderableTuple(e0, e1, e2)
        {
        }
    };

};