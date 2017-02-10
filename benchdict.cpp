/****************************************************************************

                                                Kimiko Yamamoto
                                                CSE 100, Winter Quarter
                                                2/9/17
                                                A13208241
                              Assignment 2

File Name:      benchdict.cpp
Description:    This program finds the running times of the find function for
                BST, HashTable, and TST.  

                ./benchdict [min_size] [step_size] [num_iterations] [dictfile]

****************************************************************************/


#include <iostream>
#include <fstream>
#include <set>
#include "util.h"
#include "DictionaryTrie.h"
#include "DictionaryBST.h"
#include "DictionaryHashtable.h"
using namespace std;

int main(int argc, char** argv) 
{

  unsigned int min_size = atoi(argv[1]);
  unsigned int step_size = atoi(argv[2]);
  unsigned int num_iterations = atoi(argv[3]);
  unsigned int hundred = 100;
  vector<std::string> words;  //the words to find
  string read_string;
  size_t space;
  vector<string>::iterator wit;
  vector<string>::iterator wen;

  Timer t;
  long long end_time;
  long long avg_time;

  //BST
  std::cout << std::endl << "DictionaryBST" << std::endl;

  for(unsigned int j=0; j < num_iterations; ++j) {
  
    DictionaryBST* dict_bst = new DictionaryBST();
    ifstream ifs;
    ifs.open(argv[4]);
    words.clear();
    avg_time = 0;
    //read in words into the dictionary 
    Utils::load_dict(*dict_bst, ifs, min_size+j*step_size);

    if( ifs.eof() ) {
      std::cout << "Warning: not enough words" << std::endl;
    }
    
    //put next 100 words into words vector
    for(unsigned int i=0; i < hundred; ++i ) {
      getline(ifs, read_string);
      space = read_string.find_first_of(" ");
      words.push_back(read_string.substr(++space));
    }
    wit = words.begin();
    wen = words.end();
  
    //time the find function for words in words vector
    for(int k=0; k < 23; ++k) {
      t.begin_timer();

      for(; wit != wen; ++wit) {
        dict_bst->find(*wit);
      }
  
      end_time = t.end_timer();
      avg_time += end_time;
    }
   
    avg_time = avg_time/23;
  
    std::cout << min_size+j*step_size << "\t" << avg_time << std::endl;
    ifs.close();
    delete(dict_bst);
 }

  //Hashtable
  std::cout << std::endl << "DictionaryHashtable" << std::endl;

  for(unsigned int j=0; j < num_iterations; ++j) {

    DictionaryHashtable* dict_hash = new DictionaryHashtable();
    ifstream ifs;
    ifs.open(argv[4]);
    words.clear();
    avg_time = 0;
    //read words into dictionary
    Utils::load_dict(*dict_hash, ifs, min_size+j*step_size);

    if( ifs.eof() ) {
      std::cout << "Warning: not enough words" << std::endl;
    }
  
    //put next 100 words into words vector
    for(unsigned int i=0; i < hundred; ++i ) {
      getline(ifs, read_string);
      space = read_string.find_first_of(" ");
      words.push_back(read_string.substr(++space));
    }

    wit = words.begin();
    wen = words.end();
  
    //time the find function for word vector
    for(int k=0; k < 23; ++k) {
      t.begin_timer();

      for(; wit != wen; ++wit) {
        dict_hash->find(*wit);
      }
  
      end_time = t.end_timer();
      avg_time += end_time;
    }

    avg_time = avg_time/23;  

    std::cout << min_size+j*step_size << "\t" << avg_time << std::endl;
    ifs.close();
    delete(dict_hash);
  }

  //TST
  std::cout << std::endl << "DictionaryTrie" << std::endl;

  for(unsigned int j=0; j < num_iterations; ++j) {

    DictionaryTrie* dict_tst = new DictionaryTrie();
    ifstream ifs;
    ifs.open(argv[4]);
    words.clear();
    avg_time = 0;
    //read words into dictionary
    Utils::load_dict(*dict_tst, ifs, min_size+j*step_size);

    if( ifs.eof() ) {
      std::cout << "Warning: not enough words" << std::endl;
    }

    //put next 100 words into words vector
    for(unsigned int i=0; i < hundred && !ifs.eof(); ++i ) {
      getline(ifs, read_string);
      space = read_string.find_first_of(" ");
      words.push_back(read_string.substr(++space));
    }
    wit = words.begin();
    wen = words.end();

    //time the find function for word vector
    for(int k=0; k < 23; ++k) {
      t.begin_timer();

      for(; wit != wen; ++wit) {
        dict_tst->find(*wit);
      }
      end_time = t.end_timer();
      avg_time += end_time;
    }
  
    avg_time = avg_time/23;

    std::cout << min_size+j*step_size << "\t" << avg_time << std::endl;
    ifs.close();
    delete(dict_tst);
  }

  return 0;
}

