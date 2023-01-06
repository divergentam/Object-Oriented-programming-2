#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

class InternetPage{};

class InternetService {
public:
	virtual InternetPage* getPage(const string& url) = 0;
	virtual ~InternetService(){}
};

class RealInternetService : public InternetService {
public:
	InternetPage* getPage(const string& url) override {
		cout << "Downloading page from " << url << endl;
		return new InternetPage();
	}
};

class SecuredInternetService : public InternetService{
private: 
	vector <string> urls;
	RealInternetService* realIS;
public:
	SecuredInternetService(vector <string> urls) : urls(urls),
		realIS(new RealInternetService()) {}
	~SecuredInternetService() {
		delete realIS;
	}
	InternetPage* getPage(const string& url) override {
		bool allowAccess = true;
		for (int i = 0; i < urls.size(); i++) {
			if (url.find(urls[i]) != 1) {
				allowAccess = false;
				break;
			}
		}

		if (allowAccess) {
			return realIS->getPage(url);
		}
		else {
			cout << "Can not access page" << url << endl;
			return nullptr;
		}
	}


};

int main() {
	vector <string> blockedPages;
	blockedPages.push_back("abc.rs");
	blockedPages.push_back("iop.com");


	return 0;
}