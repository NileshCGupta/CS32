//
//  Multiset.cpp
//  Project2
//
//  Created by Nilesh Gupta on 7/7/15.
//  Copyright (c) 2015 Nilesh Gupta. All rights reserved.
//

#include "Multiset.h"

Multiset::Multiset()
{
    start = nullptr;
    Bigness = 0;
    UniqueBigness = 0;
}

bool Multiset::insert(const ItemType& value)
{
    Node* q = start;

    if(q == nullptr)
    {
        q = new Node;
        q->item = value;
        q->count = 1;
        q->next = nullptr;
        q->prev = nullptr;
        start = q;
        Bigness++;
        UniqueBigness++;
        return true;
    }

    for(int i = 0; i < UniqueBigness; i++)
    {
        if(q->item == value)
        {
            q->count++;
            Bigness++;
            return true;
        }
            
        if(q->next != nullptr)
            q = q->next;
    }
    
    Node* nextNode = new Node;
    nextNode->item = value;
    nextNode->count = 1;
    nextNode->next = nullptr;
    nextNode->prev = q;
    
    q->next = nextNode;
    Bigness++;
    UniqueBigness++;
    
    return true;
}

int Multiset::erase(const ItemType& value)
{
    Node* q = start;
    
    for(int i = 0; i < UniqueBigness; i++)
    {
        if(q->item == value)
        {
            q->count--;
            Bigness--;
            if(q->count == 0) // node no longer has items
            {
                if(q->prev != nullptr) // checks if q is first element
                    q->prev->next = q->next;
                else
                    start = q->next;
                if(q->next != nullptr) // checks if q is last element
                    q->next->prev = q->prev;
                delete q;
                UniqueBigness--;
            }
            return 1;
        }
        
        if(q->next != nullptr)
            q = q->next;
    }
    return 0;

}

int Multiset::eraseAll(const ItemType& value)
{
    Node* q = start;
    int count = 0;
    
    for(int i = 0; i < UniqueBigness; i++)
    {
        if(q->item == value)
        {
            if(q->prev != nullptr)
                q->prev->next = q->next; // effectively removes node from list
            if(q->next != nullptr) // checks if q is last element
                q->next->prev = q->prev;
            UniqueBigness--;
            Bigness -= q->count;
            count = q->count;
            delete q;
            return count;
        }
        if(q->next != nullptr)
            q = q->next;
    }
    return count;
}

bool Multiset::contains(const ItemType& value) const
{
    Node* q = start;
    bool contain = false;
    
    for(int i = 0; i < UniqueBigness; i++)
    {
        if(q->item == value)
            contain = true;
        if(q->next != nullptr)
            q = q->next;
    }
    return contain;
}

int Multiset::count(const ItemType& value) const
{
    Node* q = start;
    int number = 0;
    
    for(int i = 0; i < UniqueBigness; i++)
    {
        if(q->item == value)
            number = q->count;
        if(q->next != nullptr)
            q = q->next;
    }
    return number;
}

int Multiset::get(int i, ItemType& value) const
{
    Node* q = start;
    
    if(!(i >= 0 && i < UniqueBigness))
        return 0;

    for(int j = 0; j < i; j++)
        q = q->next;
    
    value = q->item;
    return q->count;
}

bool Multiset::getMostFrequentValue(ItemType &value) const
{
    if(UniqueBigness == 0)
        return false;
    
    Node* q = start;
    ItemType mode;
    int modeCount = 0, numModes = 0;

    for(int i = 0; i < UniqueBigness; i++) // finds highest count
    {
        if(q->count > modeCount)
            modeCount = q->count;
        if(q->next != nullptr)
            q = q->next;
    }
    
    q = start; // reset q

    for(int i = 0; i < UniqueBigness; i++) // check if more than one value have highest instances
    {
        if(q->count == modeCount)
        {
            numModes++;
            mode = q->item;
        }
        if(q->next != nullptr)
            q = q->next;
    }
    
    if(numModes > 1)
        return false;
    
    value = mode;
    return true;
}

bool Multiset::getLargestValue(ItemType &value) const
{
    if(UniqueBigness == 0)
        return false;
    
    Node* q = start;
    ItemType largest;
    int ties = 0;
    
    for(int i = 0; i < UniqueBigness; i++) // finds largest value
    {
        if(q->item > largest)
            largest = q->item;
        if(q->next != nullptr)
            q = q->next;
    }
    
    q = start; // reset q
    
    for(int i = 0; i < UniqueBigness; i++) // check if any values tie for first
    {
        if(q->item == largest)
            ties++;
        if(q->next != nullptr)
            q = q->next;
    }
    
    if(ties == 1)
    {
        value = largest;
        return true;
    }
    
    return false;
}

bool Multiset::getSecondLargestValue(ItemType &value) const
{
    Node* q = start;
    int ties = 0;
    ItemType largest, secondlargest;
    
    for(int i = 0; i < UniqueBigness; i++) // find largest value
    {
        if(q->item > largest)
            largest = q->item;
        if(q->next != nullptr)
            q = q->next;
    }
    
    q = start; // reset q

    for(int i = 0; i < UniqueBigness; i++) // find second largest value
    {
        if(q->item < largest && q->item > secondlargest)
            secondlargest = q->item;
        if(q->next != nullptr)
            q = q->next;
    }
    
    q = start; // reset q

    for(int i = 0; i < UniqueBigness; i++) // check if any values tie for second
    {
        if(q->item == secondlargest)
            ties++;
        if(q->next != nullptr)
            q = q->next;
    }
        
    if(ties == 1)
    {
        value = secondlargest;
        return true;
    }
    
    return false;
}

