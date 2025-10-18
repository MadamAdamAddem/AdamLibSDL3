#include <AdamLib/Nodes/Node.hpp>
#include <cstddef>
#include <unordered_set>
#include <iostream>
using namespace AdamLib;



std::unordered_set<std::string> to_be_freed;



// Script::Script(PFunc _p, RFunc _r, FFunc _f) : 
//   process_f(_p), 
//   ready_f(_r),
//   free_f(_f)
//   {}

Node::Node(const std::string& _name, NodeInstanceController* _controller, Node* _parent) :
  name_(_name),
  controller_(_controller),
  parent_(_parent)
{
  if(controller_)
  {
    controller_->self_ = this;
    controller_->onReady();
  }
}

Node::~Node()
{
    
  propogate_process_.clear();
}



void Node::process(double _dT)
{
  if(controller_)
    controller_->process(_dT);

  propogate_process_.emit(_dT);

}

bool Node::addChild(Node* _node)
{
  if(node_map_.contains(_node->name_) || _node == this || _node == parent_)
    return false;


  _node->parent_ = this;

  auto& child = node_map_[_node->name_];

  child.child_.reset(_node);

  child.process_connection_ = (propogate_process_.connect(
    std::bind(&Node::process, _node, std::placeholders::_1)
  ));

  child.set_pos_connection_ = (propogate_set_pos_.connect(
    std::bind(&Node::setPos, _node, std::placeholders::_1)
  ));

  child.move_pos_connection_ = (propogate_move_pos_.connect(
    std::bind(&Node::movePos, _node, std::placeholders::_1)
  ));

  


  _node->updatePath();

  return true;
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
    c.second.child_->immediatelyKillAllChildren();
  }

  node_map_.clear();
}

void Node::printChildren(int _depth)
{
  std::cout << "\n";
  if(node_map_.empty())
    return;



  for(auto& kid : node_map_)
  {
    for(int i=0; i<_depth; ++i)
      std::cout << "    ";
    
    std::cout << kid.first << "/";
    kid.second.child_->printChildren(_depth + 1);
  }

  std::cout << std::endl;
}

void Node::updatePath()
{
  if(!parent_)
    global_path_ = "/" + name_;
  else
    global_path_ = parent_->global_path_ + "/" + name_;

  for(auto& c : node_map_)
  {
    c.second.child_->updatePath();
  }
}

Node* Node::getMyChild(const std::string& _local_path)  
{
  if(_local_path.empty())
    return this;


  size_t pos = _local_path.find('/');
  size_t i = (pos == std::string::npos) ? _local_path.size() : pos;
  std::string first = _local_path.substr(0, i++);

  if(i > _local_path.size())
    i = _local_path.size();

  if(node_map_.contains(first))
    return node_map_[first].child_->getMyChild(_local_path.substr(i));
  else
    return nullptr;

  
}

bool Node::changeName(const std::string& _name)
{
  auto node_extract = parent_->node_map_.extract(name_);
  node_extract.key() = _name;
  parent_->node_map_.insert(std::move(node_extract));
  name_ = _name;

  return true;
}

Node* Node::disconnectChild(const std::string& _child_name)
{
  if(!node_map_.contains(_child_name))
    return nullptr;

  Node* child = node_map_[_child_name].child_.release();
  node_map_.erase(_child_name);
  return child;
}

bool Node::moveToBeChildOf(Node* _parent)
{
  if(_parent == nullptr || _parent == parent_)
    return false;

  parent_->disconnectChild(name_);
  return _parent->addChild(this);
}



void Node::setPos(const Vec2& _pos) 
{
  auto diff = _pos - pos_;
  movePos(diff);
}

void Node::movePos(const Vec2& _move) 
{
  pos_ += _move;
  propogate_move_pos_.emit(_move);
}

Vec2 Node::getPos() 
{
  return pos_;
}

std::string Node::posAsString()
{
  return std::string("(" + std::to_string(pos_.x) + "," + std::to_string(pos_.y) + ")");
}

//static:

Node& Node::getRoot()
{
  static Node root{"root", nullptr};
  return root;
}

Node* Node::getNode(const std::string& _global_path)
{
  std::string path = _global_path.substr(6);
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
    Node* tmp = Node::getNode(n);
    if(tmp)
    {
      if(tmp->controller_)
        tmp->controller_->onFree();
    }

  }

  for (auto& n : to_be_freed) 
  {
    Node* tmp = Node::getNode(n);
    if(tmp)
    {
      tmp->parent_->immediatelyObliterateMyChild(tmp->name_);
    }

  }
  to_be_freed.clear();
}






//-----NodeTemplate:

NodeTemplate::NodeTemplate(const std::string& _default_name, std::function<NodeInstanceController*()> _controllerfact) :
  default_name_(_default_name), controller_factory_(_controllerfact)
{
  
}


bool NodeTemplate::registerChildTemplate(NodeTemplate* _child)
{
  if(!_child)
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
  NodeInstanceController* controller = (controller_factory_ ? controller_factory_() : nullptr);
  Node* self = createNode(controller);
  
  for(auto& c : children_)
  {
    self->addChild(c->createInstance());
  }

  self->setPos(default_pos_);
  return self;
}

Node* NodeTemplate::createNode(NodeInstanceController* _controller)
{
  return new Node(default_name_, _controller);
}



//----NodeInstanceController:
NodeInstanceController::~NodeInstanceController()
{
  for(auto& c : connections_)
  {
    c.disconnect();
  }
}

void NodeInstanceController::registerConnection(ConnectionController _controller) 
{
  connections_.push_back(_controller);
}

Node* NodeInstanceController::self() {return self_;}


void NodeInstanceController::process(double _dT) {}

void NodeInstanceController::onReady() {}

void NodeInstanceController::onFree() {}

//---- No Controller