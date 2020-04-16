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
          srand (time(NULL));   //Initialize random seed: This means every time you run the program it will change the numbers generated

          int m = 1000000;
          int random_number;
          int size = 10;

          int inputSize [size];
          clock_t start, endBuild, endDelete;
          double buildTime [size];
          double deleteTime [size];

          for(int i = 0; i < size; i++) {
            inputSize[i] = 0;
            buildTime[i] = 0.000000;
            deleteTime[i] = 0.000000;
          }

          for (int j = 0; j < size; j++) {
            if (j < 5) {
              start = clock();
              inputSize[j] = floor (0.1 * m * (j + 1));
              for(int i = 0; i < floor (0.1 * m * (j + 1)); i++) {
                random_number = rand() % 5000000 + 1;
                lHeap.add(lHeap.getRoot(), random_number);
              }
              endBuild = clock();
              buildTime[j] = double(endBuild - start) / double(CLOCKS_PER_SEC);
              lHeap.remove();
              endDelete = clock();
              deleteTime[j] = double(endDelete - start) / double(CLOCKS_PER_SEC);
              lHeap.clear();
            } else {
              start = clock();
              inputSize[j] = floor (0.1 * m * (j - 4));
              for(int i = 0; i < floor (0.1 * m * (j - 4)); i++) {
                random_number = rand() % 5000000 + 1;
                sqHeap.add(sqHeap.getRoot(), random_number);
              }
              endBuild = clock();
              buildTime[j] = double(endBuild - start) / double(CLOCKS_PER_SEC);
              sqHeap.remove();
              endDelete = clock();
              deleteTime[j] = double(endDelete - start) / double(CLOCKS_PER_SEC);
              sqHeap.clear();
            }
          }

          cout << "______________________Performance (Min Leftist Heap)_______________________\n";
          cout << "___________________________________________________________________________\n";
          cout << "Input size:";
          for (int i = 0; i < size/2; i++)
            cout << "\t|\t" << inputSize[i];
          cout << "\nBuild (s):\t";
          for (int i = 0; i < size/2; i++)
            cout << "|\t" << setprecision(5) << buildTime[i];
          cout << "\nDelete min (s):\t";
          for (int i = 0; i < size/2; i++)
            cout << "|\t" << setprecision(5) << deleteTime[i];
          cout << "\n___________________________________________________________________________\n\n\n";

          cout << "______________________Performance (Min Skew Heap)__________________________\n";
          cout << "___________________________________________________________________________\n";
          cout << "Input size:";
          for (int i = size/2; i < size; i++)
            cout << "\t|\t" << inputSize[i];
          cout << "\nBuild (s):\t";
          for (int i = size/2; i < size; i++)
            cout << "|\t" << setprecision(5) << buildTime[i];
          cout << "\nDelete min (s):\t";
          for (int i = size/2; i < size; i++)
            cout << "|\t" << setprecision(5) << deleteTime[i];
          cout << "\n___________________________________________________________________________\n\n\n";
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
