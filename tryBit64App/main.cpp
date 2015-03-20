//
//  main.cpp
//  tryBit64App
//
//  Created by liyoudi on 15/3/20.
//  Copyright (c) 2015年 liyoudi. All rights reserved.
//

#include <iostream>

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    printf("sizeof(void *) = %ld\n", sizeof((void *) argv));
    printf("sizeof(long long) = %ld\n", sizeof(long long));
    printf("sizeof(long) = %ld\n", sizeof(long));
    return 0;
}
