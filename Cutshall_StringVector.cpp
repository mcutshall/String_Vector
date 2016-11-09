// Cutshall_StringVector.cpp : Defines the entry point for the console application.
/*
Program: Strings, Vectors, and Text I/O Prjoect

Purpose: This program creates a string vector and populates it with text from a .txt file of 
pcc campus information. The program then capitalizes the first letter of each word, and both letters
of any state abbreviation, such as AZ. The split and capitalized information stored in the vector
is then written to a .txt file called "pcc_campuses_revised", which is stored in the project folder, along
with the original "pcc_campuses.txt" file. 

Developer: Michael Cutshall

Created: 2/10/2016
*/

#include "stdafx.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>

using namespace std;

//Create function prototype
void readFile(vector<string>&, ifstream &);
void capitalize(vector<string>&);
void fileOutput(vector<string>&);

int main()
{
	//Create ifstream for input file, and create campus string vector
	ifstream myFile("pcc_campuses.txt");
	vector<string> campuses;

	//call functions for reading in and splitting file, capitalizing text, and writting output file.
	readFile(campuses, myFile);
	capitalize(campuses);
	fileOutput(campuses);
}

//The readFile method splits the text from the input file by commas, and stores the text in a string vector.
void readFile(vector<string>& campuses, ifstream &myFile) {
	string input;

	//Read the file line by line and use stringstream to split text after finding a comma.
	if (myFile.is_open()) {
		while (getline(myFile, input)) {
			stringstream sstream(input);
			string split;

			while (getline(sstream, split, ',')) {
				campuses.push_back(split); //add split text to back/end of string vector
			}
		}
		myFile.close();

	}
	else cout << "Unable to open file." << endl;
}

//Capitalize the first letter of each word, and both letters of a state abbreviation.
void capitalize(vector<string>& campuses) {
	for (auto &s : campuses) {
		for (auto &c : s) {
			//if there are spaces before the first character and the character after the second is null/ 0
			if ((*(&c - sizeof(char) - sizeof(char))) == ' ' && (*(&c + sizeof(char)) == 0)) {
				c = toupper(c);
			}
			//if the character follows a space
			else if ((*(&c - sizeof(char))) == ' ') {
				c = toupper(c);
			}
		}
	}
}

void fileOutput(vector<string>& campuses) {

	ofstream output_file("./pcc_campuses_revised.txt");//name the output file	
	ostream_iterator<string> output_iterator(output_file, ",");//use an iterator to write text separated by a comma
	copy(campuses.begin(), campuses.end(), output_iterator);//copy elements into output_iterator range
}

