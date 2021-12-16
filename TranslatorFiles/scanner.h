#ifndef G13_SCANNER
#define G13_SCANNER

#include <string>
using namespace std; // Michael Snodgrass - I only use this for assignments.

// First the tables need to be declared.

// Update the tokentype to be WORD1, WORD2, PERIOD, ERROR, EOFM, etc.
enum tokentype {ERROR, WORD1, WORD2, PERIOD, VERB, VERBNEG, VERBPAST, VERBPASTNEG, IS, WAS, OBJECT, SUBJECT, DESTINATION, PRONOUN, CONNECTOR, EOFM};

extern string tokenName[];

extern std::pair<string, tokentype> reservedWords[];

extern ifstream fin;

bool word(string s);
bool period(string s);
void scanner(tokentype& tt, string& w);

#endif // G13_SCANNER
