/*
{
  "ret": "101",
  "error": [
    {
      "errortype": "A0001",
      "errorstroke": {
        "0": "0.2",
        "1": "0.3"
      }
    },
    {
      "errortype": "A0021",
      "errorstroke": {
        "0": "0.2",
        "1": "0.3"
      }
    }
  ]
*/
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <string>

using namespace boost::property_tree;

int main(int argc, const char * argv[]) {

    std::string str_json = "{\"ret\":\"101\",\"error\":[{\"errortype\":\"A0001\",\"errorstroke\":{\"0\":\"0.2\",\"1\":\"0.3\"}},{\"errortype\":\"A0021\",\"errorstroke\":{\"0\":\"0.2\",\"1\":\"0.3\"}}]}";

    ptree pt;                       //define property_tree object
    std::stringstream ss(str_json);
    try {
        read_json(ss, pt);          //parse json
    } catch (ptree_error & e) {
        return 1;
    }

    std::cout << pt.get<std::string>("ret") << std::endl;
    ptree errortype = pt.get_child("error");            // get_child to get errors

    // first way
    for (boost::property_tree::ptree::iterator it = errortype.begin(); it != errortype.end(); ++it) {
        std::cout << it->first;
        std::cout << it->second.get<std::string>("errortype") << std::endl;
        ptree errorstroke = it->second.get_child("errorstroke");
        for (ptree::iterator iter = errorstroke.begin(); iter != errorstroke.end(); ++iter) {
            std::string key = iter->first;
            std::cout << iter->first << std::endl;
            std::cout << iter->second.data() << std::endl;
        }
    }
/*
     101
     A0001
     0
     0.2
     1
     0.3
     A0021
     0
     0.2
     1
     0.3
*/
    return 0;
}
