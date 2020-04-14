/* -----------------------------------------------------------------------------
*
* File Name:  BinaryNode.h
* Author: Marco Borth
* Assignment:   EECS-560 Lab 6 – Implementation of Binary Search Trees
* Description:  BinaryNode Template Class is defined here;
* Date: 3/12/20
*
---------------------------------------------------------------------------- */

#ifndef BINARY_NODE_H
#define BINARY_NODE_H

#include <string>
#include <stdexcept>
using namespace std;

template <typename T>
class BinaryNode
{
private:
  T m_entry;
  BinaryNode<T>* m_left;
  BinaryNode<T>* m_right;

public:
/*
* @pre none.
* @param entry must be a T value.
* @post m_entry is set to entry.
*/
  void setEntry(T entry);

/*
* @pre none.
* @post return m_entry value.
*/
  T getEntry() const;

/*
* @pre none.
* @param left must be a T object.
* @post m_left creates a BinaryNode<T> which is set to m_left.
*/
  void setLeft(T left);

  void inheritLeft(BinaryNode<T>* left);

/*
* @pre none.
* @post return m_left.
*/
  BinaryNode<T>* getLeft() const;

/*
* @pre none.
* @param right must be a T object.
* @post m_right creates a BinaryNode<T> which is set to m_right.
*/
  void setRight(T right);

  void inheritRight(BinaryNode<T>* right);

/*
* @pre none.
* @post return m_right.
*/
  BinaryNode<T>* getRight() const;

  int getRank();

/*
* @pre none.
* @post creates a BinaryNode.
*/
  BinaryNode();

/*
* @pre none.
* @param entry must be a valid T entry
* @post creates a BinaryNode with givin T entry.
*/
  BinaryNode(T entry);

/*
* @pre Node object must be constructed.
* @post deletes BinaryNode, deletes m_entry, m_left and m_right = nullptr.
*/
  ~BinaryNode();
};

#include "BinaryNode.cpp"

#endif
