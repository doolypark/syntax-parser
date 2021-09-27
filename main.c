// John Park (R#11487176) | Assingment #3 | 10/14/2020
//
// This program accepts a file through argv and iterates through functions to         print out lexemes and its corresponding tokens. 
//
//

#include <stdio.h>
#include <ctype.h>
#include <string.h>

// classification of char
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 2 // things that are not defined at all
#define OTHER 3 //things that are not digit and char but is defined


// token values
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
#define LESSER_OP 27
#define GREATER_OP 28
#define NEQUAL_OP 30
#define LEQUAL_OP 31
#define GEQUAL_OP 32
#define KEY_READ 33
#define KEY_WRITE 34
#define KEY_WHILE 35
#define KEY_DO 36
#define KEY_OD 37
#define SEMICOLON 38
#define EQUAL_OP 39


int nextToken; 
int lexLen; 
char lexeme[100]; 
FILE *in_fp; 
char nextChar; 
int charClass;
char tokeName[30];

// function prototypes
void addChar();
void getChar();
void getNonBlank();
int lex();


// Attempts to open file, if it opens succesfully, calls lex() while nextToken is     not EOF, otherwise print an error message
int main(int argc, char *argv[]) 
{
    /* Open the input data file and process its contents */
    if ((in_fp = fopen(argv[1], "r")) == NULL) {
        printf("ERROR - cannot open file \n");
    } else {
        getChar(); 
        printf("DanC Analyzer :: R11487176\n\n\n");
        do{
          lex();        
        }while(nextToken != EOF);
          
    }

    return 0;
}

// finds characters that are not digit or alphabet. Returns int nextToken
int lookup(char ch) {

  //Assigns correct token to each symbol. Defaults to UNKNOWN.
    switch (ch) {
        case '(':
            addChar();
            nextToken = LEFT_PAREN;
            break;
        case ')':
            addChar();
            nextToken = RIGHT_PAREN;
            break;
        case '+':
            addChar();
            nextToken = ADD_OP;
            break;
        case '-':
            addChar();
            nextToken = SUB_OP;
            break;
        case '*':
            addChar();
            nextToken = MULT_OP;
            break;
        case '/':
            addChar();
            nextToken = DIV_OP;
            break;
        case ';':
            addChar();
            nextToken = SEMICOLON;
            break;
        case '<':
            addChar(); 
            nextToken = LESSER_OP;
            break;
        case '>':
            addChar();
            nextToken = GREATER_OP;
            break;
        case '=':
            addChar();
            nextToken = EQUAL_OP;
            break;
        default:
            addChar();
            nextToken = UNKNOWN; 
            break;
    }
    return nextToken;
}

// function to add nextChar into lexeme array
void addChar() {
    // adds nextChar into lexeme array until length of array is 98, if it is          greater, prints out error message.
    if (lexLen <= 98) {
        lexeme[lexLen] = nextChar;
        lexLen = lexLen + 1;
        lexeme[lexLen] = 0;
    } else {
        printf("Error - lexeme is too long \n");
    }
}

// gets charClass of the next character
void getChar() {

    // assignes classification of character to its respective group
    if ((nextChar = getc(in_fp)) != EOF) {
        if (isalpha(nextChar))
            charClass = LETTER;
        else if (isdigit(nextChar))
            charClass = DIGIT;
        else 
            charClass = OTHER;
    } else {
        charClass = EOF;
    }
}

// a function to call getChar until it returns a non-whitespace 
void getNonBlank() {
    // skips whitespaces to read
    while (isspace(nextChar)) 
        getChar();
}

