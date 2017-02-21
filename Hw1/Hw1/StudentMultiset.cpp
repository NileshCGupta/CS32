//
//  StudentMultiset.cpp
//  Hw1
//
//  Created by Nilesh Gupta on 6/30/15.
//  Copyright (c) 2015 Nilesh Gupta. All rights reserved.
//

#include "StudentMultiset.h"
#include <iostream>
using namespace std;

bool StudentMultiset::add(unsigned long id)
// Add a student id to the StudentMultiset.  Return true if and only
// if the id was actually added.
{
    return set.insert(id);
}

int StudentMultiset::size() const
// Return the number of items in the StudentMultiset.  If an id was
// added n times, it contributes n to the size.
{
    return set.size();
}

void StudentMultiset::print() const
// Print to cout every student id in the StudentMultiset one per line;
// print as many lines for each id as it occurs in the StudentMultiset.
{
    ItemType x = 0;
    for(int i = 0; i < set.uniqueSize(); i++)
    {
        int repeat = set.get(i,x);
        for(int j = 0; j < repeat; j++)
            cout << x << endl;
    }
}