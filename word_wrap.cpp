#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void WordWrap(const string& inputString, vector<string>& outputString, unsigned int lineLength)
{
   istringstream iss(inputString);

   string line;

   do
   {
      string word;
      iss >> word;

      if (line.length() + word.length() > lineLength)
      {
         outputString.push_back(line);
         line.clear();
      }
      line += word + " ";

   }while (iss);

   if (!line.empty())
   {
      outputString.push_back(line);
   }
}

/*
A simple test:

Input string: "aaa bbb ccccccc dddd d111111111111111 33333 4444444444 222222222  ajdkjklad 341343"

Length per line: 20

Output lines of strings:

Line 1: aaa bbb ccccccc dddd
Line 2: d111111111111111
Line 3: 33333 4444444444
Line 4: 222222222  ajdkjklad
*/
