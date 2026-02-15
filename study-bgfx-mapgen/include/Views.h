#pragma once

#include <bx/bx.h>
#include <bgfx/bgfx.h>
#include "renderable.h"

#define WNDW_WIDTH 1600
#define WNDW_HEIGHT 900
#define PROJ_FAR 1000000
namespace mg
{
    struct View0 : public View
    {
        // const bx::Vec3 eye = {0.0f, 0.0f, -150.0f};//z as camera position
        // bx::Handedness::Enum handedness = bx::Handedness::Right;
        static constexpr bgfx::ViewId VID = 0;
        INJECT(View0()) : View(VID)
        {
        }
        void init() override
        {
            // bgfx::setViewClear(kClearView, BGFX_CLEAR_COLOR);
            bgfx::setViewClear(vid, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF, 1.0f, 0);
            bgfx::setViewRect(vid, 0, 0, bgfx::BackbufferRatio::Equal);

            const bx::Vec3 eye = {0.0f, 0.0f, 100.0f}; // z as camera position
            const bx::Vec3 at = {0.0f, 0.0f, 0.0f};    // zero
            const bx::Vec3 up = {0.0f, 1.0f, 0.0f};    // y as up
            MtxUtil::mtxLookAt(view, eye, at, up);
            bx::mtxProj(proj, 60.0f, float(WNDW_WIDTH) / float(WNDW_HEIGHT), 0.1f, PROJ_FAR, bgfx::getCaps()->homogeneousDepth);

            printf("View matrix:\n");
            for (int i = 0; i < 4; ++i)
            {
                printf("  [%f, %f, %f, %f]\n",
                       view[i * 4 + 0], view[i * 4 + 1], view[i * 4 + 2], view[i * 4 + 3]);
            }
        }
    };

    struct View1 : public View
    {
        static constexpr bgfx::ViewId VID = 1;
        // const bx::Vec3 eye = {0.0f, 0.0f, -150.0f};//z as camera position
        // bx::Handedness::Enum handedness = bx::Handedness::Right;
        INJECT(View1()) : View(VID)
        {
        }
        void init() override
        {
            // bgfx::setViewClear(kClearView, BGFX_CLEAR_COLOR);
            bgfx::setViewClear(vid, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF, 1.0f, 0);
            bgfx::setViewRect(vid, 0, 0, bgfx::BackbufferRatio::Equal);

            const bx::Vec3 eye = {0.0f, 0.0f, 200.0f}; // z as camera position
            const bx::Vec3 at = {0.0f, 0.0f, 0.0f};    // zero
            const bx::Vec3 up = {0.0f, 1.0f, 0.0f};    // y as up
            MtxUtil::mtxLookAt(view, eye, at, up);
            bx::mtxOrtho(proj, 0.0f, 100.0f, 0.0f, 100.0f, 0.1f, PROJ_FAR, 0.0f, bgfx::getCaps()->homogeneousDepth);

            printf("View matrix:\n");
            for (int i = 0; i < 4; ++i)
            {
                printf("  [%f, %f, %f, %f]\n",
                       view[i * 4 + 0], view[i * 4 + 1], view[i * 4 + 2], view[i * 4 + 3]);
            }
        }
    };

    struct AllViews : public ViewTuple<View0, View1>
    {
        INJECT(AllViews(View0 *v0, View1 *v1)) : ViewTuple(v0, v1)
        {
        }
    };

};