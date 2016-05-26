#ifndef DSAEXCEPT_H
#define DSAEXCEPT_H

#include <stdexcept>

using std::runtime_error;
using std::string;

class index_error : runtime_error
{
public:
    index_error(const string &what_arg) : runtime_error(what_arg) {}
};

class no_such_element : runtime_error
{
public:
    no_such_element(const string &what_arg) : runtime_error(what_arg) {}
};

class empty_container : runtime_error
{
public:
    empty_container(const string &what_arg) : runtime_error(what_arg) {}
};

#endif