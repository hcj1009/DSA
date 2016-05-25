#ifndef EMPTY_STACK_H
#define EMPTY_STACK_H

#include <exception>

class empty_stack : std::exception
{
private:
    const char *errmsg;

public:
    empty_stack(const char *msg)
    {
        errmsg = msg;
    }

    virtual const char *what() const throw()
    {
        return errmsg;
    }
};

#endif