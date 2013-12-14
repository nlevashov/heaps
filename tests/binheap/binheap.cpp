#include <iostream>
#include <string>

#include "../../heaps/binheap.h"

using namespace std;


int main() {
	binheap<int, int> a, b;
	b = a;

	for (int i = -5; i <= 5; i++) a.push(i, i * 100);

	b = a;

	for (int i = -5; i <= 5; i++) {
		pair<int, int> p = b.pop();
		cout << p.first << ' ' << p.second << '\t';
	}
	cout << endl;

	auto c = a;

	for (int i = -5; i <= 5; i++) {
		pair<int, int> p = a.top();
		cout << p.first << ' ' << p.second << '\t';
	}
	cout << endl;

	for (int i = -5; i <= 5; i++) {
		pair<int, int> p = a.pop();
		cout << p.first << ' ' << p.second << '\t';
	}
	cout << endl;

	for (int i = -5; i <= 5; i++) {
		pair<int, int> p = c.pop();
		cout << p.first << ' ' << p.second << '\t';
	}
	cout << endl;

//-----------------------------

	binheap<float, string> x, y, z, temp;

	for (float i =  0.5; i < 10; i += 1) x.push(i, "ab");
	for (float i = 10.5; i < 20; i += 1) y.push(i, "cd");
	for (float i = 20.5; i < 30; i += 1) z.push(i, "ef");

	x.join(y);

	temp = x;
	int size = temp.size();
	for (int i = 0; i < size; i++) {
		pair<float, string> p = temp.pop();
		cout << p.first << ' ' << p.second << '\t';
	}
	cout << endl;

	x += z;

	size = x.size();
	for (int i = 0; i < size; i++) {
		pair<float, string> p = x.pop();
		cout << p.first << ' ' << p.second << '\t';
	}
	cout << endl;

	binheap<int, int> empty;
	//empty.top();
	//empty.pop();

	return 0;
}
