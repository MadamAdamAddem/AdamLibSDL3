#include <AdamLib/Nodes/Node.hpp>
#include <AdamLib/Defines.hpp>
#include <unordered_set>
#include <iostream>

using namespace AdamLib;



std::unordered_set<std::string> to_be_freed;


Node::Node(std::string _name, NodeInstanceController* _controller, Node* _parent) :
  parent_(_parent), controller_(_controller), name_(std::move(_name))
{
  if(controller_)
    controller_->self_ = this;
  
}

Node::~Node()
{
  propagate_move_pos_.clear();
  propagate_process_.clear();
}


/*-----Child SubClass-----*/
Node::Child::Child(ConnectionController&& _process_connection, ConnectionController&& _move_pos_connection, Node* _child_node) :
  process_connection_(std::move(_process_connection)), move_pos_connection_(std::move(_move_pos_connection)), child_node_(_child_node) {}

Node::Child::Child(Child&& _c) noexcept :
  process_connection_(std::move(_c.process_connection_)), move_pos_connection_(std::move(_c.move_pos_connection_)), child_node_(_c.child_node_.release()) 
{

}

Node::Child::~Child()
{
  process_connection_.disconnect();
  move_pos_connection_.disconnect();
}
/*-----Child SubClass-----*/


void Node::process(double _dT)
{
  if(controller_)
    controller_->process(_dT);

  propagate_process_.emit(_dT);

}


/*-----Path and Name Management-----*/

void Node::updatePath()
{
  if(!parent_)
    global_path_ = "/" + name_;
  else
    global_path_ = parent_->global_path_ + "/" + name_;

  for(const auto& [name, child] : node_map_)
  {
    child.child_node_->updatePath();
  }
}

bool Node::followsNameConventions(const std::string &_name)
{
  if(_name.find('/') == std::string::npos)
    return true;

  
  return false;
}

/*-----Path and Name Management-----*/


/*-----Children Management-----*/

bool Node::addChild(Node* _node)
{
  
  if(_node == this || _node == parent_ || _node->parent_ == this)
    return false;

  while(node_map_.contains(_node->name_))
    _node->name_.push_back(CHAR_TO_APPEND);
  
  


  _node->parent_ = this;

  auto pp = propagate_process_.connect(
    [=] (const double _arg) {_node->process(_arg);}
    );

  auto pmp = propagate_move_pos_.connect(
  [=] (const Vec2& _arg) {_node->movePos(_arg);}
    );

  node_map_.emplace(
    _node->name_, Child{std::move(pp), std::move(pmp), _node}
    );

  _node->updatePath();
  return true;
}

Node* Node::getMyChild(const std::string& _local_path)  
{
  if(_local_path.empty())
    return this;


  const size_t pos = _local_path.find('/');
  size_t i = (pos == std::string::npos) ? _local_path.size() : pos;
  const std::string first = _local_path.substr(0, i++);

  if(i > _local_path.size())
    i = _local_path.size();

  if(const auto it = node_map_.find(first); it != node_map_.end())
    return it->second.child_node_->getMyChild(_local_path.substr(i));
  else
    return nullptr;

  
}

Node* Node::disconnectChild(const std::string& _child_name)
{
  const auto it = node_map_.find(_child_name);
  if(it == node_map_.end())
    return nullptr;

  Node* child = it->second.child_node_.release();
  node_map_.erase(_child_name);
  return child;
}

bool Node::immediatelyObliterateMyChild(const std::string& _local_path)
{
  Node* tbd_child = getMyChild(_local_path);
  if(tbd_child == nullptr || tbd_child == this)
    return false;


  
  tbd_child->immediatelyKillAllChildren();
  node_map_.erase(tbd_child->name_);  
  return true;
}

void Node::immediatelyKillAllChildren()
{
  for(auto& c : node_map_)
  {
    c.second.child_node_->immediatelyKillAllChildren();
  }

  node_map_.clear();
}

bool Node::moveToBeChildOf(Node* _parent)
{
  if(_parent == nullptr || _parent == parent_)
    return false;

  if(parent_ != nullptr)
    parent_->disconnectChild(name_);

  return _parent->addChild(this);
}

void Node::printChildren(int _depth) const
{
  std::cout << "\n";
  if(node_map_.empty())
    return;



  for(auto& [name, child] : node_map_)
  {
    for(int i=0; i<_depth; ++i)
      std::cout << "   ";
    
    std::cout << name << "/";
    child.child_node_->printChildren(_depth + 1);
  }

}
/*-----Children Management-----*/


/*-----Position Management-----*/

void Node::setPos(const Vec2& _pos) 
{
  auto diff = _pos - pos_;
  movePos(diff);
}

void Node::movePos(const Vec2& _move) 
{
  pos_ += _move;
  propagate_move_pos_.emit(_move);
}

std::string Node::posAsString() const
{
  return std::string("(" + std::to_string(pos_.x) + "," + std::to_string(pos_.y) + ")");
}

/*-----Position Management-----*/

//static:

Node& Node::getRoot()
{
  static Node root{"root", nullptr};
  return root;
}

Node* Node::getNode(const std::string& _global_path)
{
  const std::string path = _global_path.substr(6);
  return getRoot().getMyChild(path);
}

void Node::printTree()
{
  Node& root = Node::getRoot();
  std::cout << root.name_ << "/";

  root.printChildren(1);

}

void Node::queueFree(Node* tbd)
{
  if(tbd)
    to_be_freed.insert(tbd->global_path_);
}

void Node::freeQueued() 
{

  //run this first to ensure any onFree overrides have full access to all nodes
  //probably should be optimized
  for (auto& n : to_be_freed) 
  {
    if(const Node* tmp = Node::getNode(n))
    {
      if(tmp->controller_)
        tmp->controller_->onFree();
    }

  }

  for (auto& n : to_be_freed) 
  {
    if(const Node* tmp = Node::getNode(n))
    {
      tmp->parent_->immediatelyObliterateMyChild(tmp->name_);
    }

  }
  to_be_freed.clear();
}






//-----NodeTemplate:

NodeTemplate::NodeTemplate(std::string _default_name, std::function<NodeInstanceController*()> _controller_factory) :
controller_factory_(std::move(_controller_factory)), default_name_(std::move(_default_name)) {}

bool NodeTemplate::registerChildTemplate(NodeTemplate* _child)
{
  if(!_child)
    return false;

  if(_child == this)
    return false;

  if(_child->default_name_.find('/') != std::string::npos)
    return false;

  //Performance shouldn't matter since template creation will only happen once at beginning
  //technically O(n^2) but wtv
  for(auto& c : children_)
  {
    if(c->default_name_ == _child->default_name_)
      return false;
  }

  children_.push_back(_child);

  return true;
}

Node* NodeTemplate::createInstance()
{
  Node* self = createNode((controller_factory_ ? controller_factory_() : nullptr));
  
  for(auto& c : children_)
  {
    self->addChild(c->createInstance());
  }

  self->setPos(default_pos_);
  if(self->controller_)
    self->controller_->onReady();

  return self;
}



//----NodeInstanceController:
void NodeInstanceController::registerConnection(ConnectionController&& _controller) 
{
  connections_.emplace_back(std::move(_controller));
}

Node* NodeInstanceController::self() {return self_;}

void NodeInstanceController::process(double _dT) {}

void NodeInstanceController::onReady() {}

void NodeInstanceController::onFree() {}

//---- No Controller