#include <iostream>
#include <string>
#include <fstream>

#ifndef TEXT_TO_BIN_H
#define TEXT_TO_BIN_H
class TextToBin
{
private:
	static constexpr std::size_t strlen = 40;
	typedef struct Record
	{
		unsigned long long ISBN = 0;
		char author[strlen] = {};
		char title[strlen] = {};
		Record() {};
		Record(const unsigned long long _ISBN, const std::string _author, const std::string _title) : ISBN(_ISBN)
		{
			strcpy(author, _author.c_str());
			strcpy(title, _title.c_str());
		};
	} Record;
public:
	TextToBin();
	void readTxtFile(const char *, const char*);
	void searcRec(const char *, unsigned long long);
	Record genRec(const unsigned long long, const char *, const char *) const;
	void addRec(const char*, const Record&);
	void displayRecByAddr(const char*, std::size_t addr);
};

#endif 