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

// Type of error: Lexical Error.
// Done by: Michael Snodgrass 
void syntaxerror1( string savedLexeme, tokentype expectedTokenType ) {
  
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

// Type of error: ** Parser error
// Done by: ** Isaac Sayasane 
void syntaxerror2(string savedLexeme, string parserFunction)
{
  cout << "SYNTAX ERROR: unexpected " << savedLexeme << " found in "
       << parserFunction << endl;
  exit(1);
}

// ** Need the updated match and next_token with 2 global vars
// saved_token and saved_lexeme

tokentype saved_token;
string saved_lexeme;
bool token_available = false; // Set the intial value to false because next_token will automatically fill in saved_token and saved_lexeme.

// Purpose: ** Looks ahead to see what token comes next from the scanner.
// Done by: ** Isaac Sayasane
tokentype next_token()
{
  if (!token_available)   // if there is no saved token yet
    { 
      scanner(saved_token, saved_lexeme);   // call scanner to grab a new token
                                          // saved_token is the token type and 
                                    // saved_lexeme is the word that is read in
      token_available = true;          // mark that fact that you have saved it
                                    //in saved_lexme
      
      // Tell the user that the scanner is in fact called.
      cout << "Scanner called using word: " << saved_lexeme << endl;

      //DEBUG COMMENT
      //cout << "saved_token: " << tokenName[saved_token] << endl;
      if (saved_token == ERROR)
	{ 
	  syntaxerror1(saved_lexeme, saved_token);
	}
    }
  return saved_token;    // return the saved token
}

// Purpose: ** Checks and eats up the expected token.
// Done by: ** Isaac Sayasane
bool match(tokentype expected) 
{
  if (next_token() != expected)   // mismatch has occurred with the next token
    {
      // calls a syntax error function here to generate a syntax error message here and do recovery
      syntaxerror1(saved_lexeme, expected);
	}
  else  // match has occurred
    {
      token_available = false;                // eat up the token
      cout << "Matched " << tokenName[expected] << endl; // display type for 
                                                         // tracing
      return true;                            // say there was a match
    } 
}

// ----- RDP functions - one per non-term -------------------

// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function
// ** Be sure to put the name of the programmer above each function

// I added prototypes.
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
	syntaxerror2(saved_lexeme, "story");
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
  // This will call afterSubject to check if it is an afterSubject.
  afterSubject();
}

// Grammar: <after subject> := <verb> <tense> PERIOD | <noun> <after noun>
// Done by: Michael Snodgrass
void afterSubject() {
  // Tell the user that the program is now processing a sentence.
  cout << "Processing <after subject>" << endl;
  
  switch( next_token() )
  {
    // <verb> <tense> PERIOD
    // Since <verb> only has WORD2 only check WORD2.
    case tokentype::WORD2:
      // <verb>
      verb();
      // <tense>
      tense();
      // PERIOD
      match( tokentype::PERIOD );
      break;
      
    // <noun> <after noun>
    // Since <noun> can be WORD1 or PRONOUN, check WORD1 and PRONOUN.
    case tokentype::WORD1:
    case tokentype::PRONOUN:
      // <noun>
      noun();
      // <after noun>
      afterNoun();
      break;
      
    // Neither the two cases.
    default:
      // Exit the program for failing to read after the subject.
      syntaxerror2(saved_lexeme, "afterSubject");
  }
}

// Grammar: <after noun> := <be> PERIOD | DESTINATION <verb> <tense> PERIOD
//                        | OBJECT <after object>
// Done by: ** Isaac Sayasane
void afterNoun() 
{
  cout << "Processing <after noun>" << endl;
  
  switch(next_token())
    {
      // <be> PERIOD
    case tokentype::IS:
    case tokentype::WAS:
      be();
      match(tokentype::PERIOD);
      break;	
		  	
      // DESTINATION <verb> <tense> PERIOD
    case tokentype::DESTINATION:
      match(tokentype::DESTINATION);
      verb();
      tense();
      match(tokentype::PERIOD);
      break;
		  
      //OBJECT <after object>
    case tokentype::OBJECT:
      match(tokentype::OBJECT);
      afterObject();
      break;
		  
    default:
      syntaxerror2(saved_lexeme, "afterNoun");
      exit(1);
    }
}

