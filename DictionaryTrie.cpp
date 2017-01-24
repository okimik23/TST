#include "util.h"
#include "DictionaryTrie.h"

/* Create a new Dictionary that uses a Trie back end */
DictionaryTrie::DictionaryTrie(){
	root = NULL;
}

/* Insert a word with its frequency into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not (i.e. it was already in the dictionary or it was
 * invalid (empty string) */
bool DictionaryTrie::insert(std::string word, unsigned int freq)
{
  //already in dictionary
  if( find(word) ) {
    return false;
  }

  //empty string
  if( word.length() == 0 ) {
    return false;
  }
  
  index = 0; //the char in the word
  TSTNode* curr = locate_node(word, root, index);
  
  //start new tree
  if( !root ) {
    root = new TSTNode(word[index]);
    curr = root;
  }
  
  //check if word is already in trie
  else if( index == word.length() ) {
    curr->finish = true;
    return true;
  }

  //find node to continue word if not root
  else if( curr->letter != word[index] ) {
    //word branches to the left
    if( curr->letter > word[index] ) {
      curr = curr->left;
      curr = new TSTNode(word[index]);
    }
    else {
      curr = curr->right;
      curr = new TSTNode(word[index]);
    }
    index++;
  }

  //fill in rest of word in new branch
  for( ; index < word.length(); index++ ) {
    curr = curr->middle;
    curr = new TSTNode(word[index]);
  }
  
  curr->finish = true;
  curr->frequency = freq;
  return true;
}

/* Returns node of char to start inserting a word */
TSTNode* DictionaryTrie::locate_node(std::string word, TSTNode* curr, 
	unsigned int i) //const
{

  if( !curr ) { //keep?
    index = 0;
    return NULL;
  }
  index = 0;
  while( index < word.length() ) {
    if( curr->letter == word[index] ) {
      if( curr->middle != NULL && index != (word.length()-1) ) {
	 curr = curr->middle;
	 index++;
      }
      else
	return curr;
    }

    else if( curr->letter > word[index] ) {
      if( curr->left != NULL ) {
        curr = curr-> left;
      }
      else return curr;
    }

    else {
      if( curr->right != NULL ) {
        curr = curr-> right;
      }
      else return curr;
    }
 
  }
  return curr;
}

//TSTNode* DictionaryTrie::get_node(

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) const
{
 //check if tree exists
 /* if( !root ) {
    return false;
  } 
  
  unsigned int i = 0;
  TSTNode* curr = locate_node(word, root, i);
  
  if( curr->letter == word[word.length()] ) {
    if( curr->finish ) {
     // if( curr->frequency < frequency) {  How to check???
     return true;

    }
  }
*/
  return false;
}

/* Return up to num_completions of the most frequent completions
 * of the prefix, such that the completions are words in the dictionary.
 * These completions should be listed from most frequent to least.
 * If there are fewer than num_completions legal completions, this
 * function returns a vector with as many completions as possible.
 * If no completions exist, then the function returns a vector of size 0.
 * The prefix itself might be included in the returned words if the prefix
 * is a word (and is among the num_completions most frequent completions
 * of the prefix)
 */
std::vector<std::string> DictionaryTrie::predictCompletions(std::string prefix, unsigned int num_completions)
{
  std::vector<std::string> words;
  return words;
}

/* Destructor */
DictionaryTrie::~DictionaryTrie(){
	deleteAll(root);
}

void DictionaryTrie::deleteAll(TSTNode* n) {

  if( !n) {
    return;
  }
  if( n->left ) {
    deleteAll(n->left);
  }
  if( n->right) {
    deleteAll(n->right);
  }
  if( n->middle ) { 
   deleteAll(n->middle);
  }
  
  delete n;
}
