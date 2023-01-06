/*
Napisati klasu InternetServiceHandler koja ima metodu WebPage* getPage(string url,
string ip). Napisati i klase DownloadPageInternetServiceHandler kojom se preuzima
sadrđaj sa traženog url-a, RestrictedAccessInternetServiceHandler koja ima listu ip adresa
sa kojih je zabranjeno preuzimati sadržaj, kao i klasu CacheInternetServiceHandler koja
pamti ranije preuzete sadržaje i vraća ih ukoliko se budu ponovo tražili.
Kada korisnik zatraži sadržaj stranice treba prvo ispitati ima li pravo da traži dati sadržaj,
zatim da li je dati sadržaj već dostupan i tek na kraju preuzeti sadržaj (ukoliko mora).
Koja je razlika ove primene u odnosnu na Dekoratora?
*/

#include <iostream>
#include <unordered_map>
#include <unordered_set>

class WebPage {
public:
	std::string url;
	WebPage(std::string url) : url(url){}
};

class InternetServiceHandler {
protected:
	InternetServiceHandler* next = nullptr;
public:
	virtual WebPage* getPage(const std::string& url, const std::string& ip) {
		if (next) 
			return next->getPage(url, ip);
		return nullptr;
	}
	void setLast(InternetServiceHandler* hendler) {
		InternetServiceHandler* temp = this;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = hendler;
	}
	virtual ~InternetServiceHandler() {
		delete next;
	}
};

class DownloadPageInternetServiceHandler : public InternetServiceHandler {
public:
	WebPage* getPage(const std::string& url, const std::string & ip) override {
		return new WebPage(url);
	}
};

class RestrictedAccessInternetServiceHandler : public InternetServiceHandler {
	std::unordered_set<std::string> blocked_ip;
public:
	RestrictedAccessInternetServiceHandler(std::unordered_set<std::string> blocked_ip) : blocked_ip(blocked_ip){}
	WebPage* getPage(const std::string& url, const std::string& ip) override {
		if (blocked_ip.find(ip) == blocked_ip.end()) { // ako nije u listi blokiranih
			return InternetServiceHandler::getPage(url, ip);
		}
		else
			return nullptr;
	}
};

class CacheInternetServiceHandler : public InternetServiceHandler {
	std::unordered_map<std::string, WebPage*> cashe;
public:
	WebPage* getPage(const std::string& url, const std::string& ip) override{
		if (cashe.find(url) == cashe.end()) {
			WebPage* page = InternetServiceHandler::getPage(url, ip); // prvo treba da vidimo sta je webpage
			if (page != NULL) {
				cashe[url] = page;
			}
			return page;
		}
		else {
			std::cout << "Vracam kesirani sadrzaj sa stranice " << url << std::endl;
			return cashe[url];
		}
	}
};

int main() {
	std::unordered_set <std::string> blocked_ip;
	blocked_ip.insert("12.32.43.54");
	blocked_ip.insert("12.32.43.154");

	InternetServiceHandler* hendler = new RestrictedAccessInternetServiceHandler(blocked_ip);

	hendler->setLast(new CacheInternetServiceHandler());
	hendler->setLast(new DownloadPageInternetServiceHandler());

	WebPage* page1 = hendler->getPage("www.wordpress.com", "12.21.43.167");
	if (page1)
		std::cout << "Preuzet sadrzaj sa stranice " << page1->url << std::endl;
	else 
		std::cout << "Nije moguce preuzeti sadrzaj sa stranice: www.wordpress.com i ip: 12.21.43.167" << std::endl;

	WebPage* page2 = hendler->getPage("www.pmf.edu.rs", "12.31.45.154");
	if (page2)
		std::cout << "Preuzet sadrzaj sa stranice " << page2->url << std::endl;
	else
		std::cout << "Nije moguce preuzeti sadrzaj sa stranice: www.pmf.edu.rs i ip: 12.31.45.154 " << std::endl;

	WebPage* page3 = hendler->getPage("www.nestoxxx.com", "12.32.43.154");
	if (page3)
		std::cout << "Preuzet sadrzaj sa stranice " << page3->url << std::endl;
	else
		std::cout << "Nije moguce preuzeti sadrzaj sa stranice: www.nestoxxx.com i ip: 12.32.43.154 " << std::endl;


	WebPage* page4 = hendler->getPage("www.pmf.edu.rs", "12.31.45.155");
	if (page4)
		std::cout << "Preuzet sadrzaj sa stranice " << page2->url << std::endl;
	else
		std::cout << "Nije moguce preuzeti sadrzaj sa stranice: www.pmf.edu.rs i ip: 12.31.45.154 " << std::endl;

	return 0;
}