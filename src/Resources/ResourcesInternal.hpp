#pragma once
#include <SDL3/SDL_render.h>
#include <string>

namespace AdamLib
{

  class Resource
  {
  protected:


  public:
    virtual void initializeResource(const std::string& path) = 0;
    Resource() = default;
    virtual ~Resource() = default;


  };


  class TextureResource : public Resource
  {
  public:

    TextureResource();
    ~TextureResource();

    virtual void initializeResource(const std::string& _path) override;

    inline SDL_Texture* getTexture() {return texture_;}

    SDL_Texture* texture_;
    
  };

}