// Grammar: <after object> := [<noun> DESTINATION] <verb> <tense> PERIOD
// Done by: Michael Snodgrass
void afterObject() {
  // Tell the user that the program is now processing a sentence.
  cout << "Processing <after object>" << endl;
  
  // [<noun> DESTINATION]
  switch( next_token() )
  {
    // Check if the next output will be a noun.
    case tokentype::WORD1:
    case tokentype::PRONOUN:
      // <noun>
      noun();
      // DESTINATION
      match( tokentype::DESTINATION );
      break;

    // If not then do not call a syntax error.
    default:
      // This time do not call syntax error.
      // If I had to check for only one tokentype this would have been an if statement.
      // It is only a choice in style and effiency.
      break;
  }
  
  // <verb>
  // Call the verb function.
  verb();
  
  // <tense>
  // Call the tense funciton.
  tense();

  // Finally match the token to the PERIOD.
  match( tokentype::PERIOD );
}

// Grammar: ** WORD1 | PRONOUN
// Done by: ** Isaac Sayasane
void noun() 
{
  cout << "Processing <noun>" << endl;
  
  switch(next_token())
    {
      //WORD1
    case tokentype::WORD1:
      match(tokentype::WORD1);
      break;
		  
      //PRONOUN
    case tokentype::PRONOUN:
      match(tokentype::PRONOUN);
      break;
		  
    default:
      syntaxerror2(saved_lexeme, "noun");
      exit(1);
    }
}

// Grammar: ** WORD2
// Done by: ** Isaac Sayasane
void verb() 
{
  cout << "Processing <verb>" << endl;

  switch(next_token())
    {
      //WORD2
    case tokentype::WORD2:
      match(tokentype::WORD2);
      break;
		  
    default:
      syntaxerror2(saved_lexeme, "verb");
      exit(1);
    }
}

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
      syntaxerror2(saved_lexeme, "be");
  };
}

// Grammar: ** VERBPAST | VERBPASTNEG | VERB | VERBNEG
// Done by: ** Isaac Sayasane
void tense() 
{
  cout << "Processing <tense>" << endl;

  switch(next_token())
    {
      // VERBPAST
    case tokentype::VERBPAST:
      match(tokentype::VERBPAST);
      break;
		  
      // VERBPASTNEG
    case tokentype::VERBPASTNEG:
      match(tokentype::VERBPASTNEG);
      break;
		  
      // VERB
    case tokentype::VERB:
      match(tokentype::VERB);
      break;
		  
      // VERBNEG
    case tokentype::VERBNEG:
      match(tokentype::VERBNEG);
      break;
		  
    default:
      syntaxerror2(saved_lexeme, "tense");
      exit(1);
    }
}

string filename;

//----------- Driver ---------------------------

// The new test driver to start the parser
// Done by: Michael Snodgrass
int main()
{
  // Tell the user to input a file name.
  cout << "Enter the input file name: ";
  
  // Get the filename from user input.
  cin >> filename;

  // Now open the file.
  fin.open(filename.c_str());
  
  if( fin.is_open() )
  {
    // call the <story> to start parsing
    story();
    
    // Tell the user that we have successfully parsed the fin file.
    cout << endl << "Successfully parsed <story>." << endl;
    
    // close the input file.
    fin.close();
    
    // I did not forget to at least return something.
    return 0;
  }
  else // The file is not open.
  {
    // Tell the user that the file cannot be opened.
    cout << "Error: cannot open \"" << filename << "\"" << endl;
    
    // Return a zero.
    return 0;
  }
}// end
//** require no other input files!
//** syntax error EC requires producing errors.txt of error messages
//** tracing On/Off EC requires sending a flag to trace message output functions
