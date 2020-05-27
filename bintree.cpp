/*

Бинарное дерево описывается так:
typedef struct link {
    int id;
    link *left, *right;
} tree;
Добавить элемент в дерево:
    Если дерево пустое, добавляем элемент
    Иначе
        Если элемент меньше поля id добавляем в левое поддерево,
        Иначе добавляем в правое поддерево.
Удалить элемент из дерева:
    Если элемент лист(левое и правое поддерево пустое) - удаляем его
    Иначе
    Если есть только один левый/правый потомок, его надо подцепить к предку
         (используется механизм возврата из рекурсии)
    Иначе
        (есть оба потомка) находим самый правый элемент в левом поддереве
        (это лист или имеет только одного левого потомка)
        меняем поле id на id найденного элемента, удаляем найденный элемент,
        можно искать самый левый элемент в правом поддереве
        далее алгоритм действий тот же.
Обход дерева:
Для вывода дерева на печать или других действий с  элементами дерева используются три варианта обхода дерева:

     inorder                  preorder                   postorder
1.Обход левого поддерева     1.Обработка корня         1.Обход левого поддерева
2.Обработка корня            2.Обход левого поддерева  2.Обход правого поддерева
3.Обход правого поддерева    3.Обход правого           3.Обход корня

При выводе дерева на печать структура дерева очевидна только при preorder обходе.
При inorder обходе получаем отсортированную последовательность.
Для наглядности структуры дерева при inorder обходе можно использовать
глубину рекурсии, в С++ есть функция setw(),
а в С придется формировать форматную строку.


                    5(1)
                   /    \
                3(0)     7(1)
                /       /    \
           2(-1)     6(1)    9(-1)
                            /
                           8(-1)


Инд.задание:
11) Написать программу нахождения суммы весов вершин на пути
    из корня в листья (для указанного примера 0,3,0)

    Уточнение: вывести сумму весов всех листьев.

*/


#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
using namespace std;
//-----------------------------------------------
struct bin_tree {
    int weight;
    int id;
    struct bin_tree *left;
    struct bin_tree *right;
};
//-----------------------------------------------
void Bpush(bin_tree*& head, int x, int w)
{
    if (!head) {
        bin_tree*t = new bin_tree;
        t->weight = w;
        t->id = x;
        t->left = NULL;
        t->right = NULL;
        head = t;
    } else {
        if (x < head->id) Bpush(head->left, x, w);
        else              Bpush(head->right, x, w);
    }
}
//-----------------------------------------------
void show (bin_tree*& head, int n)
{
    if (head != NULL) {
        show(head->left, n+2);
        cout << setw(n*3) << head->id <<'('<<head->weight<<')'<< endl;
        show(head->right, n+2);
    }
}
//-----------------------------------------------
bin_tree* Bdel(bin_tree*& head, int x)
{
    if (!head) { cout << "No this element in tree\n"; return head; }
    if (x < head->id) { head->left  = Bdel(head->left,  x); return head; }
    if (x > head->id) { head->right = Bdel(head->right, x); return head; }
    if(!head->right) { head = head->left;  return head; }
    if(!head->left ) { head = head->right; return head; }
    bin_tree *tmp = head->left;
    if (tmp->right) {
        while (tmp->right->right) tmp = tmp->right;
        head->id = tmp->right->id;
        head->weight = tmp->right->weight;
        tmp->right = tmp->right->left;
    }
    else {
        head->id = tmp->id;
        head->weight = tmp->weight;
        head->left=head->left->left;
    }
    return head;
}
//-----------------------------------------------
// Если это лист, печатаем x+w
// Если нет, вызываем для поддерева с аргументов x+w
void Indi(bin_tree*& head, int x)
{
    x += head->weight;
    if(head->left == NULL && head->right==NULL) { std::cout<<x<<" "; return; }
    if(head->left  != NULL) Indi(head->left,  x);
    if(head->right != NULL) Indi(head->right, x);
}
//-----------------------------------------------
int main()
{
    bin_tree *head = NULL;
    for (int i=0;i<10;i++)
        Bpush(head,rand()%199-100, rand()%3-1);

    show(head, 1);
    int action, w, x;
    while (true) {
        std::cout << "------------------\n";
        std::cout << "0 - Exit\n";
        std::cout << "1 - Insert el.\n";
        std::cout << "2 - Delele el.\n";
        std::cout << "3 - Print tree\n";
        std::cout << "4 - Indiv: Sum of weights of all leaves\n";
		std::cin >> action;
		switch (action) {
		case(1):
			std::cout << "Value and weight:\n";
			cin >> x;
			cin >> w;
			Bpush(head, x, w);
			break;
		case(2):
			std::cout << "Value:\n";
			cin >> x;
			Bdel(head, x);
			break;
		case(3):
			show(head, 1);
			break;
		case(4):
		    cout << "\nResult: ";
		    x=0;
		    Indi(head, x);
		    cout << "\n";
		    break;
		case(0):
			return 0;
		}
	}
}
/*
// Написать программу нахождения суммы весов вершин на пути
// из корня в листья (для указанного примера 0,3,0)
// Пусть возвращает 999999999, если такого нет
//

#define INFTY 999999999
int Indi(bin_tree*& head, int s)
{
    if(head == NULL) return INFTY;
    if(head->id==s) return head->weight;
    if(head->id <s) {
        int t = Indi(head->right,s);
        if(t==INFTY) return t;
        return t+head->weight;
    }
    // остался случай head->id >s
    int t = Indi(head->left,s);
    if(t==INFTY) return t;
    return t+head->weight;
}


*/
