﻿// Graph.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "Graph.h"

int main()
{
	TyutkoMath::Graph q;
	q.AddTop({});
	q.AddTop({0});
	q.AddTop({1}); 
	q.AddTop({2});
	q.AddTop({ 3 });
	q.AddTop({ 4 });
	q.AddTop({ 5 });
	q.AddTop({ 6 });
	q.AddTop({ 7 });
	q.AddTop({});
	q.AddTop({});
	q.AddTop({});
	std::cout << std::endl << std::endl << std::endl << q.CountOfComponents();
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
