/*
{
  "array": [
    1,
    2,
    3
  ],
  "boolean": true,
  "null": null,
  "number": 123,
  "object": {
    "a": "b",
    "c": "d",
    "e": "f"
  },
  "string": "Hello World"
}
*/

#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <string>
using namespace std;
using namespace boost::property_tree;

int main(int argc, const char * argv[]) {

    std::string str_json = "{\"array\":[1,2,3],\"boolean\":true,\"null\":null,\"number\":123,\"object\":{\"a\":\"b\",\"c\":\"d\",\"e\":\"f\"},\"string\":\"Hello World\"}";

    ptree pt;                       //define property_tree object
    std::stringstream ss(str_json);
    try {
        read_json(ss, pt);          //parse json
    } catch (ptree_error & e) {
        return 1;
    }

    ptree arraypt = pt.get_child("array");
    for (boost::property_tree::ptree::iterator it = arraypt.begin(); it != arraypt.end(); ++it) {
        cout << it->second.data() << " ";
    }
    cout << endl;

    std::cout << pt.get<bool>("boolean") << std::endl;
    std::cout << pt.get<std::string>("null") << std::endl;
    std::cout << pt.get<int>("number") << std::endl;
    std::cout << pt.get<std::string>("string") << std::endl;
    ptree opt = pt.get_child("object");

    BOOST_FOREACH(ptree::value_type &v, opt){
        cout << v.first << " : ";
        cout << v.second.data() << endl;
    }

    return 0;
}
