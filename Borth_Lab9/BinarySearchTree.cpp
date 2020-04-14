/* -----------------------------------------------------------------------------
 *
 * File Name:  BinarySearchTree.cpp
 * Author: Marco Borth
 * Assignment:   EECS-560 Lab 6 – Implementation of Binary Search Trees
 * Description:  BinarySearchTree methods are defined.
 * Date: 3/12/20
 *
 ---------------------------------------------------------------------------- */

template <typename T, typename K>
BinarySearchTree<T, K>::BinarySearchTree() {
	m_root = nullptr;
	nodeCount = 0;
	orderCount = 0;
}

template <typename T, typename K>
BinarySearchTree<T, K>::BinarySearchTree(const BinarySearchTree<T, K>& original) {
	m_root = recCopyHelper(original.getRoot());
}

template <typename T, typename K>
BinarySearchTree<T, K>::~BinarySearchTree() {
	clear();
	m_root = nullptr;
	//delete nodeCount;
}

template<typename T, typename K>
BinaryNode<T>* BinarySearchTree<T, K>::recCopyHelper(const BinaryNode<T>* subTreeCopy) {
  if(subTreeCopy == nullptr) {
    return nullptr;
  }
  BinaryNode<T>* nodeCopy = new BinaryNode<T>(subTreeCopy->getEntry());
	nodeCopy->inheritLeft(recCopyHelper(subTreeCopy->getLeft()));
	nodeCopy->inheritRight(recCopyHelper(subTreeCopy->getRight()));
	return nodeCopy;
}

template <typename T, typename K>
BinarySearchTree<T, K>& BinarySearchTree<T, K>::operator=(const BinarySearchTree<T, K>& original) {
	m_root = nullptr;
	nodeCount = 0;
  m_root = recCopyHelper(original.getRoot());
}

template <typename T, typename K>
void BinarySearchTree<T, K>::add(BinaryNode<T>* curSubTree, T entry) {
	if (m_root == nullptr) {
		m_root = new BinaryNode<T>(entry);
		nodeCount++;
	} else {
		addRec(m_root, entry, 0);
	}
}

template <typename T, typename K>
void BinarySearchTree<T, K>::addRec(BinaryNode<T>* curSubTree, T entry, int depth) {
	depth++;
	if (entry < curSubTree->getEntry()) {
		if (curSubTree->getLeft() == nullptr) {
			curSubTree->setLeft(entry);
			nodeCount++;
		} else {
			addRec(curSubTree->getLeft(), entry, depth);
		}
	} else {
		if (curSubTree->getRight() == nullptr) {
			curSubTree->setRight(entry);
			nodeCount++;
		} else {
			addRec(curSubTree->getRight(), entry, depth);
		}
	}

	if(depth > m_height)
		m_height = depth;
}

template <typename T, typename K>
bool BinarySearchTree<T, K>::search(K key) {
	if(m_root != nullptr) {
    return(searchRec(key, m_root));
  } else {
    return false;
  }
}

template <typename T, typename K>
bool BinarySearchTree<T, K>::searchRec(K key, BinaryNode<T>* curSubTree) {
	if (key == curSubTree->getEntry()) {
    return true;
	} else if (key < curSubTree->getEntry()) {
		if(curSubTree->getLeft() != nullptr) {
      return(searchRec(key,curSubTree->getLeft()));
    } else {
      return false;
    }
	} else {
		if(curSubTree->getRight() != nullptr) {
      return(searchRec(key,curSubTree->getRight()));
    } else {
      return false;
    }
	}
}

template <typename T, typename K>
void BinarySearchTree<T, K>::clear() {
	postOrderDelete(m_root);
	m_root = nullptr;
}

