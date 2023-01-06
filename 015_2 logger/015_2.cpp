#include <iostream>
#include <fstream>

enum class logTip { INFO, WARNING, DEBUG, ERROR };

class Logger {
protected:
	Logger* next = nullptr;
public:
	virtual void log(const std::string& message, logTip tip) {
		if (next)
			next->log(message, tip);
	}
	void setLast(Logger* logger) {
		Logger* temp = this;
		while (temp->next)
			temp = temp->next;
		temp->next = logger;
	}
};

class InfoLogger : public Logger {
	void log(const std::string& message, logTip tip) override {
		if (tip == logTip::INFO)
			std::cout << "INFO: " << message << std::endl;
		else
			Logger::log(message, tip);
	}
};

class DebugLogger : public Logger {
	void log(const std::string& message, logTip tip) override {
		if (tip == logTip::DEBUG)
			std::cout << "DEBUG: " << message << std::endl;
		else
			Logger::log(message, tip);
	}
};

class WarningLogger : public Logger {
	void log(const std::string& message, logTip tip) override {
		if (tip == logTip::WARNING) {
			std::cout << "WARNING: " << message << std::endl;
			std::ofstream fajl("warning.txt");
			fajl << "WARNING: " << message << std::endl;
			fajl.close();
		}
		else
			Logger::log(message, tip);
	}
};

int main() {
	Logger* logger = new InfoLogger();
	logger->setLast(new DebugLogger());
	logger->setLast(new WarningLogger());

	logger->log("Dobro jutro moja voljena", logTip::INFO);
	logger->log("Ne voli te niko kao ja", logTip::WARNING);
	logger->log("Kao jaaaaaaaaaaaaaa", logTip::DEBUG);


	return 0;
}