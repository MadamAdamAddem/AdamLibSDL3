#pragma once
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


}