template <typename T, typename K>
void BinarySearchTree<T, K>::remove(K key) {
	if (key == m_root->getEntry()) {
		if (m_root->getLeft() == nullptr && m_root->getRight() == nullptr) // m_root has no children.
		{
			m_root->~BinaryNode();
			m_root = nullptr;
			nodeCount = 0;
		}
		else if (m_root->getLeft() != nullptr && m_root->getRight() == nullptr) // m_root has only left child.
		{
			BinaryNode<T>* temp = m_root;
			BinaryNode<T>* leftChild = m_root->getLeft();
      temp->~BinaryNode();
      m_root = leftChild;
			nodeCount--;
		}
		else if (m_root->getLeft() == nullptr && m_root->getRight() != nullptr) // m_root has only right child.
		{
			BinaryNode<T>* temp = m_root;
			BinaryNode<T>* rightChild = m_root->getRight();
      temp->~BinaryNode();
      m_root = rightChild;
			nodeCount--;
		}
		else // m_root has 2 children.
		{
			if(m_root->getRight()->getLeft() == nullptr) {
				BinaryNode<T>* leftChild = m_root->getLeft();
				BinaryNode<T>* rightChild = m_root->getRight();
				m_root->~BinaryNode();
				m_root = rightChild;
				m_root->inheritLeft(leftChild);
				nodeCount--;
			} else {
				BinaryNode<T>* rightChild = m_root->getRight();
				BinaryNode<T>* minNode = minPriority(rightChild);
				BinaryNode<T>* minNodeParent = nullptr;
				if(rightChild->getLeft()->getEntry() == minNode->getEntry()) {
					minNodeParent = rightChild;
				} else {
					minNodeParent = minPriorityParent(rightChild);
				}
				m_root->setEntry(minNode->getEntry());

				BinaryNode<T>* temp = minNodeParent->getLeft()->getRight();
				minNodeParent->getLeft()->~BinaryNode();
				minNodeParent->inheritLeft(temp);
				nodeCount--;
			}
		}
	}
	else {
		removeRec(m_root, key);
	}
}

template <typename T, typename K>
void BinarySearchTree<T, K>::removeRec(BinaryNode<T>* curSubTree, K key) {
	// removeRec should only be called if remove successfully finds a BinaryNode.
	if(key < curSubTree->getEntry()) {
    if(curSubTree->getLeft() != nullptr) {
      if(key == curSubTree->getLeft()->getEntry()) {
        if(curSubTree->getLeft()->getLeft() == nullptr && curSubTree->getLeft()->getRight() == nullptr) // curSubTree->getRight() has no children.
        {
          curSubTree->getLeft()->~BinaryNode();
          curSubTree->inheritLeft(nullptr);
					nodeCount--;
        }
        else if(curSubTree->getLeft()->getLeft() != nullptr && curSubTree->getLeft()->getRight() == nullptr) // curSubTree->getRight() has left child.
        {
          BinaryNode<T>* temp = curSubTree->getLeft()->getLeft();
        	curSubTree->getLeft()->~BinaryNode();
          curSubTree->inheritLeft(temp);
					nodeCount--;
        }
        else if(curSubTree->getLeft()->getLeft() == nullptr && curSubTree->getLeft()->getRight() != nullptr) // curSubTree->getRight() has right child.
        {
          BinaryNode<T>* temp = curSubTree->getLeft()->getRight();
          curSubTree->getLeft()->~BinaryNode();
          curSubTree->inheritLeft(temp);
					nodeCount--;
        }
        else // curSubTree->getRight() has 2 children.
        {
					if(curSubTree->getLeft()->getRight()->getLeft() == nullptr) {
						BinaryNode<T>* leftGrandChild = curSubTree->getLeft()->getLeft();
						BinaryNode<T>* rightGrandChild = curSubTree->getLeft()->getRight();
	          curSubTree->getLeft()->~BinaryNode();
	          curSubTree->inheritLeft(rightGrandChild);
						curSubTree->getLeft()->inheritLeft(leftGrandChild);
						nodeCount--;
					} else {
						BinaryNode<T>* rightGrandChild = curSubTree->getLeft()->getRight();
						BinaryNode<T>* minNode = minPriority(rightGrandChild);
						BinaryNode<T>* minNodeParent = nullptr;
						if(rightGrandChild->getLeft()->getEntry() == minNode->getEntry()) {
							minNodeParent = rightGrandChild;
						} else {
							minNodeParent = minPriorityParent(rightGrandChild);
						}
						curSubTree->getLeft()->setEntry(minNode->getEntry());

						BinaryNode<T>* temp = minNodeParent->getLeft()->getRight();
	        	minNodeParent->getLeft()->~BinaryNode();
	          minNodeParent->inheritLeft(temp);
						nodeCount--;
					}
        }
      }
			else {
        removeRec(curSubTree->getLeft(), key);
      }
    }
  } else {
    if(curSubTree->getRight() != nullptr) {
      if(key == curSubTree->getRight()->getEntry()) {
        if(curSubTree->getRight()->getRight() == nullptr && curSubTree->getRight()->getLeft() == nullptr) // curSubTree->getRight() has no children.
        {
          curSubTree->getRight()->~BinaryNode();
          curSubTree->inheritRight(nullptr);
					nodeCount--;
        }
        else if(curSubTree->getRight()->getRight() != nullptr && curSubTree->getRight()->getLeft() == nullptr) // curSubTree->getRight() has left child.
        {
          BinaryNode<T>* temp = curSubTree->getRight()->getRight();
          curSubTree->getRight()->~BinaryNode();
          curSubTree->inheritRight(temp);
					nodeCount--;
        }
        else if(curSubTree->getRight()->getRight() == nullptr && curSubTree->getRight()->getLeft() != nullptr) // curSubTree->getRight() has right child.
        {
          BinaryNode<T>* temp = curSubTree->getRight()->getLeft();
          curSubTree->getRight()->~BinaryNode();
          curSubTree->inheritRight(temp);
					nodeCount--;
        }
        else // curSubTree->getRight() has 2 children.
        {
					if(curSubTree->getRight()->getRight()->getLeft() == nullptr) {
						BinaryNode<T>* leftGrandChild = curSubTree->getRight()->getLeft();
						BinaryNode<T>* rightGrandChild = curSubTree->getRight()->getRight();
	          curSubTree->getRight()->~BinaryNode();
	          curSubTree->inheritRight(rightGrandChild);
						curSubTree->getRight()->inheritLeft(leftGrandChild);
						nodeCount--;
					} else {
						BinaryNode<T>* rightGrandChild = curSubTree->getRight()->getRight();
						BinaryNode<T>* minNode = minPriority(rightGrandChild);
						BinaryNode<T>* minNodeParent = nullptr;
						if(rightGrandChild->getLeft()->getEntry() == minNode->getEntry()) {
							minNodeParent = rightGrandChild;
						} else {
							minNodeParent = minPriorityParent(rightGrandChild);
						}
						curSubTree->getRight()->setEntry(minNode->getEntry());

						BinaryNode<T>* temp = minNodeParent->getLeft()->getRight();
	        	minNodeParent->getLeft()->~BinaryNode();
	          minNodeParent->inheritLeft(temp);
						nodeCount--;
					}
        }
      }
			else {
        removeRec(curSubTree->getRight(), key);
      }
    }
  }
}

