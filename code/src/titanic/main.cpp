////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief      Main module for Problem 1: Titanic.
/// \author     Georgii Zhulikov
/// \author     Sergey Shershakov
/// \version    0.1.1
/// \date       03.02.2022
///             This code is for educational purposes of the course "Introduction
///             to programming" provided by the Faculty of Computer Science
///             at the Higher School of Economics.
///
/// EXAMPLE
/// 1) Define an alias VecStrings for the std::vector<std::string> datatype
/// using the typedef keyword.
/// 1.1) Define the same alias with the keyword "using"
///
/// EXAMPLE
/// 2) Create a function called getSurvivorSurnames that obtains an input stream
/// object (given by reference) istream& (input.csv), reads the whole file
/// line by line and saves surnames ("Braund; Mr. Owen Harris" will be just
/// "Braund") of survived people from input.csv (Survived column).
/// The function returns data of type VecStrings -- vector of surnames of survivors.
///
/// Use intermediate functions in exercise 2 to do the following:
/// 2.1) Extract data (surname and whether the person survived or not) from one line of input.
/// 2.2) (optional) Extract surname from a string containing full name.
/// 
///
/// PRACTICE
/// 3) Create a function printVec.
/// The function prints the content of the given vector of strings out to the standard output.
/// It should takes a vector as argument by reference and print the value of the 
/// elements as well as their enumeration.
///     Example output:
///     1) Name_1
///     2) Name_2
///     ...
///     N) Name_n
/// 
/// 3.1) (Optional homework) Try adding templates to the function, so it can print a vector
/// of any printable type, not just a vector of strings.
///
/// PRACTICE
/// 4) Create a function called getFareForClass that takes an input stream object
/// istream& and an integer number representing class (PClass, 1 to 3), reads the stream 
/// until the end and returns the mean fare value of people of the given class.
/// The function returns a single value of type double -- the mean fair value.
/// Use at least two intermediate functions in problem 4.
/// Proposed intermediate functions:
/// 4.1) Extract needed data from a single line (PClass and Fare)
/// 4.2) Compute the mean (average) value of a given vector
///
///
/// EXAMPLE
/// 5) Reverse the vector containing names of surviving passengers using std::reverse.
/// Sort this vector using std::sort
/// Include library <algorithm> to access these functions.
/// Use iterators.
///
/// EXAMPLE
/// 6) Implement a function printVecIter that takes two vector iterators as arguments
/// and prints the elements of the underlying vector. The iterators should represent
/// the start and the end of the vector.
/// 
/// PRACTICE
/// 7) Change (or implement, if you haven't) the function from task 4.2 to follow the
/// same logic as the function printVecIter from task 6. Use iterators to compute the
/// mean value of a vector.
///
/// PRACTICE
/// 8) Use a regular iterator and a reverse iterator (.rbegin(), .rend()) to print the vector 
/// containing survivor names in a straightforward order and in a reverse order
/// with the function printVecIter.
/// 
/// EXAMPLE
/// 9) Using the sorted list of surnames find the person with surname "Mellors". Use the
/// function "std::find". The function will return an iterator.
/// Print the value of this iterator and the next two values.
/// 
/// PRACTICE
/// 10) Find the person with surname "Young" following the example from task 9.
/// Create a new vector and use functions std::find and std::copy to copy all surnames between
/// "Mellors" and "Young" into it.
///
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <random>
#include <algorithm>

typedef std::vector<std::string> VecString;

using VecString = std::vector<std::string>;

VecString getSurvivorSurnames(std::istream& in);

std::istream& calcSumFromStream(std::istream& in, double& sum)
{
// floating point numbers from it
// until the end of line
    double number;
    std::string buffer;
    std::getline(in, buffer);
    
    sum = 0;
    std::stringstream sstr(buffer);
    while (sstr >> number)
    {
        sum += number;
    }
    return in;
}



// void print(const std::vector<std::string>& v)
// {
//     for (int i = 0; i < n; ++i)
//     {

//     }

//     for (const std::string& name: v)
//     {
        
//     }
// }


// double computeMeanIter(const std::vector<double>& fares, int pClass)
// {
//     // ....
//     // computes average of fares
// }


void printVec(const VecString& collection)
{
    for (int i = 0; i < collection.size(); ++i)
    {
        std::cout << i+1 << ") " << collection[i] << std::endl;
    }

    // int count = 1;
    // for (const std::string& item: collection)
    // {
    //     std::cout << count << ") " << item << std::endl;
    //     ++count;
    // }
}


void printVecIter(const VecString::iterator& beginIter, const VecString::iterator& endIter)
{
    int count = 1;
    for (VecString::iterator it = beginIter; it != endIter; ++it)
    {
        std::cout << count << ") " << *it << std::endl;
        ++count;
    }
}



std::istream& readInputLine(std::istream& in, std::string& lastName, bool& survived)
{
    std::string buffer;
    std::getline(in, buffer);

    if (!in)
    {
        return in;
    }
    
    std::stringstream sstr(buffer);

    // PassengerID
    std::getline(sstr, buffer, ',');

    // Survived
    std::getline(sstr, buffer, ',');
    survived = bool(std::stoi(buffer));

    // Pclass
    std::getline(sstr, buffer, ',');

    // Name
    std::getline(sstr, buffer, ',');

    // "Braund; Mr. Owen Harris" - > Braund
    int semicolonIndex = buffer.find(";");
    lastName = buffer.substr(0, semicolonIndex);
    // lastName = extractLastName(buffer);

    // Sex
    // Age
    // SibSp
    return in;
}



VecString getSurvivorSurnames(std::istream& in)
{
    std::string buffer;

    std::getline(in, buffer);
    bool survived;
    std::string lastName;
    VecString survivorNames;

    std::vector<double> fares;

    while (readInputLine(in, lastName, survived))
    {
        if (survived)
        {
            survivorNames.push_back(lastName);
        }
    }

    // double mean = getAverageValueOfVector(fares.begin(), fares.end());

    return survivorNames;
}



int main()
{
    const std::string INP_FILE_NAME = "../data/titanic/titanic.csv";
    std::ifstream inputFile;
    inputFile.open(INP_FILE_NAME);
    VecString surnames = getSurvivorSurnames(inputFile);
    inputFile.close();


    std::reverse(surnames.begin(), surnames.end());
    // python_list.reverse()


    printVecIter(surnames.begin(), surnames.end());

    std::sort(surnames.begin(), surnames.end());
    // std::reverse(surnames.begin(), surnames.end());

    printVec(surnames);


/// 9) Using the sorted list of surnames find the person with surname "Mellors". Use the
/// function "std::find". The function will return an iterator.
/// Print the value of this iterator and the next two values.
    // Mellors
    VecString::iterator it = std::find(surnames.begin(), surnames.end(), "Mellors");

    std::cout << *it << std::endl;
    ++it;
    std::cout << *it << std::endl;
    ++it;
    std::cout << *it << std::endl;

    //         from        to     write result here
    // std::copy(itMellors, itYoung, newVector.begin());

/// PRACTICE
/// 10) Find the person with surname "Young" following the example from task 9.
/// Create a new vector and use functions std::find and std::copy to copy all surnames between
/// "Mellors" and "Young" into it.






    // other functions here
}
