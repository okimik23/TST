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
  //check if empty string
  if( word.length() == 0 ) {
    return false;
  }
  //already in tree
  if( find(word) ) {
    return false;
  }

  TSTNode* curr;
  unsigned int index = 0;

  //no root
  if( !root ) {
    root = new TSTNode(word[index]);
    curr = root;
    ++index;
    while( index < word.length() ) {
      curr->middle = new TSTNode(word[index]);
      curr = curr->middle;
      index++;
    }
  }

  else {

    curr = root;
 
    //trie exists
    while( index < word.length() ) {

      //go middle
      if( curr->letter == word[index] ) {
        if( index == (word.length()-1) ) {
          break;
        }
        else if( curr->middle ) {
          curr = curr->middle;
          ++index;
        }
        else {
          curr->middle = new TSTNode(word[index]);
          curr = curr->middle;
          ++index;
          break;
        }
      }
    
      //go left
      else if( curr->letter > word[index] ) {
        if( curr->left ) {
          curr = curr->left;
        }
        else {
          curr->left = new TSTNode(word[index]);
          curr = curr->left;
          ++index;
          break;
        }
      }

      //go right
      else {  
        if( curr->right ) {
          curr = curr->right;
        }
        else {
          curr->right = new TSTNode(word[index]);
          curr = curr->right;
          ++index;
          break;
        }
      }

    }
  
  //fill in rest of trie
  while( index < word.length() ) {
    if( index == (word.length()-1) && curr->letter == word[index] ) {
      break;
    }
    curr->middle = new TSTNode(word[index]);
    curr = curr->middle;
    ++index;
  }
 }

  curr->finish = true;
  curr->frequency = freq;
  
  return true;

}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) const
{
 //check if tree exists
  if( !root ) {
    return false;
  } 
  
  //look for word in the tree
  unsigned int index = 0;
  TSTNode* curr = root;

  while( index < word.length() ) {

    //go middle
    if( curr->letter == word[index] ) {
      if( index == (word.length()-1) ) {
	break;
      }
      else if( curr->middle ) {
        curr = curr->middle;
        ++index;

      }
      else break;
    }
    
    //go left
    else if( curr->letter > word[index] ) {
      if( curr->left ) {
        curr = curr->left;
      }
      else break;
    }

    //go right
    else { //if( curr->right < word[index] ) {
      if( curr->right ) {
        curr = curr->right;
      }
      else break;
    }

  }

  //check if the word was completely found
  if( word[index] == word[word.length()-1] ) {
    if( curr->finish ) {
     return true;

    }
  }

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
