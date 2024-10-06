#include <iostream>
#include <string>
#include "Stack.h"

using namespace std;

// Functions
bool isBalanced(string srt);
int prec(char c);
string InfixtoPostfix(string str);
string InfixToPrefix(string infix);
string reverseString(const string& str);
double EvaluatePostfix(string postfix);
double EvaluatePrefix(string prefix);
int power(int x, int p);
bool isdig(char n);


int main() {
    string UserInput;
    char choice = '0';

    do {
        cout << "Enter your choice:\n 1: Infix to Prefix\n 2: Infix to Postfix\n 3: Postfix Evaluation\n 4: Prefix Evaluation\n 5: Exit\n";
        cin >> choice;
        cin.ignore();

        if (choice == '1' || choice == '2') {
            cout << "Enter infix expression: ";
            getline(cin, UserInput);
            if (!isBalanced(UserInput)) {
                cout << "Expression is not balanced." << endl;
                continue;
            }
        }

        if (choice == '1') {
            string prefix = InfixToPrefix(UserInput);
            cout << "Prefix: " << prefix << endl;
        }
        else if (choice == '2') {
            string postfix = InfixtoPostfix(UserInput);
            cout << "Postfix: " << postfix << endl;
        }
        else if (choice == '3') {
            string postfix;
            cout << "Enter Postfix Expreesion: ";
            getline(cin, postfix);
            cout << "Postfix evaluation: " <<EvaluatePostfix(postfix)<< endl;
        }
        else if (choice == '4') {
            string prefix;
            cout << "Enter Prefix Expression: ";
            getline(cin, prefix);
            cout << "Prefix evaluation: " <<EvaluatePrefix(prefix) <<endl;
        }
        else if (choice == '5') {
            cout << "Exiting the program." << endl;
        }
        else {
            cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != '5');

    return 0;
}

// Balanced string
bool isBalanced(string srt) {
    Stack s;
    bool hasBrackets = false;

    for (auto it : srt) {
        if (it == '(' || it == '{' || it == '[') {
            s.push(it);
            hasBrackets = true;
        }
        else if (it == ')' || it == '}' || it == ']') {
            if (s.isempty()) {
                return false;
            }
            char ch = s.pop();

            if ((it == ')' && ch != '(') || (it == ']' && ch != '[') || (it == '}' && ch != '{')) {
                return false;
            }
        }
    }
    if (hasBrackets) {
        return s.isempty();
    }
    else {
        return true;
    }
}

// Precedence Function
int prec(char c) {
    if (c == '^')
        return 3;
    else if (c == '/' || c == '*')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}

// Infix to Postfix Conversion
string InfixtoPostfix(string str) {
    Stack s;
    string result;
    for (int i = 0; i < str.length(); i++) {
        char c = str[i];

        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
            result += c;

        else if (c == '(')
            s.push('(');

        else if (c == ')') {
            while (!s.isempty() && s.gettop() != '(') {
                result += s.gettop();
                s.pop();
            }
            s.pop();
        }
        else {
            while (!s.isempty() && prec(c) <= prec(s.gettop())) {
                result += s.gettop();
                s.pop();
            }
            s.push(c);
        }
    }

    while (!s.isempty()) {
        result += s.gettop();
        s.pop();
    }
    return result;
}

// Reverse Function
string reverseString(const string& str) {
    string reversed;
    for (int i = str.length() - 1; i >= 0; i--) {
        reversed += str[i];
    }
    return reversed;
}

// Infix to Prefix Conversion
string InfixToPrefix(string infix) {
    infix = reverseString(infix);
    for (int i = 0; i < infix.size(); i++) {
        if (infix[i] == '(')
            infix[i] = ')';
        else if (infix[i] == ')')
            infix[i] = '(';
    }

    string converted = InfixtoPostfix(infix);
    converted = reverseString(converted);

    return converted;
}


//Power 
int power(int x, int p) {
    if (p == 0) {
        return 1;
    }
    else
        return x * power(x, p - 1);
}


//Is Digit
bool isdig(char n) {
    return n >= '0' && n <= '9';
}

//is Operand
bool isAlpha(char c) {
    if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z'){
        return true;
    }
      return false;
}




//Evluation of Postfix
double EvaluatePostfix(string postfix) {
    Stack s;
    for (int i = 0; i < postfix.length(); i++) {
        char c = postfix[i];
        if (isdig(c)) {
            s.push(c-'0');
        }
        else if (isAlpha(c)) {
            int value;
            cout << "Enter value for " << c << ": ";
            cin >> value;
            s.push(value);
        }
        else {
            int operand2 = s.gettop();
            s.pop();
            int operand1 = s.gettop();
            s.pop();
            if (c == '+') {
                s.push(operand1 + operand2);
            }
            else if (c == '-') {
                s.push(operand1 - operand2);

            }
            else if (c == '*') {
                s.push(operand1 * operand2);
            }
            else if (c == '/') {
                s.push(operand1 / operand2);
            }
            else if(c == '^') {
                s.push(power(operand1, operand2));
            }
        }
    }
    return s.gettop();
}


//Evluation of Prefix

double EvaluatePrefix(string prefix) {
    Stack s;
    for (int i = prefix.length()-1; i>=0 ; i--) {
        char c = prefix[i];
        if (isdig(c)) {
            s.push(c - '0');
        }
        else if (isAlpha(c)) {
            int value;
            cout << "Enter value for " << c << ": ";
            cin >> value;
            s.push(value);
        }
        else {
            int operand1 = s.gettop();
            s.pop();
            int operand2 = s.gettop();
            s.pop();
            if (c == '+') {
                s.push(operand1 + operand2);
            }
            else if (c == '-') {
                s.push(operand1 - operand2);

            }
            else if (c == '*') {
                s.push(operand1 * operand2);
            }
            else if (c == '/') {
                s.push(operand1 / operand2);
            }
            else if (c == '^') {
                s.push(power(operand1, operand2));
            }
        }
    }
    return s.gettop();
}
