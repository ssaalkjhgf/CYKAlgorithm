//
//  CYKAlgorithm.cpp
//  CYKAlgorithm
//
//  Created by Mengzhang Qian on 2018/5/6.
//  Copyright © 2018 QMZ. All rights reserved.
//

#include <string>
#include <iostream>
#include <fstream>
#include "../include/CNF.h"
using namespace std;

//************************************************************************************
//Load a Chomsky normal form CFG from a file
void loadCNF(CNF& cnf, string file);

//************************************************************************************
//Split a string in regard to character c
vector<string> split(string str, char c);

//************************************************************************************
//Use CYK algorithm to judge whether the string str is in the Chomsky normal form CFG
bool CYK(string str, const CNF& cnf);

//************************************************************************************
//main function
int main(int argc, const char** argv)
{
	if (argc != 2) {
		cout << "Invalid input!\n";
		exit(3);
	}	
	CNF cnf;
	loadCNF(cnf, argv[1]);
	//cnf.print();
	string str;
	cout << "Please input a string: ";
	getline(cin, str);
	if (CYK(str, cnf)) {
		cout << "Accept!\n";
	}
	else {
		cout << "Reject!\n";
	}
    return 0;
}

//************************************************************************************
//Split a string in regard to character c
vector<string> split(string str, char c) {
	vector<string> segments;
	string tmp;
	for (size_t i = 0; i < str.length(); i++) {
		if (str[i] == c) {
			if (tmp != "")
				segments.push_back(tmp);
			tmp = "";
		}
		else {
			tmp = tmp + str[i];
		}
	}
	if (tmp != "")
		segments.push_back(tmp);
	return segments;
}

//************************************************************************************
//Load a Chomsky normal form CFG from a file
void loadCNF(CNF& cnf, string file) {
	fstream fin(file);
	//If failed to open the file
	if (fin.fail()) {
		cout << "Cannot open input file!\n";
		exit(1);
	}
	string rule;
	//Read one line in the file one time
	while (getline(fin, rule)) {
		int namePos = rule.find("->");
		//Not found "->"
		if (namePos == string::npos) {
			cout << "Invalid input file!\n";
			exit(2);
		}
		Variable name;
		//Get the name of the variable that the rule produces
		for (int i = 0; i < namePos; i++) {
			name = name + rule[i];
		}
		Variable restRule;
		//Get the rest part of the rule
		for (size_t i = namePos + 2; i < rule.length(); i++) {
			restRule = restRule + rule[i];
		}
		//Get all the rules of this production by dividing the rest part of the rule with '|'
		vector<string> rules = split(restRule, '|');
		//For each rules, add it into the Chomsky normal form CFG respectively
		for (auto i = rules.begin(); i != rules.end(); i++) {
			int spacePos = i->find(' ');
			//No spaces, the rule is with a terminal string
			if (spacePos == string::npos) {
				ProductionRuleWithTerminal p(name, *i);
				cnf.addRule(p);
				continue;
			}
			//Has spaces, the rule is with two variables
			string val1, val2;
			for (int k = 0; k < spacePos; k++) {
				val1 = val1 + (*i)[k];
			}
			for (size_t k = spacePos + 1; k < i->length(); k++) {
				val2 = val2 + (*i)[k];
			}
			ProductionRuleWithNonterminal p(name, val1, val2);
			cnf.addRule(p);
		}
	}
}

//************************************************************************************
//Use CYK algorithm to judge whether the string str is in the Chomsky normal form CFG
bool CYK(string str, const CNF& cnf) {
	//Get each word in the string str
	vector<string> sentence = split(str, ' ');
	int wordCount = sentence.size();

	//Allocate memory for CYKMat, a matrix of set storing all the parsing conditions of str[i..j]
	set<Variable>** CYKMat = new set<Variable>*[wordCount + 1];
	for (int i = 0; i <= wordCount; i++) {
		CYKMat[i] = new set<Variable>[wordCount + 1];
	}

	//Preprocess the words, get the CYKMat[i][i]
	for (int i = 1; i <= wordCount; i++) {
		CYKMat[i][i] = cnf.produce(sentence[i - 1]);
	}
	//Calculate the rest part of CYKMat
	//For each length
	for (int length = 2; length <= wordCount; length++) {
		//For each starting position
		for (int i = 1; i <= wordCount - length + 1; i++) {
			//For each middle point of str[i..i+length-1]
			for (int k = i; k < i + length - 1; k++) {
				//Get the set of variables that CYKMat[i][k] and CYKMat[k+1][i+length-1] can produce
				set<Variable> tmp = cnf.produce(CYKMat[i][k], CYKMat[k + 1][i + length - 1]);
				//Union
				CYKMat[i][i + length - 1].insert(tmp.begin(), tmp.end());
			}
		}
	}

	//If CYKMat[1][wordCount] consists of the starting symbol, accept the string
	if (CYKMat[1][wordCount].find(cnf.getStartSymbol()) == CYKMat[1][wordCount].end())
		return false;
	else
		return true;
}
