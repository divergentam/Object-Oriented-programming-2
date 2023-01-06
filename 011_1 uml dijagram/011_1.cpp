#include <iostream>

using std::cout;
using std::endl;


class Subject {
public:
	virtual void doAction() = 0;
	virtual ~Subject(){}
};

class RealSubject : public Subject {
public:
	void doAction() override {
		cout << "RealSubject::doAction()" << endl;
	}
};

class Proxy : public Subject {
private:
	RealSubject* realSub;
public:
	Proxy() {
		realSub = new RealSubject();
	}
	~Proxy(){}
	void doAction()override {
		cout << "Proxy::doAction()" << endl;
		realSub->doAction();
	}
};

int main() {
	Subject* subject = new Proxy();
	subject->doAction();

	return 0;
}