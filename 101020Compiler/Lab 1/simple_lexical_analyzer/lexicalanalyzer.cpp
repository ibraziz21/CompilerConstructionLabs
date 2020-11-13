#include <regex>
#include <map>
#include <iterator>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

map<string, string> roles{
    {"[a-z]+", "Identifier"},
    {"[0-9]+", "Number"},
    {"if|else|do|while|switch|case|break|continue|default|for|auto|const|int|float|double|string|void|char|char*|bool|return|cin|cout|endl|main", "Keyword"},
    {"\\+|\\-|\\*|\\/|\\>|\\<|\\=|\\++|\\==|\\--|\\&&|\\!=|\\+=", "Operator"},
    {"\\;|\\(|\\)|\\{|\\}|\\<|\\>|\\[|\\]|\\&|\\:", "Separator"},
};

// storage for reg.expressions and role matches
map<size_t, pair<string, string>> matches;

// mapping tokens and roles
void lex(const string &str)
{

    // for all strings in a line of code, match with the role it qualifies
    for (auto role = roles.begin(); role != roles.end(); ++role)
    {
        regex r(role->first);
        auto words_begin = sregex_iterator(str.begin(), str.end(), r);
        auto words_end = sregex_iterator();

        // populate results storage with the token and its respective role at each position
        for (auto it = words_begin; it != words_end; ++it)
        {
            matches[it->position()] = make_pair(it->str(), role->second);
        }
    }

    //output tokens and roles
    for (auto match = matches.begin(); match != matches.end(); ++match)
    {
        cout << match->second.first << " : " << match->second.second << endl;
    }
}

//fetch code to be analysed from a file
void codeAnalyse(const string &filename)
{
    string line;
    ifstream file(filename);

  
    if (!file.is_open())
    {
        cout << "An error occurred while opening the file" << endl;
        exit(0);
    }

    //fetch each line from specified file and pass to analyser function for mapping
    for (line; getline(file, line);)
    {
        lex(line);
    }
    file.close();
}

int main()
{
    codeAnalyse("phrase.txt");
}