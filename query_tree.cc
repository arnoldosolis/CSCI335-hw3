// Arnoldo Solis
// Main file for Part 2.1 of Homework 3.

#include "avl_tree.h"
// You will have to add #include "sequence_map.h"
#include "sequence_map.h"
#include <iostream>
#include <string>
// Needed for reading in file
#include <fstream>
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

namespace {
// @dbx_filename: an input filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void QueryTree(const string &dbx_filename, TreeType &a_tree) 
{
  // Code for running Part 2.1
  // You can use public functions of TreeType. For example:
  // Initializes an ifstream object named rebase210
  std::ifstream rebase210;
  // Uses object to open file
  rebase210.open(dbx_filename);
  // Checks if file is able to open or if it
  if (rebase210.fail())
  {
    // Prints error message
    std::cout << "Unable to open file or file does not exist!" << std::endl;
    // Exits
    exit(1);
  }

  // takes in rebase
  std::string db_line;
  // Skips the header of the Database
  skipHeader(rebase210, db_line);

  // Read the file line by line
  while (getline(rebase210, db_line))
  {
    // takes in enzyme acronym
    std::string an_enz_acro;
    // converter
    std::stringstream ss_dbline(db_line);
    // Gets all the enzyme acroynms
    if (!db_line.empty())
    {
      // Takes all the acronyms in
      getline(ss_dbline, an_enz_acro, '/');
    }
    
    // stores recognition sequences
    std::string a_reco_seq;
    // Reads all the recognition sequences
    while (getline(ss_dbline, a_reco_seq, '/') && !a_reco_seq.empty())
    {
      // Makes a new_sequence_map that will be inserted into tree
      SequenceMap new_sequence_map(a_reco_seq, an_enz_acro);
      // Inserts new_seqeunce_map into tree
      a_tree.insert(new_sequence_map);
    }
  }
  // Closes the file
  rebase210.close();

  // String that stores user input
  std::string u_input;
  // Prompts user input
  std::cout << "Enter recognition sequences: " << std::endl;
  // While reading user input
  while (std::cin >> u_input)
  {
    // Creates a new sequence map object
    SequenceMap map{u_input, ""};
    // if the tree contains the user inputed value
    if (a_tree.contains(map))
    {
      // prints the value
      a_tree.printValue(map);
    }
    else
    {
      // prints that item was not found
      std::cout << "Not Found" << std::endl;
    }
  }
}
}  // namespace

int main(int argc, char **argv) 
{
  if (argc != 2) 
  {
    cout << "Usage: " << argv[0] << " <databasefilename>" << endl;
    return 0;
  }
  const string dbx_filename(argv[1]);
  cout << "Input filename is " << dbx_filename << endl;
  // Note that you will replace the type AvlTree<int> with AvlTree<SequenceMap>
  // AvlTree<int> a_tree;
  AvlTree<SequenceMap> a_tree;
  QueryTree(dbx_filename, a_tree);
  return 0;
}
