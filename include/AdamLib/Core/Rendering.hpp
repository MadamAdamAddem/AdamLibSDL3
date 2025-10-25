#pragma once
#include <AdamLib/Defines.hpp>
#include <AdamLib/Math.hpp>

namespace AdamLib
{

class TextureInstance;

namespace Renderer
{

  struct SetOfPoints;

  //! I wonder what this one does
  void render_all();

  //! Adds given instance to render queue, must be removed manually
  void addTexture(TextureInstance* _res);

  //! Removes given instance from render queue.
  void removeRenderable(TextureInstance* _res);


};


}