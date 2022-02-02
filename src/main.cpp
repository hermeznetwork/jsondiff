#include <iostream>
#include <vector>
#include <string>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iomanip>
#include <sys/time.h>
#include "jsondiff.hpp"
#include "colors.hpp"

using namespace std;
using json = nlohmann::json;

int main(int argc, char **argv)
{
    string file1, file2;
    bool bDiffValue = false;
    bool bOnlyDifferences = false;

    // Parse arguments
    string usage = "Usage: jsondiff <file1> <file2> -v (diff values) -d (report only differences)";
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-v") == 0)
        {
            bDiffValue = true;
        }
        else if (strcmp(argv[i], "-d") == 0)
        {
            bOnlyDifferences = true;
        }
        else if (file1 == "")
        {
            file1 = argv[i];
        }
        else if (file2 == "")
        {
            file2 = argv[i];
        }
        else
        {
            cerr << "Error: Unrecognized argument: " << argv[i] << endl;
            cout << usage << endl;
            exit(-1);
        }
    }
    if (file1=="" || file2=="")
    {
        cerr << "Error: Missing arguments" << endl;
        cout << usage << endl;
        exit(-1); 
    }
    cout << "jsondiff of file1: " << CYAN << file1 << RESET << " and file2: " << BLUE << file2 << endl;

    // Load and parse JSON files
    json json1, json2;

    std::ifstream inputStream1(file1);
    if (!inputStream1.good())
    {
        cerr << "Error: failed loading JSON file " << file1 << endl;
        exit(-1);
    }
    inputStream1 >> json1;
    inputStream1.close();

    std::ifstream inputStream2(file2);
    if (!inputStream2.good())
    {
        cerr << "Error: failed loading JSON file " << file2 << endl;
        exit(-1);
    }
    inputStream2 >> json2;
    inputStream2.close();

    JsonDiff jsonDiff;
    jsonDiff.bDiffValue = bDiffValue;
    jsonDiff.bOnlyDifferences = bOnlyDifferences;

    jsonDiff.diff_json(json1, json2);

    cout << RESET << "Done" << endl;
}