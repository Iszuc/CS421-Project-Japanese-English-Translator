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

// TABLES Done by: ** Michael Snodgrass

// ** Update the tokentype to be WORD1, WORD2, PERIOD, ERROR, EOFM, etc.
enum tokentype {ERROR, WORD1, WORD2, PERIOD, VERB, VERBNEG, VERBPAST, VERBPASTNEG, IS, WAS, OBJECT, SUBJECT, DESTINATION, PRONOUN, CONNECTOR, EOFM};

// ** For the display names of tokens - must be in the same order as the tokentype.
string tokenName[30] = { "ERROR", "WORD1", "WORD2", "PERIOD", "VERB", "VERBNEG", "VERBPAST", "VERBPASTNEG", "IS", "WAS", "OBJECT", "SUBJECT", "DESTINATION", "PRONOUN", "CONNECTOR", "EOFM" }; 

// ** Need the reservedwords table to be set up here. 
// ** Do not require any file input for this. Hard code the table.
// ** a.out should work without any additional files.


// ------------ Scaner and Driver ----------------------- 

ifstream fin;  // global stream for reading from the input file

// Scanner processes only one word each time it is called
// Gives back the token type and the word itself
// ** Done by: Michael Snodgrass
int scanner(tokentype& tt, string& w)
{
  // ** Grab the next word from the file via fin
  fin >> w;
  
  // 1. If it is eofm, return right now.   
  if( w.compare( "eofm" ) == 0 )
    return 0; // NOTE: Michael Snodgrass - I do not know what to return for this actually since scanner call is not being used as a parameter.
  
  if( word( w ) ) // If w is a Japanese word
  {
    // Then check what exactly w is.
    // This if then else statement will set tt to what word is.

    // TODO Set tt to VERB. ----------------------------------------------------------------
    // TODO Set tt to VERBNEG. -------------------------------------------------------------
    // TODO Set tt to VERBPAST. ------------------------------------------------------------
    // TODO Set tt to VERBPASTNEG. ---------------------------------------------------------
    if( w.compare( "desu" ) == 0 ) // If w is desu, then w is a "IS" word.
        tt = IS; // Return the IS type.
    else // If w is deshita, then w is a "WAS" word.
    if( w.compare( "deshita" ) == 0 )
        tt = WAS; // Return the WAS type.
    else // If w is o, then w is an OBJECT word.
    if( w.compare( "o" ) == 0 )
        tt = OBJECT; // Return the OBJECT type.
    else // If w is wa, then w is a SUBJECT word.
    if( w.compare( "wa" ) == 0 )
        tt = SUBJECT; // Return the SUBJECT type.
    else // If w is ni, then w is a DESTINATION word.
    if( w.compare( "ni" ) == 0 )
        tt = DESTINATION; // Return the DESTINATION type.
    // TODO Set tt to PRONOUN. --------------------------------------------------------------
    else // If w is mata, soshite, shikashi, and dakara then w is a CONNECTOR word.
    if( w.compare( "mata" ) == 0 || w.compare( "soshite" ) == 0  || w.compare( "shikashi" ) == 0 || w.compare( "dakara" ) == 0 )
        tt = CONNECTOR; // Return the CONNECTOR type.
    // TODO Set tt to WORD2. ----------------------------------------------------------------
    else // If w is not WORD2, then w is WORD1
        tt = WORD1; // Return the WORD1 type.
  }
  else // If w is just a peroid
  if( period( w ) )
  {
    tt = PERIOD; // Set the token type to error.
  }
  else // If w is unrecognized.
  {
    tt = ERROR; // Set the token type to error.
  }
  
  /*  **
  2. Call the token functions (word and period) 
     one after another (if-then-else).
     Generate a lexical error message if both DFAs failed.
     Let the tokentype be ERROR in that case.
  3. If it was a word,
     check against the reservedwords list.
     If not reserved, tokentype is WORD1 or WORD2
     decided based on the last character.
  4. Return the token type & string  (pass by reference)
  */

}//the end of scanner




// The temporary test driver to just call the scanner repeatedly  
// This will go away after this assignment
// DO NOT CHANGE THIS!!!!!! 
// Done by:  Rika
int main()
{
  tokentype thetype;
  string theword; 
  string filename;

  cout << "Enter the input file name: ";
  cin >> filename;

  fin.open(filename.c_str());

  // the loop continues until eofm is returned.
   while (true)
    {
       scanner(thetype, theword);  // call the scanner which sets
                                   // the arguments  
       if (theword == "eofm") break;  // stop now

       cout << "Type is:" << tokenName[thetype] << endl;
       cout << "Word is:" << theword << endl;   
    }

   cout << "End of file is encountered." << endl;
   fin.close();

}// end

