#include <stdio.h>
#include "nov-python.hpp"

ostream &operator<<(ostream &out, Value &A)
{
    if (A.type == 0)
    {
        out << A.intValue;
    }
    else if (A.type == 2)
    {
        out << (A.intValue == 0 ? "False" : "True");
    }
    else if (A.type == 1)
    {
        out << A.doubleValue;
    }
    else
    {
        out << A.stringValue;
    }
    return out;
}

Value NovExpression::evaluate(const Vars &vars) const
{
    Value value(0);
    if (e1 != NULL && e2 != NULL)
    {
        // Binary Expression
        if (op == "+")
        {
            return e1->evaluate(vars) + e2->evaluate(vars);
        }
        else if (op == "-")
        {
            return e1->evaluate(vars) - e2->evaluate(vars);
        }
        else if (op == "*")
        {
            return e1->evaluate(vars) * e2->evaluate(vars);
        }
        else if (op == "/")
        {
            return e1->evaluate(vars) / e2->evaluate(vars);
        }
        else if (op == "%")
        {
            return e1->evaluate(vars) % e2->evaluate(vars);
        }
        else if (op == "^")
        {
            return e1->evaluate(vars) ^ e2->evaluate(vars);
        }
        else if (op == "<")
        {
            return e1->evaluate(vars) < e2->evaluate(vars);
        }
        else if (op == ">")
        {
            return e1->evaluate(vars) > e2->evaluate(vars);
        }
        else if (op == "<=")
        {
            return e1->evaluate(vars) <= e2->evaluate(vars);
        }
        else if (op == ">=")
        {
            return e1->evaluate(vars) >= e2->evaluate(vars);
        }
        else if (op == "==")
        {
            return e1->evaluate(vars) == e2->evaluate(vars);
        }
        else if (op == "!=")
        {
            return e1->evaluate(vars) != e2->evaluate(vars);
        }
    }
    return value;
};

Value NovConstant::evaluate(const Vars &vars) const
{
    return value;
};

Value NovIdent::evaluate(const Vars &vars) const
{
    return vars.fetch(name);
};

void NovAssignment::evaluate(Vars &vars)
{
    Value value = e1->evaluate(vars);
    if (op == "=")
    {
        //cout << "Evaluate NovAssignment: " << identName << " = " << value << endl;
        vars.write(identName, e1->evaluate(vars));
    }
    else if (op == "+=")
    {
        value = vars.fetch(identName) + value;
        vars.write(identName, value);
    }
    else if (op == "-=")
    {
        value = vars.fetch(identName) - value;
        vars.write(identName, value);
    }
    else if (op == "*=")
    {
        value = vars.fetch(identName) * value;
        vars.write(identName, value);
    }
    else if (op == "/=")
    {
        value = vars.fetch(identName) / value;
        vars.write(identName, value);
    }
    else if (op == "%=")
    {
        value = vars.fetch(identName) % value;
        vars.write(identName, value);
    }
    else if (op == "^=")
    {
        value = vars.fetch(identName) ^ value;
        vars.write(identName, value);
    }
    else if (op == "print")
    {
        cout << value << endl;
    }
}

void NovStmtIfElse::evaluate(Vars &vars)
{
    Value value = condition->evaluate(vars);
    Value cmp = value != Value(0);
    if (cmp.intValue != 0)
    {
        if (trueStmtList != NULL)
        {
            trueStmtList->evaluate(vars);
        }
    }
    else
    {
        if (falseStmtList != NULL)
        {
            falseStmtList->evaluate(vars);
        }
    }
}

void NovStmtWhile::evaluate(Vars &vars)
{
    while (true)
    {
        Value value = condition->evaluate(vars);
        Value cmp = value != Value(0);
        if (cmp.intValue != 0)
        {
            if (loopStmtList != NULL)
            {
                loopStmtList->evaluate(vars);
            }
        }
        else
        {
            break;
        }
    }
}

void NovStmtFor::evaluate(Vars &vars)
{
    Value fromValue = from->evaluate(vars);
    Value toValue = to->evaluate(vars);
    Value cmp = fromValue <= toValue;
    Value step(1);
    while (true)
    {
        cmp = fromValue < toValue;
        vars.write(identName, fromValue);
        if (cmp.intValue != 0)
        {
            if (loopStmtList != NULL)
            {
                loopStmtList->evaluate(vars);
            }
        }
        else
        {
            break;
        }
        fromValue = fromValue + step;
    }
}

void NovStatement::evaluate(Vars &vars)
{
    //cout << "Evaluate NovStatement" << endl;
}

void NovStatementList::evaluate(Vars &vars)
{
    //cout << "Evaluate NovStatementList" << endl;
    list<NovStatement *>::iterator it = stmtList.begin();
    for (it = stmtList.begin(); it != stmtList.end(); it++)
    {
        (*it)->evaluate(vars);
    }
}

void NovProgram::evaluate()
{
    //cout << "Evaluate NovProgram" << endl;
    statmentList->evaluate(vars);
}