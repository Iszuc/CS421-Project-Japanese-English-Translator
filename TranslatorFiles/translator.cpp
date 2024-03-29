
#include "scanner.h"

#include<iostream>
#include<fstream>
#include<string>
using namespace std;

// INSTRUCTION: Complete all ** parts.

//=================================================
// File translator.cpp written by Group Number: 13
//=================================================

// ----- Additions to the parser.cpp ---------------------

// ** Declare Lexicon (i.e. dictionary) that will hold the content of lexicon.txt
// Make sure it is easy and fast to look up the translation.
// Do not change the format or content of lexicon.txt 
//  Done by: ** Isaac Sayasane
const int SIZE = 50; //About 50 words are in our lexicon.txt
string Lexicon[SIZE][2]; 

tokentype saved_token;
string saved_lexeme;
string saved_E_word; // This is the saved English word if an English word is found otherwise it is a Japanese word.
bool token_available = false; // Set the intial value to false because next_token will automatically fill in saved_token and saved_lexeme.
ofstream translated_output;

//    getEword() - using the current saved_lexeme, look up the English word
//                 in Lexicon if it is there -- save the result   
//                 in saved_E_word
//  Done by: ** Isaac Sayasane
void getEword()
{
  //Default to Japanese word incase it is not found
  saved_E_word = saved_lexeme;
  for(int i = 0; i < SIZE; i++)
    {
      //Save the English word instead if found
      if(saved_lexeme == Lexicon[i][0]){
	saved_E_word = Lexicon[i][1]; 
	return;
      }
    }
}  

//    gen(line_type) - using the line type,
//                     sends a line of an IR to translated.txt
//                     (saved_E_word or saved_token is used)
//  Done by: Michael Snodgrass
void gen( string line_type ) {
  // Start by printing out "line_type: "
  translated_output << line_type << ": ";
  
  // If the line_type happens to be tense.
  if(line_type == "TENSE")
    // Then output the token name of the token.
    translated_output << tokenName[ saved_token ];
  else // If the line_type is something else entirely.
    // Then output the saved English or Japanese word.
    translated_output << saved_E_word;
  
  // Finally print the end of the line!
  translated_output << endl;
}

// ----- Four Utility Functions and Globals -----------------------------------

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
  cout << "SYNTAX ERROR: Expected " << tokenName[ expectedTokenType ] << " but found " << savedLexeme << endl;
  
  // Exit the program.
  exit(1);
}

// Type of error: ** Parser error
// Done by: ** Isaac Sayasane 
void syntaxerror2(string savedLexeme, string parserFunction)
{
  cout << "SYNTAX ERROR: Unexpected " << savedLexeme << " found in "
       << parserFunction << endl;
  exit(1);
}

// ** Need the updated match and next_token with 2 global vars
// saved_token and saved_lexeme

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

// Make each non-terminal into a function here
// Be sure to put the corresponding grammar rule above each function
// Be sure to put the name of the programmer above each function

// I added prototypes.
void s();
void afterSubject();
void afterNoun();
void afterObject();
void noun();
void verb();
void be();
void tense();

// ----- Changes to the parser.cpp content ---------------------

// ** Comment update: Be sure to put the corresponding grammar
//    rule with semantic routine calls
//    above each non-terminal function

// ** Each non-terminal function should be calling
//    getEword and/or gen now.


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

// Grammar: <s> := [CONNECTOR #getEword# #gen(“CONNECTOR”)#] <noun> #getEword# SUBJECT #gen(“ACTOR”)# <after subject>
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
    
    // #getEword#
    getEword();
    
    // Output: "CONNECTOR: SomeEnglishWord"
    gen( "CONNECTOR" );
  }
  
  // <noun>
  // This will call noun to check if it is a noun.
  noun();
  
  // #getEword#
  getEword();
  
  // SUBJECT
  // See if subject is called.
  match( tokentype::SUBJECT );
  
  // Output: "ACTOR: SomeEnglishWord"
  gen( "ACTOR" );
  
  // <after subject>
  // This will call afterSubject to check if it is an afterSubject.
  afterSubject();
  
  // Add some spacing to the file.
  translated_output << endl;
}

// Grammar: <after subject> := <verb> #getEword# #gen(“ACTION”)# <tense> #gen(“TENSE”)# PERIOD | <noun> #getEword# <after noun>
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
      
      // #getEword#
      getEword();
      
      // Output: "ACTION: SomeEnglishWord"
      gen( "ACTION" );
      
      // <tense>
      tense();
      
      // Output: "TENSE: SomeEnglishWord"
      gen("TENSE");
      
      // PERIOD
      match( tokentype::PERIOD );
      break;
      
    // <noun> <after noun>
    // Since <noun> can be WORD1 or PRONOUN, check WORD1 and PRONOUN.
    case tokentype::WORD1:
    case tokentype::PRONOUN:
      // <noun>
      noun();
      
      // #getEword#
      getEword();
      
      // <after noun>
      afterNoun();
      break;
      
    // Neither the two cases.
    default:
      // Exit the program for failing to read after the subject.
      syntaxerror2(saved_lexeme, "afterSubject");
  }
}

