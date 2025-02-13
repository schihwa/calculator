#include <string>
#include <algorithm>
#include <cctype>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <iostream>

#include <cctype>
#include <queue>
#include <stack>
#include <string_view>

std::queue<char> postfix_to_infix(std::string_view postfix_expression)
{
    std::queue<char> infix_expression;
    std::stack<char> operator_stack;

    for (char token : postfix_expression)
    {
        if (std::isdigit(token))
        {
            infix_expression.push(token);
        }
        else if (token == '(')
        {
            operator_stack.push(token);
        }
        else if (token == ')')
        {
            while (!operator_stack.empty() && operator_stack.top() != '(')
            {
                infix_expression.push(operator_stack.top());
                operator_stack.pop();
            }
            if (!operator_stack.empty())
            {
                operator_stack.pop();
            }
        }
        else if (token == '+' || token == '-')
        {
            while (!operator_stack.empty() && operator_stack.top() != '(')
            {
                infix_expression.push(operator_stack.top());
                operator_stack.pop();
            }
            operator_stack.push(token);
        }
        else if (token == '*' || token == '/')
        {
            while (!operator_stack.empty() && operator_stack.top() != '(' &&
                   (operator_stack.top() == '*' || operator_stack.top() == '/'))
            {
                infix_expression.push(operator_stack.top());
                operator_stack.pop();
            }
            operator_stack.push(token);
        }
    }
    while (!operator_stack.empty())
    {
        infix_expression.push(operator_stack.top());
        operator_stack.pop();
    }

    return infix_expression;
}

#include <cctype>
#include <queue>
#include <stack>
#include <stdexcept>

int postfix_eval(std::queue<char> postfix_expression)
{
    std::stack<int> computations;

    while (!postfix_expression.empty())
    {
        char token = postfix_expression.front();
        postfix_expression.pop();

        if (std::isdigit(token))
        {
            computations.push(token - '0');
        }
        else
        {
            // Pop the right and then left operand.
            int operand2 = computations.top();
            computations.pop();
            int operand1 = computations.top();
            computations.pop();
            int result = 0;

            // Perform the operation based on the operator.
            switch (token)
            {
            case '+':
                result = operand1 + operand2;
                break;
            case '-':
                result = operand1 - operand2;
                break;
            case '*':
                result = operand1 * operand2;
                break;
            case '/':
                result = operand1 / operand2;
                break;
            }
            // Push the result back onto the stack.
            computations.push(result);
        }
    }

    return computations.top();
}

int main(int argc, char const *argv[])
{
    std::string expression = "5 * (9*4 * (5-2)) + 3"; // test expression so I can focus on core code
    std::queue<char> postfix_expression = postfix_to_infix(std::string_view(expression));

    int result = postfix_eval(postfix_expression);
    std::cout << "Result: " << result << std::endl;

    // while (!postfix_expression.empty())
    // {
    //     std::cout << postfix_expression.front();
    //     postfix_expression.pop();
    // }

    return 0;
}
