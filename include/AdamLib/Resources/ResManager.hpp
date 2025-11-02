#pragma once

#include <AdamLib/Resources/Resource.hpp>
#include <memory>
#include <string>


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