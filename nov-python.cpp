#include <stdio.h>
#include "nov-python.hpp"

ostream &operator<<(ostream &out, Value &A)
{
    if (A.type == 0)
    {
        out << A.intValue;
    }
    else
    {
        out << A.doubleValue;
    }
    return out;
}

Value NovExpression::evaluate() const
{
    Value value(0);
    //cout << e1 << " " << op << " " << e2 << endl;
    if (e1 != NULL && e2 != NULL)
    {
        // Binary Expression
        if (op == '+')
        {
            Value vvv = e1->evaluate() + e2->evaluate();
            cout << "+:" << vvv << endl;
            return e1->evaluate() + e2->evaluate();
        }
        else if (op == '-')
        {
            return e1->evaluate() - e2->evaluate();
        }
        else if (op == '*')
        {
            return e1->evaluate() * e2->evaluate();
        }
        else if (op == '/')
        {
            return e1->evaluate() / e2->evaluate();
        }
        else if (op == '^')
        {
            return e1->evaluate() ^ e2->evaluate();
        }
        else if (op == '<')
        {
            return e1->evaluate() < e2->evaluate();
        }
    }
    return value;
};

Value NovConstant::evaluate() const
{
    return value;
};

Value NovIdent::evaluate() const
{
    Value value(100);
    return value;
};