// lexical analyzer for expressions
int lex() {
    lexLen = 0;
    getNonBlank();

    switch (charClass) {

        // Identifier parser
        case LETTER:
            addChar();
            getChar();
            while (charClass == LETTER) {
                addChar();
                getChar();
            }
            if(strcmp("while", lexeme) == 0){
              nextToken = KEY_WHILE;
            }
            else if(strcmp("write", lexeme) == 0){
              nextToken = KEY_WRITE;
            }
            else if(strcmp("read", lexeme) == 0){
              nextToken = KEY_READ;
            }
            else if(strcmp("do", lexeme) == 0){
              nextToken = KEY_DO;
            }
            else if(strcmp("od", lexeme) == 0){
              nextToken = KEY_OD;
            }
            else{
              nextToken = IDENT;
            }  
            break;

        // Integer literal parser 
        case DIGIT:
            addChar();
            getChar();
            while (charClass == DIGIT) {
                addChar();
                getChar();
            }
            nextToken = INT_LIT;
            break;

        // Symbol parser 
        case OTHER:
            lookup(nextChar);
            if (nextChar == ':'){
              getChar();
              if(nextChar == '='){
                lookup(nextChar); 
                nextToken = ASSIGN_OP;
              }        
            }
            if (nextChar == '<'){
              getChar();
              if(nextChar == '='){
                lookup(nextChar); 
                nextToken = LEQUAL_OP;
              }
              else if (nextChar == '>'){
                lookup(nextChar);
                nextToken = NEQUAL_OP;
              }        
            }
            if (nextChar == '>'){
              getChar();
              if(nextChar == '='){
                lookup(nextChar);
                nextToken = GEQUAL_OP;
              }
            }
            getChar();
            break;

        // EOF
        case EOF:
            nextToken = EOF;
            break;
    } // End of switch

    // Assignes name of token of token type
    if (nextToken == ASSIGN_OP){
      strcpy(tokeName, "ASSIGN_OP");
    }
    else if(nextToken == LESSER_OP){
      strcpy(tokeName, "LESSER_OP");
    }
    else if(nextToken == GREATER_OP){
      strcpy(tokeName, "GREATER_OP");
    }
    else if(nextToken == EQUAL_OP){
      strcpy(tokeName, "EQUAL_OP");
    }
    else if(nextToken == NEQUAL_OP){
      strcpy(tokeName, "NEQUAL_OP");
    }
    else if(nextToken == LEQUAL_OP){
      strcpy(tokeName, "LEQUAL_OP");
    }
    else if(nextToken == GEQUAL_OP){
      strcpy(tokeName, "GEQUAL_OP");
    }
    else if(nextToken == ADD_OP){
      strcpy(tokeName, "ADD_OP");
    }
    else if(nextToken == SUB_OP){
      strcpy(tokeName, "SUB_OP");
    }
    else if(nextToken == MULT_OP){
      strcpy(tokeName, "MULT_OP");
    }
    else if(nextToken == DIV_OP){
      strcpy(tokeName, "DIV_OP");
    }
    else if(nextToken == KEY_READ){
      strcpy(tokeName, "KEY_READ");
    }
    else if(nextToken == KEY_WRITE){
      strcpy(tokeName, "KEY_WRITE");
    }
    else if(nextToken == KEY_WHILE){
      strcpy(tokeName, "KEY_WHILE");
    }
    else if(nextToken == KEY_DO){
      strcpy(tokeName, "KEY_DO");
    }
    else if(nextToken == KEY_OD){
      strcpy(tokeName, "KEY_OD");
    }
    else if(nextToken == IDENT){
      strcpy(tokeName, "IDENT");
    }
    else if(nextToken == INT_LIT){
      strcpy(tokeName, "INT_LIT");
    }
    else if(nextToken == LEFT_PAREN){
      strcpy(tokeName, "LEFT_PAREN");
    }
    else if(nextToken == RIGHT_PAREN){
      strcpy(tokeName, "RIGHT_PAREN");
    }
    else if(nextToken == SEMICOLON){
      strcpy(tokeName, "SEMICOLON");
    }
    else if(nextToken == UNKNOWN){
      strcpy(tokeName, "UNKNOWN");
    }

    // prints lexeme and tokennames if token isn't EOF
    if(nextToken != EOF){
      printf("%-10s\t\t%s\n", lexeme, tokeName);
    }
    
    
    
    return nextToken;
} /* End of function lex */

