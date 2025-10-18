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
class NodeInstanceController;
class NodeTemplate;

#define BMETHOD(Class, Method) std::bind(&Class::Method, this)


//! Base Node class
/*!




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

  std::unordered_map<std::string, Child> node_map_; //!< Map's node name to Child object

  std::unique_ptr<NodeInstanceController> controller_; 

  Signal<double> propogate_process_;
  Signal<Vec2> propogate_set_pos_;
  Signal<Vec2> propogate_move_pos_;

  Node* parent_;
  Node(const std::string& _name, NodeInstanceController* _controller = nullptr, Node* parent = nullptr);

  Vec2 pos_{0,0};

  std::string name_;
  std::string global_path_{"/root"};

public:

  virtual ~Node();

  virtual void process(double _dT);

  /*!
      \param _node
        The node to be added. 
        Ownership will be taken by the node this method is called on.

      \return
        True on success, false on failure.
        Failure occurs if node is already a direct child, node is direct parent, or node is this.
        On failure, ownership of _node is not taken.
  */
  bool addChild(Node* _node);

  //! Instantly deletes child specified by path. Prefer use of queueFree().
  /*!
      \param _local_path
        The local path to child node.

      \return
        True on success, false on failure.
        Failure occurs if node was not found, or if path leads to this.
        Obliteration does not occur if failure occurs.
  */  
  bool immediatelyObliterateMyChild(const std::string& _local_path);

  //! What do you think genius
  void immediatelyKillAllChildren();
  
  
  //! Removes direct child from ownership by node, returns disconnected node.
  /*!
      \param _child_name
        The name of the direct child of this node.

      \return
        Pointer to disconnected child node.
        Nullptr if child was not found from name.
  */  
  Node* disconnectChild(const std::string& _child_name);


  //! Disconnects this node and re-connects to specified parent node
  /*!
      \param _parent
        The new parent of this node.

      \return
        True on success, false on failure.
        Failure occurs if _parent is equal to current parent, or nullptr, or for any addChild failure reason.
  */  
  bool moveToBeChildOf(Node* _parent);

  //! Determines if given name follows naming conventions (NOT IMPLEMENTED)
  /*!
      \param _name
        The name to be tested.

      \return
        True if name is valid, false if invalid.
  */  
  static bool followsNameConventions(const std::string& _name);

  //! Changes this node's name (NOT FULLY IMPLEMENTED)
  /*!
      \param _name
        The name to be changed to.

      \return
        True if name is valid. Should be false if invalid, but for now always returns true.
  */  
  bool changeName(const std::string& _name);
  

  //! Prints all node's children to std::cout
  /*!
      \param _depth
        This parameter exists for recursion purposes and should be ignored. Sets initial print width.
  */  
  void printChildren(int _depth = 0);


  //! Updates this node's path variable to match reality
  void updatePath();

  //! Sets this node's global position. Child nodes will maintain relative position, but will move global position.
  /*!
      \param _pos
        The new global position to be set.
  */  
  virtual void setPos(const Vec2& _pos);

  //! Move this node's position, children will follow
  /*!
      \param _move
        The transformation to move the node's position by.
  */  
  virtual void movePos(const Vec2& _move);

  //! Get global position
  Vec2 getPos();

  //! Get global position as string
  std::string posAsString();
  

  //! Gets child located at _local_path
  /*!
      \param _local_path
        The local path to child node.

      \return
        Returns pointer to node at path, nullptr if not found.
  */  
  Node* getMyChild(const std::string& _local_path);
  
  //! Returns root singleton (Change)
  static Node& getRoot();

  //! Gets node located at _global_path
  /*!
      \param _global_path
        The global path to child node. Path must start with "/root".

      \return
        Returns pointer to node at path, nullptr if not found.
  */  
  static Node* getNode(const std::string& _global_path);

  //! Prints entire node tree starting from root
  static void  printTree();

  //! Adds node to death row to be deleted before next loop start
  /*!
      \param _to_be_deleted
        The node to be deleted. Will still be valid until next loop.
  */
  static void  queueFree(Node* _to_be_deleted);

  //! Frees queue'd nodes before next loop start
  static void  freeQueued();


};


class NodeTemplate
{
  std::vector<NodeTemplate*> children_;
  std::function<NodeInstanceController*()> controller_factory_;
protected:
  virtual Node* createNode(NodeInstanceController* _controller);

public:
  NodeTemplate(const std::string& _default_name, std::function<NodeInstanceController*()> _controller_factory = nullptr);
  ~NodeTemplate() = default;

  std::string default_name_;
  Vec2 default_pos_{0,0};
  
  bool registerChildTemplate(NodeTemplate* _child);
  Node* createInstance();

};


//! Base Node Instance Controller class
/*!

*/
class NodeInstanceController
{
  friend class Node;
  friend class NodeTemplate;

protected:

  void registerConnection(ConnectionController _connection);

  Node* self_;
  std::vector<ConnectionController> connections_;
  
  virtual void process(double _dT);
  virtual void onReady();
  virtual void onFree();
  virtual Node* self();

public:
  NodeInstanceController() = default;
  ~NodeInstanceController();

};


#define Controller(Typename) [] () -> Typename* {return new Typename();}


}