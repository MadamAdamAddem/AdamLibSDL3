#pragma once
#include <AdamLib/Nodes/Node.hpp>


/*

  This is a header designed to be modified for any new node types you may want to create.

  Find and Replace 'NewNode' with the name of your node type, preferably in the format '<Name>Node' for consistency.
  Find and Replace 'BaseNode' with the name of the node you wish to derive from (Ex: BaseNode->CollisionNode),
  then remove the macros following this comment.

  Basic implementations of the methods are provided in the header file, but should be relocated to a cpp file.

  Any other instance where the code shown contains simply 'Node' is required to stay that way, do not modify to 'BaseNode'.

*/

#define BaseNode Node
#define BaseNodeTemplate NodeTemplate
#define BaseNodeInstanceController NodeInstanceController

namespace AdamLib
{

class NewNode;
class NewNodeTemplate;
class NewNodeInstanceController;

class NewNode : public BaseNode
{
  friend class NewNodeTemplate;
  
protected:
  //BaseNode constructor parameters will have to be adjusted manually to match desired basenode type
  NewNode(const std::string& _name, NodeInstanceController* _controller = nullptr, Node* _parent = nullptr) :
  BaseNode(_name, _controller, _parent)
  {
    /*
      ...
    */
  }

public:

  //Optional, override only if needed for some reason (Ex: Managed resource must have its position moved when this node is moved)
  virtual void movePos(const Vec2& _move) override
  {
    Node::movePos(_move); //Must be called first to ensure propogation. After call, pos_ will already be updated to reflect move.

    /*
      ...
    */
  }
};


struct NewNodeInstanceController : public BaseNodeInstanceController
{
  NewNodeInstanceController() = default;
  NewNode* self() override;
};

class NewNodeTemplate : public BaseNodeTemplate
{

protected:

  /*
    Mandatory override for proper instantiation. 
    If your template class contains any data that must be used to instantiate a node, this is where you'd do it.
    Constructor parameters may have to change to match NewNode. 
  */
  virtual Node* createNode(NodeInstanceController* _controller) override
  {
    return new NewNode(default_name_, _controller);
  }

public:

  //Constructor parameters may have to change to match BaseNode and NewNode.
  NewNodeTemplate(const std::string& _name, std::function<NewNodeInstanceController*()> _controller_factory = nullptr) :
  BaseNodeTemplate(_name, _controller_factory)
  {

  }
};



//Macro to allow user to create NewNode factory easier
#define NewNodeController(Typename) [] () -> NewNodeInstanceController* {return static_cast<NewNodeInstanceController*>(new Typename());}


}