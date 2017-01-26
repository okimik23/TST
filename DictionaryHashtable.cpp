#include "util.h"
#include "DictionaryHashtable.h"
#include <unordered_set>

/* Create a new Dictionary that uses a Hashset back end */
DictionaryHashtable::DictionaryHashtable(){}

/* Insert a word into the dictionary. */
bool DictionaryHashtable::insert(std::string word)
{
	if( find(word) ) {
		return false;
	}

	dictionary_h.insert(word);
	return true;
	
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryHashtable::find(std::string word) const
{

	if( dictionary_h.find(word) != dictionary_h.end() ) {
		return true;
	}
	
	return false;
}

/* Destructor */
DictionaryHashtable::~DictionaryHashtable(){
	
}
