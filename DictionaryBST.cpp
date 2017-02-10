/****************************************************************************

                                                Kimiko Yamamoto
                                                CSE 100, Winter Quarter
                                                2/9/17
                                                A13208241
                              Assignment 2

File Name:      DictionaryBST.cpp
Description:    DictionaryBST creates a dictionary using a BST.
                It has functions to insert a new word or to find a word.
                There is also a default deconstructor.

****************************************************************************/


#include "util.h"
#include "DictionaryBST.h"
#include <set>

/* Create a new Dictionary that uses a BST back end */
DictionaryBST::DictionaryBST(){}

/* Insert a word into the dictionary. */
bool DictionaryBST::insert(std::string word)
{	
	if( find(word) ) {
		return false;
	}

	dictionary.insert(word);
	return true;

}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryBST::find(std::string word) const
{
	if( dictionary.find(word) != dictionary.end() ) {
		return true;
	}
	
	return false;

}

/* Destructor */
DictionaryBST::~DictionaryBST(){
	dictionary.clear();
}
