#include <iostream>
#include <httpxx/Url.hpp>

// use example:
// parser-url "/index.html?a=1&b=2"
// parser-url "http://www.google.com:80/index.html?a=1&b=2"
int main(int argc, char **argv)
{
    if(argc != 2) {
        std::cout << "usage: parser-url url" << std::endl;
        return 0;
    }
    std::string u = argv[1];
    http::Url url(u);
    if(!url.valid()) {
        std::cout << "parse url fail" << std::endl;
        return 0;
    }
    std::cout << "host info: " << url.schema() << " " << url.host() << " " << url.port() << std::endl;
    std::cout << "pash info: " << url.path() << " " << url.query() << std::endl;
    std::map<std::string, std::string> value = url.query_values();
    std::cout << "values: ";
    for(std::map<std::string, std::string>::iterator it = value.begin(); it != value.end(); it++) {
        std::cout << it->first << "=" << it->second << " ";
    }
    std::cout << std::endl;
    return 0;
}