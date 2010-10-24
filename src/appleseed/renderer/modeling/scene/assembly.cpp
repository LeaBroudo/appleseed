
//
// This source file is part of appleseed.
// Visit http://appleseedhq.net/ for additional information and resources.
//
// This software is released under the MIT license.
//
// Copyright (c) 2010 Francois Beaune
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

// Interface header.
#include "assembly.h"

using namespace foundation;
using namespace std;

namespace renderer
{

//
// Assembly class implementation.
//

struct Assembly::Impl
{
    string                      m_name;
    ColorContainer              m_colors;
    TextureContainer            m_textures;
    TextureInstanceContainer    m_texture_instances;
    BSDFContainer               m_bsdfs;
    EDFContainer                m_edfs;
    SurfaceShaderContainer      m_surface_shaders;
    MaterialContainer           m_materials;
    LightContainer              m_lights;
    ObjectContainer             m_objects;
    ObjectInstanceContainer     m_object_instances;
};

namespace
{
    const UniqueID g_class_uid = new_guid();
}

Assembly::Assembly(
    const char*         name,
    const ParamArray&   params)
  : Entity(g_class_uid, params)
  , impl(new Impl())
{
    assert(name);

    impl->m_name = name;

    m_flushable = m_params.get_optional<bool>("flushable", false);
}

Assembly::~Assembly()
{
    delete impl;
}

void Assembly::release()
{
    delete this;
}

const char* Assembly::get_name() const
{
    return impl->m_name.c_str();
}

ColorContainer& Assembly::colors() const
{
    return impl->m_colors;
}

TextureContainer& Assembly::textures() const
{
    return impl->m_textures;
}

TextureInstanceContainer& Assembly::texture_instances() const
{
    return impl->m_texture_instances;
}

BSDFContainer& Assembly::bsdfs() const
{
    return impl->m_bsdfs;
}

EDFContainer& Assembly::edfs() const
{
    return impl->m_edfs;
}

SurfaceShaderContainer& Assembly::surface_shaders() const
{
    return impl->m_surface_shaders;
}

MaterialContainer& Assembly::materials() const
{
    return impl->m_materials;
}

LightContainer& Assembly::lights() const
{
    return impl->m_lights;
}

ObjectContainer& Assembly::objects() const
{
    return impl->m_objects;
}

ObjectInstanceContainer& Assembly::object_instances() const
{
    return impl->m_object_instances;
}


//
// AssemblyFactory class implementation.
//

auto_release_ptr<Assembly> AssemblyFactory::create(
    const char*         name,
    const ParamArray&   params)
{
    return auto_release_ptr<Assembly>(new Assembly(name, params));
}

}   // namespace renderer
