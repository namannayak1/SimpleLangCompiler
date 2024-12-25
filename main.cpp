#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include <cctype>
#include<bits/stdc++.h>

using namespace std;

// Token types
enum TokenType {
    TYPE_INT,
    TYPE_VAR,
    TYPE_NUM,
    TYPE_EQUALS,
    TYPE_ADD,
    TYPE_SUB,
    TYPE_IF,
    TYPE_ELSE,
    TYPE_COMPARE_EQ,
    TYPE_COMPARE_NEQ,
    TYPE_GREATER,
    TYPE_LESSER,
    TYPE_OPEN_BRACE,
    TYPE_CLOSE_BRACE,
    TYPE_OPEN_PAREN,
    TYPE_CLOSE_PAREN,
    TYPE_ENDLINE,
    TYPE_UNKNOWN,
    TYPE_EOF
};

struct Token {
    TokenType category;
    string value;
};

class Scanner {
private:
    ifstream inputFile;
    char currentChar;

    void nextChar() {
        currentChar = inputFile.get();
    }

    bool isSpace(char c) const { return isspace(c); }
    bool isLetter(char c) const { return isalpha(c); }
    bool isNumber(char c) const { return isdigit(c); }
    bool isAlphanumeric(char c) const { return isalnum(c); }

public:
    explicit Scanner(const string &fileName) {
        inputFile.open(fileName);
        if (!inputFile.is_open()) {
            throw runtime_error("Cannot open file");
        }
        nextChar();
    }

    Token fetchNextToken() {
        while (!inputFile.eof()) {
            if (isSpace(currentChar)) {
                nextChar();
                continue;
            }

            if (isLetter(currentChar)) {
                string word;
                while (isAlphanumeric(currentChar)) {
                    word += currentChar;
                    nextChar();
                }
                if (word == "int") return {TYPE_INT, word};
                if (word == "if") return {TYPE_IF, word};
                if (word == "else") return {TYPE_ELSE, word};
                return {TYPE_VAR, word};
            }

            if (isNumber(currentChar)) {
                string number;
                while (isNumber(currentChar)) {
                    number += currentChar;
                    nextChar();
                }
                return {TYPE_NUM, number};
            }

            switch (currentChar) {
                case '=':
                    nextChar();
                    if (currentChar == '=') {
                        nextChar();
                        return {TYPE_COMPARE_EQ, "=="};
                    }
                    return {TYPE_EQUALS, "="};
                case '!':
                    nextChar();
                    if (currentChar == '=') {
                        nextChar();
                        return {TYPE_COMPARE_NEQ, "!="};
                    }
                    return {TYPE_UNKNOWN, "!"};
                case '>':
                    nextChar();
                    return {TYPE_GREATER, ">"};
                case '<':
                    nextChar();
                    return {TYPE_LESSER, "<"};
                case '+':
                    nextChar();
                    return {TYPE_ADD, "+"};
                case '-':
                    nextChar();
                    return {TYPE_SUB, "-"};
                case '{':
                    nextChar();
                    return {TYPE_OPEN_BRACE, "{"};
                case '}':
                    nextChar();
                    return {TYPE_CLOSE_BRACE, "}"};
                case '(':
                    nextChar();
                    return {TYPE_OPEN_PAREN, "("};
                case ')':
                    nextChar();
                    return {TYPE_CLOSE_PAREN, ")"};
                case ';':
                    nextChar();
                    return {TYPE_ENDLINE, ";"};
                default:
                    char tempChar = currentChar;
                    nextChar();
                    return {TYPE_UNKNOWN, string(1, tempChar)};
            }
        }
        return {TYPE_EOF, ""};
    }
};

class SyntaxAnalyzer {
private:
    Scanner &scanner;
    Token currentToken;
    map<string, bool> variables;

    void expect(TokenType type) {
        if (currentToken.category == type) {
            currentToken = scanner.fetchNextToken();
        } else {
            throw runtime_error("Unexpected token: " + currentToken.value);
        }
    }

public:
    explicit SyntaxAnalyzer(Scanner &scannerRef) : scanner(scannerRef) {
        currentToken = scanner.fetchNextToken();
    }

    void analyzeProgram() {
        while (currentToken.category != TYPE_EOF) {
            if (currentToken.category == TYPE_INT) {
                analyzeDeclaration();
            } else if (currentToken.category == TYPE_VAR) {
                analyzeAssignment();
            } else if (currentToken.category == TYPE_IF) {
                analyzeIfStatement();
            } else {
                throw runtime_error("Invalid token in program: " + currentToken.value);
            }
        }
    }

    void analyzeDeclaration() {
        expect(TYPE_INT);
        if (currentToken.category == TYPE_VAR) {
            string variableName = currentToken.value;
            variables[variableName] = true;
            cout << "Variable declared: " << variableName << endl;
            expect(TYPE_VAR);
            expect(TYPE_ENDLINE);
        } else {
            throw runtime_error("Variable name expected after 'int'");
        }
    }

    void analyzeAssignment() {
        string variableName = currentToken.value;
        if (variables.find(variableName) == variables.end()) {
            throw runtime_error("Variable not declared: " + variableName);
        }
        expect(TYPE_VAR);
        expect(TYPE_EQUALS);
        analyzeExpression();
        cout << "Value stored in: " << variableName << endl;
        expect(TYPE_ENDLINE);
    }

    void analyzeIfStatement() {
        expect(TYPE_IF);
        expect(TYPE_OPEN_PAREN);
        analyzeCondition();
        expect(TYPE_CLOSE_PAREN);
        expect(TYPE_OPEN_BRACE);
        while (currentToken.category != TYPE_CLOSE_BRACE) {
            analyzeAssignment();
        }
        expect(TYPE_CLOSE_BRACE);

        if (currentToken.category == TYPE_ELSE) {
            expect(TYPE_ELSE);
            expect(TYPE_OPEN_BRACE);
            while (currentToken.category != TYPE_CLOSE_BRACE) {
                analyzeAssignment();
            }
            expect(TYPE_CLOSE_BRACE);
        }
    }

    void analyzeCondition() {
        analyzeExpression();
        if (currentToken.category == TYPE_COMPARE_EQ) {
            expect(TYPE_COMPARE_EQ);
            analyzeExpression();
            cout << "Check equality" << endl;
        }
    }

    void analyzeExpression() {
        analyzeTerm();
        while (currentToken.category == TYPE_ADD || currentToken.category == TYPE_SUB) {
            TokenType operation = currentToken.category;
            expect(operation);
            analyzeTerm();
            if (operation == TYPE_ADD) {
                cout << "Add operation" << endl;
            } else {
                cout << "Subtract operation" << endl;
            }
        }
    }

    void analyzeTerm() {
        analyzeFactor();
    }

    void analyzeFactor() {
        if (currentToken.category == TYPE_NUM) {
            cout << "Load number: " << currentToken.value << endl;
            expect(TYPE_NUM);
        } else if (currentToken.category == TYPE_VAR) {
            cout << "Load variable: " << currentToken.value << endl;
            expect(TYPE_VAR);
        } else if (currentToken.category == TYPE_OPEN_PAREN) {
            expect(TYPE_OPEN_PAREN);
            analyzeExpression();
            expect(TYPE_CLOSE_PAREN);
        } else {
            throw runtime_error("Invalid token in expression");
        }
    }
};

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <file_name>" << endl;
        return 1;
    }

    try {
        Scanner scanner(argv[1]);
        SyntaxAnalyzer parser(scanner);
        parser.analyzeProgram();
    } catch (const exception &err) {
        cerr << "Error: " << err.what() <<endl;
        return 1;
    }

    return 0;
}
