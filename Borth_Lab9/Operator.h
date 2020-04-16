/* -----------------------------------------------------------------------------
 *
 * File Name:  Operator.h
 * Author: Marco Borth
 * Assignment:   EECS 560 Lab 9 – Experimental Profiling on Leftist and Skew Heaps
 * Description:  Operator Class is defined.
 * Date: 4/14/20
 *
 ---------------------------------------------------------------------------- */

#ifndef OPERATOR_H
#define OPERATOR_H

#include "LeftistHeap.h"
#include "SkewHeap.h"
#include <string>
#include <stdexcept>
using namespace std;

class Operator
{
private:
  int option;

  string file;
  ifstream inFile;

  LeftistHeap<int> lHeap;
  SkewHeap<int> sqHeap;

public:
/**
* @pre none.
* @post stops running after code exits loop.
*/
	void run();

  void buildLeftistHeap();

  void buildSkewHeap();

/**
* @pre none.
* @post prints list of commands to display for the user.
*/
  void printCommands();

/*
* @pre filename is a string.
* @post Operator object is constructed, file == filename.
*/
  Operator(string filename);
};
#endif