template<typename T, typename K>
BinaryNode<T>* BinarySearchTree<T, K>::minPriority(BinaryNode<T>* curSubTree) {
	if(curSubTree->getLeft() == nullptr) {
		return curSubTree;
	} else {
		return minPriority(curSubTree->getLeft());
	}
}

template<typename T, typename K>
BinaryNode<T>* BinarySearchTree<T, K>::minPriorityParent(BinaryNode<T>* curSubTree) {
	if(curSubTree->getLeft()->getLeft() == nullptr) {
		return curSubTree;
	} else {
		return minPriorityParent(curSubTree->getLeft());
	}
}

template<typename T, typename K>
BinaryNode<T>* BinarySearchTree<T, K>::rightMostSwapNode(BinaryNode<T>* curSubTree, bool ranOnce)
{
  if(!ranOnce)
  {
    return(rightMostSwapNode(curSubTree->getLeft(),true));
  }
  else
  {
    if(curSubTree->getRight() != nullptr)
    {
      return(rightMostSwapNode(curSubTree->getRight(),true));
    }
    else
    {
      return curSubTree;
    }
  }
}

template<typename T, typename K>
void BinarySearchTree<T, K>::deleteSwapNode(BinaryNode<T>* curSubTree, bool ranOnce)
{
  if(!ranOnce)
  {
    deleteSwapNode(curSubTree->getLeft(),true);
  }
  else
  {
    if(curSubTree->getRight() != nullptr)
    {
      deleteSwapNode(curSubTree->getRight(),true);
    }
    else
    {
      if(curSubTree->getLeft() == nullptr)
      {
        curSubTree->~BinaryNode();
      }
      else
      {
				/*
				BinaryNode<T>* temp = subtree;
				BinaryNode<T>* leftChild = subtree->getLeft();
	      subtree->inheritLeft(leftChild);
	      temp->~BinaryNode();
				*/

				curSubTree->setEntry(curSubTree->getLeft()->getEntry());
        curSubTree->getLeft()->~BinaryNode();
      }
    }
  }
}

