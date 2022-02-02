#ifndef JSONDIFF_HPP
#define JSONDIFF_HPP

#include <iostream>
#include <vector>
#include <string>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iomanip>
#include <sys/time.h>
#include "colors.hpp"

using namespace std;
using json = nlohmann::json;

class JsonDiff
{
public:
    bool bDiffValue;
    bool bOnlyDifferences;
    JsonDiff() : bDiffValue(false), bOnlyDifferences(false) {};

    void diff_json   (json &json1, json &json2);
    void diff_object (json &json1, json &json2, string prefix, string name);
    void diff_array  (json &json1, json &json2, string prefix, string name);
    void diff_value  (json &json1, json &json2, string prefix, string name);
};

#endif