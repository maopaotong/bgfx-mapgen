#pragma once
#include <bgfx/bgfx.h>
#include "FileUtil.h"
namespace mg
{
    struct ShaderUtil
    {

        static bgfx::ProgramHandle loadProgram(std::string vname, std::string fname, std::string group)
        {
            std::string vfile = "shaders/" + group + "/" + vname + ".vert.sc.bin";
            std::string ffile = "shaders/" + group + "/" + fname + ".frag.sc.bin";
            const bgfx::Memory *vMem = FileUtil::load(vfile);
            const bgfx::Memory *fMem = FileUtil::load(ffile);
            bgfx::ShaderHandle vsh = bgfx::createShader(vMem);
            bgfx::ShaderHandle fsh = bgfx::createShader(fMem);
            bgfx::ProgramHandle handle = bgfx::createProgram(vsh, fsh, true /* destroy shaders when program is destroyed */);

            return handle;
        }
    };
};