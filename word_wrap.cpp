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


// 2nd example
#include <iostream>
#include <string>
#include <cctype>

std::string word_wrap(std::string text, unsigned per_line)
{
    unsigned line_begin = 0;

    while (line_begin < text.size())
    {
        const unsigned ideal_end = line_begin + per_line ;
        unsigned line_end = ideal_end <= text.size() ? ideal_end : text.size()-1;

        if (line_end == text.size() - 1)
            ++line_end;
        else if (std::isspace(text[line_end]))
        {
            text[line_end] = '\n';
            ++line_end;
        }
        else    // backtrack
        {
            unsigned end = line_end;
            while ( end > line_begin && !std::isspace(text[end]))
                --end;

            if (end != line_begin)                  
            {                                       
                line_end = end;                     
                text[line_end++] = '\n';            
            }                                       
            else                                    
                text.insert(line_end++, 1, '\n');
        }

        line_begin = line_end;
    }

    return text;
}

int main()
{
    std::string player_name = "Eric";
    std::string age = "152";
    std::string gender = "transgender";

    enum body_type { fit, unfit };
    body_type body = fit;

    std::string working_text = "Your name is " + player_name + " and you're " + age + " years old. You're a " + gender + " and your body type is ";

    std::cout << word_wrap(working_text, 10) << "\n\n" ;
    std::cout << word_wrap(working_text + (body == fit ? "burly and strong." : "fat and blubbery."), 10) << '\n';
}
