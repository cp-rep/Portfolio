#ifndef WAVLTREE_H
#define WAVLTREE_H
#include <iostream>
#include <vector>

// explanations for public member functions are provided in project2.h
// each file that uses a WAVL tree should #include this file 
template <typename KeyType, typename ValType>
class WAVLTree {
	public:
		// DO NOT MODIFY PUBLIC MEMBERS BELOW THIS LINE
		WAVLTree();
		~WAVLTree();
		void insert(KeyType key, ValType val);
		ValType find(const KeyType& key);
		int getSize();
		int getHeight();
		int getRank(const KeyType& key);
		// DO NOT MODIFY PUBLIC MEMBERS ABOVE THIS LINE
		
		// define new public members
		struct Node
		{
		  KeyType m_key;
		  ValType m_rc; 
		  int m_rank;
		  Node* m_left;
		  Node* m_right;
		  int m_height;
		  ValType m_brc;
		};

		// first fit
		KeyType insertFirst(const ValType& val);
		KeyType findFirst(const ValType& val, Node* in_node);
		bool testBucket(const ValType& val, Node* in_node);
		void updateF(std::vector<double>& in_free_space);
		void updateFree(Node* in_node, std::vector<double>& in_free_space);
		ValType fixLargest(Node* in_node);

		// public member variables
		Node* m_root;
		Node* m_next;
		Node* m_prev;
		int m_size;

		// public member functions
		void deleteTree(Node* in_node);
		Node* deleteNode(Node* in_node, KeyType in_key);
		Node* getMinimum(Node* in_node);
		int compareHeight(Node* in_node);
		Node* insertNode(Node* in_node, KeyType in_key,
				               ValType in_val);
		int get_height(Node* in_node);
		Node* rebalance(Node* in_node);
		Node *rightRotation(Node* in_node);
		Node *leftRotation(Node* in_node);
		
	private:
		// private member variables
		int m_count;

		// private member functions
		Node* makeNode(const KeyType &key, const ValType &val);
		
}; // end of "WAVLTree"



// ==== constructor =======================================================
//
// ========================================================================
template <typename KeyType, typename ValType>
WAVLTree<KeyType, ValType>::WAVLTree()
{
  m_root = nullptr;
  m_next = nullptr;
  m_prev = nullptr;
  m_size = 0;
  m_count = 0;
  
} // end of "constructor"



// ==== destructor ========================================================
//
// ========================================================================
template <typename KeyType, typename ValType>
WAVLTree<KeyType, ValType>::~WAVLTree()
{
  deleteTree(m_root);
} // end of "destructor"



// ==== insert ============================================================
//
// ========================================================================
template <typename KeyType, typename ValType>
void WAVLTree<KeyType, ValType>::insert(KeyType key, ValType val)
{
  m_root = insertNode(m_root, key, val);
} // end of "insert"



// ==== find ==============================================================
//
// ========================================================================
template <typename KeyType, typename ValType>
ValType WAVLTree<KeyType, ValType>::find(const KeyType& key)
{
  Node* temp = m_root;

  while(temp != nullptr)
    {
      if(temp->m_key < key)
	{
	  temp = temp->m_right;
	}
      else if(temp->m_key > key)
	{
	  temp = temp->m_left;
	}
      else
	{
	  return temp->m_rc;
	}
    }
  
    return -1;
} // end of "find"



// ==== getSize ===========================================================
//
// ========================================================================
template <typename KeyType, typename ValType>
int WAVLTree<KeyType, ValType>::getSize()
{
  return m_size;
} // end of "getSize"



// ==== getHeight =========================================================
//
// ========================================================================
template <typename KeyType, typename ValType>
int WAVLTree<KeyType, ValType>::getHeight()
{
  // returns total height of tree
  if(m_root != nullptr)
      return m_root->m_height;
  else
    return 0;
} // end of "getHeight"



// ==== getRank ===========================================================
//
// ========================================================================
template <typename KeyType, typename ValType>
int WAVLTree<KeyType, ValType>::getRank(const KeyType& key)
{
  return m_root->m_height;
} // end of "getRank"



// ==== makeNode ==========================================================
//
// ========================================================================
template <typename KeyType, typename ValType>
  typename WAVLTree<KeyType, ValType>::Node* WAVLTree<KeyType,
  ValType>::makeNode(const KeyType &key, const ValType &val)
{
  Node* n = new Node;
  n->m_left = nullptr;
  n->m_right = nullptr;
  n->m_key = key;
  n->m_rc = val;
  n->m_rank = 0;
  n->m_height = 1;
  n->m_brc = val;
  n->m_rank = n->m_height;

  return n;
} // end of "makeNode"



