#ifndef DSAEXCEPT_H
#define DSAEXCEPT_H

#include <stdexcept>

using std::runtime_error;
using std::string;

class illegal_argument : public runtime_error
{
public:
    illegal_argument(const string &what_arg)
        : runtime_error(what_arg) {}
};

class index_error : public runtime_error
{
public:
    index_error(const string &what_arg) 
        : runtime_error(what_arg) {}
};

class no_such_element : public runtime_error
{
public:
    no_such_element(const string &what_arg) 
        : runtime_error(what_arg) {}
};

class duplicate_element : public runtime_error
{
public:
    duplicate_element(const string &what_arg) 
        : runtime_error(what_arg) {}
};

class empty_container : public runtime_error
{
public:
    empty_container(const string &what_arg) 
        : runtime_error(what_arg) {}
};

class full_container : public runtime_error
{
public:
    full_container(const string &what_arg)
        : runtime_error(what_arg) {}
};

#endif