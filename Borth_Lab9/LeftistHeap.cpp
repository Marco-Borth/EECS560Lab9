/* -----------------------------------------------------------------------------
 *
 * File Name:  LeftistHeap.cpp
 * Author: Marco Borth
 * Assignment:   EECS 560 Lab 9 – Experimental Profiling on Leftist and Skew Heaps
 * Description:  LeftistHeap methods are defined.
 * Date: 4/14/24
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
	} else {
		addRec(m_root, entry, 0);
	}
}

template <typename T>
void LeftistHeap<T>::addRec(BinaryNode<T>* curSubTree, T entry, int depth) {
	depth++;
	if (curSubTree->getLeft() == nullptr) {
		curSubTree->setLeft(entry);
		nodeCount++;
		if (curSubTree->getEntry() > curSubTree->getLeft()->getEntry()) {
			T temp = curSubTree->getLeft()->getEntry();
			curSubTree->getLeft()->setEntry(curSubTree->getEntry());
			curSubTree->setEntry(temp);
		}
	} else if (curSubTree->getRight() == nullptr) {
		curSubTree->setRight(entry);
		nodeCount++;
		if (curSubTree->getEntry() > curSubTree->getRight()->getEntry()) {
			T temp = curSubTree->getRight()->getEntry();
			curSubTree->getRight()->setEntry(curSubTree->getEntry());
			curSubTree->setEntry(temp);
		}
	} else if (curSubTree->getLeft()->getEntry() >= curSubTree->getRight()->getEntry()) {
		addRec(curSubTree->getLeft(), entry, depth);
		if (curSubTree->getEntry() > curSubTree->getLeft()->getEntry()) {
			T temp = curSubTree->getLeft()->getEntry();
			curSubTree->getLeft()->setEntry(curSubTree->getEntry());
			curSubTree->setEntry(temp);
		}
	} else {
		addRec(curSubTree->getRight(), entry, depth);
		if (curSubTree->getEntry() > curSubTree->getRight()->getEntry()) {
			T temp = curSubTree->getRight()->getEntry();
			curSubTree->getRight()->setEntry(curSubTree->getEntry());
			curSubTree->setEntry(temp);
		}
	}

	if (curSubTree->getRank() == 2 && curSubTree->getLeft()->getRank() < curSubTree->getRight()->getRank()) {
		BinaryNode<T>* leftChild = curSubTree->getLeft();
		BinaryNode<T>* rightChild = curSubTree->getRight();
		curSubTree->inheritLeft(rightChild);
		curSubTree->inheritRight(leftChild);
	}

	if(depth > m_height)
		m_height = depth;
}

template <typename T>
void LeftistHeap<T>::remove() {
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
				m_root->setRight(h1);
				if (m_root->getRank() == 2 && m_root->getLeft()->getRank() < m_root->getRight()->getRank()) {
					BinaryNode<T>* temp = m_root->getLeft();
					m_root->setLeft(m_root->getRight());
					m_root->setRight(temp);
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
