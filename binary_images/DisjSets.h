/*
* Title:            CreateGraphAndTest.cpp
* Author:           Calvin Quach
* Purpose:          DisjSet object implementation (Its disjoint set lol), implementation straight from textbook
* Date of Creation: 05/02/2016
* 
*	NOTE:
*		there is no 0 element in this set
*/
#ifndef DISJSETS_H_
#define DISJSETS_H_
#include <iostream>
#include <vector>


using namespace std;

//disjoint set find(0) is non exisitent only (1 to numElements)
class DisjSets{
public:
	explicit DisjSets( int numElements ) {
		for(size_t i = 0; i < numElements+1; ++i){
			s.push_back(-1);
		}
	}

	//
	int Find( int x ) const{
		//cout << "No Change Find" << endl;
		if(s[x] < 1)
			return s[x];
		else
			return Find( s[x] );
	}

	//@param x: the int that is to be found
	//@return: the set the int belongs to
	int Find( int x ){
		//cout << "CHANGE find " << endl;
		if(s[x] < 1)
			return x;
		else
			return s[x] = Find( s[x] );
	}

	//@param root1: first set
	//@param root2: second set
	// joins the two sets together
	void UnionSets(int root1, int root2){
		if(s[root2] < s[root1])		//root2 is deeper
			s[root1] = root2;		//Make root2 new root
		else{
			if(s[root1] == s[root2])
				--s[root1];			//update height if same
			s[root2] = root1;		//ake root1 new root
		}
	}

	//@return: whether all the elements are under one set
	bool AllConnected(){
		for(int i = 1; i < s.size(); i++)
			if(s[i] == -1)
				return false;
		return true;
	}

  void print() {
    for(int i = 1; i < s.size(); i++)
      cout << s[i] << ' ';
    cout << endl;
  }

	/*
	size_t GetSize(){
		return s.size();
	}
	int GetPos(int pos){
		return s[pos];
	}
	*/

private:
	vector<int> s;

};
#endif
