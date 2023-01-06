#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;





template<typename T>
class StackImplementator {
public:
	virtual void push(T) = 0;
	virtual T peek() const = 0;
	virtual void pop() = 0;
	virtual bool empty()const = 0;
	virtual int size()const = 0;
	virtual ~StackImplementator() {}
};

//prakticno adapriramo vektor za koriscenje
template <typename T>
class VectorStackImplementator : public StackImplementator<T> {
	vector<T> v;
public:
	void push(T elem) override {
		v.push_back(elem);
	}
	void pop() override {
		v.pop_back();
	}
	T peek()const override {
		return v.back();
	}
	bool empty() const override {
		return v.empty();
	}
	int size() const override {
		return v.size();
	}
};

template <typename T>
class ArrayStackImplementator : public StackImplementator<T> {
private:
	T* niz;
	int index;
	int capacity;
	void resize() {
		T* new_niz = new T[capacity * 2];
		for (int i = 0; i < capacity; i++) {
			new_niz[i] = niz[i];
		}
		delete niz;
		niz = new_niz;
		capacity *= 2;
	}

public:
	ArrayStackImplementator() : index(0), capacity(10) {
		niz = new T[capacity];
	}
	void pop() override {
		if (index > 0) {
			index--;
		}
		else {
			cout << "Array is empty" << endl;
		}
	}
	T peek() const override {
		if (index > 0) return niz[index - 1];
		cout << "Array is empty" << endl;
	}
	void push(T elem) override {
		if (index == capacity) resize();
		niz[index++] = elem;
	}
	int size() const override {
		return index;
	}
	bool empty() const override {
		return index == 0;
	}
};

//ako se ne navede po def je vekstackiml
template <typename T , template<typename> class Implementator>
class Stack {
private:
	Implementator<T> implementator;
public:
	int size()const { return implementator.size(); }
	bool empty()const { return implementator.empty(); }
	T peek()const { return implementator.peek(); }
	virtual void push(T elem) { return implementator.push(elem); }
	virtual void pop() { return implementator.pop(); }
};

template <typename T, template<typename> class Implementator>
class LimitedCapacityStack :public Stack<T, Implementator> {
	int capacity;
public:
	LimitedCapacityStack(int cap) : capacity(cap){}
	void push(T elem) {
		if (this->size() < capacity) {
			Stack<T, Implementator>::push(elem);
		}
		else {
			cout << "Stack overflow!" << endl;
		}
	}
};

int main() {
	LimitedCapacityStack<int, ArrayStackImplementator> s(2);
	s.push(1);
	s.push(12);
	s.push(-1);

	while (!s.empty()) {
		cout << s.peek() << endl;
		s.pop();
	}
}