bool Multiset::replace(ItemType original, ItemType new_value)
{
    Node* q = start, *r = start;
    
    for(int i = 0; i < UniqueBigness; i++)
    {
        if(q->item == original)
        {
            for(int j = 0; j < UniqueBigness; i++) // checks if new value is already in set
            {
                if(r->item == new_value)
                {
                    r->count += q->count;
                    if(q->prev != nullptr)
                        q->prev->next = q->next; // effectively removes node from list
                    if(q->next != nullptr) // checks if q is last element
                        q->next->prev = q->prev;
                    delete q;
                    UniqueBigness--;
                    return true;
                }
                if(r->next != nullptr)
                    r = r->next;
            }
            q->item = new_value;
            return true;
        }
        if(q->next != nullptr)
            q = q->next;
    }
    return false;
}
    
int Multiset::countIf(char op, ItemType value) const
{
    if(op != '>' && op != '=' && op != '<')
        return -1;
    
    Node *q = start;
    int ItemCount = 0;
    
    if(op == '=')
    {
        ItemCount = count(value);
    }
    
    if(op == '<')
    {
        for(int i = 0; i < UniqueBigness; i++)
        {
            if(q->item < value)
                ItemCount += q->count;
            if(q->next != nullptr)
                q = q->next;
        }
        
    }
    
    if(op == '>')
    {
        for(int i = 0; i < UniqueBigness; i++)
        {
            if(q->item > value)
                ItemCount += q->count;
            if(q->next != nullptr)
                q = q->next;
        }
    }
    return ItemCount;
}

void Multiset::swap(Multiset& other)
// Exchange the contents of this multiset with the other one.
{
    Node* temp = start;
    start = other.start;
    other.start = temp;
    
    int t = Bigness;
    Bigness = other.Bigness;
    other.Bigness = t;
    
    
    int e = UniqueBigness;
    UniqueBigness = other.UniqueBigness;
    other.UniqueBigness = e;
}

void Multiset::copyIntoOtherMultiset(Multiset &other) const
// Insert all the items into the multiset in other.
{
    Node* q = start;
    
    for(int i = 0; i < UniqueBigness; i++)
    {
        for(int j = 0; j < q->count; j++)
            other.insert(q->item);
        if(q->next != nullptr)
            q = q->next;
    }
}

Multiset::~Multiset()
{
    Node* q = start;
    while (q != nullptr)
    {
        Node *r = q->next;
        delete q;
        q = r;
    }
    start = nullptr;
    Bigness = 0;
    UniqueBigness = 0;
}

Multiset& Multiset::operator=(const Multiset& other)
{
    if(this != &other)
    {
        Node* q = start; // de-allocates dynamic memory
        while(q != nullptr)
        {
            delete q;
            q = q->next;
        }
        
        q = start; Node* r = other.start; Node *prev = start;// resets q and creates tracker pointer for other Multiset
        for(int i = 0; i < other.UniqueBigness; i++)
        {
            if(i == 0)
            {
                start = new Node;
                start->prev = nullptr;
                start->next = nullptr;
                start->item = r->item;
                start->count = r->count;
                r = r->next;
                prev = start;
            }
            else
            {
                q->next = new Node;
                q->next->item = r->item;
                q->next->count = r->count;
                q->next->next = nullptr;
                q->next->prev = q;
                q = q->next;
            }
        }
        Bigness = other.Bigness;
        UniqueBigness = other.UniqueBigness;
    }
    return *this;
}

Multiset::Multiset(const Multiset& other)
{
    Node* q = start, *r = other.start;
    for(int i = 0; i < other.UniqueBigness; i++)
    {
        if(i == 0)
        {
            q = new Node;
            q->prev = nullptr;
        }
        else
        {
            Node* s = start;
            for(int j = 0; j < i; j++)
                if(s->next != nullptr)
                    s = s->next;
            q->prev = s;
        }
        q->item = r-> item;
        q->count = r->count;
        q->next = nullptr;
        if(r->next != nullptr)
        {
            q->next = new Node;
            q = q->next;
            r = r->next;
        }
    }
    Bigness = other.Bigness;
    UniqueBigness = other.UniqueBigness;
}

void combine(const Multiset& ms1, const Multiset& ms2, Multiset& result)
{
    if(!(result.empty()))
    {
        for(int i = 0; i < result.uniqueSize(); i++)
        {
            ItemType x;
            result.get(i, x);
            result.eraseAll(x);
        }

    }
    ms1.copyIntoOtherMultiset(result);
    ms2.copyIntoOtherMultiset(result);
}

void subtract(const Multiset& ms1, const Multiset& ms2, Multiset& result)
{
    if(!(result.empty()))
    {
        for(int i = 0; i < result.uniqueSize(); i++)
        {
            ItemType x;
            result.get(i, x);
            result.eraseAll(x);
        }
    }
    for(int i = 0; i < ms1.uniqueSize(); i++)
    {
        ItemType x = 0;
        int diff = ms1.get(i, x) - ms2.count(x);
        if (diff > 0)
        {
            for(int j = 0; j < diff; j++)
                result.insert(x);
        }
    }
}





