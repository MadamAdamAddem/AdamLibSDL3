#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include <vector>

#include <AdamLib/Math.hpp>
#include <AdamLib/Signal.hpp>


namespace AdamLib
{


class Node;
class NodeTemplate;
class NodeInstanceController;

#define BMETHOD(Class, Method) std::bind(&Class::Method, this)

/*

To Do:

  -Add on-ready node initialization.
    Ex: Node* n_node = get_node_on_ready(..., &n_node);
    Returns nullptr if node not ready or existent
    When node is loaded, fill n_node with ptr to node

  -Solve node being able to have (itself or parent) as child
  -Solve node being able to have (itself or child) as parent

  -Optimize node-path system

*/

class Node
{
  friend class NodeTemplate;

protected:
  struct Child
  {
    Child() = default;
    ~Child()
    {
      process_connection_.disconnect();
      set_pos_connection_.disconnect();
      move_pos_connection_.disconnect();
    }

    ConnectionController process_connection_;
    ConnectionController set_pos_connection_;
    ConnectionController move_pos_connection_;

    std::unique_ptr<Node> child_;
  };

  std::unordered_map<std::string, Child> node_map;

  std::unique_ptr<NodeInstanceController> controller_;

  Signal<double> propogate_process_;
  Signal<Vec2> propogate_set_pos_;
  Signal<Vec2> propogate_move_pos_;

  Node* parent_;
  Node(const std::string& _name, NodeInstanceController* _controller = nullptr, Node* parent = nullptr);

  Vec2 pos_{0,0};

public:

  virtual ~Node();

  virtual void process(double _dT);

  //False if child not added because name does not follow constraints
  bool addChild(Node* _node);

  //False if node DNE or path is blank
  bool immediatelyObliterateMyChild(const std::string& _local_path);
  bool immediatelyKillAllChildren();
  
  //returns child, nullptr if child DNE
  Node* disconnectChild(const std::string& _child_name);

  bool moveToBeChildOf(Node* _parent);

  //True if name matches naming constraints
  bool isValidName(const std::string& _name);

  //False if name unchanged because newname does not follow constraints
  bool changeName(const std::string& _name);
  

  void printChildren(int depth = 0);
  void updatePath();

  virtual void setPos(const Vec2& _pos);
  virtual void movePos(const Vec2& _move);
  Vec2 getPos();
  std::string posAsString();
  

  //nullptr on failure to find child, empty string returns self (warning)
  Node* getMyChild(const std::string& _local_path);
  

  static Node& getRoot();
  static Node* getNode(const std::string& _global_path);
  static Node* getParentOf(const std::string& _global_path);
  static void  printTree();
  static void  queueFree(Node* tbd);
  static void  freeQueued();

  std::string name_;
  std::string global_path_{"/root"};
  
};



class NodeTemplate
{
protected:
  std::vector<NodeTemplate*> children_;

public:
  NodeTemplate(const std::string& _name, NodeInstanceController* _controller = nullptr);
  ~NodeTemplate() = default;

  std::string name_;
  NodeInstanceController* controller_;
  Vec2 default_pos_{0,0};


  //recommended to not use allocated memory
  //if so, freeing is your responsibility
  //returns false if invalid name
  bool registerChildTemplate(NodeTemplate* _child);

  virtual Node* createInstance();

};






struct NodeInstanceController
{
  NodeInstanceController() = default;
  ~NodeInstanceController();

  void registerConnection(ConnectionController _connection);

  Node* subject_;
  std::vector<ConnectionController> connections_;
  
  virtual void process(double _dT);
  virtual void ready();
  virtual void onFree();
  virtual Node* self();

};




}