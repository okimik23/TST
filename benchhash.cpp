/****************************************************************************

                                                Kimiko Yamamoto
                                                CSE 100, Winter Quarter
                                                2/9/17
                                                A13208241
                              Assignment 2

File Name:      benchhash.cpp
Description:    This program takes two hash functions and finds the number
                of 'hits' each slot will get.  Then it finds the number of
                slots receiving a certain amount of hits.  The average number
                of steps for a successful search and the worst case steps 
                for a successful search are also found.

                ./benchhash [dictfile] [num_words]

****************************************************************************/


#include<fstream>
#include <iostream>
#include<vector>

using namespace std;


//stackoverflow
int hash1 (string word, int table_size)   
{       int sum = 0;
        for (unsigned int k = 0; k < word.length(); k++)
            sum = sum + int(word[k]);
        return  sum % table_size; 
}

//stackoverflow
int hash2 (string word, int table_size)
{
   int seed = 131; 
   unsigned long hash = 0;
   for(unsigned int i = 0; i < word.length(); i++)
   {
      hash = (hash * seed) + word[i];
   }
   return hash % table_size;
}


int main(int argc, char** argv) 
{
  double size = 2*atoi(argv[2]);
  double result;
  double avg1, avg2, max1, max2;
  vector<int>h1(size, 0);
  vector<int>h2(size, 0);
  vector<int>h1_r(size, 0);
  vector<int>h2_r(size, 0);
  ifstream ifs;
  ifs.open(argv[1]);
  string read_string;
  int space;

  //hashing 
  for( int i=0; i < atoi(argv[2]); ++i) {
    getline(ifs, read_string);
    space = read_string.find_first_of(" ");
    read_string = read_string.substr(++space);
    
    result = hash1(read_string, size);
    h1[result]++;

    result = hash2(read_string, size);
    h2[result]++;
  }
  
  //finding number of slots for each number of hits
  for(int j=0; j < atoi(argv[2]); ++j) {
    result = h1[j];
    h1_r[result]++;
    
    if( result > max1 ) {
      max1 = result;
    }

    result = h2[j];
    h2_r[result]++;

    if( result > max2 ) {
      max2 = result;
    }
  }
  
  int sum = 0;
  for(int g=0; g <= 1+max1; g++) {
    for(int h=g; h <= 1+max1; h++) {
      sum += h1_r[h];
    }
    avg1 += g*sum;
    sum = 0;
  }
  
  sum = 0;
  for(int g=0; g <= 1+max2; g++) {
    for(int h=g; h <= 1+max2; h++) {
      sum += h2_r[h];
    }
    avg2 += g*sum;
    sum = 0;
  }
  avg1 /= atoi(argv[2]);
  avg2 /= atoi(argv[2]);  
  
  //hash1
  cout <<"Printing the statistics for hashFunction1 with hash table size ";
  cout << size << endl;
  cout << "#hits\t#slots receiving the #hits" << endl;
  for(int k=0; k <= max1+1; ++k) {
    if( h1_r[k] != 0 ) {
      cout << k << "\t  " << h1_r[k] << endl;
    }
  }
  cout << "The average number of steps for a successful search for hash";
  cout << " function 1 would be " << avg1 << endl;
  cout << "The worst case steps that would be needed to find a word is " <<
  max1 << endl;

  //hash2
  cout <<"Printing the statistics for hashFunction2 with hash table size ";
  cout << size << endl;
  cout << "#hits\t#slots receiving the #hits" << endl;
  for(int k=0; k <= max2+1; ++k) {
    if( h2_r[k] != 0 ) {
      cout << k << "\t  " << h2_r[k] << endl;
    }
  }
  cout << "The average number of steps for a successful search for hash";
  cout << " function 1 would be " << avg2 << endl;
  cout << "The worst case steps that would be needed to find a word is " <<
  max2 << endl;

  ifs.close();
  return 0;
}
