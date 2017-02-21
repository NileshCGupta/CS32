//
//  main.cpp
//  Hw4
//
//  Created by Nilesh Gupta on 8/3/15.
//  Copyright (c) 2015 Nilesh Gupta. All rights reserved.
//

//#include "Multiset.h"  // class template from problem 1
//#include <string>
//using namespace std;
//
//class URL
//{
//public:
//	URL(string i) : m_id(i) {}
//	URL() : m_id("http://cs.ucla.edu") {}
//	string id() const { return m_id; }
//private:
//	string m_id;
//};
//
//int main()
//{
//	Multiset<int> mi;
//	mi.insert(7);  // OK
//	Multiset<string> ms;
//	ms.insert("http://www.symantec.com");  // OK
//	Multiset<URL> mu;
//	mu.insert(URL("http://www.symantec.com"));  // error!
//}
//

#include "Multiset.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

void test1()
{
	Multiset<int> mi;
	Multiset<string> ms;
	assert(mi.empty());
	assert(ms.size() == 0);
	assert(mi.uniqueSize() == 0);
	assert(mi.insert(10));
	assert(ms.insert("hello"));
	assert(mi.contains(10));
	assert(ms.count("hello") == 1);
	assert(mi.erase(10) == 1);
	string s;
	assert(ms.get(0, s)  &&  s == "hello");
	Multiset<string> ms2(ms);
	ms.swap(ms2);
	ms = ms2;
	combine(mi,mi,mi);
	combine(ms,ms2,ms);
	assert(ms.eraseAll("hello") == 2);
	subtract(mi,mi,mi);
	subtract(ms,ms2,ms);
}

void test2()
{
	Multiset<unsigned long> ms;
	assert(ms.empty());
	unsigned long x = 999;
	assert(ms.get(0, x) == 0 && x == 999);  // x unchanged by get failure
	assert(!ms.contains(42));
	
	ms.insert(42);
	ms.insert(42);
	
	assert(!ms.getSecondLargestValue(x) && x == 999);
	assert(ms.size() == 2 && ms.uniqueSize() == 1);
	assert(ms.get(1, x) == 0 && x == 999);  // x unchanged by get failure
	assert(ms.get(0, x) == 2 && x == 42);
	
	assert(ms.getLargestValue(x) && x == 42);
	assert(ms.countIf('=', 42) == 2);
	assert(ms.countIf('>', 42) == 0);
	assert(ms.countIf('<', 42) == 0);
}

int main()
{
	test1();
	cout << "Passed test1" << endl;
	test2();
	cout << "Passed test2" << endl;
}