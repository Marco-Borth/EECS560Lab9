/* -----------------------------------------------------------------------------
 *
 * File Name:  LeftistHeap.cpp
 * Author: Marco Borth
 * Assignment:   EECS 560 Lab 9 – Experimental Profiling on Leftist and Skew Heaps
 * Description:  LeftistHeap methods are defined.
 * Date: 4/17/20
 *
 ---------------------------------------------------------------------------- */

template <typename T>
LeftistHeap<T>::LeftistHeap() {
	m_root = nullptr;
	nodeCount = 0;
	m_height = 0;
}

template <typename T>
LeftistHeap<T>::~LeftistHeap() {
	clear();
	m_root = nullptr;
}

template <typename T>
bool LeftistHeap<T>::isEmpty() const {
	if (m_root != nullptr)
		return false;
	else
		return true;
}

template <typename T>
int LeftistHeap<T>::getNumberOfNodes() const {
	return nodeCount;
}

template <typename T>
int LeftistHeap<T>::getHeight() const {
	return m_height;
}

template <typename T>
BinaryNode<T>* LeftistHeap<T>::getRoot() const {
	return m_root;
}

template <typename T>
void LeftistHeap<T>::add(BinaryNode<T>* curSubTree, T entry) {
	if (m_root == nullptr) {
		m_root = new BinaryNode<T>(entry);
		nodeCount++;
	}
	else {
		BinaryNode<T>* temp = new BinaryNode<T>(entry);
		nodeCount++;
		m_root = merge(temp, m_root);
	}
}

template <typename T>
void LeftistHeap<T>::remove() {
	if (m_root->getLeft() == nullptr && m_root->getRight() == nullptr) {
		m_root->~BinaryNode();
		m_root = nullptr;
		nodeCount = 0;
		m_height = 0;
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
	else {
		BinaryNode<T>* h1 = m_root->getLeft();
		BinaryNode<T>* h2 = m_root->getRight();
		m_root->inheritLeft(nullptr);
		m_root->inheritRight(nullptr);
		m_root->~BinaryNode();
		nodeCount--;

		m_root = merge(h1, h2);
	}

	if (nodeCount == 0) {
		m_height = 0;
	} else {
		measureHeight();
	}
}

template <typename T>
BinaryNode<T>* LeftistHeap<T>::merge(BinaryNode<T>* h1, BinaryNode<T>* h2) {
	if (h1 == nullptr) {
		return h2;
	} else if (h2 == nullptr) {
		return h1;
	} else if (h1 != nullptr && h2 != nullptr) {
		if (h1->getEntry() < h2->getEntry()) {
			BinaryNode<T>* temp = nullptr;
			temp = mergeRec(h1, h2);
			return temp;
		} else {
			BinaryNode<T>* temp = nullptr;
			temp = mergeRec(h2, h1);
			return temp;
		}
		return h1;
	} else {
		return nullptr;
	}
}

template <typename T>
BinaryNode<T>* LeftistHeap<T>::mergeRec(BinaryNode<T>* h1, BinaryNode<T>* h2)
{
    if (h1->getLeft() == nullptr)
        h1->inheritLeft(h2);
    else {
        h1->inheritRight(merge(h1->getRight(), h2));
        if (h1->getLeft()->getRank() < h1->getRight()->getRank()) {
					BinaryNode<T>* leftChild = h1->getLeft();
					BinaryNode<T>* rightChild = h1->getRight();
					h1->inheritLeft(rightChild);
					h1->inheritRight(leftChild);
				}
    }
    return h1;
}

template <typename T>
void LeftistHeap<T>::clear() {
	postOrderDelete(m_root);
	m_root = nullptr;
}

template <typename T>
void LeftistHeap<T>::postOrderDelete(BinaryNode<T>* curSubTree) {
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

template <typename T>
void LeftistHeap<T>::levelOrder() {
	measureHeight();
	for(int i = 0; i <= m_height; i++) {
		levelOrderRec(m_root, 0, i);
	}
}

template <typename T>
void LeftistHeap<T>::levelOrderRec(BinaryNode<T>* curSubTree, int depth, int targetDepth) {
	if (curSubTree != nullptr) {
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
}

template <typename T>
void LeftistHeap<T>::measureHeight() {
	m_height = 0;

	if (m_root->getLeft() != nullptr) {
		incrementHeight(m_root->getLeft(), 0);
	}

	if (m_root->getRight() != nullptr) {
		incrementHeight(m_root->getRight(), 0);
	}
}

template <typename T>
void LeftistHeap<T>::incrementHeight(BinaryNode<T>* curSubTree, int depth) {
	depth++;

	if (depth > m_height) {
		m_height++;
	}

	if (curSubTree->getLeft() != nullptr) {
		incrementHeight(curSubTree->getLeft(), depth);
	}

	if (curSubTree->getRight() != nullptr) {
		incrementHeight(curSubTree->getRight(), depth);
	}
}
