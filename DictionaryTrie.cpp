/****************************************************************************

                                                Kimiko Yamamoto
                                                CSE 100, Winter Quarter
                                                2/9/17
                                                A13208241
                              Assignment 2

File Name:      DictionaryTrie.cpp
Description:    DictionaryTrie creates a dictionary using a ternary search trie.
                It has functions to insert a new word or to find a word.
                The function predictCompletions can find the most frequent words
                in the dictionary trie that start with a certain prefix.

****************************************************************************/


#include "util.h"
#include "DictionaryTrie.h"
#include <queue>
#include <algorithm>
#include <string>
#include<set>
#include<cstdlib>

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

  TSTNode* curr;
  unsigned int index = 0;
  bool already_there = false;

  //check if empty string
  if( word.length() == 0 ) {
    return false;
  }
  //already in tree
  if( find(word) ) {
    
    already_there = true;
  }

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
        //word should be completed
        if( index == (word.length()-1) ) {
          ++index;
          break;
        }
        //word does not need to branch yet
        else if( curr->middle && index != (word.length()-1) ) {
          curr = curr->middle;
          ++index;
        }
        else {
          //word is inserted in the middle node
          if( !already_there && index != (word.length()-1) ) {
            curr->middle = new TSTNode(word[++index]);
          }
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
          //word creates new branch at letter
          if( !already_there ) {
            curr->left = new TSTNode(word[index]);
          }
          curr = curr->left;
          ++index;
          break;
        }
      }

      //go right
      else if( curr->letter < word[index] ) {  
        if( curr->right ) {
          curr = curr->right;
        }
        else { 
          //word creates new branch at letter
          if( !already_there ) {
            curr->right = new TSTNode(word[index]);
          }
          curr = curr->right;
          ++index;
          break;
        }
      }

    }

    //fill in rest of trie
    while( index < word.length() && !already_there ) {
     
      if( curr && index == (word.length()) && curr->letter == word[index] ) {
        break;
      }
      if( !already_there ) {
        curr->middle = new TSTNode(word[index]);
      }
      curr = curr->middle;
      ++index;
    }
  }

  //duplicate word so check for larger frequency
  if( already_there ) {
    if( freq > curr->frequency ) {
      curr->frequency = freq;
    }
    return false;
  }
  
  curr->finish = true;
  curr->frequency = freq;
  curr->s_word = word;

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
        return curr->finish;
      }
      if( curr->middle){
        curr = curr->middle;
        ++index;
      }
     else return false;
    }
    
    //go left
    else if( curr->letter > word[index] ) {
      if( curr->left ) {
        curr = curr->left;
      }
      else return false;
    }

    //go right
    else  if ( curr->letter < word[index] ) {
      if( curr->right ) {
        curr = curr->right;
      }
      else return false;
    }

  }
    
    //check if the word was inserted
    if( curr->finish ) {
     return true;

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
  std::queue<TSTNode*> q;

  //empty prefix returns empty string
  if( prefix == "" ) {
    return words;
  }
  
  if( num_completions <= 0 ) {
    return words;
  }

  //check if tree exists
  if( !root ) {
    return words;
  }

  //look for prefix in the tree, same as find
  unsigned int index = 0;
  TSTNode* curr = root;

  while( index < prefix.length() ) {

    //go middle
    if( curr->letter == prefix[index] ) {
      if( index == (prefix.length()-1) ) {
	break;
      }
      else if( curr->middle ) {
        curr = curr->middle;
        ++index;

      }
      else break;
    }
    
    //go left
    else if( curr->letter > prefix[index] ) {
      if( curr->left ) {
        curr = curr->left;
      }
      else break;
    }

    //go right
    else if( curr->letter < prefix[index] ) {
      if( curr->right ) {
        curr = curr->right;
      }
      else break;
    }

  }

  //prefix not in dictionary
  if( curr->letter != prefix[index] ) {
    std::cout << "Invalid Input. Please retry with correct input" 
      << std::endl;
    return words;
  }

  //start BFS
  q.push(curr);
  TSTNode* nodes[num_completions];
  for(unsigned int i=0; i < num_completions; i++ ) {
    nodes[i] = 0;
  }
  TSTNode* temp;
  TSTNode* original;
  bool first = true;
  // fill in queue
  while( !q.empty() ) {
    curr = q.front();
    q.pop();
    
    //visit node
    if( curr->finish ) { 
      temp = curr;
      original = curr;
      for(unsigned int i=0; i < num_completions; ++i)
      {
        if( nodes[i] == 0 ) {
	  nodes[i] = curr;
          break;
        }

        else if( nodes[i]->frequency < curr->frequency ) {
  	  temp = nodes[i];
          nodes[i] = curr;
          curr = temp;
        }
      }
        curr = original;
      }
    
    //add nodes to queue
    if( curr->middle != NULL ) {
      q.push(curr->middle);
    }
    if( !first ) {
      if( curr->left != NULL ) {
        q.push(curr->left);
      }
    
      if( curr->right != NULL ) {
        q.push(curr->right);
      }
    }
    first = false;

  }

  for(unsigned int j = 0; j < num_completions; ++j ) {
    if( nodes[j] != 0 ) {
      words.push_back(nodes[j]->s_word);
    }
  }

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
