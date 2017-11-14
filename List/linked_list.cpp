#include "stdafx.h"
#include <iostream>
using namespace std;

template <typename T>
class List
{
	struct Element
	{
		T data;
		Element* next;

		Element(T _data = T(), Element* _next = nullptr)
			: data(_data), next(_next) {}
	};

	Element *front;
	//може да има и указател към края на списъка с цел добавяне
	//на елементи в края за константно време

	void copy(List const& l)
	{
		if (l.front == nullptr)
			return;

		Element* toCopy = l.front; //с този указател обхождаме 
		//елементите на списъка от който копираме
		Element* newElement = new Element(toCopy->data); //този указател
		//ще помни адреса на новия елемент
		Element* lastCopied = newElement; //сочи към последния елемент
		//в новия списък
		front = newElement;

		while(toCopy->next!=nullptr)
		{
			toCopy = toCopy->next; //обхождаме елементите на
			//списъка подаден като аргумент
			newElement = new Element(toCopy->data); //заделяме 
			//нова памет
			lastCopied->next = newElement; //поставяме новия
			//елемент в края на новия списък
			lastCopied = newElement; //последния елемент
			//на новия списък вече е новия елемент
		}
	}

	void clean()
	{
		Element* toDelete = front;
		Element* tmp;
		//използваме тези два указателя за да изтрием елементите
		//на списъка един по един без да губим верижката
		while(toDelete!=nullptr)
		{
			tmp = toDelete;
			toDelete = toDelete->next;
			delete tmp;
		}
	}

	Element* findElement(int index) const
	{
		//трябва да върнем указател към кутийката с подадения индекс
		Element* currentElement = front;
		//опитваме се да стигнем до този индекс
		for (int i = 0; i < index; i++)
		{
			//ако достигнем края на списъка преди достигането на идекса
			if (currentElement == nullptr)
				return nullptr;

			currentElement = currentElement->next;
		}
		return currentElement;
	}

public:
	List() : front(nullptr){}

	List(List const& l) : front(nullptr) 
	{
		this->copy(l);
	}

	List& operator=(List const& l) 
	{
		if (this != &l) 
		{
			this->clean();
			this->copy(l);
		}
		return l;
	}

	~List() {
		this->clean();
	}

	bool empty() const 
	{
		return front == nullptr;
	}

	// включване преди позиция
	bool insertBefore(T const& x, int index) 
	{
		if (index < 0)
			return false;
		if(index==0 || empty()) //ако списъка е празен или
		//вмъкваме преди първия елемент
		{
			front = new Element(x, front); //създаваме нов елемент за
			//начало на списъка, като го насочваме към предишното начало
			return true;
		}
		//в противен случай може да извикаме следната функция
		return insertAfter(x, index - 1);
	}

	// включване след позиция
	bool insertAfter(T const& x, int index) 
	{
		//ако списъка е празен слагаме новия елемент в началото
		if (empty()) 
		{
			front = new Element(x);
			return true;
		}

		Element* currentElement = findElement(index);
		//ако не намерим такъв индекс
		if (currentElement==nullptr)
			return false;
		
		//аналогично на ред 115
		currentElement->next = new Element(x, currentElement->next);
		return true;
	}

	/*
	 * При фунцкиите за изтриване на елемент може да се направи така, че
	 * да връщат стойността на елемента, който изтриват.
	 * Точно това е ролята на първия аргумент при следващите 3 функции.
	 */

	// изключване преди позиция
	bool deleteBefore(T& x, int index) 
	{
		//ако списъка не е празен и не се опитваме да изтрием
		//елемента преди първи то спокойно можем да извикаме
		//функцията за изтриване на дадена позиция
		if (index == 0 || empty())
			return false;
		return deleteAt(x, index - 1);
	}

	// изключване на позиция
	bool deleteAt(T& x, int index) 
	{
		if (empty())
			return false;
		//ако не изтриваме първия елемент то изтиването
		//може да се изпълни от следващата фунцкия
		if (index == 0)
		{
			x = front->data;
			Element* toDelete = front;
			front = front->next;
			delete toDelete;
			return true;
		}

		return deleteAfter(x, index - 1);
	}

	// изключване след позиция
	bool deleteAfter(T& x, int index) 
	{
		//намираме елемента, който ще трием
		Element* currentElement = findElement(index);
		if (currentElement == nullptr || currentElement->next == nullptr)
			return false;
		
		//ако е легитимен елемент го изтриваме
		Element* toDelete = currentElement->next;
		currentElement->next = toDelete->next;
		x = toDelete->data;

		delete toDelete;
		return true;
	}

	// достъп до елемент на позиция
	// !трябва да се добави сигурност!
	T const& elementAt(int index) const
	{
		Element* element = findElement(index);
		return element->data;
	}
};
