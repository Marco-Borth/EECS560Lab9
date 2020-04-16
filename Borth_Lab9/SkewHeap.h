/* -----------------------------------------------------------------------------
 *
 * File Name:  SkewHeap.h
 * Author: Marco Borth
 * Assignment:   EECS 560 Lab 9 – Experimental Profiling on Leftist and Skew Heaps
 * Description:  SkewHeap Template Class is defined.
 * Date: 4/16/20
 *
 ---------------------------------------------------------------------------- */

#ifndef SKEWHEAP_H
#define SKEWHEAP_H

#include "BinaryNode.h"
#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept> //For runtime_error
using namespace std;

template <typename T>
class SkewHeap
{
private:
  BinaryNode<T>* m_root;
  int nodeCount, m_height;

/*
* @pre add calls addRec.
* @param curSubTree is a valid BinaryNode<T> pointer.
* @param entry is a valid T object.
* @post if entry < curSubTree->getEntry(), a BinaryNode is added to the left pointer of curSubTree if left == nullptr.
* @post else if entry > curSubTree->getEntry(), a BinaryNode is added to the right pointer of curSubTree if right == nullptr.
* @post if left or right != nullptr, the BinaryNode is to be then added to either curSubTree->getLeft or curSubTree-> getRight.
* @post no duplicates are to be allowed.
*/
  void addRec(BinaryNode<T>* curSubTree, T entry, int depth);

  void merge(BinaryNode<T>* curSubTree, BinaryNode<T>* otherSubTree, int depth);

/*
* @pre none.
* @param curSubTree is a valid BinaryNode<T> pointer.
* @post deletes every BinaryNode in BinarySearchTree in postOrder.
*/
  void postOrderDelete(BinaryNode<T>* curSubTree);

  void levelOrderRec(BinaryNode<T>* curSubTree, int depth, int targetDepth);

public:
/*
* @pre define T object.
* @post MaxHeap object is constructed.
*/
  SkewHeap();

/*
* @pre none.
* @post ~MaxHeap clears all BinaryNodes and deletes m_arr.
*/
  ~SkewHeap();

/*
* @pre none.
* @post isEmpty returns false if m_heapSize > 0, returns true otherwise.
*/
  bool isEmpty() const;

/*
* @pre none.
* @post getNumberOfNodes returns nodeCount.
*/
  int getNumberOfNodes() const;

/*
* @pre none.
* @post getHeight returns m_height.
*/
  int getHeight() const;

/*
* @pre none.
* @post returns m_root.
*/
  BinaryNode<T>* getRoot() const;

/*
* @pre none.
* @param curSubTree is a valid BinaryNode<T> pointer.
* @param entry is a valid T object.
* @post adds a BinaryNode to m_root if m_root == nullptr, calls on addRec otherwise.
*/
  void add(BinaryNode<T>* curSubTree, T entry);

  void remove();

/*
* @pre none.
* @post deletes all BinaryNodes within m_arr.
*/
  void clear();

  void levelOrder();
};

#include "SkewHeap.cpp"

#endif
