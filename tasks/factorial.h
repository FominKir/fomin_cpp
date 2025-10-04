#include <iostream>

template<int N>
struct factorial{
    static const int value = factorialCount<N, (N>0)>::value;
};

template<int N, bool is_positive>
struct factorialCount{
    static const int value = N * factorialCount<N-1, (N-1>0)>::value;
};

template<int N>
struct factorialCount<N, false>{
    static const int value = 1;
};