////
////  main.cpp
////  Project2
////
////  Created by Nilesh Gupta on 7/7/15.
////  Copyright (c) 2015 Nilesh Gupta. All rights reserved.
////
//
//#include "Multiset.h"
//#include <iostream>
//#include <cassert>
//using namespace std;
//
//void test()
//{
//    Multiset sms;
//    assert(sms.insert("cumin"));
//    assert(sms.insert("turmeric"));
//    assert(sms.insert("cumin"));
//    assert(sms.insert("coriander"));
//    assert(sms.insert("cumin"));
//    assert(sms.insert("turmeric"));
//    assert(sms.size() == 6  &&  sms.uniqueSize() == 3);
//    assert(sms.count("turmeric") == 2);
//    assert(sms.count("cumin") == 3);
//    assert(sms.count("coriander") == 1);
//    assert(sms.count("cardamom") == 0);
//}
//
//int main()
//{
//    ItemType value;
//    Multiset ms1, ms2;
//    
//    ms1.insert("ABC"); ms1.insert("ABC");
//    ms1.insert("XYZ"); ms1.insert("GDP");
//    
//    ms2.insert("Hello"); ms2.insert("ABC");
//    ms2.insert("XYZ");   ms2.insert("PPP");
//    
//    assert( ms2.countIf('=',"ABC") == 1 );
//    
//    ms1.copyIntoOtherMultiset(ms2);
//    assert(ms2.uniqueSize() == 5 && ms2.size() == 8 );
//    
//    assert( ms2.countIf('=',"ABC") == 3 );
//    assert( ms2.countIf('>',"ABC") == 5 );
//    assert( ms2.countIf('<',"ABC") == 0 );
//}
//
//

//#include "Multiset.h"
//#include <iostream>
//#include <cassert>
//    
//    using namespace std;
//    
//    void test()
//    {
//        cerr << "test A" << endl;
//        Multiset ms;
//        cerr << "test B" << endl;
//        ms.insert(IntWrapper(10));
//        cerr << "test C" << endl;
//        ms.insert(IntWrapper(20));
//        cerr << "test D" << endl;
//        Multiset ms2;
//        cerr << "test E" << endl;
//        ms2.insert(IntWrapper(30));
//        cerr << "test F" << endl;
//        ms2 = ms;
//        cerr << "test G" << endl;
//        ms2.insert(IntWrapper(40));
//        cerr << "test H" << endl;
//    }
//    
//    int main()
//    {
//        test();
//        cerr << "DONE" << endl;
//    }

