/* -----------------------------------------------------------------------------
 *
 * File Name:  SkewHeap.cpp
 * Author: Marco Borth
 * Assignment:   EECS 560 Lab 9 – Experimental Profiling on Leftist and Skew Heaps
 * Description:  SkewHeap methods are defined.
 * Date: 4/19/20
 *
 ---------------------------------------------------------------------------- */

template <typename T>
SkewHeap<T>::SkewHeap() {
	m_root = nullptr;
	nodeCount = 0;
	m_height = 0;
}

template <typename T>
SkewHeap<T>::~SkewHeap() {
	clear();
	m_root = nullptr;
}

template <typename T>
bool SkewHeap<T>::isEmpty() const {
	if (m_root != nullptr)
		return false;
	else
		return true;
}

template <typename T>
int SkewHeap<T>::getNumberOfNodes() const {
	return nodeCount;
}

template <typename T>
int SkewHeap<T>::getHeight() const {
	return m_height;
}

template <typename T>
BinaryNode<T>* SkewHeap<T>::getRoot() const {
	return m_root;
}

template <typename T>
void SkewHeap<T>::add(BinaryNode<T>* curSubTree, T entry) {
	BinaryNode<T>* temp = new BinaryNode<T>(entry);
	nodeCount++;
	m_root = merge(m_root, temp);
}

template <typename T>
void SkewHeap<T>::remove() {
	if (m_root->getLeft() == nullptr && m_root->getRight() == nullptr) {
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
BinaryNode<T>* SkewHeap<T>::merge(BinaryNode<T>* h1, BinaryNode<T>* h2) {
	if (h1 == nullptr) {
		return h2;
	}

	if (h2 == nullptr) {
		return h1;
	}

	if (h1->getEntry() > h2->getEntry()) {
		BinaryNode<T>* temp = nullptr;
		temp = h1;
		h1 = h2;
		h2 = temp;
	}

	BinaryNode<T>* leftChild = h1->getLeft();
	BinaryNode<T>* rightChild = h1->getRight();
	h1->inheritLeft(rightChild);
	h1->inheritRight(leftChild);

	h1->inheritLeft(merge(h2, h1->getLeft()));

	return h1;
}

template <typename T>
void SkewHeap<T>::clear() {
	postOrderDelete(m_root);
	m_root = nullptr;
}

template <typename T>
void SkewHeap<T>::postOrderDelete(BinaryNode<T>* curSubTree) {
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
void SkewHeap<T>::levelOrder() {
	measureHeight();
	for(int i = 0; i <= m_height; i++) {
		levelOrderRec(m_root, 0, i);
	}
}

template <typename T>
void SkewHeap<T>::levelOrderRec(BinaryNode<T>* curSubTree, int depth, int targetDepth) {
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

template <typename T>
void SkewHeap<T>::measureHeight() {
	m_height = 0;

	if (m_root->getLeft() != nullptr) {
		incrementHeight(m_root->getLeft(), 0);
	}

	if (m_root->getRight() != nullptr) {
		incrementHeight(m_root->getRight(), 0);
	}
}

template <typename T>
void SkewHeap<T>::incrementHeight(BinaryNode<T>* curSubTree, int depth) {
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
