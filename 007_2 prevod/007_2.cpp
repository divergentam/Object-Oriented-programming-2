#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

class TitleFile {
public:
	virtual vector<std::tuple<int, int, string >*>
		parseFile(const string&) = 0;
	virtual ~TitleFile(){}
};

class SrtTitle : public TitleFile {
public:
	virtual vector<std::tuple<int, int, string >*>
		parseFile(const string& filename) {
		cout << "Opening file" + filename + "witg srt subtitle.." << endl;
		return vector<std::tuple<int, int, string>*>();
	}
};

class SubTitle : public TitleFile {
public:
	virtual vector<std::tuple<int, int, string >*>
		parseFile(const string& filename) {
		cout << "Opening file" + filename + "witg sub subtitle.." << endl;
		return vector<std::tuple<int, int, string>*>();
	}
};

class TxtTitle : public TitleFile {
public:
	virtual vector<std::tuple<int, int, string >*>
		parseFile(const string& filename) {
		cout << "Opening file" + filename + "witg txt subtitle.." << endl;
		return vector<std::tuple<int, int, string>*>();
	}
};

class TitleDisplay {
protected:
	int fontSize = 14;
	std::string fontStyle = "Times New Roman";
	TitleFile* titlef;
	vector<std::tuple<int, int, string>*> subtitles;

	void parseFile(const string& fileName) {
		cout << "Parsing " << fileName << endl;
		subtitles = titlef->parseFile(fileName);
	};

public:
	TitleDisplay(TitleFile* titlef,const string& fileName) :
		titlef(titlef) {
		parseFile(fileName);
	}
	virtual void displaySubtitle() {
		cout << "Showing basic subtitles" << endl;
	}
};

class PremiumTitleDisplay : public TitleDisplay {
public:
	PremiumTitleDisplay(TitleFile* file, const string& fileName,
		int fontSize,const string& fontStyle) : TitleDisplay(file, fileName) {
		this->fontSize = fontSize;
		this->fontStyle = fontStyle;
	}
	void displaySubtitle()override {
		cout << "Showing premium subtitle with fontSize = " << fontSize <<
			", fontStyle = " << fontStyle << endl;
	}
};

int main() {
	TitleDisplay* t1 = new TitleDisplay(new SrtTitle(), "title.srt");
	TitleDisplay* t2 = new PremiumTitleDisplay(new TxtTitle(), "title2.txt", 14, "Arial");

	t1->displaySubtitle();
	t2->displaySubtitle();

	delete t1;
	delete t2;

	return 0;
}