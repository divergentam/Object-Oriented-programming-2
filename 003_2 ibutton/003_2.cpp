#include <iostream>
#include <unordered_map>

using std::cout;
using std::cin;
using std::string;
using std::endl;

enum class ButtonType{BUTTON, RADIO_BUTTON, CHECK_BOX};

class IButton {
protected:
	string tekst;
	string backgroundColor;
	static std::unordered_map<ButtonType, IButton*> prototypes;
public:
	IButton(string tekst, string backgroundColor) : 
		tekst(tekst), backgroundColor(backgroundColor){}
	IButton(const IButton& drugi) {
		this->tekst = drugi.tekst;
		this->backgroundColor = drugi.backgroundColor;
	}
	void setText(string txt){
		tekst = txt;
	}
	void SetBackgroundColor(string bgc) {
		backgroundColor = bgc;
	}
	virtual IButton* clone() = 0;
	virtual void describe() = 0;

	static IButton* getButton(ButtonType type);
};

//za staticki atribut prototypes
std::unordered_map<ButtonType, IButton*> IButton::prototypes = std::unordered_map<ButtonType, IButton*>();

class Button : public IButton {
protected:
	int width;
	int height;
public:
	Button(string text, string bgColor, int width, int height) : 
	IButton(text,bgColor) , width(width), height(height){}
	Button(const Button& drugi) : IButton(drugi) {
		this->width = drugi.width;
		this->height = drugi.height;
	}
	IButton* clone() {
		return new Button(*this);
	}
	void setWidth(int width) {
		this->width = width;
	}
	void setHeight(int height) {
		this->height = height;
	}
	+
};

class RadioButton : public IButton {
protected:
	string RBID;
public:
	RadioButton(string text, string bgColor, string RBID) :
		IButton(text, bgColor), RBID(RBID)  {}
	RadioButton(const RadioButton& drugi) : IButton(drugi) {
		this->RBID = drugi.RBID;
	}
	IButton* clone() {
		return new RadioButton(*this);
	}
	void setRBID(string RBID) {
		this->RBID = RBID;
	}
	void describe() {
		cout << "RadioButton: ( " << tekst << ", " << backgroundColor << ", " << RBID << " )" << endl;
	}
};

class CheckBox : public IButton {
protected:
	bool checked;
public:
	CheckBox(string text, string bgColor, bool checked = false) :
		IButton(text, bgColor), checked(checked) {}
	CheckBox(const CheckBox& drugi) : IButton(drugi) {
		this->checked = checked;
	}
	IButton* clone() {
		return new CheckBox(*this);
	}
	void setChecked (bool checked) {
		this->checked = checked;
	}
	void describe() {
		cout << "CheckedBox: ( " << tekst << ", " << backgroundColor << ", " << checked << " )" << endl;
	}
};

/*
* Ako u programu nije do sada konstruisan IButton tipa ButtonType 
onda ce fja getButton prvo da kreira prototip tipa ButtonType i 
vratice clone tog tipa
Ako je u programu vec napravljen IButton tipa ButtonType onda
ce se samo vratiti kopija tog IButton-a  mi cemo pomocu settera 
da postavimo neke vrednosti koje zelimo da promenimo
*/

IButton* IButton::getButton(ButtonType type) {
	if (prototypes.find(type) == prototypes.end()) {
		switch (type) {
		case ButtonType::BUTTON:
			cout << "Kreiram prototip tipa BUTTON" << endl;
			prototypes[type] = new Button("", "#BBBBBB", 30, 10);
			break;
		case ButtonType::RADIO_BUTTON:
			cout << "Kreiram prototip tipa RADIO_BUTTON" << endl;
			prototypes[type] = new RadioButton("", "#BBBBBB", "");
			break;
		case ButtonType::CHECK_BOX:
			cout << "Kreiram prototip tipa CHECK_BOX" << endl;
			prototypes[type] = new CheckBox("", "#BBBBBB");
			break;
		}
	}
	return prototypes[type]->clone();
}

int main() {
	//Pravimo konverziju iz IButton* u Button*
	Button* b1 = (Button*) IButton::getButton(ButtonType::BUTTON);
	b1->setText("Button 1");
	b1->describe();

	Button* b2 = (Button*)IButton::getButton(ButtonType::BUTTON);
	b2->setText("Button 2");
	b2->setWidth(60);
	b2->describe();

	RadioButton* b3 = (RadioButton*)IButton::getButton(ButtonType::RADIO_BUTTON);
	b3->setText("Button 3");
	b3->setRBID("RadioButton1");
	b3->describe();

	RadioButton* b4 = (RadioButton*)IButton::getButton(ButtonType::RADIO_BUTTON);
	b4->setText("Button 4");
	b4->setRBID("RadioButton2");
	b4->describe();

	CheckBox* b5 = (CheckBox*)IButton::getButton(ButtonType::CHECK_BOX);
	b5->setText("Button 5");
	b5->setChecked(true);
	b5->describe();

	delete b1;
	delete b2;
	delete b3;
	delete b4;
	delete b5;

	return 0;
}



