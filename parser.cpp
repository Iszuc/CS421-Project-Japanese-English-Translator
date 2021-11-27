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

// Type of error: ** PROBABLY NOT A LEXICAL ERROR.
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
void s();
void afterSubject();
void afterNoun();
void afterObject();
void noun();
void verb();
void be();
void tense();

// Grammar: <story> := <s> { <s> }
// Done by: Michael Snodgrass
void story() {
  // Tell the user that the program is now processing story.
  cout << "Processing <story>\n" << endl;
  
  // <s>
  // First process sentence which is <s>
  s();

  // { <s> }  
  // Loop until the end conditions are meet.
  while( true )
  {
    // Check if the next token to be read has this.
    switch( next_token() )
    {
      // Check if this is actually the end.
      case tokentype::EOFM:
        // Exit the program peacefully.
        return;
      // next_token has to be CONNECTOR or WORD1 or PRONOUN in order to be s, sentence.
      case tokentype::CONNECTOR:
      case tokentype::WORD1:
      case tokentype::PRONOUN:
        s(); // Call s to check if this is a sentence.
        break; // exit this switch statement for now.
      // if next_token is something else exit the program.
      default:
        cout << "TODO Add a syntax error!" << endl;
        exit(1);
    }
  }
}

// Grammar: <s> := [CONNECTOR] <noun> SUBJECT <after subject>
// Done by: Michael Snodgrass
void s() {
  // Tell the user that the program is now processing a sentence.
  cout << "Processing <s>" << endl;
  
  // [CONNECTOR]
  // This tests for the CONNECTOR token.
  if( next_token() == tokentype::CONNECTOR )
  {
    // match the tokentype::CONNECTOR.
    match( tokentype::CONNECTOR );
    // match should always succeed at this point.
  }
  
  // <noun>
  // This will call noun to check if it is a noun.
  noun();
  
  // SUBJECT
  // See if subject is called.
  match( tokentype::SUBJECT );
  
  // <after subject>
  // See if afterSubject is called.
  afterSubject();
}

// Grammar: **
// Done by: **
void afterSubject() {}

// Grammar: **
// Done by: **
void afterNoun() {}

// Grammar: **
// Done by: **
void afterObject() {}

// Grammar: **
// Done by: **
void noun() {}

// Grammar: **
// Done by: **
void verb() {}

// Grammar: <be> := IS | WAS
// Done by: Michael Snodgrass
void be() {
  // Tell the user that the program is now processing forms of be.
  cout << "Processing <be>" << endl;
  
  // IS | WAS
  switch( next_token() )
  {
    // IS
    // If next_token is an IS type then match it.
    case tokentype::IS:
      match( tokentype::IS );
      break;
    // WAS
    // If next_token is a WAS type then match it.
    case tokentype::WAS:
      match( tokentype::WAS );
      break;
    // If next_token is some other type then it is a syntax error.
    default:
      // Throw a syntax error.
      cout << "TODO Add a syntax error!" << endl;
      exit( 1 );
  };
}

// Grammar: **
// Done by: **
void tense() {}

string filename;

//----------- Driver ---------------------------

// The new test driver to start the parser
// Done by: Michael Snodgrass
int main()
{
  cout << "Enter the input file name: ";
  cin >> filename;
  fin.open(filename.c_str());

  //** calls the <story> to start parsing
  story();
  
  //** closes the input file
  fin.close();
  
  // I did not forget to at least return something.
  return 0;
}// end
//** require no other input files!
//** syntax error EC requires producing errors.txt of error messages
//** tracing On/Off EC requires sending a flag to trace message output functions
