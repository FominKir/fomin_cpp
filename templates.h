#include <iostream>
#include <array>
#include <string>

template<typename... Args>
size_t X(Args... args) {
    
    const int size = sizeof...(args);
    // int res[size] = {args...};
    
    size_t maxSizeOf = 0;
    // for(int i=0; i < size; i++){
    //     if(maxSizeOf<sizeof(args...[i])){
    //         maxSizeOf = sizeof(args...[i]);
    //     }
    // }

    return size;

    //return max sizeof of params.
    //BOOST_PP
}

