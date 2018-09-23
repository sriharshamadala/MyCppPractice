#include <iostream>
#include <stack>
#include <sstream>
#include <string>

using namespace std;

bool isOperator (string token) {
  bool result = false;
  if (token.length() == 1) {
    char temp_char = token[0];
    if ((temp_char == '+') ||
        (temp_char == '-') ||
        (temp_char == '*') ||
        (temp_char == '/')) {
      result = true;
    }
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

