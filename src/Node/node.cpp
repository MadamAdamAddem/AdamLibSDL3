#include "../include/Node.h"

using namespace AdamLib;



Script::Script(PFunc _p, RFunc _r) : process_f(_p), ready_f(_r) {}

Node::Node(std::string _name, Script _script) :  name_(_name), process_(_script.process_f), ready_(_script.ready_f) {}
Node::~Node()
{
  propogate_process_.clear();
}

void Node::process(double dT)
{
  if(process_)
    process_(dT, this);

  propogate_process_.emit(dT);
}


void Node::add_child(Node* _child)
{
  node_map[_child->name_].process_id  = propogate_process_.connect(std::bind(&Node::process, _child, std::placeholders::_1));
  node_map[_child->name_].child.reset(_child);

}

void Node::remove_child(std::string _name)
{
  if(!node_map.contains(_name))
    return;

  propogate_process_.disconnect(node_map[_name].process_id);
  node_map.erase(_name);
}

