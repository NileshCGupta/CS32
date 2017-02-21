//
//  main.cpp
//  Hw3
//
//  Created by Nilesh Gupta on 7/25/15.
//  Copyright (c) 2015 Nilesh Gupta. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

class SmartPhone
{
	public:
		SmartPhone(string phone) {model = phone;}
		virtual void printWebBrowser() const = 0;
		virtual ~SmartPhone() {}
		string futureMove() const {return future + " market share;";}
		string name() const {return model;}
		void setFuture(string s) {future = s;}
	
	private:
		string model;
		string future;
};

class iOS: public SmartPhone
{
	public:
		iOS(string phone, string ver):
		SmartPhone(phone), version(ver) {setFuture("continues to lose");}
		void printWebBrowser() const {cout << "Safari " + version;}
		~iOS() {cout << "Destroying " + name() + " the iOS" << endl;}
	
	private:
		string version;
};

class Android: public SmartPhone
{
	public:
		Android(string phone):
		SmartPhone(phone) {setFuture("tries to gain");}
		void printWebBrowser() const { cout << " Chrome";}
		~Android() {cout << "Destroying " + name() + " the Android" << endl;}
};

class Windows: public SmartPhone
{
	public:
		Windows(string phone):
		SmartPhone(phone) {setFuture("tries to maintain");};
		void printWebBrowser() const { cout << "IE";}
		~Windows() {cout << "Destroying " + name() + " the Windows" << endl;}
};

void availability(const SmartPhone* cp)
{
	cout << cp->name() << ", using ";
	cp->printWebBrowser();
	cout << ", " << cp->futureMove() << "." << endl;
}

//int main()
//{
//	SmartPhone* phones[4];
//	phones[0] = new Windows("Nokia Lumia 521");
//	// iOS has a name and initial version number for the Safari Browser
//	phones[1] = new iOS("iPhone 6", "5.1.7");
//	phones[2] = new Android("Samsung Galaxy S5");
//	phones[3] = new Android("Sony Xperia Z1S");
//	
//	cout << "The SmartPhones availability!" << endl;
//	for (int k = 0; k < 4; k++)
//		availability(phones[k]);
//	
//	// Clean up the SmartPhones before exiting
//	cout << "Cleaning up" << endl;
//	for (int k = 0; k < 4; k++)
//		delete phones[k];
//}

//The SmartPhones availability!
//Nokia Lumia 521, using IE, tries to maintain its market share.
//iPhone 6, using Safari version 5.1.7, continues to lose market share.
//Samsung Galaxy S5, using Chrome, tries to gain market share.
//Sony Xperia Z1S, using Chrome, tries to gain market share.
//Cleaning up
//Destroying Nokia Lumia 521 the Windows
//Destroying iPhone 6 the iOS
//Destroying Samsung Galaxy S5 the Android
//Destroying Sony Xperia Z1S the Android

