/* -----------------------------------------------------------------------------
 *
 * File Name:  SkewHeap.cpp
 * Author: Marco Borth
 * Assignment:   EECS 560 Lab 9 – Experimental Profiling on Leftist and Skew Heaps
 * Description:  SkewHeap methods are defined.
 * Date: 4/14/24
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
	if (m_root == nullptr) {
		m_root = new BinaryNode<T>(entry);
		nodeCount++;
	} else if (m_root->getRight() == nullptr) {
		if (m_root->getLeft() == nullptr) {
			m_root->setLeft(entry);
			nodeCount++;
			if (m_root->getEntry() > m_root->getLeft()->getEntry()) {
				T temp = m_root->getLeft()->getEntry();
				m_root->getLeft()->setEntry(m_root->getEntry());
				m_root->setEntry(temp);
			}
		} else {
			curSubTree->setRight(entry);
			nodeCount++;
			if (m_root->getEntry() > m_root->getRight()->getEntry()) {
				T temp = m_root->getRight()->getEntry();
				m_root->getRight()->setEntry(m_root->getEntry());
				m_root->setEntry(temp);
			}
			if (m_root->getLeft()->getEntry() < m_root->getRight()->getEntry()) {
				BinaryNode<T>* leftChild = m_root->getLeft();
				BinaryNode<T>* rightChild = m_root->getRight();
				m_root->inheritLeft(rightChild);
				m_root->inheritRight(leftChild);
			}
		}
	} else {
		addRec(m_root, entry, 0);
	}
}

template <typename T>
void SkewHeap<T>::addRec(BinaryNode<T>* curSubTree, T entry, int depth) {
	depth++;
	if (curSubTree->getRight() != nullptr) {
		addRec(curSubTree->getRight(), entry, depth);
	} else {
		curSubTree->setRight(entry);
		nodeCount++;
		if (curSubTree->getEntry() > curSubTree->getRight()->getEntry()) {
			T temp = curSubTree->getRight()->getEntry();
			curSubTree->getRight()->setEntry(curSubTree->getEntry());
			curSubTree->setEntry(temp);
		}
	}

	BinaryNode<T>* leftChild = curSubTree->getLeft();
	BinaryNode<T>* rightChild = curSubTree->getRight();
	curSubTree->inheritLeft(rightChild);
	curSubTree->inheritRight(leftChild);

	if(depth > m_height)
		m_height = depth;
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
		BinaryNode<T>* temp = m_root;
		BinaryNode<T>* h1 = m_root->getLeft();
		BinaryNode<T>* h2 = m_root->getRight();
		temp->~BinaryNode();

		if (h1->getEntry() > h2->getEntry()) {
			m_root = h2;
			BinaryNode<T>* h2rightChild = m_root->getRight();
			if (h2rightChild == nullptr) {
				m_root->inheritRight(h1);
				if (m_root->getRank() == 2 && m_root->getLeft()->getRank() < m_root->getRight()->getRank()) {
					BinaryNode<T>* temp = m_root->getLeft();
					m_root->inheritLeft(m_root->getRight());
					m_root->inheritRight(temp);
				} else {
					BinaryNode<T>* leftChild = m_root->getLeft();
					BinaryNode<T>* rightChild = m_root->getRight();
					m_root->inheritLeft(rightChild);
					m_root->inheritRight(leftChild);
				}
			}
		} else {
			m_root = h1;
			BinaryNode<T>* leftgrandrightChild = m_root->getRight();
		}
	}
}

template <typename T>
void SkewHeap<T>::merge(BinaryNode<T>* curSubTree, BinaryNode<T>* otherSubTree, int depth) {
	depth++;
	if (curSubTree->getRight() != nullptr) {
		merge(curSubTree->getRight(), otherSubTree, depth);
	} else {
		curSubTree->inheritRight(otherSubTree);
		nodeCount++;
		if (curSubTree->getEntry() > curSubTree->getRight()->getEntry()) {
			T temp = curSubTree->getRight()->getEntry();
			curSubTree->getRight()->setEntry(curSubTree->getEntry());
			curSubTree->setEntry(temp);
			BinaryNode<T>* newTree = curSubTree->getRight();
			while (newTree->getLeft() != nullptr && newTree->getRight() != nullptr) {
				if (newTree->getLeft() != nullptr && newTree->getRight() == nullptr) {
					if (newTree->getLeft()->getEntry() > newTree->getEntry()) {
						T temp = newTree->getLeft()->getEntry();
						newTree->getLeft()->setEntry(newTree->getEntry());
						newTree->setEntry(temp);
						newTree = newTree->getLeft();
					}
				} else if (newTree->getLeft() == nullptr && newTree->getRight() != nullptr) {
					if (newTree->getRight()->getEntry() > newTree->getEntry()) {
						T temp = newTree->getRight()->getEntry();
						newTree->getRight()->setEntry(newTree->getEntry());
						newTree->setEntry(temp);
						newTree = newTree->getRight();
					}
				} else if (newTree->getLeft() != nullptr && newTree->getRight() != nullptr) {
					if (newTree->getLeft()->getEntry() < newTree->getRight()->getEntry()) {
						if (newTree->getRight()->getEntry() > newTree->getEntry()) {
							T temp = newTree->getRight()->getEntry();
							newTree->getRight()->setEntry(newTree->getEntry());
							newTree->setEntry(temp);
							newTree = newTree->getRight();
						}
					} else {
						if (newTree->getLeft()->getEntry() > newTree->getEntry()) {
							T temp = newTree->getLeft()->getEntry();
							newTree->getLeft()->setEntry(newTree->getEntry());
							newTree->setEntry(temp);
							newTree = newTree->getLeft();
						}
					}
				} else {
					break;
				}
			}
		}
	}

	BinaryNode<T>* leftChild = curSubTree->getLeft();
	BinaryNode<T>* rightChild = curSubTree->getRight();
	curSubTree->inheritLeft(rightChild);
	curSubTree->inheritRight(leftChild);

	if(depth > m_height)
		m_height = depth;
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