template <typename T, typename K>
void BinarySearchTree<T, K>::inOrderSuccessor(K key) {
	inOrder();
	bool successorFound = false;

	for(int i = 1; i <= orderList.getLength(); i++) {
		if(orderList.getEntry(i) == key) {
			if(i + 1 <= orderList.getLength() && !successorFound) {
				cout << orderList.getEntry(i + 1);
				successorFound = true;
			} else if(!successorFound) {
				cout << key;
			}
		}
	}
}

template <typename T, typename K>
void BinarySearchTree<T, K>::kthSmallestItem(int k) {
	inOrder();
	int kthItem = 1;
	int i = 1;

	if(k > 1 && k <= orderList.getLength()) {
		while(i <= orderList.getLength()) {
			if(kthItem == k) {
				break;
			}

			if(i + 1 <= orderList.getLength() && orderList.getEntry(i) != orderList.getEntry(i + 1))
				kthItem++;

			i++;
		}
	}

	if(kthItem == k) {
		cout << "\nThe " << k;
		if (k % 10 == 1)
			cout << "st";
		else if (k % 10 == 2)
			cout << "nd";
		else if (k % 10 == 3)
			cout << "rd";
		else
			cout << "th";

		cout << " smallest item in the tree is " << orderList.getEntry(i) << ".\n\n";
	} else {
		cout << "\nERROR! kth item not found.\n\n";
	}
}

template <typename T, typename K>
void BinarySearchTree<T, K>::postOrderDelete(BinaryNode<T>* curSubTree) {
	if (curSubTree->getLeft() != nullptr) {
		postOrderDelete(curSubTree->getLeft());
	}

	if (curSubTree->getRight() != nullptr) {
		postOrderDelete(curSubTree->getRight());
	}

	if (curSubTree->getEntry() != m_root->getEntry()) {
		curSubTree->~BinaryNode();
	} else {
		m_root->~BinaryNode();
		m_root = nullptr;
	}
	nodeCount--;
}

template <typename T, typename K>
void BinarySearchTree<T, K>::preOrderAdd(BinaryNode<T>* curSubTree, T entry) {
	add(curSubTree, curSubTree->getEntry());

	if (curSubTree->getLeft() != nullptr) {
		preOrderAdd(curSubTree->getLeft(), curSubTree->getLeft()->getEntry());
	}

	if (curSubTree->getRight() != nullptr) {
		preOrderAdd(curSubTree->getRight(), curSubTree->getRight()->getEntry());
	}
}

template <typename T, typename K>
BinaryNode<T>* BinarySearchTree<T, K>::getRoot() const {
	return m_root;
}

template <typename T, typename K>
void BinarySearchTree<T, K>::saveToFile(string filename, string traversalOrder) {
	if (traversalOrder == "PRE" || traversalOrder == "PREORDER" ||
			traversalOrder == "IN" || traversalOrder == "INORDER" ||
			traversalOrder == "POST" || traversalOrder == "POSTORDER") {
		//Open File.
	  outFile.open(filename);

		if (traversalOrder == "PRE" || traversalOrder == "PREORDER") {
			preOrderWrite(m_root);
		} else if (traversalOrder == "IN" || traversalOrder == "INORDER") {
			inOrderWrite(m_root);
		} else if (traversalOrder == "POST" || traversalOrder == "POSTORDER") {
			postOrderWrite(m_root);
		}

	  // Close File.
	  outFile.close();
	}
}

template <typename T, typename K>
void BinarySearchTree<T, K>::preOrder(BinaryNode<T>* curSubTree) {
	cout << curSubTree->getEntry() << " ";

	if (curSubTree->getLeft() != nullptr) {
		preOrder(curSubTree->getLeft());
	}

	if (curSubTree->getRight() != nullptr) {
		preOrder(curSubTree->getRight());
	}
}

