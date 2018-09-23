#include <gtest/gtest.h>
#include "expression_evaluation.h"

using namespace std;

TEST (ExpressionEvaluationTest, postfixEvaluation) {
  string expression = "2.0 3.0 * 4 1.0 * + 9.5 -";
  EXPECT_TRUE(isValidPostfixExpression(expression));
  float result = evaluatePostfix<float>(expression);
  EXPECT_EQ(result, 0.5);
}

TEST (ExpressionEvaluationTest, infixToPostfix) {
  string expression = "2.0 * 3.0 + 4 * 1.0 - 9.5";
  cout << "Infix expression: " << endl;
  cout << expression << endl;

  string postfix_expression = infixToPostfix(expression);
  cout << "Postfix expression: " << endl;
  cout << postfix_expression << endl;
  EXPECT_EQ(postfix_expression, "2.0 3.0 * 4 1.0 * + 9.5 - ");
  float result = evaluatePostfix<float>(postfix_expression);
  EXPECT_EQ(result, 0.5);
}

TEST (ExpressionEvaluationTest, infixToPostfixEqualPrecedence) {
  string expression = "2.0 * 4.0 / 4";
  cout << "Infix expression: " << endl;
  cout << expression << endl;

  string postfix_expression = infixToPostfix(expression);
  cout << "Postfix expression: " << endl;
  cout << postfix_expression << endl;
  EXPECT_EQ(postfix_expression, "2.0 4.0 * 4 / ");
}

TEST (ExpressionEvaluationTest, infixToPostfixParanthesis1) {
  string expression = "2.0 * ( 4.0 + 3.5 )";
  cout << "Infix expression: " << endl;
  cout << expression << endl;

  string postfix_expression = infixToPostfix(expression);
  cout << "Postfix expression: " << endl;
  cout << postfix_expression << endl;
  EXPECT_EQ(postfix_expression, "2.0 4.0 3.5 + * ");
  float result = evaluatePostfix<float>(postfix_expression);
  EXPECT_EQ(result, 15);
}

TEST (ExpressionEvaluationTest, infixToPostfixParanthesis2) {
  string expression = "( ( 4.0 + 3.5 ) * 2.0 - 12 ) * 2";
  cout << "Infix expression: " << endl;
  cout << expression << endl;

  string postfix_expression = infixToPostfix(expression);
  cout << "Postfix expression: " << endl;
  cout << postfix_expression << endl;
  EXPECT_EQ(postfix_expression, "4.0 3.5 + 2.0 * 12 - 2 * ");
  float result = evaluatePostfix<float>(postfix_expression);
  EXPECT_EQ(result, 6);
}
