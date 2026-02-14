#pragma once
#include "renderable.h"
#include "Common.h"
#include <array>

namespace mg
{

    struct Entity00 : public Entity
    {

        Entity00() : Entity("s00")
        {
        }
        int init() override
        {
            int err = Entity::init();
            if (err)
            {
                return err;
            }

            vlayout.begin()
                .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
                .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
                .end();

            int vCount = 8;

            const PosColorVertex *vertices = new PosColorVertex[vCount]{
                {0.0f, 0.0f, 00.0f, 0xff, 0xff, 0xff, 0xff}, // 0
                {1.0f, 0.0f, 00.0f, 0xff, 0x00, 0x00, 0xff}, // 1 r
                {0.0f, 1.0f, 00.0f, 0x00, 0xff, 0x00, 0xff}, // 2 g
                {0.0f, 0.0f, -1.0f, 0x00, 0x00, 0xff, 0xff}, // 3 b
            };
            /*


                2
                |
                | 3
                |/
                0--------1
            */
            
            int iCount = 3 * 3;
            const uint16_t *tlist = new uint16_t[iCount]{
                // clang-format off
                0,1,2,//
                0,3,1,//
                0,2,3,//
                // clang-format on
            };

            vbh = bgfx::createVertexBuffer(bgfx::makeRef(vertices, vCount * sizeof(PosColorVertex), [](void *mData, void *uData)
                                                         { delete[] static_cast<PosColorVertex *>(mData); }),
                                           vlayout);
            ibh = bgfx::createIndexBuffer(bgfx::makeRef(tlist, iCount * sizeof(uint16_t), [](void *mData, void *uData)
                                                        { delete[] static_cast<uint16_t *>(mData); }));

            bx::mtxScale(mtx1, 10.0f, 10.0f, 10.0f);
            return 0;
        }
        
        void submit(int viewId) override
        {
            bx::mtxRotateXY(mtx2, counter * 0.01f, counter * 0.01f);
            bx::mtxMul(mtx3, mtx2, mtx1);
            bgfx::setTransform(mtx3);            

            // bgfx::setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_DEPTH_TEST_LESS, 0);

            uint64_t state = 0                            //
                             | BGFX_STATE_WRITE_RGB       //
                             | BGFX_STATE_WRITE_A         //
                             | BGFX_STATE_WRITE_Z         //
                             | BGFX_STATE_DEPTH_TEST_LESS //
                             | BGFX_STATE_CULL_CW        //
                //| BGFX_STATE_MSAA            //
                //| BGFX_STATE_PT_POINTS //
                ;
            bgfx::setState(state);
            Entity::submit(viewId);
            counter++;
        }
    };

};
