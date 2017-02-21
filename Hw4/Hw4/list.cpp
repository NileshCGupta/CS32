//
//  list.cpp
//  Hw4
//
//  Created by Nilesh Gupta on 8/4/15.
//  Copyright (c) 2015 Nilesh Gupta. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class MenuItem
{
	public:
		MenuItem(string nm) : m_name(nm) {}
		virtual ~MenuItem() {}
		string name() const { return m_name; }
		virtual bool add(MenuItem* m) = 0;
		virtual const vector<MenuItem*>* menuItems() const = 0;
	private:
		string m_name;
};

class PlainMenuItem : public MenuItem   // PlainMenuItem allows no submenus
{
	public:
		PlainMenuItem(string nm) : MenuItem(nm) {}
		virtual bool add(MenuItem* m) { return false; }
		virtual const vector<MenuItem*>* menuItems() const { return NULL; }
};

class CompoundMenuItem : public MenuItem  // CompoundMenuItem allows submenus
{
	public:
		CompoundMenuItem(string nm) : MenuItem(nm) {}
		virtual ~CompoundMenuItem();
		virtual bool add(MenuItem* m) { m_menuItems.push_back(m); return true; }
		virtual const vector<MenuItem*>* menuItems() const { return &m_menuItems; }
	private:
		vector<MenuItem*> m_menuItems;
};

CompoundMenuItem::~CompoundMenuItem()
{
	for (int k = 0; k < m_menuItems.size(); k++)
		delete m_menuItems[k];
}

void listAll(const MenuItem* m, string path) // two-parameter overload
{
	//	You will write this code.
//	vector <MenuItem*>* items = m->menuItems();
	if(m->menuItems() == NULL && path == "")
	{
		cout << m->name() << endl;
		return;
	}
	
	if(m->menuItems() == NULL)
		return;
	
	vector <MenuItem*> items = *m->menuItems();
	for(int i = 0; i < items.size(); i++)
	{
		if(path != "")
			cout << path << items[i]->name() << endl;
		else
			cout << items[i]->name() << endl;
		string newPath = path;
		newPath += items[i]->name() + "/";
		listAll(items[i], newPath);
	}
}

void listAll(const MenuItem* m)  // one-parameter overload
{
	if (m != NULL)
		listAll(m, "");
}