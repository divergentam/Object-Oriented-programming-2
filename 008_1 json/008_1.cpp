# include <iostream>
#include <fstream>
#include <unordered_map>

using std::cout;
using std::endl;
using std::string;



class JsonElement {
public:
	virtual void exportToFile(std::ofstream&, int) = 0;
};

template <typename T>
class SimpleJsonElement : public JsonElement {
	T value;
public:
	SimpleJsonElement(T value) : value(value){}
	void exportToFile(std::ofstream& file, int ) {
		if constexpr(std::is_same <T, string>::value) {
			file << "\"" << value << "\"";
		}
		else if constexpr (std::is_same<T, std::nullptr_t>::value)
			file << "null:";
		else if constexpr (std::is_arithmetic<T>::value)
			file << value;
		else if constexpr (std::is_same<T, bool>::value)
			file << (value ? "true" : "false");
	}
};

class JsonObject : public JsonElement{
	std::unordered_map<string, JsonElement*> values;
public:
	void addElement(string key, JsonElement* value) {
		values[key] = value;
	}
	void exportToFile(std::ofstream& file, int indentLevel) {
		string identation = "";
		for (int i = 0; i < indentLevel; ++i) {
			identation += "\t";
			file << identation << " {";
			identation += "\t";
		}
			int size = values.size();
			int i = 0;
			for (auto it = values.begin(); it != values.end(); it++) {
				file << "\"" << it->first << "\"";
				it->second->exportToFile(file, indentLevel + 1);
				if (i == size - 1)
					file << endl;
				else
					file << "," << endl;
				i++;
			}
		
	}
};