/*Реализуйте свой стек. Решения, использующие std::stack, получат 1 балл. Решения, хранящие стек в массиве, получат 1.5 балла. Решения, использующие указатели, получат 2 балла.

Гарантируется, что количество элементов в стеке ни в какой момент времени не превышает 10000.

Обработайте следующие запросы :

push n : добавить число n в конец стека и вывести «ok»;
pop: удалить из стека последний элемент и вывести его значение, либо вывести «error», если стек был пуст;
back: сообщить значение последнего элемента стека, либо вывести «error», если стек пуст;
size: вывести количество элементов в стеке;
clear: опустошить стек и вывести «ok»;
exit: вывести «bye» и завершить работу.
*/
#include <iostream>
#include <string>

using namespace std;


class Stack {
private:
	struct Comp {
		int data;
		Comp *next;
	};
	Comp *top = 0;
	int size = 0;
public:
	Stack();
	~Stack();
	void clear() {
		while (size != 0) {
			pop();
		}
		top = 0;
	}
	int len() {
		return size;
	}
	auto back() {
		return top->data;
	}
	void push(int n) {
		Comp *el = new Comp();
		el->data = n;
		el->next = top;
		top = el;
		size++;

	}
	void pop() {
		Comp *del = top;
		top = top->next;
		delete del;
		size--;
	}
};

Stack::~Stack() {
	while (top != 0) {
		Comp *el = top;
		top = top->next;
		delete el;
	}
}

Stack::Stack() {
	Comp *top = 0;
	int size = 0;
}

int main()
{
	string s;
	int n;
	auto stack = new Stack();
	while (s != "exit") {
		cin >> s;
		if (s[0] == 'p') {
			if (s[1] == 'u') {
				cin >> n;
				stack->push(n);
				cout << "ok" << '\n';
			}
			else {
				if (stack->len() == 0) cout << "error" << "\n";
				else cout << stack->back() << "\n", stack->pop();
			}
		}
		if (s[0] == 'b') {
			if (stack->len() == 0) cout << "error" << "\n";
			else cout << stack->back() << "\n";
		}
		if (s[0] == 's') {
			cout << stack->len() << '\n';
		}
		if (s[0] == 'c') {
			stack->clear();
			cout << "ok" << '\n';
		}
	}
	cout << "bye";
	return 0;
}