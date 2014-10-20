//
//  eval.cpp
//  HW 2
//
//  Created by Li-Wei Tseng on 4/26/14.
//  Copyright (c) 2014 Li-Wei Tseng. All rights reserved.
//
#define EVAL
#ifdef EVAL

#include <iostream>
#include <string>
#include <stack>
#include <cassert>
using namespace std;

bool checkParanthesis(const string& infix);

int evaluate(string infix, string& postfix, bool& result)
{
    // Evaluates a boolean expression
    //   If infix is a syntactically valid infix boolean expression,
    //   then set postfix to the postfix form of that expression, set
    //   result to the value of the expression, and return zero.  If
    //   infix is not a syntactically valid expression, return 1; in
    //   that case, postfix may or may not be changed, but result must
    //   be unchanged.)
    
    ///////////check syntactically valid infix boolean expression///////
    
    if(!checkParanthesis(infix))//check if parantheses are balanced
        return 1;
    
    ////////////infix convertion///////////////////
    
    postfix = ""; //make postfix an empty string
    stack<char> operatorStack; //create an empty stack for operator
    
    for(int i = 0; i < infix.size(); i++)
    {
        switch (infix[i])
        {
            case ' ': //ignore white space
                break;
                
            case 'T': //append operands to postfix
            case 'F':
                if((i > 0) && ((infix[i-1] == 'T') || (infix[i-1] == 'F') || (infix[i-1] == ')')))
                   return 1; //if the current nonblank chars isn't legal, return 1
                
                postfix += infix[i];
                break;
                
            case '(': //push '(' onto the stack
                if((i > 0) && ((infix[i-1] == 'T') || (infix[i-1] == 'F')|| (infix[i-1] == ')')))
                    return 1; //if the current nonblank chars isn't legal, return 1
                
                operatorStack.push(infix[i]);
                break;
                
            case ')':
                
                if((i > 0) && ((infix[i-1] == '!') || (infix[i-1] == '&')|| (infix[i-1] == '|') || (infix[i-1] == '(')))
                    return 1; //if the current nonblank chars isn't legal, return 1
                
                // pop stack until matching '('
                while(!operatorStack.empty() && operatorStack.top() != '(')
                {
                    postfix += operatorStack.top();
                    operatorStack.pop();
                }
                if(!operatorStack.empty())
                    operatorStack.pop(); //remove '('
                else
                    return 1;//error checking
                break;
                
            case '!':
                if((i > 0) && ((infix[i-1] == 'T') || (infix[i-1] == 'F') || (infix[i-1] == ')')))
                    return 1; //if the current nonblank chars isn't legal, return 1
                
//                while(!operatorStack.empty() && operatorStack.top() != '(' && operatorStack.top() <= infix[i])//using ACSSII chars ! < & < |, reverse the order
//                {
//                    postfix += operatorStack.top();
//                    operatorStack.pop();
//                }
                operatorStack.push(infix[i]);
                break;
                
            case '&':
            case '|':
                if((i > 0) && ((infix[i-1] == '!') || (infix[i-1] == '&')|| (infix[i-1] == '|') || (infix[i-1] == '(')))
                    return 1; //if the current nonblank chars isn't legal, return 1
                while(!operatorStack.empty() && operatorStack.top() != '(' && operatorStack.top() <= infix[i])//using ACSSII chars ! < & < |, reverse the order
                {
                    postfix += operatorStack.top();
                    operatorStack.pop();
                }
                operatorStack.push(infix[i]);
                break;
                
            default: //other chars
                return 1;
                break;
        }//end switch
    }//end for
    
    
    while(!operatorStack.empty())
    {
        postfix += operatorStack.top();
        operatorStack.pop();
    }
    
    ////////////postfix evaluation///////////////////
    stack<char> operandStack;
    for(int i = 0; i < postfix.size(); i++)
    {
        if(postfix[i] == 'T' || postfix[i] == 'F')
        {
            operandStack.push(postfix[i]);
        }
        else if(postfix[i] == '!')//handle 'not' case: convert operand first if there's '!'
        {
            char operand1 = operandStack.top();
            operandStack.pop();
            switch(operand1)
            {
                case 'T': operandStack.push('F');
                    break;
                case 'F': operandStack.push('T');
                    break;
            }
        }
        else if(postfix[i] == '|')//handle 'or' case: if there's a 'T' then evaluate to true
        {
            char operand1;
            if(!operandStack.empty())//check if the program can pop the stack
            {
                operand1 = operandStack.top();
                operandStack.pop();
            }
            else
                return 1;
            
            char operand2;
            if(!operandStack.empty())//check if the program can pop the stack
            {
                operand2 = operandStack.top();
                operandStack.pop();
            }
            else
                return 1;
            
            if(operand1 == 'T' || operand2 == 'T')
                operandStack.push('T');
            else
                operandStack.push('F');
        }
        else //handle 'and' case: evalute to false if there's a 'F'
        {
            char operand1;
            if(!operandStack.empty())//check if the program can pop the stack
            {
                operand1 = operandStack.top();
                operandStack.pop();
            }
            else
                return 1;
            
            char operand2;
            if(!operandStack.empty())//check if the program can pop the stack
            {
                operand2 = operandStack.top();
                operandStack.pop();
            }
            else
                return 1;
            
            if(operand1 == 'F' || operand2 == 'F')
                operandStack.push('F');
            else
                operandStack.push('T');
        }
    }

    if(operandStack.size() != 1)
        return 1; //if stack doesn't have exactly one item, return 1
    
    if(operandStack.top() == 'T')
    {
        result = true;
    }
    else
    {
        result = false;
    }
    return 0;
}

