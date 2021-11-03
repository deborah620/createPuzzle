/*
**File Name: mytest.cpp
**Author: Deborah Miller
**Date: 2/8/2021
**Email: d169@umbc.edu
**Description: test file for proj0
*/

#include "puzzle.h"
const int SELF = 4; //used to test the assignment operator

class Tester{//this is your tester class, you add your test functions in this class
    public:
    bool testCopyConstructor(const Puzzle& puzzle);
    bool testAssignmentOperator(const Puzzle& puzzle, int num);
    void measureCopyTime(Puzzle& puzzle);
    bool testClear(Puzzle puzzle);
};

int main() {
    Tester tester;
    {
        //test deep copy, object with many members
        Puzzle p1(1000);
        cout << "Test case, Copy Constructor: same members, same size, different pointers (deep copy):" << endl;
        if (tester.testCopyConstructor(p1)) cout << "Copy constructor passed!" << endl;
        else cout << "Copy constructor failed!" << endl;
    }
    {
        //test the edge case, object with 1 member
        cout << "\nTest case, Copy Constructor: 1 member:" << endl;
        Puzzle p1(1);
        if (tester.testCopyConstructor(p1)) cout << "Copy constructor passed!" << endl;
        else cout << "Copy constructor failed!" << endl;
    }
    {
        //test the edge case, 0 member, i.e. empty object
        cout << "\nTest case, Copy Constructor: zero members:" << endl;
        Puzzle p1(0);
        if (tester.testCopyConstructor(p1)) cout << "Copy constructor passed!" << endl;
        else cout << "Copy constructor failed!" << endl;
    }
    {
        //test the user error case, creating object with table size less than 0 
        cout << "\nTest case, Copy Constructor: table size less than 0:" << endl;
        Puzzle p1(-10);
        if (tester.testCopyConstructor(p1)) cout << "Copy constructor passed!" << endl;
        else cout << "Copy constructor failed!" << endl;
    }
    {
      //test assignment operator, object with many members
      cout << "\nTest case, Assignment Operator: same members, same size, different pointers" << endl;
      Puzzle p1(10);
      if (tester.testAssignmentOperator(p1, 5)) cout << "Assignment operator passed!" << endl;
      else cout << "Assignment operator failed!" << endl;
    }
    {
      //test the edge case, object with 1 member (assignment operator)
      cout << "\nTest case, Assignment Operator: 1 member:" << endl;
      Puzzle p1(1);
      if (tester.testAssignmentOperator(p1, 7)) cout << "Assignment Operator passed!" << endl;
      else cout << "Assignment Operator failed!" << endl;
    }
    {
      //test the edge case, 0 member, i.e. empty object (assignment operator)
      cout << "\nTest case, Assignment Operator: zero members:" << endl;
      Puzzle p1(0);
      if (tester.testAssignmentOperator(p1, 10)) cout << "Assignment Operator passed!" << endl;
      else cout << "Assignment Operator failed!" << endl;
    }
    {
      //test the edge case, with the variable on the left 0 member
      cout << "\nTest case, Assignment Operator: left zero members:" << endl;
      Puzzle p1(5);
      if (tester.testAssignmentOperator(p1, 7)) cout << "Assignment Operator passed!" << endl;
      else cout << "Assignment Operator failed!" << endl;
    }
    {
      //test the user error case, creating object with table size less than 0 (assignment operator)
      cout << "\nTest case, Assignment Operator: table size less than 0:" << endl;
      Puzzle p1(-5);
      if (tester.testAssignmentOperator(p1, 9)) cout << "Assignment Operator passed!" << endl;
      else cout << "Assignment Operator failed!" << endl;
    }
    {
      //test self assignment,
      cout << "\nTest case, Assignment Operator: self assignemnt:" << endl;
      Puzzle p1(4);
      if (tester.testAssignmentOperator(p1, 3)) cout << "Assignment Operator passed!" << endl;
      else cout << "Assignment Operator failed!" << endl;
    }
    {
      //Measuring the efficiency of the copy constructor
      cout << "\nMeasuring the efficiency of the copy constructor:" << endl;

      //scaling factor
      const int a = 2;

      int numTrials = 5;
	
      //original input size
      int N = 1000; 

      //loop, runs n times and function grows occordingly
      //increases in time as it increases in size 
      for (int i = 0; i < numTrials; i++) {
	Puzzle p1(N);
	tester.measureCopyTime(p1);
	N = N * a;
      }
    }
    {
      //an example of dump
      cout << "\nHere is an example of a table:" << endl;
      Puzzle p1(10);
      p1.dump();
      cout << endl;
    }
    {
      //make sure clear works
      cout << "\nTesting Clear()" << endl;
      Puzzle p1(-10);
      if (tester.testClear(p1)) cout << "Cleared!" << endl;
      else cout << "Cleared failed!" << endl;
    }
    return 0;
}
bool Tester::testCopyConstructor(const Puzzle& puzzle){
    Puzzle copy(puzzle);

    //the case of empty object
    if (puzzle.m_size == 0 && copy.m_size == 0) return true;

    //the case that sizes are the same and the table pointers are not the same
    else if (puzzle.m_size == copy.m_size && puzzle.m_table != copy.m_table){
      for (int i=0;i<puzzle.m_size;i++){
            for (int j=0;j<puzzle.m_size;j++)
            {
                if ((puzzle.m_table[i][j] != copy.m_table[i][j]) || //check the value
                    (puzzle.m_table[i] == copy.m_table[i])){        //check the ith pointer
		  return false;
                }
            }
        }
        return true;
    }

    //everything else
    else return false;
}

bool Tester::testAssignmentOperator(const Puzzle &puzzle, int num) {
  Puzzle assignment(num);
  assignment = puzzle;
  
  //the case of empty object
  if (puzzle.m_size == 0 && assignment.m_size == 0) return true;

  //the case of self assignment
  else if(puzzle.m_size == SELF) {
    int assignSize = assignment.m_size;
    //tries to set assignment = to itself
    assignment = assignment;
    //fails if assignment current size is equal to it's past size
    if (assignment.m_size != assignSize)
      return true;
  }

  //the case that sizes are the same and the table pointers are not the same
  else if (puzzle.m_size == assignment.m_size && puzzle.m_table != assignment.m_table){
    for (int i=0;i<puzzle.m_size;i++){
      for (int j=0;j<puzzle.m_size;j++)
	{
	  if ((puzzle.m_table[i][j] != assignment.m_table[i][j]) || //check the value
	      (puzzle.m_table[i] == assignment.m_table[i])){        //check the ith pointer
	    return false;
	  }
	}
    }
    return true;
  }

  //everything else
  else return false;
}

void Tester::measureCopyTime(Puzzle& puzzle)
{
    //Measuring the efficiency of copying algorithm with system clock ticks
    //Clock ticks are units of time of a constant but system-specific length, as those returned by function clock().
    //Dividing a count of clock ticks by CLOCKS_PER_SEC yields the number of seconds.
    double T = 0.0;//to store running times
    clock_t start, stop;//stores the clock ticks while running the program
    {
        start = clock();
	Puzzle copy(puzzle);//the algorithm to be analyzed for efficiency
        stop = clock();
        T = stop - start;//number of clock ticks the algorithm took
        cout << "Copying one puzzle with " << copy.m_size * copy.m_size << " members took " << T << " clock ticks ("<< T/CLOCKS_PER_SEC << " seconds)!" << endl;
    }
}
bool Tester::testClear(Puzzle puzzle){
  puzzle.clear();
  if(puzzle.m_size == 0)
    return true;
  return false;
}
