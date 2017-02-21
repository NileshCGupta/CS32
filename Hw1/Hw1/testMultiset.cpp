
//  testMultiset.cpp
//  Hw1
//
//  Created by Nilesh Gupta on 6/30/15.
//  Copyright (c) 2015 Nilesh Gupta. All rights reserved.


#include "Multiset.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Multiset ms;
    assert(ms.empty());
    unsigned long x = 999;
    assert(ms.get(0, x) == 0  &&  x == 999);
    assert( ! ms.contains(42));
    
    ms.insert(42);
    ms.insert(42);
    
    assert( ! ms.getSecondLargestValue(x)  &&  x == 999 );
    assert(ms.size() == 2  &&  ms.uniqueSize() == 1);
    assert(ms.get(1, x) == 0  &&  x == 999);
    assert(ms.get(0, x) == 2  &&  x == 42);
    
    ms.~Multiset();
    
    assert(ms.getLargestValue(x) && x == 42 );
    assert(ms.countIf('=',42) == 2);
    assert(ms.countIf('>',42) == 0);
    assert(ms.countIf('<',42) == 0);
    
    cout << "Passed all tests" << endl;
    
}