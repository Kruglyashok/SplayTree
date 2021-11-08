#include "text_to_bin.h"

TextToBin::TextToBin()
{
}

void TextToBin::readTxtFile(const char *inpFilename, const char* outFilename)
{
	setlocale(LC_ALL, "Russian");
	Record rec{};
	std::size_t rec_size = sizeof(rec);
	std::cout << "rec_size = " << rec_size << std::endl;
	FILE* inputFile, *outputFile;
	if (!fopen_s(&inputFile, inpFilename, "r") && !fopen_s(&outputFile, outFilename, "w+b"))
	{
		std::cout << "\nin and out files were opened" << std::endl;
		while (!feof(inputFile))
		{
			fscanf_s(inputFile, "%I64d,%[^\n,],%[^\n,]", &rec.ISBN, rec.author, sizeof(char) * maxstrlen, rec.title, sizeof(char) * maxstrlen);
			std::cout << "isbn = " << rec.ISBN << " auth = " << rec.author << " title = " << rec.title << std::endl;
			fwrite(&rec, rec_size, 1, outputFile);
		}
		fclose(inputFile);
		fclose(outputFile);
	}
	else
	{
		std::cout << "\nin or out file was not opened" << std::endl;
		return;
	}
}

void TextToBin::searcRec(const char * binFileName, unsigned long long ISBN)
{
	setlocale(LC_ALL, "Russian");
	FILE* binFile;
	Record rec{};
	std::size_t rec_size = sizeof(rec);
	bool found{ false };
	if (!fopen_s(&binFile, binFileName, "rb"))
	{
		std::cout << "\nbin file was opened" << std::endl;
		while((fread(&rec, rec_size, 1, binFile)) == 1)
		{
			if (rec.ISBN == ISBN)
			{
				found = true;
				std::cout << "found Record: " << rec.ISBN << " " << rec.author << " " << rec.title << std::endl;
				break;
			}
		}
		if (!found)
			printf("\n Record Not found in this file!");
		fclose(binFile);
	}
	else
	{
		std::cout << "\nBin File was not found" << std::endl;
	}
}
Record TextToBin::genRec(const unsigned long long ISBN, const char* author, const char* title) const
{
	return Record(ISBN, author, title);
}
void TextToBin::addRec(const char* binFileName, const Record& rec)
{
	FILE* binFile;
	std::size_t rec_size = sizeof(rec);
	if (!fopen_s(&binFile, binFileName, "a+b"))
	{
		std::cout << "\nbin file was opened" << std::endl;
		fwrite(&rec, rec_size, 1, binFile);
		fclose(binFile);
	}
	else
	{
		std::cout << "\nbin file was not opened" << std::endl;
	}
}

void TextToBin::displayRecByAddr(const char* binFileName, std::size_t addr)
{
	setlocale(LC_ALL, "Russian");
	FILE* binFile;
	Record rec{};
	std::size_t rec_size = sizeof(rec);
	bool found{ false };
	if (!fopen_s(&binFile, binFileName, "rb"))
	{
		std::cout << "\nbin file was opened" << std::endl;
		fseek(binFile, rec_size * addr, SEEK_SET);
		fread(&rec, rec_size, 1, binFile);
		std::cout << "found Record: " << rec.ISBN << " " << rec.author << " " << rec.title << std::endl;
	}
	else
	{
		std::cout << "\nBin File was not found" << std::endl;
	}
}
