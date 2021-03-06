/*
Завдання 2.
В реалізації патерну Абстрактна фабрика (Abstract factory)  завдання 1 оформити всі фабрики як Одинаки(Singleton).

*/

#include "stdafx.h"
#include <iostream> 
#include <string>
#include <assert.h>



using namespace std;

//abstract Button
class IButton
{
protected:

	string name;

public:

	virtual void press() = 0;
	virtual void print() = 0;

};

//Concrete Button1
class WinButton : public IButton
{

public:

	WinButton(string name)
	{
		this->name = name;
	}

	virtual void press()
	{
		cout << "WinButton " << name << " method Press\n";
	}

	virtual void print()
	{
		cout << "WinButton " << name << " method Print\n";
	}
};

//Concrete Button2
class MacButton : public IButton
{
public:

	MacButton(string name)
	{
		this->name = name;
	}

	virtual void press()
	{
		cout << "MacButton " << name << " method Press\n";
	}

	virtual void print()
	{
		cout << "MacButton " << name << " method Print\n";
	}
};

//abstract CheckBox 
class ICheckBox
{
protected:

	string name;
	bool flag;

public:

	virtual void click() = 0;
	virtual void print() = 0;

};

//Concrete CheckBox 1
class WinCheckBox : public ICheckBox
{
public:

	WinCheckBox(string name, bool flag)
	{
		this->name = name;
		this->flag = flag;
	}

	virtual void click()
	{
		cout << "WinCheckBox method Click\n";
		flag = !flag;
	}

	virtual void print()
	{
		cout << "WinCheckBox name: " << name << ", state: " << flag << endl;
	}
};

//Concrete CheckBox 2
class MacCheckBox : public ICheckBox
{
public:

	MacCheckBox(string name, bool flag)
	{
		this->name = name;
		this->flag = flag;
	}

	void click()
	{
		cout << "MacCheckBox Click\n";
		flag = !flag;
	}

	void print()
	{
		cout << "MacCheckBox name: " << name << ", state: " << flag << endl;
	}
};

// Abstract Factory
class GUIFactory
{
public:
	virtual IButton* createButton() = 0;
	virtual ICheckBox* createCheckBox() = 0;
};

// Concrete Factory1
class WinFactory : public GUIFactory
{
protected:

	WinFactory(string name)
	{
		this->name = name;
	}
	string name;
	static WinFactory *winfactory;

public:

	static WinFactory* getInstanse(string nameFactory = "win")
	{
		if (winfactory == nullptr)
			winfactory = new WinFactory(nameFactory);
		return winfactory;
	}

	string getNameWinFactory() const
	{
		return name;
	}

	void setNameWinFactory(string newName)
	{
		name = newName;
	}

	virtual IButton* createButton()
	{
		IButton *pB = new WinButton("'OK'");
		return pB;
	}

	virtual ICheckBox* createCheckBox()
	{
		ICheckBox *pCb = new WinCheckBox("'Reverse'", true);
		return pCb;
	}
};

// Concrete Factory2
class MacFactory : public GUIFactory
{
protected:

	MacFactory(string name)
	{
		this->name = name;
	}
	string name;
	static MacFactory *macfactory;

public:

	static MacFactory* getInstanse(string nameFactory = "mac")
	{
		if (macfactory == nullptr)
			macfactory = new MacFactory(nameFactory);
		return macfactory;
	}

	string getNameMacFactory() const
	{
		return name;
	}

	void setNameMacFactory(string newName)
	{
		name = newName;
	}

	virtual IButton* createButton()
	{
		IButton *pB = new MacButton("'Cancel'");
		return pB;
	}

	virtual ICheckBox* createCheckBox()
	{
		ICheckBox *pCb = new MacCheckBox("'Sort'", true);
		return pCb;
	}
};

void use(GUIFactory* f)
{
	IButton* myButton = f->createButton();
	ICheckBox* myCheckBox = f->createCheckBox();
	myButton->press();
	myButton->print();
	cout << "---------\n";
	myCheckBox->print();
	myCheckBox->click();
	myCheckBox->print();
	cout << "-=-=-=-=-\n\n";
}

WinFactory *WinFactory::winfactory = 0;
MacFactory *MacFactory::macfactory = 0;

int main()
{
	cout << "\tDemonstration Singltone\n";
	WinFactory * win1 = WinFactory::getInstanse(); //створили екземпляр win
	cout << "Name of object win1: " << win1->getNameWinFactory() << endl; 
	WinFactory * win2 = WinFactory::getInstanse("android"); // робимо спробу створити ще один екземпляр класу WinFactory на імя android
	cout << "Name of object win2: " << win2->getNameWinFactory() << endl; // бачимо, що не виходить, на екрані старий win

	cout << "\nwin1 : " << win1 << "\twin2 : " << win2 << endl << endl;
	_ASSERT(win1 == win2); // маскрос перевірить умову, якщо невірна, то буде помилка виконання

	MacFactory * mac = MacFactory::getInstanse(); //створили екземпляр mac

	cout << "\tWork program\n";
	use(win2);
	use(mac);


	cout << endl;
	system("pause");
	return 0;
}