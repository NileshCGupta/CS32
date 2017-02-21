//
//  Multiset.h
//  Project2
//
//  Created by Nilesh Gupta on 7/7/15.
//  Copyright (c) 2015 Nilesh Gupta. All rights reserved.
//

#ifndef __Project2__Multiset__
#define __Project2__Multiset__

#include <string>
typedef std::string ItemType;

class Multiset
{
    public:
        Multiset();
        Multiset(const Multiset& other);
        ~Multiset();
        bool empty() const {return UniqueBigness == 0;}
        int size() const {return Bigness;}
        int uniqueSize() const {return UniqueBigness;}
        bool insert(const ItemType& value);
        int erase(const ItemType& value);
        int eraseAll(const ItemType& value);
        bool contains(const ItemType& value) const;
        int count(const ItemType& value) const;
        int get(int i, ItemType& value) const;
        bool getMostFrequentValue(ItemType& value) const;
        bool getLargestValue(ItemType& value) const;
        bool getSecondLargestValue(ItemType& value) const;
        bool replace(ItemType original, ItemType new_value);
        int countIf(char op, ItemType value) const;
        void swap(Multiset& other);
        void copyIntoOtherMultiset(Multiset& other) const;
        Multiset& operator=(const Multiset& other);

    private:
        struct Node
        {
            ItemType item;
            int count = 0;
            Node *next = nullptr;
            Node *prev = nullptr;
        };
        Node* start;
        int Bigness;
        int UniqueBigness;
};

void combine(const Multiset& ms1, const Multiset& ms2, Multiset& result);
void subtract(const Multiset& ms1, const Multiset& ms2, Multiset& result);

#endif /* defined(__Project2__Multiset__) */
