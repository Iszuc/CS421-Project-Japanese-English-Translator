#include "scanner.h"

#include<iostream>
#include<fstream>
#include<string>
using namespace std;

/* Look for all **'s and complete them */

//=====================================================
// File scanner.cpp written by: Group Number: ** 13
//=====================================================

// --------- Two DFAs ---------------------------------

// WORD DFA
// Done by: ** Isaac Sayasane
// RE:   ** (V | Vn | consonant V | consonant V n | consonant-pair V |
//          consonant-pair V n)^+
bool word (string s)
{

  int state = 0;
  int charpos = 0;
  /* replace the following todo the word dfa  */
  /*State names to numbers
    q0 = 0   qc = 1   qs = 2
    qsa = 3  qt = 4   qy = 5
    q0q1 = 6
   */

  //character "arrays"
  string V = "aiueoIE";
  string endConsonants = "dwzyj";
  string startConsonants = "bghkmnpr";
  string start2Consonants = "bghkmpr";

  while (s[charpos] != '\0')
    {
      //Trs q0
      if (state == 0 && s[charpos] == 'c')
      state = 1;
      else
      if (state == 0 && s[charpos] == 's')
      state = 2;
      else
      if (state == 0 && s[charpos] == 't')
      state = 4;
      else
      if (state == 0 && V.find(s[charpos]) != string::npos)
      state = 6;
      else
      if (state == 0 && endConsonants.find(s[charpos]) != string::npos)
      state = 3;
      else
      if (state == 0 && startConsonants.find(s[charpos]) != string::npos)
      state = 5;
      else

      //Trs qc
      if (state == 1 && s[charpos] == 'h')
      state = 3;
      else

      //Trs qs
      if (state == 2 && s[charpos] == 'h')
      state = 3;
      else
      if (state == 2 && V.find(s[charpos]) != string::npos)
      state = 6;
      else

      //Trs qsa
      if (state == 3 && V.find(s[charpos]) != string::npos)
      state = 6;
      else

      //Trs qt
      if (state == 4 && s[charpos] == 's')
      state = 3;
      else
      if (state == 4 && V.find(s[charpos]) != string::npos)
      state = 6;
      else

      //Trs qy
      if (state == 5 && s[charpos] == 'y')
      state = 3;
      else
      if (state == 5 && V.find(s[charpos]) != string::npos)
      state = 6;
      else

      //Trs q0q1
      if (state == 6 && s[charpos] == 'n')
      state = 0;
      else
      if (state == 6 && s[charpos] == 'c')
      state = 1;
      else
      if (state == 6 && s[charpos] == 's')
      state = 2;
      else
      if (state == 6 && s[charpos] == 't')
      state = 4;
      else
      if (state == 6 && V.find(s[charpos]) != string::npos)
      state = 6;
      else
      if (state == 6 && endConsonants.find(s[charpos]) != string::npos)
      state = 3;
      else
      if (state == 6 && start2Consonants.find(s[charpos]) != string::npos)
      state = 5;
      else
	return(false);
      charpos++;
    }//end of while

  // where did I end up????
  if (state == 0 || state == 6) return(true);  // end in a final state
  else return(false);                          // (q0 or q0q1)
}

// PERIOD DFA
// Done by: ** Isaac Sayasane
bool period (string s)
{  // complete this **
  int state = 0;
  int charpos = 0;

  while (s[charpos] != '\0')
    {
      if (state == 0 && s[charpos] == '.')
      state = 1;
      else
	return(false);
      charpos++;
    } //end of while

// where did I end up????
if (state == 1) return(true);  // end in a final state
 else return(false);
}

// ------ Three  Tables -------------------------------------

// TABLES Done by: ** Michael Snodgrass (tokentype and tokenname), Logan Schlick (reservedWords)

// tokentype moved to header.

// ** For the display names of tokens - must be in the same order as the tokentype.
string tokenName[30] = { "ERROR", "WORD1", "WORD2", "PERIOD", "VERB", "VERBNEG", "VERBPAST", "VERBPASTNEG", "IS", "WAS", "OBJECT", "SUBJECT", "DESTINATION", "PRONOUN", "CONNECTOR", "EOFM" };

// ** Need the reservedwords table to be set up here.
// ** Do not require any file input for this. Hard code the table.
// ** a.out should work without any additional files.

std::pair<string, tokentype> reservedWords[19] =
{
	{"masu", VERB},
	{"masen", VERBNEG},
	{"mashita", VERBPAST},
	{"masendeshita", VERBPASTNEG},
	{"desu", IS},
	{"deshita", WAS},
	{"o", OBJECT},
	{"wa", SUBJECT},
	{"ni", DESTINATION},
	{"watashi", PRONOUN},
	{"anata", PRONOUN},
	{"kare", PRONOUN},
	{"kanoio", PRONOUN},
	{"sore", PRONOUN},
	{"mata", CONNECTOR},
	{"soshite", CONNECTOR},
	{"shikashi", CONNECTOR},
	{"dakara", CONNECTOR},
	{"eofm", EOFM}
};

// ------------ Scaner and Driver -----------------------

ifstream fin;  // global stream for reading from the input file

// Scanner processes only one word each time it is called
// Gives back the token type and the word itself
// ** Done by: Michael Snodgrass & Logan Schlick
void scanner(tokentype& tt, string& w)
{
  // ** Grab the next word from the file via fin
  fin >> w;
  
  if( w == "eofm" ) // If w is eofm then,
  {
    tt = EOFM; // The token type is EOFM.
    return; // Return now.
  }
  else
  if( word( w ) ) // If w is a Japanese word
  {
    // Compare w against each reserved word.
    for(int i = 0; i < 19; i++)
    {
      if(reservedWords[i].first == w) // If w is a reserved word,
      {
        tt = reservedWords[i].second; // Set tt to the token type of the reserved word.
	      return; // End the function early.
      }
    }
    // If this point is reached, then w is not a reserved word.
    if(w.back() == 'I' || w.back() == 'E') // If w ends in I or E,
    {
      tt = WORD2; // Then it's token type is WORD2.
    }
    else // If w ends in a lowercase vowel,
    {
      tt = WORD1; // Then it's token type is WORD1.
    }
  }
  else // If w is just a period
  if( period( w ) )
  {
    tt = PERIOD; // Set the token type to period.
  }
  else // If w is unrecognized.
  {
    // Tell the user that there had been a Lexical error.
    cout << "Lexical error: " << w << " is not a valid token" << endl;
    tt = ERROR; // Set the token type to error.
  }
}//the end of scanner
