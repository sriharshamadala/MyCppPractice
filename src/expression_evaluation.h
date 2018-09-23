#include <iostream>
#include <stack>
#include <sstream>
#include <string>
#include <exception>

using namespace std;

bool isOperator (string token) {
  bool result = false;
  if (token.length() == 1) {
    char temp_char = token[0];
    if ((temp_char == '+') ||
        (temp_char == '-') ||
        (temp_char == '*') ||
        (temp_char == '/') ||
        (temp_char == '^')) {
      result = true;
    }
  }
  return result;
}

int getOperatorPriority (char oper) {
  int result = 1;
  switch (oper) {
    case '(':
      result = 4;
      break;
    case ')':
      result = 4;
      break;
    case '^':
      result = 3;
      break;
    case '*':
      result = 2;
      break;
    case '/':
      result = 2;
      break;
    case '+':
      result = 1;
      break;
    case '-':
      result = 1;
      break;
  }
  return result;
}

template<typename T>
T executeOperation (T op1, T op2, char oper) {
  T result = 0;
  switch (oper) {
    case '+':
      result = op1 + op2;
      break;
    case '-':
      result = op1 - op2;
      break;
    case '*':
      try {
        result = op1 * op2;
      } catch (exception e) {
        cout << "Exception: " << e.what() << endl;
      }
      break;
    case '/':
      try {
        result = op1 / op2;
      } catch (exception e) {
        cout << "Exception: " << e.what() << endl;
      }
      break;
    case '^':
      // TODO Need to handle exponent operator.
      break;
  }
  return result;
}

template<typename T>
T evaluatePostfix (string expression, char delimiter = ' ') {
  istringstream iss(expression);
  string token;
  stack<T> my_stack;

  while (getline(iss, token, delimiter)) {
    if (isOperator(token)) {
      // If operator, pop the top two elements,
      // perform the operation,
      // push the result to the stack.
      T op2 = my_stack.top();
      my_stack.pop();
      T op1 = my_stack.top();
      my_stack.pop();
      T result = executeOperation(op1, op2, token[0]);
      my_stack.push(result);
    } else {
      // If operand, simply push to the stack.
      istringstream temp_iss(token);
      T temp_op;
      temp_iss >> temp_op;
      my_stack.push(temp_op);
    }
  }

  return my_stack.top();
}

bool isValidPostfixExpression (string expression, char delimiter = ' ') {
  istringstream iss(expression);
  string token;
  int stack_length = 0;

  while (getline(iss, token, delimiter)) {
    if (isOperator(token)) {
      stack_length--;
    } else {
      stack_length++;
    }
    if (stack_length < 1) {
      return false;
    }
  }
  return true;
}

bool isHigherPrecedence (char oper_token, char oper_stack) {
  int priority_token = getOperatorPriority(oper_token);
  int priority_stack = getOperatorPriority(oper_stack);
  // the case of equality is resolved using left to right associativity.
  // an equal priority operator should also resolve the expression thus far.
  return (priority_token > priority_stack);
}

bool isOpeningParanthesis (string token) {
  return ((token.length() == 1) && (token[0] == '('));
}

bool isOpeningParanthesis (char oper_token) {
  return (oper_token == '(');
}

bool isClosingParanthesis (string token) {
  return ((token.length() == 1) && (token[0] == ')'));
}

string infixToPostfix (string infix_expression, char delimiter = ' ') {
  string postfix_expression;
  istringstream iss(infix_expression);
  string token;
  stack<char> oper_stack;

  while (getline(iss, token, delimiter)) {
    if (isOperator(token)) {
      char oper_token = token[0];
      while ((!oper_stack.empty()) &&
          (!isHigherPrecedence(oper_token, oper_stack.top())) &&
          (!isOpeningParanthesis(oper_stack.top()))) {
        postfix_expression += oper_stack.top();
        postfix_expression += " ";
        oper_stack.pop();
      }
      oper_stack.push(oper_token);
    } else if (isClosingParanthesis(token)) {
      // No need to push to stack. pop the top element as it should be
      // an opening paranthesis.
      while ((!oper_stack.empty()) &&
          (!isOpeningParanthesis(oper_stack.top()))) {
        postfix_expression += oper_stack.top();
        postfix_expression += " ";
        oper_stack.pop();
      }
      try {
        oper_stack.pop();
      } catch (exception e) {
        cout << "Exception: " << e.what() << endl;
      }
    } else if (isOpeningParanthesis(token)) {
      oper_stack.push('(');
    } else {
      // operands stay in order relative to each other.
      postfix_expression += token;
      postfix_expression += " ";
    }
  }
  
  // pop the remaining operators in the stack
  while (!oper_stack.empty()) {
    postfix_expression += oper_stack.top();
    postfix_expression += " ";
    oper_stack.pop();
  }
  return postfix_expression;
}