void testCase()
{
    string pf;
    bool answer;
    //valid cases
    assert(evaluate("T", pf, answer) == 0  &&  pf == "T"  &&  answer);
    assert(evaluate("(F)", pf, answer) == 0  &&  pf == "F"  &&  !answer);
    assert(evaluate("T| F", pf, answer) == 0  &&  pf == "TF|"  &&  answer);
    assert(evaluate("T&(F)", pf, answer) == 0  &&  pf == "TF&"  &&  !answer);
    assert(evaluate("T & !F", pf, answer) == 0  &&  pf == "TF!&"  &&  answer);
    assert(evaluate("!(F|T)", pf, answer) == 0  &&  pf == "FT|!"  &&  !answer);
    assert(evaluate("!F|T", pf, answer) == 0  &&  pf == "F!T|"  &&  answer);
    assert(evaluate("T|F&F", pf, answer) == 0  &&  pf == "TFF&|"  &&  answer);
    assert(evaluate("T&!(F|T&T|F)|!!!(F&T&F)", pf, answer) == 0 &&  answer);
    assert(evaluate("F  |  !F & (T&F) ", pf, answer) == 0 &&  pf == "FF!TF&&|"  &&  !answer);
    assert(evaluate(" F  ", pf, answer) == 0 &&  pf == "F"  &&  !answer);
    assert(evaluate("((T))", pf, answer) == 0 &&  pf == "T"  &&  answer);
    assert(evaluate("(T & !F)", pf, answer) == 0  &&  pf == "TF!&"  &&  answer);
    assert(evaluate("!F  |  !F & (T&F) ", pf, answer) == 0  &&  pf == "F!F!TF&&|"  &&  answer);
    assert(evaluate("(T&(F|F))", pf, answer) == 0 && pf == "TFF|&" && !answer);
    assert(evaluate("F&T&F", pf, answer) == 0 && pf == "FT&F&"  && !answer);


    
    //check invalid cases
    assert(evaluate("(T&(F|F)", pf, answer) == 1);
    assert(evaluate("T|", pf, answer) == 1);
    assert(evaluate("F F", pf, answer) == 1);
    assert(evaluate("TF", pf, answer) == 1);
    assert(evaluate("()", pf, answer) == 1);
    assert(evaluate("(  )", pf, answer) == 1);
    assert(evaluate("(  T&F)T", pf, answer) == 1);
    assert(evaluate("T(F|T)", pf, answer) == 1);
    assert(evaluate("T(&T)", pf, answer) == 1);
    assert(evaluate("", pf, answer) == 1);
    assert(evaluate("  ", pf, answer) == 1);
    assert(evaluate("T!", pf, answer) == 1);
    assert(evaluate("T(", pf, answer) == 1);
    assert(evaluate("(TT", pf, answer) == 1);
    assert(evaluate("&TF", pf, answer) == 1);
    assert(evaluate(")(", pf, answer) == 1);
    assert(evaluate("#2", pf, answer) == 1);
    assert(evaluate("F&&", pf, answer) == 1);
    assert(evaluate("F!!", pf, answer) == 1);
    assert(evaluate("F!!T", pf, answer) == 1);
    
    //check valid cases
    assert(evaluate("T", pf, answer) == 0  &&  pf == "T"  &&  answer);
    assert(evaluate("T|T", pf, answer) == 0  &&  pf == "TT|"  &&  answer);
    assert(evaluate("T&T", pf, answer) == 0  &&  pf == "TT&"  &&  answer);
    assert(evaluate("F|F", pf, answer) == 0  &&  pf == "FF|"  &&  !answer);
    assert(evaluate("T & !F", pf, answer) == 0  &&  pf == "TF!&"  &&  answer);
    assert(evaluate("!(F|T)", pf, answer) == 0  &&  pf == "FT|!"  &&  !answer);
    assert(evaluate("!F|T", pf, answer) == 0  &&  pf == "F!T|"  &&  answer);
    assert(evaluate("T|F&F", pf, answer) == 0  &&  pf == "TFF&|"  &&  answer);
    assert(evaluate("T&!(F|T&T|F)|!!!(F&T&F)", pf, answer) == 0  &&  pf == "TFTT&|F|!&FT&F&!!!|"  &&  answer);
    assert(evaluate("(T&((F|T)&(T)))", pf, answer) == 0  &&  pf == "TFT|T&&"  &&  answer);
    
    assert(evaluate("(T|F)T", pf, answer) == 1);
    assert(evaluate("F&(&T)", pf, answer) == 1);
    assert(evaluate("F&|T", pf, answer) == 1);
    assert(evaluate("T!T", pf, answer) == 1);
    assert(evaluate("(F", pf, answer) == 1);
    assert(evaluate("F)", pf, answer) == 1);
    assert(evaluate("TF", pf, answer) == 1);
    assert(evaluate("F:T", pf, answer) == 1);
    assert(evaluate("F&:", pf, answer) == 1);
    assert(evaluate("F T&T", pf, answer) == 1);
    assert(evaluate("1& |T", pf, answer) == 1);

}

int main()
{
    testCase();
    cout << "Passed all tests" << endl;
}

bool checkParanthesis(const string& infix)
{
    stack<char> aStack;
    bool balancedSoFar = true;
    int i = 0;
    
    while(balancedSoFar && i < infix.size())
    {
        //push an open brace
        if(infix[i] == '(')
            aStack.push(infix[i]);
        //close brace
        else if(infix[i] == ')')
        {
            if(!aStack.empty())
                aStack.pop(); //pop a matching open brace
            else
                balancedSoFar = false;
        }//ignore all chars other than braces
        ++i;

    }//end while
    
    if(balancedSoFar && aStack.empty())
        return true;
    else
        return false;
}

#endif //EVAL

