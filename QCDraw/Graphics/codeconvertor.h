#ifndef CODECONVERTOR_H
#define CODECONVERTOR_H
#include <QString>
class CodeConvertor
{
public:
    CodeConvertor();
    static QString fromLocal(const char* str);
private:
    static bool _bFirst;
};

#endif // CODECONVERTOR_H
