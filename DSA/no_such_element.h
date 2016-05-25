#ifndef NO_SUCH_ELEMENT_H
#define NO_SUCH_ELEMENT_H

#include <exception>

class no_such_element : std::exception
{
private:
    const char *errmsg;

public:
    no_such_element(const char *what_arg)
    {
        errmsg = what_arg;
    }

    const char *what() const throw()
    {
        return errmsg;
    }
};

#endif