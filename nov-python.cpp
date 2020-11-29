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
    else
    {
        out << A.doubleValue;
    }
    return out;
}

Value NovExpression::evaluate(const Vars &vars) const
{
    Value value(0);
    //cout << e1 << " " << op << " " << e2 << endl;
    if (e1 != NULL && e2 != NULL)
    {
        // Binary Expression
        if (op == '+')
        {
            Value vvv = e1->evaluate(vars) + e2->evaluate(vars);
            cout << "+:" << vvv << endl;
            return e1->evaluate(vars) + e2->evaluate(vars);
        }
        else if (op == '-')
        {
            return e1->evaluate(vars) - e2->evaluate(vars);
        }
        else if (op == '*')
        {
            return e1->evaluate(vars) * e2->evaluate(vars);
        }
        else if (op == '/')
        {
            return e1->evaluate(vars) / e2->evaluate(vars);
        }
        else if (op == '^')
        {
            return e1->evaluate(vars) ^ e2->evaluate(vars);
        }
        else if (op == '<')
        {
            return e1->evaluate(vars) < e2->evaluate(vars);
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
        vars.write(identName, e1->evaluate(vars));
    }
    else if (op == "+=")
    {
        value = vars.fetch(identName) + value;
        vars.write(identName, e1->evaluate(vars));
    }
    cout << "Evaluate Assignment: " << value << endl;
}

void NovStatement::evaluate(Vars &vars)
{
    cout << "Evaluate NovStatement: " << endl;
}

void NovStatementList::evaluate(Vars &vars)
{
    cout << "Evaluate NovStatementList: " << endl;
    list<NovStatement *>::iterator it = stmtList.begin();
    for (it = stmtList.begin(); it != stmtList.end(); it++)
    {
        (*it)->evaluate(vars);
    }
}

void NovProgram::evaluate()
{
    cout << "Evaluate NovProgram: " << endl;
    statmentList->evaluate(vars);
}