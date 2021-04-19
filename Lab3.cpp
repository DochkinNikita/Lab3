#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

struct BookInfo //описание структуры книги
{
	string book;
	int price;
	int pages;
	double rating;
	void Out();
};

struct MyStack 
{
	struct Node
	{
		BookInfo data;
		Node* prev;
	};
	Node* Top = NULL;
	int Count;
	bool Push(BookInfo);
	bool Pop(BookInfo&);
	void Info();
};

bool MyStack::Push(BookInfo data) //добавить объект в стек 
{
	if (!Top)
	{
		Top = new Node;
		Top->prev = NULL;
		Count = 1;
	}
	else
	{
		Node* temp;
		temp = new Node;
		temp->prev = Top;
		Top = temp;
		Count++;
	}
	Top->data = data;
	return true;
}

bool MyStack::Pop(BookInfo& data) //удалить объект из стека 
{
	if (!Top) return false;
	Node* temp = Top->prev;
	data = Top->data; delete Top;
	Top = temp; Count--;
	return true;
}

void MyStack::Info() //информация о стеке 
{
	if (!Top)
	{
		cout << "Стек пустой" << endl << endl;
	}
	else
	{
		cout << endl << "Информация о стеке: " << endl;
		cout << "Размер стека = " << Count << endl;
		Top->data.Out();
	}
}

void BookInfo::Out() //информация о последней книге 
{
	cout << "Последняя книга: " << book << "\t" << "Цена: " << price << "\t" << "Страницы: " << pages << "\t" << "Рейтинг: " << rating << endl << endl;
}

//---------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------
//Вторая часть лабы

struct Product //структура товара
{
	int volume;
	double price;
	void Out();
};

void Product::Out() //вывод значений товара
{
	cout << "Значение = " << volume << ' ' << "Цена = " << price << endl << endl;
}

struct MyQueue // описание очереди
{
	struct Node
	{
		Product data;
		Node* next;
	};
	int remain = 0;
	double cost = 0;
	double profit = 0;
	Node* First = NULL;
	int Count = 0;
	bool Push(Product);
	bool Pop(Product&);
	void Info();
	bool Sell(int, double, bool);
};

bool MyQueue::Push(Product data) //добавить товар в очередь
{
	if (!First)
	{
		First = new Node;
		First->next = NULL;
		First->data = data;
		Count = 1;
		remain = First->data.volume;
		for (int i = 0; i < data.volume; i++)
		{
			cost += First->data.price;
		}
	}
	else
	{
		Node* temp;
		temp = First;
		while (temp->next != NULL) temp = temp->next;
		temp->next = new Node;
		temp->next->data = data;
		remain += temp->next->data.volume;
		for (int i = 0; i < data.volume; i++)
		{
			cost += temp->next->data.price;
		}
		temp->next->next = NULL;
		Count++;
	}
	return true;
}

bool MyQueue::Pop(Product& data) //удалить товар из очереди 
{
	if (!First) return false;
	Node* temp = First->next;
	data = First->data;
	remain -= First->data.volume;
	for (int i = 0; i < data.volume; i++)
	{
		cost -= First->data.price;
	}
	delete First;
	First = temp;
	Count--;
	return true;
}

void MyQueue::Info() //вывод информации об очереди
{
	if (!First) cout << "Очередь пустая " << endl << endl;
	else
	{
		cout << endl << "Информация об очереди: " << endl;
		cout << "Размер очереди = " << Count << endl;
		First->data.Out();
	}
	cout << "Общая стоимость = " << cost << endl << "Осталось товара= " << remain << endl << "Прибыль = " << profit << endl << endl;
}

bool MyQueue::Sell(int volume, double price, bool fsell) //продажа товара
{
	Product temp;
	if (volume == 0) return true;
	if (Count == NULL)
	{
		cout << "Недостаточно продукта !" << endl << endl;
		return true;
	}
	if (price < First->data.price && fsell == true)
	{
		cout << endl << "Цена слишком малая !" << endl;
		return false;
	}
	else
	{
		if (volume > remain)
		{
			cout << endl << "Недостаточно продукта !" << endl << endl;
			return false;
		}
		if (First->data.volume > volume || First->data.volume == volume)
		{
			First->data.volume -= volume;
			profit += (price - First->data.price) * volume;
			remain -= volume;
			for (int i = 0; i < volume; i++)
			{
				cost -= First->data.price;
			}
			if (First->data.volume == 0)
			{
				Pop(temp);
			}
			return true;
		}
		else
		{
			profit += (price - First->data.price) * First->data.volume;
			volume -= First->data.volume;
			Pop(temp);
			Sell(volume, price, false);
		}
	}
}

//---------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------