template <typename T, typename K>
void BinarySearchTree<T, K>::inOrder() {
	orderList.clear();
	if (m_root->getLeft() != nullptr) {
		inOrderRec(m_root->getLeft());
	}

	//cout << m_root->getEntry() << " ";
	orderList.insert(orderList.getLength() + 1, m_root->getEntry());

	if (m_root->getRight() != nullptr) {
		inOrderRec(m_root->getRight());
	}
}

template <typename T, typename K>
void BinarySearchTree<T, K>::inOrderRec(BinaryNode<T>* curSubTree) {
	if (curSubTree->getLeft() != nullptr) {
		inOrderRec(curSubTree->getLeft());
	}

	//cout << curSubTree->getEntry() << " ";
	orderList.insert(orderList.getLength() + 1, curSubTree->getEntry());

	if (curSubTree->getRight() != nullptr) {
		inOrderRec(curSubTree->getRight());
	}
}

template <typename T, typename K>
void BinarySearchTree<T, K>::postOrder(BinaryNode<T>* curSubTree) {
	if (curSubTree->getLeft() != nullptr) {
		postOrder(curSubTree->getLeft());
	}

	if (curSubTree->getRight() != nullptr) {
		postOrder(curSubTree->getRight());
	}

	cout << curSubTree->getEntry() << " ";
}

template <typename T, typename K>
void BinarySearchTree<T, K>::levelOrder() {
	for(int i = 0; i <= m_height; i++) {
		levelOrderRec(m_root, 0, i);
	}
}

template <typename T, typename K>
void BinarySearchTree<T, K>::levelOrderRec(BinaryNode<T>* curSubTree, int depth, int targetDepth) {
	if (depth == targetDepth) {
		cout << curSubTree->getEntry() << " ";
	} else {
		depth++;

		if (curSubTree->getLeft() != nullptr) {
			levelOrderRec(curSubTree->getLeft(), depth, targetDepth);
		}

		if (curSubTree->getRight() != nullptr) {
			levelOrderRec(curSubTree->getRight(), depth, targetDepth);
		}
	}
}

template <typename T, typename K>
void BinarySearchTree<T, K>::spiralLevelOrder() {
	for(int i = 0; i <= m_height; i++) {
		spiralLevelOrderRec(m_root, 0, i, i%2);
	}
}

template <typename T, typename K>
void BinarySearchTree<T, K>::spiralLevelOrderRec(BinaryNode<T>* curSubTree, int depth, int targetDepth, int direction) {
	if (depth == targetDepth) {
		cout << curSubTree->getEntry() << " ";
	} else {
		depth++;
		if (direction == 0) { // left to right print.
			if (curSubTree->getLeft() != nullptr) {
				spiralLevelOrderRec(curSubTree->getLeft(), depth, targetDepth, direction);
			}

			if (curSubTree->getRight() != nullptr) {
				spiralLevelOrderRec(curSubTree->getRight(), depth, targetDepth, direction);
			}
		} else if (direction == 1) { // right to left print
			if (curSubTree->getRight() != nullptr) {
				spiralLevelOrderRec(curSubTree->getRight(), depth, targetDepth, direction);
			}

			if (curSubTree->getLeft() != nullptr) {
				spiralLevelOrderRec(curSubTree->getLeft(), depth, targetDepth, direction);
			}
		}
	}
}

template <typename T, typename K>
void BinarySearchTree<T, K>::leftSideView(BinaryNode<T>* curSubTree) {
	cout << curSubTree->getEntry() << " ";
	if(curSubTree->getLeft() != nullptr)
		leftSideView(curSubTree->getLeft());
}

template <typename T, typename K>
void BinarySearchTree<T, K>::rightSideView(BinaryNode<T>* curSubTree) {
	cout << curSubTree->getEntry() << " ";
	if(curSubTree->getRight() != nullptr)
		rightSideView(curSubTree->getRight());
}

template <typename T, typename K>
int BinarySearchTree<T, K>::getOrderCount() {
	return orderCount;
}

template <typename T, typename K>
void BinarySearchTree<T, K>::resetOrderCount() {
	orderCount = 0;
}

template <typename T, typename K>
int BinarySearchTree<T, K>::getNumberCount() const {
	return nodeCount;
}

template <typename T, typename K>
bool BinarySearchTree<T, K>::isEmpty() const {
	if (m_root == nullptr)
		return true;
	else
		return false;
}
