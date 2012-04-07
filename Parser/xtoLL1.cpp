#include <cctype>
#include <fstream>
#include <sstream>
#include <xtoLL1.hpp>
#include <Terminal_NonTerminal.hpp>
using namespace std;

void ScanGrammarFromFile(Grammar& g, char* filename)
{
	ifstream f(filename);
	string s, t;
	bool ishead = true;
	vector<std::string> tail;
	do
	{
		getline(f, s, '\n');
		
		if(!s.compare("") || s[0] == '#')
			continue;
		else
		{
			ishead = true;
			Rule *r;
			stringstream ss(s);
			while(getline(ss, t, ' '))
			{
				if(!t.compare("-->"))
				{
					ishead = false;
					continue;
				}
				else if(!t.compare("|"))
				{
					r->RuleAddTail(tail);
					tail.clear();
				}
				else if(ishead)
				{
					r = new Rule(t);
					addNonTerminal(t);
				}
				else
				{
					tail.push_back(t);
					if(isupper(t[0]))
						addNonTerminal(t);
					else
						addTerminal(t);
				}
			}
			r->RuleAddTail(tail);
			tail.clear();
			g.GrammarAddRule(*r);
			//r.~Rule();
		}
	}while(f.good());
	f.close();
}

static bool HasCycles(Grammar& g, Rule r, std::string rhead)
{
	std::string t;
	int ti;
	for(int i = 0; i < r.RuleNTails(); i++)
		if(r.RuleTail(i).size() == 1)
		{
			t = r.RuleTail(i)[0];
			if(!rhead.compare(t))
				return true;
			else if((ti = g.GrammarFindRule(t)) >= 0)
				return HasCycles(g, g.GrammarRule(ti), rhead);
		}
	return false;
}

bool HasCycles(Grammar& g)	// wrapper for the above function
{
	for(int i = 0; i < g.GrammarNRules(); i++)
		if(HasCycles(g, g.GrammarRule(i), g.GrammarRule(i).RuleHead()))
			return true;
	return false;
}

bool HasNonTerminatingRules(Grammar& g)
{
	Rule r;
	vector<std::string> tail;
	int tail_nonterminals;
	bool headmatches;
	std::string head;
	for(int i = 0; i < g.GrammarNRules(); i++)
	{
		r = g.GrammarRule(i);
		cerr<<"HasNonTerminatingRules():r = ";
		r.RuleOutput();
		head = r.RuleHead();
		cerr<<"HasNonTerminatingRules():head = "<<head<<endl;
		for(int j = 0; j < r.RuleNTails(); j++)
		{
			tail = r.RuleTail(j);
			cerr<<"HasNonTerminatingRules():tail.size() = "<<tail.size()<<endl;
			cerr<<"HasNonTerminatingRules():tail = ";
			for(int k = 0; k < tail.size(); k++)
				cerr<<tail[k]<<" ";
			cerr<<endl;
			tail_nonterminals = 0;
			headmatches = false;
			for(int k = 0; k < tail.size(); k++)
			{
				if(!head.compare(tail[k]))
					headmatches = true;
				if(isNonTerminal(tail[k]))
					tail_nonterminals++;
			}
			cerr<<"HasNonTerminatingRules():headmatches = "<<headmatches<<endl;
			cerr<<"HasNonTerminatingRules():tail_nonterminals = "<<tail_nonterminals<<endl;
			if(tail_nonterminals == 1 && headmatches)
				return true;
		}
	}
	return false;
}

void EliminateEpsilonProductions(Grammar& g)
{
	return;
}

void EliminateLeftRecursion(Grammar& g)
{
	return;
}

void LeftFactorize(Grammar& g)
{
	return;
}
