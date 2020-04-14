/* -----------------------------------------------------------------------------
*
* File Name:  BinaryNode.cpp
* Author: Marco Borth
* Assignment:   EECS-560 Lab 6 – Implementation of Binary Search Trees
* Description:  BinaryNode set and get methods defined here.
* Date: 3/12/20
*
---------------------------------------------------------------------------- */

#include <string>
using namespace std;

template <typename T>
BinaryNode<T>::BinaryNode(T entry) : m_entry(entry)
{
  //m_entry = entry;
  m_left = nullptr;
  m_right = nullptr;
}

template <typename T>
BinaryNode<T>::BinaryNode()
{
  m_left = nullptr;
  m_right = nullptr;
}

template <typename T>
BinaryNode<T>::~BinaryNode()
{
  m_left = nullptr;
  m_right = nullptr;
  delete &m_entry;
}

template <typename T>
void BinaryNode<T>::setEntry(T entry)
{
  m_entry = entry;
}

template <typename T>
T BinaryNode<T>::getEntry() const
{
  return(m_entry);
}

template <typename T>
void BinaryNode<T>::setLeft(T left)
{
  m_left = new BinaryNode<T>(left);
}

template <typename T>
BinaryNode<T>* BinaryNode<T>::getLeft() const
{
  return(m_left);
}

template <typename T>
void BinaryNode<T>::inheritLeft(BinaryNode<T>* left)
{
  m_left = left;
}

template <typename T>
void BinaryNode<T>::setRight(T right)
{
  m_right = new BinaryNode<T>(right);
}

template <typename T>
BinaryNode<T>* BinaryNode<T>::getRight() const
{
  return(m_right);
}

template <typename T>
void BinaryNode<T>::inheritRight(BinaryNode<T>* right)
{
  m_right = right;
}

template <typename T>
int BinaryNode<T>::getRank() {
	if (m_left != nullptr && m_right != nullptr)
		return 2;
	else
		return 1;
}
