// main.cpp file
/*
 * Author: Aryan Gupta
 * Date: 4/23/2018
 * This program allows the user to create a binary search tree by adding or removing integers and 
 * allows them to see a visual representation of the tree
 */

#include "Node.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <cstring>
#include <queue>
#include <iomanip>

using namespace std;

// function prototypes
// add a node to the tree
void addNode(Node* head, int value);

// remove a node from the tree
Node* deleteNode(Node* head, int value);

// finds the smallest node in the tree
Node* smallestNode(Node* head);

// prints the tree
void print(Node* head);



// main method
int main() {

  // prompt user for their choice of input and get input
  char option[10];
  cout << "Would you like to enter integers from a file (type FILE) or manually (type MANUAL)? ";
  cin.getline(option, 10);

  // stores input
  int* input = new int[1000];
  int count = 0;

  
  if(strcmp(option, "FILE") == 0) {

    // stores input from file
    //int* fileInput = new int[1000];
    //int count = 0;
    
    // get the file
    char file[100];
    cout << "Enter the name of the file you want to use: ";
    cin.getline(file, 100);
    ifstream inFile;
    inFile.open(file);

    int value = 0;
    while(inFile >> value) {
      input[count] = value;
      count++;
    }
  } // if(strcmp(option, "FILE") == 0) '}'
  else if(strcmp(option, "MANUAL") == 0) {

    // stores input from user
    char* userInput = new char[1000];
    
    // prompt for input
    cout << "Enter the integer values you want to put in the tree (seperate the integers by single spaces): ";
    cin.getline(userInput, 1000);
    char* delimiter = strtok(userInput, " ");

    // convert input into integers
    while(delimiter != NULL) {
      input[count] = atoi(delimiter);
      delimiter = strtok(NULL, " ");
      count++;
    }
    
  } // else if(strcmp(option, "MANUAL") == 0) '}'

    Node* head = new Node();
    for(int i = 0; i < count; i++) {
      addNode(head, input[i]);
    }
    
    // program quit
    bool quit = false;
    
    // user command
    char option2[10];
    // tell user what to do
    cout << endl;
    cout << "Type ADD to add another integer." << endl;
    cout << "Type REMOVE to delete an integer in the tree." << endl;
    cout << "Type PRINT to print the entire tree." << endl;
    cout << "Type QUIT to terminate the program." << endl;
    
    
    while(quit == false) {
      cout << "What would you like to do: ";
      cin.getline(option2, 10);
      // if the user wants to add a number
      if(strcmp(option2, "ADD") == 0) {
	// prompt user
	int number = 0;
	cout << "Enter the integer you would like to add: ";
	cin >> number;
	cin.get();
	addNode(head, number);
      }
      // if the user wants to delete an integer
      else if(strcmp(option2, "REMOVE") == 0) {
	int number = 0;
	cout << "Enter the integer you want to delete: ";
	cin >> number;
	cin.get();
	if(head->getLeft() == NULL & head->getRight() == NULL) {
	  head->setValue(NULL);
	}
	else {
	  head = deleteNode(head, number);
	}
      }
      else if(strcmp(option2, "PRINT") == 0) {
	// if the tree is empty
	//if(head->getValue() == NULL) {
	//cout << "Nothing to print." << endl;
	//}
	//else {
	  print(head);
	  //}
      }
      else if(strcmp(option2, "QUIT") == 0) {
	cout << "Terminating program" << endl;
	quit = true;
      }
      else {
	cout << "Invalid command. Try again." << endl;
      }
    } // while(quit == false) '}'
    
    
} // int main() '}'



// functions

// add function
void addNode(Node* head, int value) {
  // if the tree is empty set the value of the root 
  if(head->getValue() == NULL) {
    head->setValue(value);
    return;
  }
  // if the root is greater than the value 
  else if(head->getValue() > value) {
    // keep going to the left if not null
    if(head->getLeft() != NULL) {
      Node* temp = head->getLeft();
      // recursive call to keep going till left is null
      addNode(temp, value);
    }
    // if left is null
    else {
      // add the node
      Node* temp = new Node();
      temp->setValue(value);
      head->setLeft(temp);
      return;
    }
  }
  // if the root is less than the value
  else if(head->getValue() < value) {
    // keep going to the right if not null
    if(head->getRight() != NULL) {
      Node* temp = head->getRight();
      // recursive call to keep going till right is null
      addNode(temp, value);
    }
    // if right is null
    else {
      // add the node
      Node* temp = new Node();
      temp->setValue(value);
      head->setRight(temp);
      return;
    }
  }
  else {
    return;
  }
} // void addNode(Node* head, int value) '}'


// delete function
Node* deleteNode(Node* head, int value) {
  // if root is greater than the value
  if(head->getValue() > value) {
    //recursive call to keep going to left until the value is found
    head->setLeft(deleteNode(head->getLeft(), value)); // delete that node
  }
  // if the root is less than the value
  else if(value > head->getValue()) {
    // recursive call to keep going to the right until the value is found
    head->setRight(deleteNode(head->getRight(), value)); // delete that node
  }
  else {
    // if 
    if(head->getLeft() == NULL) {
      Node* temp = head->getRight();
      free(head);
      return temp;
    }
    else if(head->getRight() == NULL) {
      Node* temp = head->getLeft();
      free(head);
      return temp;
    }
    Node* temp = smallestNode(head->getRight());
    head->setValue(temp->getValue());
    head->setRight(deleteNode(head->getRight(), temp->getValue()));
  }
} // void deleteNode(Node* head, int value) '}'

// smallest node finding function
Node* smallestNode(Node* head) {
  Node* current = head;
  while(current->getLeft() != NULL) {
    current = current->getLeft();
  }
  return current;
}

// level by level print
// www.geeksforgeeks.org/print-level-order-traversal-line-line/
void print(Node* head) {

  // base case
  if(head == NULL) {
    return;
  }

  // create queue
  queue<Node*> q;

  // initialize height
  q.push(head);
  
  while(1) {
    // indicate number of nodes at current level
    int count = q.size();
    if(count == 0) {
      break;
    }

    // pop nodes of current level and push all nodes of next one
    while(count > 0) {
      Node* node = q.front();
      cout << node->getValue() << " ";
      q.pop();
      if(node->getLeft() != NULL) {
	q.push(node->getLeft());
      }
      if(node->getRight() != NULL) {
	q.push(node->getRight());
      }
      count--;
    }
    cout << endl;
  }
}
