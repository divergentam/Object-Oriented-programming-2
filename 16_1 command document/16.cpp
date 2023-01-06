/*
Implementirati klasu Dokument koja od atributa ima sadržaj i ime fajla. Od metoda dodati
metode save(), addChar(), insertChar(). Kreirati odgovarajuće komande koje osim
execute() imaju i undo() metodu. Implementirati klasu Invoker kojom je moguće dodati
nove komande u red, pokrenuti sve komande u redu, proslediti komandu koju treba
odmah izvršiti i metode undo() i redo().
*/
/*
Dokument konstruktor:
ako (fajl.is_opene())
onda zelimo da procitamo sadrzaj iz dokumenta{
					sadrzaj iz dokumenta citamo preko std::stringstream stream; stream<<fajl.rdbuff(); sadrzaj = stream.str();
u suprotnom cemo reci da je sadrzaj = ""

metode:
1.save() -> ofstream i upisemo sadrzaj
2.addChar() -> na kraju dokumenta dodati char
3.insertChar()  -> 


*/


// sto se tice dokumenta fje:
// save()

#include <iostream>
#include <queue>
#include <stack>
#include <fstream>
#include <sstream>

class Dokument {
protected:
	std::string ime_fajla;
	std::string sadrzaj;
public:
	Dokument(const std::string& ime_fajla) : ime_fajla(ime_fajla) {
		std::ifstream fajl(ime_fajla);
		if (fajl.is_open()) {
			std::stringstream stream;
			stream << fajl.rdbuf();
			sadrzaj = stream.str();
			fajl.close();
		}
		else
			sadrzaj = "";
	}
	void save() {
		std::ofstream fajl(ime_fajla);
		fajl << sadrzaj;
		fajl.close();
	}
	void insertChar(char c, int pos) {
		sadrzaj.insert(pos, 1, c);
	}
	void addChar(char c) {
		sadrzaj += c;
	}
	std::string getSadrzaj() {
		return sadrzaj;
	}

	friend class InsertCharCommand;
	friend class AddCharCommand;
};

class Command {
protected:
	Dokument* dok;
public:
	Command(Dokument* dok) : dok(dok) {}
	virtual void execute() = 0;
	virtual void undo() = 0;
	virtual ~Command() {
		delete dok;
	}
};

class SaveCommand : public Command {
public:
	using Command::Command;
	void execute() override {
		dok->save();
	}
	void undo() override {}
};

class InsertCharCommand : public Command {
	char c;
	int poz;
public:
	InsertCharCommand(Dokument* dok, int poz, char c) :
		Command(dok), poz(poz), c(c) {}
	void execute() override {
		dok->insertChar(c, poz);
	}
	void undo() override {
		dok->sadrzaj = dok->sadrzaj.substr(0, poz) + dok->sadrzaj.substr(poz + 1);
	}
};

class AddCharCommand : public Command {
	char c;
public:
	AddCharCommand(Dokument* dok, char c) :
		Command(dok), c(c) {}
	void execute() override {
		dok->addChar(c);
	}
	void undo() {
		dok->sadrzaj = dok->sadrzaj.substr(0, dok->sadrzaj.size() - 1);
	}
};

class Invoker {
	std::queue<Command*> komande;
	std::stack<Command*> undoStack;
	std::stack<Command*> redoStack;
public:
	void addCommand(Command* command) {
		komande.push(command);
	}
	// onog trenutka kada izvrsimo neku novu komandu nemamo mogucnost redo()
	void executeCommand(Command* command) {
		command->execute();
		undoStack.push(command);
		while (!redoStack.empty()) {
			redoStack.pop();
		}
	}
	//bitno je kad izvrsimo komandu mozemo tu komandu da redu
	void executeCommands() {
		while (!komande.empty()) {
			Command* k = komande.front();
			komande.pop();
			k->execute();
			undoStack.push(k);
		}
	}
	void undo() {
		if (!undoStack.empty()) {
			Command* k = undoStack.top();
			undoStack.pop();
			k->undo();
			redoStack.push(k);
		}
	}
	void redo() {
		if (!redoStack.empty()) {
			Command* k = redoStack.top();
			redoStack.pop();
			k->execute();
			undoStack.push(k);
		}
	}
};

int main() {
	Dokument* d = new Dokument("test.txt");
	Invoker p;
	p.addCommand(new AddCharCommand(d, 'a'));
	p.addCommand(new AddCharCommand(d, 'b'));
	p.addCommand(new AddCharCommand(d, 'd'));
	p.addCommand(new AddCharCommand(d, 'e'));
	p.addCommand(new AddCharCommand(d, 'f'));
	p.addCommand(new InsertCharCommand(d, 42, 'c'));

	p.executeCommands();
	p.executeCommand(new SaveCommand(d));
	std::cout << "Sadrzaj dokumenta: " << d->getSadrzaj() << std::endl;

	p.undo(); // prvo undo save jer on ne menja sadrzaj dokumenta

	for (int i = 0; i < 6; i++) {
		p.undo();
		std::cout << "Sadrzaj dokumenta: " << d->getSadrzaj() << std::endl;
	}
	p.executeCommand(new SaveCommand(d));


	return 0;
}