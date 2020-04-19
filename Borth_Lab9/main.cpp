/* -----------------------------------------------------------------------------
 *
 * File Name:  main.cpp
 * Author: Marco Borth
 * Assignment:   EECS 560 Lab 9 – Experimental Profiling on Leftist and Skew Heaps
 * Description:  This lab will contain an implementation of a LeftistHeap and SkewHeap Test.
 * Date: 4/19/20
 *
 ---------------------------------------------------------------------------- */
//Start your program.

#include <iostream>
#include"Executive.h"

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		std::cout << "Incorrect number of parameters!\n";
	}
	else
	{
		Executive exec(argv[1]);
		exec.run();
	}

	return(0);
}
