#include "jsondiff.hpp"
#include "colors.hpp"

void JsonDiff::diff_json (json &json1, json &json2)
{
    if (json1.type() != json2.type())
    {
        cout << RED << "Root types differ: "<< CYAN << json1.type_name() << RED << " vs " << BLUE << json2.type_name() << endl;
    }
    else if (json1.is_object())
    {
        diff_object(json1, json2, "", "");
    }
    else if (json1.is_array())
    {
        diff_array(json1, json2, "", "");
    }
    else
    {
        diff_value(json1, json2, "", "");
    }
}

void JsonDiff::diff_object (json &json1, json &json2, string prefix, string name)
{
    for (json::iterator it = json1.begin(); it != json1.end(); ++it)
    {
        string newname = name + "[" + it.key() + "]";
        if (json2.contains(it.key()))
        {
            if (json1[it.key()].type() != json2[it.key()].type())
            {
                cout << prefix << RESET << newname << RED << " types differ: " << CYAN << json1[it.key()].type_name() << RED << " vs " << BLUE << json2[it.key()].type_name() << endl;
                continue;
            }
            if (!bOnlyDifferences)
            {
                cout << prefix << RESET << newname << GREEN << " types are equal: " << CYAN << json1[it.key()].type_name() << endl;
            }
            if (json1[it.key()].is_object())
            {
                diff_object(json1[it.key()], json2[it.key()], prefix + "  ", newname);
            }
            else if (json1[it.key()].is_array())
            {
                diff_array(json1[it.key()], json2[it.key()], prefix + "  ", newname);
            }
            else if (bDiffValue)
            {
                diff_value(json1[it.key()], json2[it.key()], prefix + "  ", newname);
            }
        }
        else
        {
            cout << prefix << RESET << "[" << it.key() << "]" << RED << " key of type " << CYAN << it.value().type_name() << RED << " not found in file 2" << endl;
        }
    }
    for (json::iterator it = json2.begin(); it != json2.end(); ++it)
    {
        string newname = name + "[" + it.key() + "]";
        if (json1.contains(it.key()))
        {

        }
        else
        {
            cout << prefix << RESET << newname << RED << " key of type " << BLUE << it.value().type_name() << RED << " not found in file 1" << endl;
        }
    }
}

void JsonDiff::diff_array (json &json1, json &json2, string prefix, string name)
{
    if (json1.size() != json2.size())
    {
        cout << prefix << RESET << name << RED << " array sizes are different: " << CYAN << json1.size() << RED << " vs " << BLUE << json2.size() << endl;
        return;
    }
    if (!bOnlyDifferences)
    {
        cout << prefix << RESET << name << GREEN << " array sizes are equal: " << CYAN << json1.size() << endl;
    }
    for (uint64_t i=0; i<json1.size(); i++)
    {
        string newname = name + "[" + to_string(i) + "]";
        if (json1[i].type() != json2[i].type())
        {
            cout << prefix << RESET << newname << RED << " types differ: " << CYAN << json1[i].type_name() << RED << " vs " << json2[i].type_name() << endl;
        }
        else if (json1[i].is_object())
        {
            diff_object(json1[i], json2[i], prefix + "  ", newname);
        }
        else if (json1[i].is_array())
        {
            diff_array(json1[i], json2[i], prefix + "  ", newname);
        }
        else if (bDiffValue)
        {
            diff_value(json1[i], json2[i], prefix, newname);
        }
    }
}

void JsonDiff::diff_value (json &json1, json &json2, string prefix, string name)
{
    if (json1.type() != json2.type())
    {
        cout << prefix << RESET << name << RED << " types differ: " << CYAN << json1.type_name() << RED << " vs " << BLUE << json2.type_name() << endl;
    }
    else
    {
        if (json1 != json2)
        {
            cout << prefix << RESET << name << RED << " values of type " << CYAN << json1.type_name() << RED << " differ: " << CYAN << json1 << RED << " vs " << BLUE << json2 << endl;
        }
        else if (!bOnlyDifferences)
        {
            cout << prefix << RESET << name << GREEN << " values of type " << CYAN << json1.type_name() << GREEN << " are equal: " << CYAN << json1 << endl;
        }
    }
}