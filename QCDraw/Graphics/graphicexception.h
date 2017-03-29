#ifndef GRAPHICEXCEPTION_H
#define GRAPHICEXCEPTION_H
#include <exception>
#include <string>
using namespace std;
class GraphicException
{
public:
public:
    GraphicException(const std::string& strWhat ) throw();
    virtual ~GraphicException() throw()
    {
    }

    const char* what() const throw()
    {
        return _what.c_str();
    }
private:
    std::string  _what;
};

#endif // GRAPHICEXCEPTION_H
