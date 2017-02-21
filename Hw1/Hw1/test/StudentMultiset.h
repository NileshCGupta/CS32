//
//  StudentMultiset.h
//  Hw1
//
//  Created by Nilesh Gupta on 6/30/15.
//  Copyright (c) 2015 Nilesh Gupta. All rights reserved.
//

#ifndef __Hw1__StudentMultiset__
#define __Hw1__StudentMultiset__

#include <stdio.h>
#include "Multiset.h"

class StudentMultiset
{
    public:
        StudentMultiset(): set() {}       // Create an empty student multiset.
        
        bool add(unsigned long id);
        // Add a student id to the StudentMultiset.  Return true if and only
        // if the id was actually added.
        
        int size() const;
        // Return the number of items in the StudentMultiset.  If an id was
        // added n times, it contributes n to the size.
        
        void print() const;
        // Print to cout every student id in the StudentMultiset one per line;
        // print as many lines for each id as it occurs in the StudentMultiset.
        
    private:
        Multiset set;
        // Some of your code goes here.
    
};

#endif /* defined(__Hw1__StudentMultiset__) */