// ==== deleteNode ========================================================
// 
// ========================================================================
template <typename KeyType, typename ValType>
  typename WAVLTree<KeyType, ValType>::Node* WAVLTree<KeyType,
           ValType>::deleteNode(Node* in_node, KeyType in_key)
{

  if(in_node == nullptr)
    return nullptr;
  // check if key is in left sub
  if(in_key < in_node->m_key)
    {
      in_node->m_left = deleteNode(in_node->m_left, in_key);
    }
  // check if key is in right sub
  else if(in_key > in_node->m_key)
    {
      in_node->m_right = deleteNode(in_node->m_right, in_key);
    }
  else
    {
      // no children
      if(in_node->m_left == nullptr && in_node->m_right == nullptr)
	{
	  m_size--;
	  delete in_node;
	  in_node = nullptr;
	}
      // right child
      else if(in_node->m_left == nullptr)
	{
	  m_size--;	  
	  Node* temp = in_node;
	  in_node = in_node->m_right;
	  delete temp;
	}
      // left child
      else if (in_node->m_right == nullptr)
	{
	  m_size--;	  
	  Node* temp = in_node;
	  in_node = in_node->m_left;
	  delete temp;
	}
      // two children
      else
	{
	  Node* temp = getMinimum(in_node->m_right);
	  in_node->m_key = temp->m_key;
	  in_node->m_right = deleteNode(in_node->m_right, temp->m_key);
	}
    }

    return rebalance(in_node);
} // end of "deleteNode"



// ==== getMinimum ======================================================
// 
// ========================================================================
template <typename KeyType, typename ValType>
  typename WAVLTree<KeyType, ValType>::Node* WAVLTree<KeyType,
                           ValType>::getMinimum(Node* in_node)
{
  Node* temp = in_node;

  while(temp->m_left != nullptr)
    temp = temp->m_left;

  return temp;
} // end of "getMinimum"



// ==== rightRotation =====================================================
// 
// ========================================================================
template <typename KeyType, typename ValType>
  typename WAVLTree<KeyType, ValType>::Node* WAVLTree<KeyType,
                        ValType>::rightRotation(Node* in_node)  
{
  Node* temp1, *temp2;

  temp1 = in_node->m_left;
  temp2 = temp1->m_right;
  temp1->m_right = in_node;
  in_node->m_left = temp2;
  
  in_node->m_height = std::max(get_height(in_node->m_left),
			       get_height(in_node->m_right)) + 1;
  
  temp1->m_height = std::max(get_height(temp1->m_left),
			     in_node->m_height) + 1;

  in_node->m_rank = in_node->m_height;
  temp1->m_rank = temp1->m_height;
  
  return temp1;
} // end of "rightRotation"



// ==== leftRotation ======================================================
// 
// ========================================================================
template <typename KeyType, typename ValType>
  typename WAVLTree<KeyType, ValType>::Node* WAVLTree<KeyType,
                         ValType>::leftRotation(Node* in_node)
{
  Node *temp1, *temp2;
  
  temp1 = in_node->m_right;
  temp2 = temp1->m_left;
  temp1->m_left = in_node;
  in_node->m_right = temp2;
  
  in_node->m_height = std::max(get_height(in_node->m_left),
			 get_height(in_node->m_right)) + 1;
  
  temp1->m_height = std::max(get_height(in_node->m_right),
			           in_node->m_height) + 1;

  in_node->m_rank = in_node->m_height;
  temp1->m_rank = temp1->m_height;

  return temp1;
} // end of "leftRotation"



// ==== compareHeight ======================================================
// 
// ========================================================================
template <typename KeyType, typename ValType>
int  WAVLTree<KeyType, ValType>::compareHeight(Node *in_node)
{
  return get_height(in_node->m_left) - get_height(in_node->m_right);    
} // end of "compareHeight"



// ==== insertNode ========================================================
// 
// ========================================================================
template <typename KeyType, typename ValType>
  typename WAVLTree<KeyType, ValType>::Node* WAVLTree<KeyType,
  ValType>::insertNode(Node* in_node, KeyType in_key,
		                        ValType in_val)
{
  if(in_node == nullptr)
    {
      m_size++;
      
      return (makeNode(in_key, in_val));
    }
  
  if(in_key < in_node->m_key)
    {
      in_node->m_left = insertNode(in_node->m_left, in_key, in_val);
    }
  else
    {
      in_node->m_right = insertNode(in_node->m_right, in_key, in_val);
    }

  return rebalance(in_node);
} // end of "insertNode"



// ==== get_height ========================================================
// 
// ========================================================================
template <typename KeyType, typename ValType>
  int WAVLTree<KeyType, ValType>::get_height(Node* in_node)
{
  if(in_node == nullptr)
    return 0;
  return in_node->m_height;
} // end of "get_height"



// ==== rebalance =========================================================
//
// ========================================================================
template <typename KeyType, typename ValType>
               typename WAVLTree<KeyType, ValType>::Node* WAVLTree<KeyType,
                                         ValType>::rebalance(Node* in_node)
{
  if(in_node == nullptr)
    return in_node;

  in_node->m_height = 1 + std::max(get_height(in_node->m_left),
				   get_height(in_node->m_right));
  if(in_node->m_height == 1)
    in_node->m_rank = 0;

  int difference = compareHeight(in_node);

  if(difference > 1 && compareHeight(in_node->m_left) >= 0)
    return rightRotation(in_node);

  if(difference < -1 && compareHeight(in_node->m_right) <= 0)
    return leftRotation(in_node);

  if(difference > 1 && compareHeight(in_node->m_left) < 0)
    {
      in_node->m_left = leftRotation(in_node->m_left);
      return rightRotation(in_node);
    }
  if(difference < -1 && compareHeight(in_node->m_right) > 0)
    {
      in_node->m_right = rightRotation(in_node->m_right);
      return leftRotation(in_node);
    }
  
  return in_node;
} // end of "rebalance"



