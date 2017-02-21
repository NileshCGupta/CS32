//
//  testStudentMultiset.cpp
//  Hw1
//
//  Created by Nilesh Gupta on 6/30/15.
//  Copyright (c) 2015 Nilesh Gupta. All rights reserved.
//

#include <stdio.h>
#include <cassert>
#include "StudentMultiset.h"

int main()
{
    StudentMultiset ms;
    
    assert(ms.add(11));
    assert(ms.add(11));
    assert(ms.add(22));
    assert(ms.add(22));
    
    assert(ms.size() == 4);
    
    ms.print();
}