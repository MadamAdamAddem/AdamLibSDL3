#pragma once

#include <functional>
#include <forward_list>

namespace AdamLib
{



template<typename... Arguments>
class Signal
{
  struct f
  {
    uint32_t id{0};
    std::function<void(Arguments...)> func;

    f(const std::function<void(Arguments...)> _func, int _id) : func(_func), id(_id) {}
  };

  uint32_t next_id{1};

  std::forward_list<f> callbacks;

public:

  uint32_t connect(std::function<void(Arguments...)> _func)
  {
    callbacks.push_front({_func, next_id});
    return next_id++;
  }

  void emit(Arguments... args)
  {
    for(auto& f : callbacks)
    {
      f.func(args...);
    }
  }
  
  void clear()
  {
    callbacks.clear();
  }

  void disconnect(int _id)
  {
    callbacks.remove_if([_id](const f& connection) {return connection.id == _id;});
  }


  inline void operator()(Arguments... args) {emit(args...);}

};

}