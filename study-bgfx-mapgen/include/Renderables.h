#pragma once
#include <vector>
#include "renderable/Renderable.h"
#include "Entity00.h"
#include "Entity01.h"
#include "Entity02.h"

namespace mg
{

    template <typename... Ts>
    struct Renderables
    {

        std::tuple<Ts...> renderables;

        Renderables()
        {
        }

        int init()
        {
            int es = 0;
            std::apply([&es, this](Ts &...e)
                       {
                           ([&es, &e]()
                            {
                                int err = e.init();
                                if (err)
                                {
                                    es++;
                                } //
                            }(),
                            ...); //
                       },
                       renderables);
            return es > 0 ? -1 : 0;
        }

        void submit()
        {
            std::apply([](Ts &...e)
                       { (e.submit(), ...); }, renderables);
        }
        void destroy()
        {
            std::apply([](Ts &...e)
                       { (e.destroy(), ...); }, renderables);
        }
    };

    struct AllRenderables : public Renderables<Entity00, Entity01, Entity02>
    {
        INJECT(AllRenderables())
        {
        }
    };

};