#pragma once

#include <memory>
#include <string>
#include "ResourcesInternal.hpp"

namespace AdamLib
{


namespace ResManager
{

  enum ResourceType
  {
    Invalid,
    Texture,
    Audio
  };
  
  std::shared_ptr<Resource> requestResource(const std::string& _path, ResourceType _type);

};

}