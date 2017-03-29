#include "graphicexception.h"

GraphicException::GraphicException(const std::string& strWhat) throw():
    _what(strWhat)
{
}
