//
//  eval.cpp
//  Hw2
//
//  Created by Nilesh Gupta on 7/9/15.
//  Copyright (c) 2015 Nilesh Gupta. All rights reserved.
//

#include <stack>
#include <iostream>
#include <cassert>
using namespace std;

int precedence(char op)
{
    if(op == '!')
        return 1;
    if(op == '&')
        return 2;
    return 3;
}

int evaluate(string infix, string& postfix, bool& result)
// Evaluates a boolean expression
//   If infix is a syntactically valid infix boolean expression,
//   then set postfix to the postfix form of that expression, set
//   result to the value of the expression, and return zero.  If
//   infix is not a syntactically valid expression, return 1; in
//   that case, postfix may or may not be changed, but result must
//   be unchanged.)
{
    // infix string with no spaces
    string raw = "";
    
    // removes spaces
    for(int i = 0; i < infix.length(); i++)
    {
        if(infix[i] != ' ')
            raw += infix[i];
    }
    
    // ensures all parentheticals are closed
    int numStartParenthesis = 0;
    int numEndParenthesis = 0;
    
    // ensures it has a T or F
    int hasOperand = 0;
    
    // checks if infix is valid
    for(int i = 0; i < raw.length(); i++)
    {
        if(raw[i] == '&' | raw[i] == '|')
        {
            // checks if & or | operator are at end of expression
            if(i == 0 | i == raw.length()-1)
                return 1;
            // checks syntax in front of and behind operators
            if((raw[i-1] != 'T' && raw[i-1] != 'F' && raw[i-1] != ')' && raw[i-1] != '!') | (raw[i+1] != 'T' && raw[i+1] != 'F' && raw[i+1] != '(' && raw[i+1] != '!'))
                return 1;
        }
        if(raw[i] == 'T' || raw[i] == 'F')
        {
            hasOperand++;
            // checks if character in front of or behind operand is invalid
            if((i != raw.length()-1 && (raw[i+1] == 'T' | raw[i+1] == 'F' | raw[i+1] == '(' )) | (i != 0 && (raw[i-1] == ')')))
                return 1;
        }
        
        if(raw[i] == '(')
            numStartParenthesis++;
        if(raw[i] == ')')
            numEndParenthesis++;
    }
    // no parenthesis left unclosed
    if(numStartParenthesis != numEndParenthesis)
        return 1;
    
    // guards against "" and statements sans operands
    if(hasOperand == 0)
        return 1;
    
    postfix = "";
    stack<char> operators;
    
    for(int i = 0; i < infix.length(); i++)
    {
        char ch = infix[i];
        switch(ch)
        {
            case 'T':
            case 'F':
                postfix += ch;
                break;
            
            case '(':
                operators.push(ch);
                break;
                
            case ')':
                while(!operators.empty() && operators.top() != '(')
                {
                    postfix += operators.top();
                    operators.pop();
                }
                operators.pop();
                break;
                
            case '!':
            case '&':
            case '|':
                // changed '<=' in pseudocode to '>=' since I number precedence backwards
                while(!operators.empty() && operators.top() != '(' && precedence(ch) >= precedence(operators.top()))
                {
                    postfix += operators.top();
                    operators.pop();
                }
                operators.push(ch);
                break;
                
            default:
                break;
        }
    }
    
    // adds remaining operators
    while(!operators.empty())
    {
        postfix += operators.top();
        operators.pop();
    }
    
    stack<bool> operand;
    
    for(int i = 0; i < postfix.length(); i++)
    {
        char ch = postfix[i];
        if(ch == 'T')
            operand.push(true);
        else if(ch == 'F')
            operand.push(false);
        else if(ch == '!')
        {
            bool top = operand.top();
            operand.pop();
            operand.push(!top);
        }
        // else ch is a binary operator
        // evaluate expression
        else
        {
            bool operand1 = operand.top();
            operand.pop();
            bool operand2 = operand.top();
            operand.pop();
            
            bool next;
            if(ch == '&')
                next = operand1 & operand2;
            else
                next = operand1 | operand2;
            operand.push(next);
        }
    }
    result = operand.top();
    return 0;
}
