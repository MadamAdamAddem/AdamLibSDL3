#pragma once

#include "Resource.h"
#include <memory>
#include <unordered_map>
#include <string>


namespace AdamLib
{


namespace ResManager
{

  extern std::unordered_map<std::string, std::weak_ptr<Resource>> resource_map;

  template <IsResource T>
  std::shared_ptr<T> requestResource(const std::string& path)
  {
    if(resource_map.contains(path))
    {
      if(!resource_map[path].expired())
        return std::static_pointer_cast<T>(resource_map[path].lock());
    }

    std::shared_ptr<T> sp = std::make_shared<T>();
    sp->createResource(path);
    resource_map[path] = std::dynamic_pointer_cast<Resource>(sp);

    return sp;
  }


};

}