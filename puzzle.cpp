/*
**File Name: puzzle.cpp
**Author: Deborah Miller
**Date: 2/8/2021
**Email: d169@umbc.edu
**Description: creates a random nxn puzzle 
*/

#include "puzzle.h"

//overloaded constructor 
Puzzle::Puzzle(int size){
    // *************************************
    // Implement the alternative constructor
    // *************************************

    if(size <= 0)
      m_size = 0;

    else
      m_size = size;

    makeMem();
    fill();    
}
//destructor
Puzzle::~Puzzle(){
    clear();
}
//clear the puzzle
void Puzzle::clear(){
    // ***************************
    // Implement clear() function
    // ***************************
  
    if(m_size > 0){
      //delete every value in array
      for(int i = 0; i < m_size; i++)
	delete[] m_table[i];
      delete[] m_table;
      m_size = 0;
    }
}
//set 2D array size
void Puzzle::makeMem(){
    // ****************************
    // Implement makeMem() function
    // ****************************

    if(m_size > 0) {
      //dynamically initialize a 2D array to m_size x m_size
      m_table = new char *[m_size];
      for (int i = 0; i < m_size; i++) {
	m_table[i] = new char[m_size];
      }
    }
}
//copy constructor
Puzzle::Puzzle(const Puzzle& rhs){
    // ***************************
    // Implement copy constructor
    // ***************************

    m_size = rhs.m_size;

    if(m_size > 0){
      makeMem();
   
      //copy every value of old array to new array
      for(int i = 0; i < m_size; i++) {
	for(int j = 0; j < m_size; j++){
	  m_table[i][j] = rhs.m_table[i][j];
	}
      }
    }
}
//overloaded =
const Puzzle& Puzzle::operator=(const Puzzle& rhs){
    // *****************************
    // Implement assignment operator
    // *****************************

    //gaurd against self assignment
    if (this != &rhs){
      //delete existing array
      if(m_size > 0){
	for(int i = 0; i < m_size; i++)
	  delete[] m_table[i];
	delete[] m_table;
	m_size = 0;
      }

      //make new array with value of array on the right of =
      m_size = rhs.m_size;

      if(m_size > 0){
	makeMem();

	//fill values with that of the right side
	for (int i = 0; i < m_size; i++) {
	  for(int j = 0; j < m_size; j++){
	    m_table[i][j] = rhs.m_table[i][j];
	  }
	}
      }
    }
    return *this;
}
void Puzzle::dump(){
    if (m_size > 0){
        int i=0;
        int j=0;
        while(i<m_size){
            while(j<m_size){
                cout << m_table[i][j] << " ";
                j++;
            }
            cout << endl;
            j=0;
            i++;
        }
        cout << endl;
    }
}
void Puzzle::fill(){
    srand(time(NULL));//create the seed value using the current time
    int i=0;
    int j=0;
    while(i<m_size){
        while(j<m_size){
            m_table[i][j] = ALPHA[rand() % MAX];//find a random char from the chars list
            j++;
        }
        j=0;
        i++;
    }
}
