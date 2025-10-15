#include <AdamLib/Resources/ResManager.hpp>

using namespace AdamLib;


std::unordered_map<std::string, std::weak_ptr<Resource>> ResManager::resource_map;


