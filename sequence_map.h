#pragma once
#include <vector>
#include <iostream>
#include <cstddef>
#include <string>
#include <sstream>
class SequenceMap
{
    public:
    /*
        Parameterized Constructor
    */
    SequenceMap(const std::string &a_rec_seq, const std::string &an_enz_acro)
    {
        // sets recognition_sequence_ equal the the paramter a_rec_seq
        recognition_sequence_ = a_rec_seq;
        // inserts an_enz_acro into enzyme_acronyms_
        enzyme_acronyms_.push_back(an_enz_acro);
    }

    /* 
        returns: that reco_seq of caller is smaller than reco_seq of calle
    */
    bool operator<(const SequenceMap &rhs) const
    {
        // returns this->recognition sequence is smaller then rhs.recognition sequence
        return recognition_sequence_ < rhs.recognition_sequence_;
    }

    /*
        Print out the enzyme_acronyms vector, for a given recognition sequence.
    */
    friend std::ostream &operator<<(std::ostream &out, const SequenceMap &some_SequenceMap)
    {
        // If sequence is empty 
        if (some_SequenceMap.recognition_sequence_ == "")
        {
            // print nothing
            out << "";
            // returns out
            return out;
        }
        else
        {
            // variable that stores the size of the enzyme acronyms
            int size = some_SequenceMap.enzyme_acronyms_.size();
            // loops through vector
            for (int i = 0; i < size; i++)
            {
                // prints out enzyme acronyms
                out << some_SequenceMap.enzyme_acronyms_.at(i);
            }
            // prints out new line
            out << std::endl;
            // returns out
            return out;
        }
    }

    /*
        Merges when there is a case of duplicates
    */
    void Merge(const SequenceMap &other_sequence)
    {
        // Stores size of enz_acro vector
        int size = enzyme_acronyms_.size();
        // loops through vector
        for (int i = 0; i < size; i++)
        {
            //Merges the acronym when there is duplicates
            enzyme_acronyms_[i] += " " + other_sequence.enzyme_acronyms_[i];
        }
    }

    /*
        Gets recognition sequence
    */
    const std::string getRecognitionSequence() const
    {
        // returns recognition sequence
        return recognition_sequence_; 
    }

    private:
    // Private string for handling recognition sequence
    std::string recognition_sequence_;
    // Private vector of vector strings that handles enzyme acroynms
    std::vector<std::string> enzyme_acronyms_;
};