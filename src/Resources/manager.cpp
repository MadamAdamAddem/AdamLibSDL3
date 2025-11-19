#include <AdamLib/Resources/Texture.hpp>
#include "ResourcesInternal.hpp"
#include "ResManager.hpp"

#include <memory>
#include <unordered_map>
#include <cassert>

using namespace AdamLib;



std::unordered_map<std::string, std::weak_ptr<Resource>> resource_map;

std::shared_ptr<Resource> ResManager::requestResource(const std::string& _path, ResourceType _type)
{
  if(resource_map.contains(_path))
  {
    if(!resource_map[_path].expired())
      return resource_map[_path].lock();
  }

  std::shared_ptr<Resource> sp;
  switch(_type)
  {
    case Texture:
      sp = std::make_shared<TextureResource>(); break;
    case Audio:
    default:
      assert(0);
  }

  sp->initializeResource(_path);
  resource_map.emplace(_path, sp);
  return sp;
}