bool GetFile(MyStack&, BookInfo&);
void GetBook(MyStack&, BookInfo&);
bool RemoveBook(MyStack& sMain, BookInfo& k, string);

int main()
{
	setlocale(LC_ALL, "ru");
	BookInfo k;
	Product k1, k11, k22;
	MyStack S;
	MyStack Temp;
	MyQueue Q;
	string title;
	int key2 = 0, key1 = 0, key = 0, price, volume;
	GetFile(S, k);
	do
	{
		cout << "1) Стек" << endl
			<< "2) Очередь" << endl
			<< "0) Выход" << endl;
		cout << endl << "Выбирите действие: ";
		cin >> key;
		cout << endl;
		switch (key)
		{
		case 1:
			do
			{
				cout << "1) Добавить продукт" << endl
					<< "2) Вытащить продукт" << endl
					<< "3) Очистить корзину" << endl
					<< "4) Показать последний товар в корзине" << endl
					<< "0) Выход" << endl;
				cout << endl << "Выбирите действие: ";
				cin >> key1;
				cout << endl;
				switch (key1)
				{
				case 1:
					GetBook(S, k);
					S.Info();
					break;
				case 2:
					cout << "Введите название книги: ";
					cin >> title;
					RemoveBook(S, k, title);
					S.Info();
					break;
				case 3:
					while (S.Pop(k))
					{
						k.Out();
					}
					S.Info();
					break;
				case 4:
					S.Info();
					break;
				default:
					if (key1 != 0)
					{
						cout << "Такого действия нет !" << endl << endl;
					}
					if (key1 == 0)
					{
						while (S.Pop(k));
						S.Info();
					}
					break;
				}
			} while (key1 != 0);
			break;
		case 2:
			do
			{
				cout << "1) Поступление товара" << endl
					<< "2) Продажа товара" << endl
					<< "3) Отчет о товаре" << endl
					<< "0) Выход" << endl;
				cout << endl << "Выбирите действие: ";
				cin >> key2;
				cout << endl;
				switch (key2)
				{
				case 1:
					cout << "Введите значение: ";
					cin >> k1.volume;
					cout << endl << "Введите цену: ";
					cin >> k1.price;
					Q.Push(k1);
					Q.Info();
					break;
				case 2:
					cout << "Введите значение: ";
					cin >> volume;
					cout << endl << "Введите цену: ";
					cin >> price;
					cout << endl;
					Q.Sell(volume, price, true);
					Q.Info();
					break;
				case 3:
					Q.Info();
					break;
				default:
					if (key2 != 0)
					{
						cout << "Такого действия нет !" << endl << endl;
					}
					if (key2 == 0)
					{
						while (Q.Pop(k1));
						Q.Info();
					}
					break;
				}
			} while (key2 != 0);
			break;
		default:
			if (key != 0)
			{
				cout << "Такого действия нет !" << endl << endl;
			}
			break;
		}
	} while (key != 0);
}

bool GetFile(MyStack& Stack, BookInfo& k) //считывание файла
{
	ifstream F("Books.txt");
	if (!F)
	{
		cout << "Файл не найден !" << endl;
		return false;
	}
	while (F >> k.book >> k.price >> k.pages >> k.rating)
	{
		Stack.Push(k);
	}
	F.close();
	return true;
}

void GetBook(MyStack& Stack, BookInfo& k) //добавить книгу 
{
	cout << "Введите название: ";
	cin >> k.book;
	cout << endl;
	cout << "Введите цену: ";
	cin >> k.price;
	cout << endl;
	cout << "Введите кол-во страниц: ";
	cin >> k.pages;
	cout << endl;
	cout << "Введите рейтинг: ";
	cin >> k.rating;
	cout << endl;
	Stack.Push(k);
}

bool RemoveBook(MyStack& sMain, BookInfo& k, string title) //удалить книгу
{
	MyStack sTemp;
	bool stopFind = false, find = false;
	while (stopFind == false)
	{
		sTemp.Push(sMain.Top->data);
		sMain.Pop(k);
		if (sTemp.Top->data.book == title)
		{
			find = true;
			stopFind = true;
			break;
		}
		if (sMain.Top == NULL)
		{
			stopFind = true;
			break;
		}
	}
	if (find == true)
	{
		sTemp.Pop(k);
		cout << endl << "Объект с названием " << title << " успешно удален!" << endl;
	}
	else
	{
		cout << endl << "Объект с названием " << title << " не найден!" << endl;
	}
	stopFind = false;
	while (stopFind == false)
	{
		if (find != true)
		{
			sMain.Push(sTemp.Top->data);
			sTemp.Pop(k);
		}
		find = false;
		if (sTemp.Top == NULL) stopFind = true;
	}
	find = false;
	return true;
}