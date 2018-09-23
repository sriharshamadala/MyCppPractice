#include <gtest/gtest.h>
#include "expression_evaluation.h"

using namespace std;

TEST (ExpressionEvaluationTest, postfixEvaluation) {
  string expression = "2.0 3.0 * 4 1.0 * + 9.5 -";
  EXPECT_TRUE(isValidPostfixExpression(expression));
  float result = evaluatePostfix<float>(expression);
  EXPECT_EQ(result, 0.5);
}