// Grammar: <after noun> := <be> #gen(“DESCRIPTION”)# #gen(“TENSE”)# PERIOD | 
//                          DESTINATION #gen(“TO”)# <verb> #getEword# #gen(“ACTION”)# <tense> #gen(“TENSE”)# PERIOD | 
//                          OBJECT #gen(“OBJECT”)# <after object>
// Done by: ** Isaac Sayasane
void afterNoun() 
{
  cout << "Processing <after noun>" << endl;
  
  switch(next_token())
    {
      // <be> #gen(“DESCRIPTION”)# #gen(“TENSE”)# PERIOD
    case tokentype::IS:
    case tokentype::WAS:
      be();
      gen("DESCRIPTION");
      gen("TENSE");
      match(tokentype::PERIOD);
      break;	
		  	
      // DESTINATION #gen(“TO”)# <verb> #getEword# #gen(“ACTION”)# <tense> #gen(“TENSE”)# PERIOD
    case tokentype::DESTINATION:
      match(tokentype::DESTINATION);
      gen("TO");
      verb();
      getEword();
      gen("ACTION");
      tense();
      gen("TENSE");
      match(tokentype::PERIOD);
      break;
		  
      //OBJECT #gen(“OBJECT”)# <after object>
    case tokentype::OBJECT:
      match(tokentype::OBJECT);
      gen("OBJECT");
      afterObject();
      break;
		  
    default:
      syntaxerror2(saved_lexeme, "afterNoun");
      exit(1);
    }
}

// Grammar: <after object> := <verb> #getEword# #gen(“ACTION”)# <tense> #gen(“TENSE”)# PERIOD | <noun> #getEword# DESTINATION #gen(“TO”)# <verb> #getEword# #gen(“ACTION”)# <tense> #gen(“TENSE”)# PERIOD
// Done by: Michael Snodgrass
void afterObject() {
  // Tell the user that the program is now processing a sentence.
  cout << "Processing <after object>" << endl;
  
  // <verb> ... | <noun> ...
  switch( next_token() )
  {
    // Check if the next output will be a noun.
    case tokentype::WORD1:
    case tokentype::PRONOUN:
      // <noun>
      noun();
      
      // #getEword#
      getEword();
      
      // DESTINATION
      match( tokentype::DESTINATION );
      
      // Output: "TO: SomeEnglishWord"
      gen("TO");
      
      // <verb>
      // Call the verb function.
      verb();
      
      // #getEword#
      getEword();
      
      // Output: "ACTION: SomeEnglishWord"
      gen("ACTION");
      
      // <tense>
      // Call the tense funciton.
      tense();
      
      // Output: "TENSE: SomeEnglishWord"
      gen("TENSE");

      // Finally match the token to the PERIOD.
      match( tokentype::PERIOD );
      break;
    // Check if the next output will be a verb.
    case tokentype::WORD2:
      // <verb>
      // Call the verb function.
      verb();

      // #getEword#
      getEword();
      
      // Output: "ACTION: SomeEnglishWord"
      gen("ACTION");
      
      // <tense>
      // Call the tense funciton.
      tense();
      
      // Output: "TENSE: SomeEnglishWord"
      gen("TENSE");
      
      // Finally match the token to the PERIOD.
      match( tokentype::PERIOD );
      break;

    // If not then do call a syntax error!
    default:
      syntaxerror2(saved_lexeme, "afterObject");
      break;
  }
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

// ---------------- Driver ---------------------------

// The final test driver to start the translator
// Done by:  Michael Snodgrass
int main()
{
  // opens the lexicon.txt file
  ifstream lexicon_file;
  
  // lexicon_file may or may not be opened.
  lexicon_file.open( "lexicon.txt" );
  
  // Check if the lexicon file is opened.
  if( lexicon_file.is_open() )
  {
    // reads it into Lexicon.
    for( int i = 0; i < SIZE; i++ )
    {
      for( int d = 0; d < 2; d++ )
      {
        // Input the lexicon contents.
        lexicon_file  >> Lexicon[ i ][ d ];
        // cout << "L[" << i << "][" << d << "] = " << Lexicon[ i ][ d ] << endl; // Simply debug output
      }
    }

    // closes lexicon.txt
    lexicon_file.close();

    // opens the output file translated.txt
    translated_output.open( "translated.txt" );

    cout << "Enter the input file name: ";
    cin >> filename;
    fin.open(filename.c_str());

    // calls the <story> to start parsing
    story();

    // closes the input file.
    fin.close();

    // closes translated.txt
    translated_output.close();
  }
  else // This loop should not run if lexicon is not found.
    cout << "Run this with \"lexicon.txt\"" << endl;
}// end
//** require no other input files!
//** syntax error EC requires producing errors.txt of error messages
//** tracing On/Off EC requires sending a flag to trace message output functions

