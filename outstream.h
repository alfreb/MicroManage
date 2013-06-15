#ifndef OUTSTREAM_H
#define OUTSTREAM_H

#include<iostream>

template<class outFunctor>
class outStream
{
public:

    template<class T>
    outStream& operator<<(T msg){
        outFunctor o;
        o(msg);
        return *this;
    };
};

#endif // OUTSTREAM_H
