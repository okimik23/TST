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
