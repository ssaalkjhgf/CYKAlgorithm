//
//  CNF.cpp
//  CYKAlgorithm
//
//  Created by Mengzhang Qian on 2018/5/6.
//  Copyright © 2018 QMZ. All rights reserved.
//

#include "../include/CNF.h"

//************************************************************************************
//Constructor
ProductionRuleWithNonterminal::ProductionRuleWithNonterminal() {

}

//************************************************************************************
//Constructor
ProductionRuleWithNonterminal::ProductionRuleWithNonterminal(Variable name, Variable v1, Variable v2) {
	this->name = name;
	this->v1 = v1;
	this->v2 = v2;
}

//************************************************************************************
//Change the production rule
void ProductionRuleWithNonterminal::changeRule(Variable name, Variable v1, Variable v2) {
	this->name = name;
	this->v1 = v1;
	this->v2 = v2;
}

//************************************************************************************
//Judge whether two variables v1 and v2 can produce a variable through the production
//Return value: the name of the produced variable or "" if they can't
Variable ProductionRuleWithNonterminal::produce(Variable v1, Variable v2) const {
	if (v1 == this->v1 && v2 == this->v2)
		return name;
	else {
		Variable fail = "";
		return fail;
	}
}

//************************************************************************************
//Print the production
void ProductionRuleWithNonterminal::print() const {
	std::cout << name << "->" << v1 << ' ' << v2 << std::endl;
}

//************************************************************************************
//Get the name of the variable that the production produces
Variable ProductionRuleWithNonterminal::getName() const {
	return name;
}

//************************************************************************************
//Constructor
ProductionRuleWithTerminal::ProductionRuleWithTerminal() {

}

//************************************************************************************
//Constructor
ProductionRuleWithTerminal::ProductionRuleWithTerminal(Variable name, Terminal str) {
	this->name = name;
	this->str = str;
}

//************************************************************************************
//Change the production rule
void ProductionRuleWithTerminal::changeRule(Variable name, Terminal str) {
	this->name = name;
	this->str = str;
}

//************************************************************************************
//Judge whether a string str can produce a variable through the production
//Return value: the name of the produced variable or "" if it can't
Variable ProductionRuleWithTerminal::produce(Terminal str) const {
	if (this->str == str)
		return name;
	else {
		Variable fail = "";
		return fail;
	}
}

//************************************************************************************
//Print the production
void ProductionRuleWithTerminal::print() const {
	std::cout << name << "->" << str << std::endl;
}

//************************************************************************************
//Get the name of the variable that the production produces
Variable ProductionRuleWithTerminal::getName() const {
	return name;
}

//************************************************************************************
//Get the set of variables that the two sets of variable val1, val2 can produce
std::set<Variable> CNF::produce(std::set<Variable> val1, std::set<Variable> val2) const {
	std::set<Variable> vals;
	for (auto rule = rulesWithNonterminal.begin(); rule != rulesWithNonterminal.end(); rule++) {
		for (auto i = val1.begin(); i != val1.end(); i++) {
			for (auto k = val2.begin(); k != val2.end(); k++) {
				Variable val = rule->produce(*i, *k);
				if (val != "")
					vals.insert(val);
			}
		}
	}
	return vals;
}

//************************************************************************************
//Get the set of variables that the string str can produce
std::set<Variable> CNF::produce(Terminal str) const {
	std::set<Variable> vals;
	for (auto i = rulesWithTerminal.begin(); i != rulesWithTerminal.end(); i++) {
		Variable val = i->produce(str);
		if (val != "")
			vals.insert(val);
	}
	return vals;
}

//************************************************************************************
//Add a production rule
void CNF::addRule(ProductionRuleWithNonterminal rule) {
	rulesWithNonterminal.push_back(rule);
}

//************************************************************************************
//Add a production rule
void CNF::addRule(ProductionRuleWithTerminal rule) {
	rulesWithTerminal.push_back(rule);
}

//************************************************************************************
//Get the start symbol of the CFG
Variable CNF::getStartSymbol() const {
	return rulesWithNonterminal[0].getName();
}

//************************************************************************************
//Print the CFG
void CNF::print() const {
	for (auto i = rulesWithNonterminal.begin(); i != rulesWithNonterminal.end(); i++) {
		i->print();
	}
	for (auto i = rulesWithTerminal.begin(); i != rulesWithTerminal.end(); i++) {
		i->print();
	}
}
