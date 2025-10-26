#pragma once

#include <functional>
#include <cstdint>
#include <forward_list>

namespace AdamLib
{

struct SignalGeneric
{
  virtual ~SignalGeneric() = default;
  
  virtual void disconnect(uint32_t _id) = 0;
};

struct ConnectionController
{
  ConnectionController(SignalGeneric* _signal, uint32_t _id) : signal_(_signal), connection_id_(_id) {}
  SignalGeneric* signal_ = nullptr;
  uint32_t connection_id_{0};
  void disconnect()
  {
    if(signal_)
    {
      signal_->disconnect(connection_id_);
      reset();
    }
  }

  void reset()
  {
    signal_ = nullptr;
    connection_id_ = 0;
  }
};




template<typename... Arguments>
class Signal : public SignalGeneric
{
  struct f
  {
    uint32_t id_{0};
    std::function<void(Arguments...)> func;

    f(const std::function<void(Arguments...)> _func, uint32_t _id) : func(_func), id_(_id) {}
  };

  uint32_t next_id{0};

  std::forward_list<f> callbacks;

public:

  ConnectionController connect(std::function<void(Arguments...)> _func)
  {
    callbacks.emplace_front(_func, ++next_id);
    return ConnectionController(this, next_id);
  }

  void emit(Arguments... args)
  {
    for(auto& f : callbacks)
    {
      f.func(args...);
    }
  }
  
  void disconnect(uint32_t _id)
  {
    callbacks.remove_if([_id](const f& func){return func.id_ == _id;});
  }

  void clear()
  {
    callbacks.clear();
  }


  inline void operator()(Arguments... args) {emit(args...);}

};

}