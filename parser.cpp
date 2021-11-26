#include "scanner.h"

#include<iostream>
#include<fstream>
#include<string>
using namespace std;

/* INSTRUCTION:  Complete all ** parts.
   You may use any method to connect this file to scanner.cpp
   that you had written.  
  e.g. You can copy scanner.cpp here by:
          cp ../ScannerFiles/scanner.cpp .  
       and then append the two files into one: 
          cat scanner.cpp parser.cpp > myparser.cpp
*/

//=================================================
// File parser.cpp written by Group Number: 13
//=================================================

// ----- Four Utility Functions and Globals -----------------------------------

// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)
//    to display syntax error messages as specified by me.  

// Type of error: ** Lexer error.
// Done by: Michael Snodgrass 
void syntaxerror1( tokentype expectedTokenType, string savedLexeme ) {
  // This makes sure that expectedTokenType has a valid enum state
  if( expectedTokenType > tokentype::EOFM || expectedTokenType < tokentype::ERROR )
  {
    // If this branch is taken then there is something wrong with this program.
    
    // The programmer needs to know this error.
    cerr << "PROGRAMMER ERROR: for void syntaxerror1( ... ) the parameter tokentype expectedTokenType is " << expectedTokenType
         << " which is not in the enum tokentype." << endl;
    
    // To prevent an out of bounds case we set expectedTokenType to ERROR. 
    expectedTokenType = tokentype::ERROR; 
  }
  
  // Tell the user that the syntax error is found.
  cout << "SYNTAX ERROR: expected " << tokenName[ expectedTokenType ] << " but found " << savedLexeme << endl;
  
  // Exit the program.
  exit(1);
}

// Type of error: **
// Done by: ** 
void syntaxerror2(  ) {    }

// ** Need the updated match and next_token with 2 global vars
// saved_token and saved_lexeme

// Purpose: **
// Done by: **
tokentype next_token(){}

// Purpose: **
// Done by: **
bool match(tokentype expected) {}

// ----- RDP functions - one per non-term -------------------

// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function
// ** Be sure to put the name of the programmer above each function

// Grammar: **
// Done by: **

string filename;

//----------- Driver ---------------------------

// The new test driver to start the parser
// Done by:  **
int main()
{
  cout << "Enter the input file name: ";
  cin >> filename;
  fin.open(filename.c_str());

  //** calls the <story> to start parsing
  //** closes the input file 

}// end
//** require no other input files!
//** syntax error EC requires producing errors.txt of error messages
//** tracing On/Off EC requires sending a flag to trace message output functions
