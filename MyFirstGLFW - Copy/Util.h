#pragma once
#include <string>
#include <iostream>
#include <fstream>

using namespace std;
string readFile(string fileName) {
	string fileText;

	ifstream myFile(fileName);
	string tempText;
	while (getline(myFile, tempText)) {
		fileText += tempText + "\n";
	}
	cout << fileText << endl;
	return fileText;
}