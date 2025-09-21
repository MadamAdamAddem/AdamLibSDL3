#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include "Math.h"
#include "Signal.h"


namespace AdamLib
{

class Node;

struct Script
{
  using PFunc = std::function<void(double, Node*)>;
  using RFunc = std::function<void(Node*)>;

  Script(PFunc _p = nullptr, RFunc _r = nullptr);
  PFunc process_f;
  RFunc ready_f;
};


class Node
{
  struct Child
  {
    int process_id;
    std::unique_ptr<Node> child;
  };

  std::unordered_map<std::string, Child> node_map;

  using PFunc = std::function<void(double, Node*)>;
  using RFunc = std::function<void(Node*)>;

  PFunc process_;
  RFunc ready_;

  Signal<double> propogate_process_;
public:

  Node(std::string _name, Script _script = Script());
  virtual ~Node();

  Vec2 pos{0,0};

  virtual void process(double dT);

  void add_child(Node* child);
  void remove_child(std::string _name);

  std::string name_;

};

}