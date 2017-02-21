//
//  newMultiset.cpp
//  Hw1
//
//  Created by Nilesh Gupta on 6/30/15.
//  Copyright (c) 2015 Nilesh Gupta. All rights reserved.
//

#include "newMultiset.h"

Multiset::Multiset()
{
    Bigness = 0;
    UniqueBigness = 0;
    set = new Thingamajig[DEFAULT_MAX_ITEMS];
}

Multiset::Multiset(int maxSize)
{
    Bigness = 0;
    UniqueBigness = 0;
    max = maxSize;
    set = new Thingamajig[maxSize];
}

Multiset::~Multiset()
{
    delete[] set;
}

Multiset::Multiset(Multiset& other)
{
    Bigness = other.Bigness;
    UniqueBigness = other.UniqueBigness;
    max = other.max;
    set = new Thingamajig[max];
    for(int i = 0; i < max; i ++)
        set[i] = other.set[i];
}

Multiset& Multiset::operator=(const Multiset& other)
{
    if(this != &other)
    {
        delete []set;
        set = 0;
        
        max = other.max;
        Bigness = other.Bigness;
        UniqueBigness = other.UniqueBigness;
        set = new Thingamajig[max];
        for(int i = 0; i < max; i ++)
            set[i] = other.set[i];
    }
    return *this;
}

bool Multiset::insert(const ItemType& value)
{
    for(int i = 0; i < UniqueBigness; i++)
        if(set[i].item == value)
        {
            set[i].count++;
            Bigness++;
            return true;
        }
    
    if(UniqueBigness == max)
        return false;
    
    set[UniqueBigness].item = value;
    set[UniqueBigness].count = 1;
    Bigness++;
    UniqueBigness++;
    return true;
}

int Multiset::erase(const ItemType& value)
// Remove one instance of value from the multiset if present.
// Return the number of instances removed, which will be 1 or 0.
{
    for(int i = 0; i < UniqueBigness; i++)
        if(set[i].item == value)
        {
            set[i].count--;
            Bigness--;
            if(set[i].count == 0) // structure no longer has any items in set
            {
                for(int j = i; j < UniqueBigness-1; j++)
                    set[j] = set[j+1]; // removes whole structure from set
                UniqueBigness--;
            }
            return 1;
        }
    
    return 0;
}

int Multiset::eraseAll(const ItemType& value)
// Remove all instances of value from the multiset if present.
// Return the number of instances removed.
{
    for(int i = 0; i < UniqueBigness; i++)
        if(set[i].item == value)
        {
            int stances = set[i].count;
            for(int j = i; j < UniqueBigness-1; j++)
                set[j] = set[j+1]; // removes structure from set
            Bigness -= stances;
            UniqueBigness--;
            return stances;
        }
    
    return 0;
}

bool Multiset::contains(const ItemType& value) const
// Return true if the value is in the multiset, otherwise false.
{
    for(int i = 0; i < UniqueBigness; i++)
        if(set[i].item == value)
            return true;
    return false;
}

int Multiset::count(const ItemType& value) const
// Return the number of instances of value in the multiset.
// What if count = 0?
{
    for(int i = 0; i < UniqueBigness; i++)
        if(set[i].item == value)
            return set[i].count;
    return 0;
}

int Multiset::get(int i, ItemType& value) const
// If 0 <= i < uniqueSize(), copy into value an item in the
// multiset and return the number of instances of that item in
// the multiset.  Otherwise, leave value unchanged and return 0.
// (See below for details about this function.)
{
    if(i >= 0 && i < UniqueBigness)
    {
        value = set[i].item;
        return set[i].count;
    }
    
    return 0;
}

bool Multiset::getMostFrequentValue(ItemType &value) const
// If there exists a single item that has the largest number of instances in the multiset,
// then copy into value that item in the multiset and return true.
// However, if there exist more than 1 item that have the largest number of instances in the multiset,
// then do not copy into value any item in the multiset and return false. In other words, value should remain unchanged.
// If there's no item in the multiset, return false.
{
    if(UniqueBigness == 0)
        return false;
    
    int ModeCount = set[0].count, NumOfModes;
    ItemType mode = 0;
    
    for(int i = 1; i < UniqueBigness; i++) // find highest instances of a value
        if(set[i].count > ModeCount)
            ModeCount = set[i].count;
    
    for(int i = 0; i < UniqueBigness; i++) // check if more than one value have highest instances
        if(set[i].count == ModeCount)
        {
            mode = set[i].item;
            NumOfModes++;
        }
    
    if(NumOfModes > 1)
        return false;
    
    value = mode;
    return true;
}

