// Arnoldo Solism
// Main file for Part 2.2 of Homework 3.

#include "avl_tree.h"
// You will have to add #include "sequence_map.h"
#include "sequence_map.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
using namespace std;

// Skips the header of the rebase210.txt database
void skipHeader(ifstream& file, string db)
{
  // Loops up to 10 because the first 10 lines of db are header
  for (int i = 0; i < 10; i++)
  {
    // Skips
    getline(file, db);
  }
}

// Global variable that counts total calls of remove()
int removeTotalCalls = 0;

namespace 
{
template <typename TreeType>
// Removes every other sequence in sequences.txt
void removeEveryOtherLine(TreeType &a_tree)
{
  // count for every other line
  int everyOtherLine = 1;
  // reading the sequence
  std::string seq_l;
  // opens sequence
  std::ifstream seqtxt("sequences.txt");
  // Gets all lines in seqeunce
  while (getline(seqtxt, seq_l))
  {
    // Counter
    everyOtherLine++;
    // If every other sequence
    if (everyOtherLine % 2 == 0)  
    {
      // Sequence Map object that is being used to delete
      SequenceMap seq(seq_l, ""); 
      // removes the seq
      a_tree.remove(seq);
      // counts everytime remove is called
      removeTotalCalls++;
    }
  }
}

// @dbx_filename: an input database filename.
// @seq_filename: an input sequences filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void TestTree(const string &dbx_filename, const string &seq_filename, TreeType &a_tree) {
  // Code for running Part 2.2
  // Initializes an ifstream object called rebase 210
  std::ifstream rebase210;
  rebase210.open(dbx_filename);
  // Checks if file is able to open or if it
  if (rebase210.fail())
  {
    // prints out error message
    std::cout << "Unable to open file or file does not exist!" << std::endl;
    // exits
    exit(1);
  }

  // string for reading in rebase
  std::string db_line;
  // Skips the header of the Database
  skipHeader(rebase210, db_line);

  // Read the file line by line
  while (getline(rebase210, db_line))
  {
    // stores enzyme acronym
    std::string an_enz_acro;
    // converter
    std::stringstream ss_dbline(db_line);
    // if db is writeable
    if (!db_line.empty())
    {
      // reads in all acronyms
      getline(ss_dbline, an_enz_acro, '/');
    }
    
    // takes in file
    std::string a_reco_seq = seq_filename;
    // reads in sequence
    while (getline(ss_dbline, a_reco_seq, '/') && !a_reco_seq.empty())
    {
      // Insert a new node into the tree for each recognition sequence
      SequenceMap new_sequence_map(a_reco_seq, an_enz_acro);
      // inserts new_sequence_map
      a_tree.insert(new_sequence_map);
    }
  }
  // Closes file
  rebase210.close();

  // Initializes ifstream object
  std::ifstream sequences;
  // objects opens file
  sequences.open(seq_filename);
  // Checks if file is able to open or if it
  if (sequences.fail())
  {
    // prints error message
    std::cout << "Unable to open file or file does not exist!" << std::endl;
    // exits
    exit(1);
  }
  // stores seqeuence.txt
  std::string seq_line;
  // takes in seqeuence.txt
  getline(sequences, seq_line);
  // closes file
  sequences.close();
  /*
    2
  */
  // Prints number of nodes
  std::cout << "2: " << a_tree.countNodes() << std::endl;
  /*
    3a & 3b
  */
  // calculates average depth by diving depth of tree and number of nodes
  float average_depth = a_tree.depthOfTree() / a_tree.countNodes();
  // calculates ratio by divinding average depth by log2 # of nodes
  float ratio = average_depth / log2(a_tree.countNodes());
  // prints avg depth
  std::cout << "3a: " << average_depth << std::endl;
  // prints ratio
  std::cout << "3b: " << ratio << std::endl;
  /*
    4a & 4b
  */ 
  // prints strings found
  a_tree.stringsFound(a_tree);
  /*
    5a & 5b
  */
  // removes a specific set of nodes (see function)
  removeEveryOtherLine(a_tree);
  // prints successful removes
  std::cout << "5a: " << a_tree.getRemovedNodeCalls() << std::endl;
  // stores total recursive calls in a float for later division
  float total = a_tree.getTotalRecursiveCalls();
  // calculates average number of recursion calls
  float avgCalls = total / removeTotalCalls;
  // prints average number of number recursion calls
  std::cout << "5b: " << avgCalls << std::endl;
  /*
    6a & 6b & 6c
  */
  // prints amount of nodes after removal
  std::cout << "6a: " << a_tree.countNodes() << std::endl;
  // prints average depth after removal
  std::cout << "6b: " << average_depth << std::endl;
  // prints ratio of tree 
  std::cout << "6c: " << ratio << std::endl;
}
}  // namespace

int
main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <databasefilename> <queryfilename>" << endl;
    return 0;
  }
  const string dbx_filename(argv[1]);
  const string seq_filename(argv[2]);
  cout << "Input file is " << dbx_filename << ", and sequences file is " << seq_filename << endl;
  // Note that you will replace the type AvlTree<int> with AvlTree<SequenceMap>
  // AvlTree<int> a_tree;
  AvlTree<SequenceMap> a_tree;
  TestTree(dbx_filename, seq_filename, a_tree);

  return 0;
}
