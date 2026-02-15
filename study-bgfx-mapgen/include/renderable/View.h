#pragma once

#include <bx/bx.h>
#include <bgfx/bgfx.h>
#include <tuple>

#define WNDW_WIDTH 1600
#define WNDW_HEIGHT 900
#define PROJ_FAR 1000000
namespace mg
{
    struct View
    {
        float view[16];
        float proj[16];
        bgfx::ViewId vid;

        View(bgfx::ViewId _vid) : vid(_vid)
        {
        }

        virtual void init() = 0;

        void update()
        {
            bgfx::setViewTransform(vid, view, proj);
        }
    };
    
    template <typename... Ts>
    struct ViewTuple
    {

        std::tuple<Ts*...> tuple;

        ViewTuple(Ts*...views):tuple(views...)
        {

        }
        void init()
        {
            std::apply([](Ts *...e)
                       { (e->init(), ...); }, tuple);
        }
        void update()
        {
            std::apply([](Ts *...e)
                       { (e->update(), ...); }, tuple);
        }
    };

};