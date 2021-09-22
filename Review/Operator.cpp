#include "Operator.h"
bool MyClass::operator<(MyClass const& m) const
{
    return number < m.number;
}

bool MyClass::operator<(int i)const{
    return number < i;
}

bool operator<(int i, MyClass const& m){
    return i < m.number;
}