#pragma once
#include <concepts>
#include <string>



namespace AdamLib
{

class Resource
{
protected:


public:
  virtual void createResource(const std::string& path) = 0;
  Resource() = default;
  virtual ~Resource() = default;


};

template<typename T>
concept IsResource = std::derived_from<T, Resource>;


}