bool Multiset::getLargestValue(ItemType &value) const
// If there exists a value that is the largest value among all the values in the multiset,
// then copy into value that item in the multiset and return true
// Otherwise, return false.
// For both unsigned long and string data type, the higher value can be found by using greater than operator (>).
// For example, 100 is greater than 20, so 100 > 20 is true.
// "ZOO" is greater than "ABC", so "ZOO" > "ABC" is true.
{
    int ties = 0;
    ItemType largest = set[0].item;
    
    for(int i = 1; i < UniqueBigness; i++) // find largest value
        if(set[i].item > largest)
            largest = set[i].item;
    
    for(int i = 0; i < UniqueBigness; i++) // check if any values tie for first
        if(set[i].item == largest)
            ties++;
    
    if(ties == 1)
    {
        value = largest;
        return true;
    }
    
    return false;
}

bool Multiset::getSecondLargestValue(ItemType &value) const
// Similar to getLargestValue(), but this time you need to find the second largest value.
// If there exists a value that is the 2nd largest value among all the values in the multiset,
// then copy into value that item in the multiset and return true.
// Otherwise, return false.
// Please note that you cannot use any sorting algorithm to sort the multiset.
{
    int ties = 0;
    ItemType largest = set[0].item, secondlargest = 0;
    
    for(int i = 1; i < UniqueBigness; i++) // find largest value
        if(set[i].item > largest)
            largest = set[i].item;
    
    for(int i = 0; i < UniqueBigness; i++) // find second largest value
        if(set[i].item < largest && set[i].item > secondlargest)
            secondlargest = set[i].item;
    
    for(int i = 0; i < UniqueBigness; i++) // check if any values tie for second
        if(set[i].item == secondlargest)
            ties++;
    
    if(ties == 1)
    {
        value = secondlargest;
        return true;
    }
    
    return false;
}

bool Multiset::replace(ItemType original, ItemType new_value)
// Replace the item that has the value equal to original by the new value new_value.
// For example, replace("ABC","XYZ") will search the multiset for the item "ABC" and replace all occurrences of "ABC" as "XYZ".
// If the replacement is successful, then return true.
// If there is no item to be replaced, then return false.
{
    for(int i = 0; i < UniqueBigness; i++)
        if(set[i].item == original)
        {
            for(int j = 0; j < UniqueBigness; i++) // checks if new value is already in set
                if(set[j].item == new_value)
                {
                    set[j].count += set[i].count;
                    for(int k = i; k < UniqueBigness-1; k++) // removes original structure element
                        set[k] = set[k+1];
                    UniqueBigness--;
                    return true;
                }
            set[i].item = new_value;
            return true;
        }
    
    return false;
}

int Multiset::countIf(char op, ItemType value) const
// Count the number of items that the item is greater than, less than, or equal to value.
// For example:
// countIf('>',100) returns the number of items in multiset in which the item is greater than 100.
// countIf('=',"ABC") returns the number of items in multiset in which the item is equal to "ABC".
// countIf('<',50) returns the number of items in multiset in which the item is less than 50.
// If op is a character other than '>','=', and '<', then return -1.
{
    if(op != '>' && op != '=' && op != '<')
        return -1;
    
    int ItemCount = 0;
    
    if(op == '=')
    {
        ItemCount = count(value);
    }
    
    if(op == '<')
    {
        for(int i = 0; i < UniqueBigness; i++)
            if(set[i].item < value)
                ItemCount += set[i].count;
    }
    
    if(op == '>')
    {
        for(int i = 0; i < UniqueBigness; i++)
            if(set[i].item > value)
                ItemCount += set[i].count;
    }
    return ItemCount;
}

void Multiset::swap(Multiset& other)
// Exchange the contents of this multiset with the other one.
{
    Multiset copy;
    copy = other;
    
    other.Bigness = this->Bigness;
    other.UniqueBigness = this->UniqueBigness;
    other.max = this->max;
    delete[] other.set;
    other.set = new Thingamajig[other.max];
    for(int i = 0; i < UniqueBigness; i++)
        other.set[i] = set[i];
    
    Bigness = copy.Bigness;
    UniqueBigness = copy.UniqueBigness;
    max = copy.max;
    delete[] set;
    set = new Thingamajig[max];
    for(int i = 0; i < copy.UniqueBigness; i++)
        set[i] = copy.set[i];
}

void Multiset::copyIntoOtherMultiset(Multiset &other) const
// Insert all the items into the multiset in other.
{
    for(int i = 0; i < UniqueBigness; i++)
        for(int j = 0; j < set[i].count; j++)
            other.insert(set[i].item);
}