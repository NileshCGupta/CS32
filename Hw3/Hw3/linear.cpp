//
//  linear.cpp
//  Hw3
//
//  Created by Nilesh Gupta on 7/25/15.
//  Copyright (c) 2015 Nilesh Gupta. All rights reserved.
//

#include <cctype>
#include <assert.h>
#include <iostream>

// Return true if any of the chars in the array is lowercase, false
// otherwise.
bool anyLowercase(const char a[], int n)
{
	if(n <= 0)
		return false;
	
	if(islower(a[0]))
		return true;
	
	if(anyLowercase((a + 1), n-1))
		return true;
	
	return false;  // This is not always correct.
}

// Return the number of lowercase chars in the array.
int countLowercase(const char a[], int n)
{
	if(n <= 0)
		return 0;
	
	if(islower(a[0]))
		return 1 + countLowercase(a + 1, n-1);
	
	else
		return countLowercase(a + 1, n-1);
}

// Return the subscript of the first lowercase char in the array.
// If no element is lowercase, return -1.
int firstLowercase(const char a[], int n)
{
	if(n <= 0)
		return -1;
	
	if(islower(a[0]))
		return 0;
	
	else
		return 1 + firstLowercase((a + 1), n-1);
	
	return -1;  // This is not always correct.
}

// Return the subscript of the least char in the array (i.e.,
// the smallest subscript m such that there is no k for which
// a[k] < a[m].)  If the array has no elements to examine, return -1.
int indexOfLeast(const char a[], int n)
{
	if(n <= 0)
		return -1;
	
	if(n == 2)
	{
		if(a[0] <= a[1])
			return 0;
		else
			return 1;
	}
	
	if(a[0] <= a[indexOfLeast(a + 1, n-1) + 1])
		return 0;
	else
		return indexOfLeast(a + 1, n-1) + 1;
}

//int main()
//{
//	char a[] = "bcadbiuwaef";
//	assert(anyLowercase(a, 15));
//	int b = indexOfLeast(a, 10);
//	std::cout << b;
//}