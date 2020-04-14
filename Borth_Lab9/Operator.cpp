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
  cout << "6. Exit\n\n> ";
}

void Operator::run() {
  cout << "\nWelcome to the Interactive Hash Table Program!\n\n";
  ifstream inFile;

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
        // 1. Is Empty - Complete!
        if (option == 1) {
          cout << "\nBinary Tree is: ";
        }
        // 2- AddMovie - Complete!
        else if (option == 2) {
          cout << "\nPreparing to Insert a New Movie...\n";
        }
        // 3- RemoveMovie - Complete!
        else if (option == 3) {

        }
        // 4- Leaf - Complete!
        else if (option == 4) {
          cout << "\nPlease enter the name of your movie which you want to test as a leaf node:\n> ";
        }
        // 5- PrintLeaves - Complete!
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