// vim:ts=8:noexpandtab
#include <SymbolTable.h>
#include <cctype>

SymbolTableElement::SymbolTableElement(const string& lexeme,
	const string& token, const unsigned int& row, const unsigned int& col)
{
	this->lexeme = lexeme;
	this->token  = token;
	this->addPosition (row, col);
}

void SymbolTableElement::addPosition (const unsigned int& row,
				      const unsigned int& col)
{
	Position tmp_position;
	tmp_position.row = row;
	tmp_position.col = col;
	positions.push_back (tmp_position);
}

string SymbolTableElement::getToken () const
{
	return this->token;
}

string SymbolTableElement::getLexeme () const
{
	return this->lexeme;
}

list<SymbolTableElement::Position> SymbolTableElement::getPositions () const
{
	return this->positions;
}

static inline unsigned int tableIndex (const string& lexeme)
{
	int index = tolower(lexeme[0] - 'a');
	return (index <= 25) ? index : 26;
}

SymbolTableElement * SymbolTable::findLexeme (const string& lexeme)
{
	unsigned int n = tableIndex(lexeme);
	list <SymbolTableElement>::iterator iter, iter_end;

	for ( iter = index[n].begin(), iter_end = index[n].end(); iter != iter_end; iter++)
	{
		if (! (iter->lexeme.compare (lexeme)) )
		{
			return &(*iter);
		}
	}

	return NULL;
}

void SymbolTable::insert (const string& lexeme, const string& token,
			  const unsigned int& row, 
			  const unsigned int& col)
{
	SymbolTableElement * element = findLexeme (lexeme);

	if (element != NULL)
	{
		element->addPosition (row, col);
	}
	else
	{
		index[tableIndex(lexeme)].push_back (SymbolTableElement(lexeme, token, row, col));
	}
}

list<SymbolTableElement::Position> 
SymbolTable::getPositions (const string& lexeme)
{
	return (this->findLexeme(lexeme))->getPositions();
}
