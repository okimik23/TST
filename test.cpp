#include<iostream>
#include<string>
#include<algorithm>
#include<set>
#include<cstdlib>
#include<fstream>
#include "util.h"
#include "DictionaryTrie.h"
#include "DictionaryBST.h"
#include "DictionaryHashtable.h"
#define LETTERS 26
using namespace std;


int main(int argc, char** argv)
{

  //Initialize words
  vector<std::string> words;
  vector<string>::iterator wit;
  vector<string>::iterator wen;
  //initialize nonwords
  set<string> nope;
  set<string>::iterator nit;
  set<string>::iterator nen;

  //Initialize data structures
  DictionaryBST d_bst;
  DictionaryHashtable d_ht;
  DictionaryTrie dt;
  int t_bst, t_ht, tt;
 
 /* 
  words.push_back("harry");
  words.push_back("sriram");
  words.push_back("cse");
  words.push_back("crucio");
  words.push_back("autocomplete");
  words.push_back("a");
*/

  words.push_back("basketball");
  words.push_back("asterisk");
  words.push_back("basket");
  words.push_back("application");
  words.push_back("a");
  words.push_back("aa");
  words.push_back("aaa");
  words.push_back("aa a");
  words.push_back("app");

  words.push_back("gugglebee");
  words.push_back("waldos");
  words.push_back("are you not entertained");
  words.push_back("never");
  words.push_back("gonna");
  words.push_back("give");
  words.push_back("you");
  words.push_back("up");
  words.push_back("never gonna give you up");
  words.push_back("h k");
  

  cout << "Inserting into Dictionaries..." << endl;

  wit = words.begin();
  wen = words.end();
  for(; wit != wen; ++wit)
    {
      cout << "Inserting: \"" << *wit << "\"... ";
      t_bst = d_bst.insert(*wit);
      t_ht = d_ht.insert(*wit);
      tt = dt.insert(*wit, 1);
      if(!t_bst)
	{
	  cout << "failed for DictionaryBST... ";
	}
      if(!t_ht)
	{
	  cout << "failed for DictionaryHashset... ";
	}
      if(!tt)
	{
	  cout << "failed for DictionaryTrie... ";
	}
      if(t_bst && t_ht && tt)
	{
	  cout << "PASSED! :D ";
	}
      cout << endl;
    }

  cout << endl << "Re-inserting elements that were just inserted into Dictionaries..." << endl;

  wit = words.begin();
  wen = words.end();
  for(; wit != wen; ++wit)
    {
      cout << "Inserting: \"" << *wit << "\"... ";
      t_bst = d_bst.insert(*wit);
      t_ht = d_ht.insert(*wit);
      tt = dt.insert(*wit, 0);
      if(t_bst)
        {
          cout << "failed for DictionaryBST... ";
        }
      if(t_ht)
        {
          cout << "failed for DictionaryHashset... ";
        }
      if(tt)
        {
          cout << "failed for DictionaryTrie... ";
        }
      if(!t_bst && !t_ht && !tt)
        {
          cout << "PASSED! :D ";
        }
      cout << endl;
    }

  cout << endl;

  
  cout << endl << "Finding elements that were just inserted into Dictionaries..." << endl;

  wit = words.begin();
  wen = words.end();
  for(; wit != wen; ++wit)
    {
      cout << "Finding: \"" << *wit << "\"... ";
      t_bst = d_bst.find(*wit);
      t_ht = d_ht.find(*wit);
      tt = dt.find(*wit);
      if(!t_bst)
        {
          cout << "failed for DictionaryBST... ";
        }
      if(!t_ht)
        {
          cout << "failed for DictionaryHashset... ";
        }
      if(!tt)
        {
          cout << "failed for DictionaryTrie... ";
        }
      if(t_bst && t_ht && tt)
        {
          cout << "PASSED! :D ";
        }
      cout << endl;
    }

  cout << endl;

  cout << endl << "Testing predictCompletions..." << endl;
  cout << "Prefix: g num_completions: 5" << endl;
  string prefix = "g";
  unsigned int num_completions = 5;
  auto completions = dt.predictCompletions(prefix, num_completions);
  for(auto it = completions.begin(); it != completions.end(); ++it) {
    cout << *it << endl;
  }
  
  cout << endl << "Prefix: a num_completions: 5" << endl;
  prefix = "a";
  num_completions = 5;
  completions = dt.predictCompletions(prefix, num_completions);
  for(auto it = completions.begin(); it != completions.end(); ++it) {
    cout << *it << endl;
  }
  
  cout << endl << "Prefix: n num_completions: 5" << endl;
  prefix = "n";
  num_completions = 5;
  completions = dt.predictCompletions(prefix, num_completions);
  for(auto it = completions.begin(); it != completions.end(); ++it) {
    cout << *it << endl;
  }
 
  cout << endl << "Prefix: h num_completions: 5" << endl;
  prefix = "h";
  num_completions = 5;
  completions = dt.predictCompletions(prefix, num_completions);
  for(auto it = completions.begin(); it != completions.end(); ++it) {
    cout << *it << endl;
  }
 
  return 0;
}
