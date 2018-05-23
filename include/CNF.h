//
//  CNF.h
//  CYKAlgorithm
//
//  Created by Mengzhang Qian on 2018/5/6.
//  Copyright © 2018 QMZ. All rights reserved.
//

#ifndef _CNF_H_
#define _CNF_H_

#include <iostream>
#include <string>
#include <vector>
#include <set>

typedef std::string Variable;
typedef std::string Terminal;

//************************************************************************************
//Implement a production rule with only non-terminal strings(variables)
class ProductionRuleWithNonterminal {
private:
	Variable name;
	Variable v1, v2;

public:
	//Constructors
	ProductionRuleWithNonterminal();
	ProductionRuleWithNonterminal(Variable name, Variable v1, Variable v2);
	//Change the production rule
	void changeRule(Variable name, Variable v1, Variable v2);
	//Judge whether two variables v1 and v2 can produce a variable through the production
	//Return value: the name of the produced variable or "" if they can't
	Variable produce(Variable v1, Variable v2) const;
	//Print the production
	void print() const;
	//Get the name of the variable that the production produces
	Variable getName() const;
};

//************************************************************************************
//Implement a production rule with variable in left and terminal string in right
class ProductionRuleWithTerminal {
private:
	Variable name;
	Terminal str;

public:
	//Constructors
	ProductionRuleWithTerminal();
	ProductionRuleWithTerminal(Variable name, Terminal str);
	//Change the production rule
	void changeRule(Variable name, Terminal str);
	//Judge whether a string str can produce a variable through the production
	//Return value: the name of the produced variable or "" if it can't
	Variable produce(Terminal str) const;
	//Print the production
	void print() const;
	//Get the name of the variable that the production produces
	Variable getName() const;
};

//************************************************************************************
//Implement a Chomsky normal form CFG
class CNF {
private:
	std::vector<ProductionRuleWithNonterminal> rulesWithNonterminal;
	std::vector<ProductionRuleWithTerminal> rulesWithTerminal;
	Variable startSymbol;

public:
	//Get the set of variables that the two sets of variable val1, val2 can produce
	std::set<Variable> produce(std::set<Variable> val1, std::set<Variable> val2) const;
	//Get the set of variables that the string str can produce
	std::set<Variable> produce(Terminal str) const;
	//Add a production rule
	void addRule(ProductionRuleWithNonterminal rule);
	//Add a production rule
	void addRule(ProductionRuleWithTerminal rule);
	//Get the start symbol of the CFG
	Variable getStartSymbol() const;
	//Print the CFG
	void print() const;
};

#endif
