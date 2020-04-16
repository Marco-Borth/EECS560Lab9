/* -----------------------------------------------------------------------------
 *
 * File Name:  Operator.cpp
 * Author: Marco Borth
 * Assignment:   EECS-560 Lab 4 – Implementation of Binary Tree
 * Description:  Operator Class will either run the Interactive program for a Hash Table (Closed Hashing)
 * Date: 2/22/20
 *
 ---------------------------------------------------------------------------- */

#include "Operator.h"
#include <iostream>
#include <string>
#include <fstream>
#include <limits>
using namespace std;

Operator::Operator(string filename){
  file = filename;
}

void Operator::printCommands() {
  cout << "-----------------------Experimental profiling (Min leftist and Min Skew heaps)-------------------------\n\n";
  cout << "1. Test build - min leftist heap\n";
  cout << "2. Test delete min - min leftist heap\n";
  cout << "3. Test build - min skew heap\n";
  cout << "4. Test delete min - min skew heap\n";
  cout << "5. Test performance of heaps\n";
  cout << "6. Exit\n\n";
  cout << "Please choose an option:\n> ";
}

void Operator::run() {
  cout << "\nWelcome to the Interactive Hash Table Program!\n\n";

  do {
    printCommands();
    cin >> option;

    while(1) {
      // Error Handling for an non-number entry.
      if(cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "\nERROR! Invalid Option!\n\n"; //if not an int, must try again.
        printCommands();
        cin >> option;
      }
      // Operation Number has been selected.
      else {
        // 1. Test build - min leftist heap - Complete!
        if (option == 1) {
          buildLeftistHeap();
          cout << "\nLevel order of min leftist heap: ";
          lHeap.levelOrder();
          cout << "\n\n";
          lHeap.clear();
        }
        // 2. Test delete min - min leftist heap - Complete!
        else if (option == 2) {
          buildLeftistHeap();
          lHeap.remove();
          cout << "\nLevel order of min leftist heap: ";
          lHeap.levelOrder();
          cout << "\n\n";
          lHeap.clear();
        }
        // 3. Test build - min skew heap - Complete!
        else if (option == 3) {
          buildSkewHeap();
          cout << "\nLevel order of min skew heap: ";
          sqHeap.levelOrder();
          cout << "\n\n";
          sqHeap.clear();
        }
        // 4. Test delete min - min skew heap - Complete!
        else if (option == 4) {
          buildSkewHeap();
          sqHeap.remove();
          cout << "\nLevel order of min skew heap: ";
          sqHeap.levelOrder();
          cout << "\n\n";
          sqHeap.clear();
        }
        // 5. Test performance of heaps - Complete!
        else if (option == 5) {
          cout << "\nOutput:  The leaf nodes are: ";
          //IMDB.printLeaves();
        }
        // 6. Exit - Complete!
        else if (option == 6) {
          cout << "\nClosing Program...\n";
        }
        // Otherwise - Complete!
        else {
          cout << "\nERROR! Invalid Option!\n\n";
        }

        break;
      }
    }
  } while(option != 6);

  lHeap.clear();

  cout << "\nBye Bye!\n";
  cout << "\nHave a nice day!...\n\n";
}

void Operator::buildLeftistHeap() {
  //Open File.
  inFile.open(file);

  if (!inFile.is_open()) {
    cout << "File name not valid!\n\n";
  } else {
    int RatingInputFailures = 0;
    int input;
    while (!inFile.eof()) {
      inFile >> input;

      if(inFile.fail()) {
        inFile.clear();
        inFile.ignore(numeric_limits<streamsize>::max(),'\n');
        RatingInputFailures++;
      } else {
        lHeap.add(lHeap.getRoot(), input);
      }
    }

    if(RatingInputFailures > 1)
      cout << "ERROR! Invalid Input for Movie Ratings Detected: " << RatingInputFailures << "\n";
  }

  // Close File.
  inFile.close();
}

void Operator::buildSkewHeap() {
  //Open File.
  inFile.open(file);

  if (!inFile.is_open()) {
    cout << "File name not valid!\n\n";
  } else {
    int RatingInputFailures = 0;
    int input;
    while (!inFile.eof()) {
      inFile >> input;

      if(inFile.fail()) {
        inFile.clear();
        inFile.ignore(numeric_limits<streamsize>::max(),'\n');
        RatingInputFailures++;
      } else {
        sqHeap.add(sqHeap.getRoot(), input);
      }
    }

    if(RatingInputFailures > 1)
      cout << "ERROR! Invalid Input for Movie Ratings Detected: " << RatingInputFailures << "\n";
  }

  // Close File.
  inFile.close();
}