// ==== deleteTree ========================================================
// 
// ========================================================================
template <typename KeyType, typename ValType>
  void WAVLTree<KeyType, ValType>::deleteTree(Node* in_node)
{
  if(in_node == nullptr)
    return;

  deleteTree(in_node->m_left);
  deleteTree(in_node->m_right);
  in_node->m_left = nullptr;
  in_node->m_right = nullptr;
  in_node->m_key = 0;
  in_node->m_rc = 0;
  in_node->m_brc = 0;
  delete in_node;
  m_size--;      
} // end of "deleteTree"



// ** FIRST FIT DATA **
// ==== insertFirst ======================================================
// 
// ========================================================================
template<typename KeyType, typename ValType>
  KeyType WAVLTree<KeyType, ValType>::insertFirst(const ValType& in_item)
{
  KeyType temp1;
  
  temp1 = findFirst(in_item, m_root);

  if(temp1 < 0)
    {
      temp1 = m_size + 1;
      ValType remaining = 1 - in_item;
      insert(temp1, remaining);
      return temp1;
    }
  
  fixLargest(m_root);
  return temp1;      
} // end of "insertFirst"



// ==== findFirst ========================================================
// 
// ========================================================================
template<typename KeyType, typename ValType>
  KeyType WAVLTree<KeyType, ValType>::findFirst(const ValType& in_item,
						             Node* in_node)
{
  KeyType temp;

  // default
  if(in_node == nullptr)
    return -1;

  // see if the item will fit on the left side
  if(in_node->m_left != nullptr)
    {
      if(in_node->m_left->m_brc - in_item > 0)
	{
	  if((temp = findFirst(in_item, in_node->m_left)) > 0)
	    return temp;
	}
      else if(std::abs(in_node->m_left->m_brc - in_item) < 1e-3)
	{
	  if((temp = findFirst(in_item, in_node->m_left)) > 0)
	    return temp;
	}
    }
  // it didn't fit left.  test the parent
  if(in_node->m_rc - in_item > 0)
    {
      in_node->m_rc = std::max(in_node->m_rc - in_item, 0.0000);
      return in_node->m_key;
    }
  else if(std::abs(in_node->m_rc - in_item) < 1e-3)
    {
      in_node->m_rc = std::max(in_node->m_rc - in_item, 0.0000);
      return in_node->m_key;
    }
  // it didn't fit on the left or in the parent. test the right side
  else if(in_node->m_right != nullptr)
    {
      if(in_node->m_right->m_brc - in_item > 0)
	{
	  if((temp = findFirst(in_item, in_node->m_right)) > 0)
	    return temp;
	}
      else if(std::abs(in_node->m_right->m_brc - in_item) < 1e-3)
	{
	  if((temp = findFirst(in_item, in_node->m_right)) > 0)
	    return temp;
	}
    }

  return -1;
}  // end of "findFirst"



// ==== testBucket ==========================================================
// 
// ========================================================================
template<typename KeyType, typename ValType>
  bool WAVLTree<KeyType, ValType>::testBucket(const ValType& in_item, Node* in_node)
{
  if(in_node != nullptr)
    {
      if(0 < in_node->m_brc - in_item)
	return true;
      else if(std::abs(1e-3 > in_node->m_brc - in_item))
	return true;
    }
  
  return false;
} // end of "testBucket"



// ==== updateF ===========================================================
// 
// ========================================================================
template <typename KeyType, typename ValType>
  void WAVLTree<KeyType, ValType>::updateF(std::vector<double>& in_free_space)
{
  updateFree(m_root, in_free_space);
} // end of "updateF"



// ==== updateFree ========================================================
// 
// ========================================================================
template <typename KeyType, typename ValType>
  void WAVLTree<KeyType, ValType>::updateFree(Node* in_node,
					std::vector<double>& in_free_space)
{
  if(in_node != nullptr)
    {
      updateFree(in_node->m_left, in_free_space);
      in_free_space.push_back(in_node->m_rc);
      updateFree(in_node->m_right, in_free_space);      
    }
  
  return; 
} // end of "updateFree"



// ==== fixLargest ========================================================
// 
// ========================================================================
template<typename KeyType, typename ValType>
  ValType WAVLTree<KeyType, ValType>::fixLargest(Node* in_node)
{
  if(in_node != nullptr)
    {
      in_node->m_brc = std::max(fixLargest(in_node->m_left), fixLargest(in_node->m_right));
      in_node->m_brc = std::max(in_node->m_brc, in_node->m_rc);
      return in_node->m_brc;
    }
  
    return 0;
} // end of "fixLargest"

#endif /* WAVLTREE_H */
