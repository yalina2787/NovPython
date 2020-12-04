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
        else if (op == "||")
        {
            return e1->evaluate(vars) || e2->evaluate(vars);
        }
        else if (op == "&&")
        {
            return e1->evaluate(vars) && e2->evaluate(vars);
        }
    }
    else if (e2 != NULL)
    {
        if (op == "str")
        {
            Value v = e2->evaluate(vars);
            ostringstream os;
            os.str("");
            os << v;
            v.type = 3;
            v.stringValue = os.str();
            return v;
        }
        else if (op == "int")
        {
            Value v = e2->evaluate(vars);
            ostringstream os;
            os.str("");
            os << v;
            v.type = 0;
            v.intValue = stoi(os.str());
            return v;
        }
        else if (op == "-")
        {
            Value v = e2->evaluate(vars);
            v = Value(0) - v;
            return v;
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

void NovAssignment::evaluate(Vars &vars, bool &breakFlag)
{
    if (e1 != NULL)
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
    else
    {
        if (op == "break")
        {
            breakFlag = true;
        }
    }
}

void NovStmtIfElse::evaluate(Vars &vars, bool &breakFlag)
{

    list<NovExpression *>::iterator eit = conditions.begin();
    list<NovStatementList *>::iterator sit = stmtLists.begin();

    bool flag = false;
    for (eit = conditions.begin(); eit != conditions.end(); eit++, sit++)
    {
        if (!flag)
        {

            Value value = (*eit)->evaluate(vars);
            Value cmp = value != Value(0);
            if (cmp.intValue != 0)
            {
                (*sit)->evaluate(vars, breakFlag);
                flag = true;
                break;
            }
        }
    }
    if (!flag && sit != stmtLists.end())
    {

        (*sit)->evaluate(vars, breakFlag);
    }

    /*
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
    }*/
}

void NovStmtWhile::evaluate(Vars &vars, bool &breakFlag)
{
    while (true)
    {
        Value value = condition->evaluate(vars);
        Value cmp = value != Value(0);
        if (cmp.intValue != 0)
        {
            if (loopStmtList != NULL)
            {
                loopStmtList->evaluate(vars, breakFlag);
                if (breakFlag)
                {
                    break;
                }
            }
        }
        else
        {
            break;
        }
    }
    breakFlag = false;
}

void NovStmtFor::evaluate(Vars &vars, bool &breakFlag)
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
                loopStmtList->evaluate(vars, breakFlag);
                if (breakFlag)
                {
                    break;
                }
            }
        }
        else
        {
            break;
        }
        fromValue = fromValue + step;
    }
    breakFlag = false;
}

void NovStatement::evaluate(Vars &vars, bool &breakFlag)
{
    //cout << "Evaluate NovStatement" << endl;
}

void NovStatementList::evaluate(Vars &vars, bool &breakFlag)
{
    //cout << "Evaluate NovStatementList" << endl;
    list<NovStatement *>::iterator it = stmtList.begin();
    for (it = stmtList.begin(); it != stmtList.end(); it++)
    {
        (*it)->evaluate(vars, breakFlag);
        if (breakFlag)
        {
            break;
        }
    }
}

void NovProgram::evaluate()
{
    //cout << "Evaluate NovProgram" << endl;
    bool breakFlag = false;
    statmentList->evaluate(vars, breakFlag);
}