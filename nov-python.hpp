#ifndef NOV_PYTHON_H
#define NOV_PYTHON_H
#include <iostream>
#include <string>
#include <map>
#include <list>

using namespace std;
using std::string;

class Value
{
public:
    Value() {}
    Value(const Value &value) : intValue(value.intValue), doubleValue(value.doubleValue), stringValue(value.stringValue), type(value.type) {}
    Value(const int value) : intValue(value), type(0) {}
    Value(const double value) : doubleValue(value), type(1) {}
    Value(const string value) : stringValue(value), type(3) {}
    Value(const bool value) : intValue(value ? 1 : 0), type(2) {}
    void copy(const Value &value)
    {
        intValue = value.intValue;
        doubleValue = value.doubleValue;
        stringValue = value.stringValue;
        type = value.type;
    }
    double doubleValue;
    int intValue;
    string stringValue;
    int type; // 0: int 1: double 2: bool 3: string

    friend ostream &operator<<(ostream &out, Value &A);

    Value &operator=(const Value &b)
    {
        intValue = b.intValue;
        doubleValue = b.doubleValue;
        stringValue = b.stringValue;
        type = b.type;
        return *this;
    }

    Value operator+(const Value &b)
    {
        if (type == 3 || b.type == 3)
        {
            return Value(stringValue + b.stringValue);
        }
        else if (type == 0 || type == 2)
        {
            if (b.type == 0 || b.type == 2)
            {
                return Value(intValue + b.intValue);
            }
            else
            {
                return Value(intValue + b.doubleValue);
            }
        }
        else
        {
            if (b.type == 0 || b.type == 2)
            {
                return Value(doubleValue + b.intValue);
            }
            else
            {
                return Value(doubleValue + b.doubleValue);
            }
        }
    }

    Value operator-(const Value &b)
    {
        if (type == 3 || b.type == 3)
        {
            return Value(stringValue + b.stringValue);
        }
        else if (type == 0 || type == 2)
        {
            if (b.type == 0 || b.type == 2)
            {
                return Value(intValue - b.intValue);
            }
            else
            {
                return Value(intValue - b.doubleValue);
            }
        }
        else
        {
            if (b.type == 0 || b.type == 2)
            {
                return Value(doubleValue - b.intValue);
            }
            else
            {
                return Value(doubleValue - b.doubleValue);
            }
        }
    }
    Value operator*(const Value &b)
    {
        if (type == 3 || b.type == 3)
        {
            return Value(stringValue + b.stringValue);
        }
        else if (type == 0 || type == 2)
        {
            if (b.type == 0 || b.type == 2)
            {
                return Value(intValue * b.intValue);
            }
            else
            {
                return Value(intValue * b.doubleValue);
            }
        }
        else
        {
            if (b.type == 0 || b.type == 2)
            {
                return Value(doubleValue * b.intValue);
            }
            else
            {
                return Value(doubleValue * b.doubleValue);
            }
        }
    }
    Value operator/(const Value &b)
    {
        if (type == 3 || b.type == 3)
        {
            return Value(stringValue + b.stringValue);
        }
        else if (type == 0 || type == 2)
        {
            if (b.type == 0 || b.type == 2)
            {
                return Value(intValue * 1.0 / b.intValue);
            }
            else
            {
                return Value(intValue / b.doubleValue);
            }
        }
        else
        {
            if (b.type == 0 || b.type == 2)
            {
                return Value(doubleValue / b.intValue);
            }
            else
            {
                return Value(doubleValue / b.doubleValue);
            }
        }
    }
    Value operator%(const Value &b)
    {
        if (type == 3 || b.type == 3)
        {
            return Value(stringValue + b.stringValue);
        }
        else if (type == 0 || type == 2)
        {
            if (b.type == 0 || b.type == 2)
            {
                return Value(intValue % b.intValue);
            }
            else
            {
                return Value(fmod(intValue, b.doubleValue));
            }
        }
        else
        {
            if (b.type == 0 || b.type == 2)
            {
                return Value(fmod(doubleValue, b.intValue));
            }
            else
            {
                return Value(fmod(doubleValue, b.doubleValue));
            }
        }
    }
    Value operator^(const Value &b)
    {
        if (type == 3 || b.type == 3)
        {
            return Value(stringValue + b.stringValue);
        }
        else if (type == 0 || type == 2)
        {
            if (b.type == 0 || b.type == 2)
            {
                return Value(intValue ^ b.intValue);
            }
            else
            {
                return Value(0);
            }
        }
        else
        {
            if (b.type == 0 || b.type == 2)
            {
                return Value(0);
            }
            else
            {
                return Value(0);
            }
        }
    }
    Value operator<(const Value &b)
    {
        if (type == 3 || b.type == 3)
        {
            return Value(stringValue + b.stringValue);
        }
        else if (type == 0 || type == 2)
        {
            if (b.type == 0 || b.type == 2)
            {
                return Value(intValue < b.intValue);
            }
            else
            {
                return Value(intValue < b.doubleValue);
            }
        }
        else
        {
            if (b.type == 0 || b.type == 2)
            {
                return Value(doubleValue < b.intValue);
            }
            else
            {
                return Value(doubleValue < b.doubleValue);
            }
        }
    }
    Value operator<=(const Value &b)
    {
        if (type == 3 || b.type == 3)
        {
            return Value(stringValue + b.stringValue);
        }
        else if (type == 0 || type == 2)
        {
            if (b.type == 0 || b.type == 2)
            {
                return Value(intValue <= b.intValue);
            }
            else
            {
                return Value(intValue <= b.doubleValue);
            }
        }
        else
        {
            if (b.type == 0 || b.type == 2)
            {
                return Value(doubleValue <= b.intValue);
            }
            else
            {
                return Value(doubleValue <= b.doubleValue);
            }
        }
    }
    Value operator>(const Value &b)
    {
        if (type == 3 || b.type == 3)
        {
            return Value(stringValue + b.stringValue);
        }
        else if (type == 0 || type == 2)
        {
            if (b.type == 0 || b.type == 2)
            {
                return Value(intValue > b.intValue);
            }
            else
            {
                return Value(intValue > b.doubleValue);
            }
        }
        else
        {
            if (b.type == 0 || b.type == 2)
            {
                return Value(doubleValue > b.intValue);
            }
            else
            {
                return Value(doubleValue > b.doubleValue);
            }
        }
    }
    Value operator>=(const Value &b)
    {
        if (type == 3 || b.type == 3)
        {
            return Value(stringValue + b.stringValue);
        }
        else if (type == 0 || type == 2)
        {
            if (b.type == 0 || b.type == 2)
            {
                return Value(intValue >= b.intValue);
            }
            else
            {
                return Value(intValue >= b.doubleValue);
            }
        }
        else
        {
            if (b.type == 0 || b.type == 2)
            {
                return Value(doubleValue >= b.intValue);
            }
            else
            {
                return Value(doubleValue >= b.doubleValue);
            }
        }
    }
    Value operator==(const Value &b)
    {
        if (type == 3 || b.type == 3)
        {
            return Value(stringValue == b.stringValue);
        }
        else if (type == 0 || type == 2)
        {
            if (b.type == 0 || b.type == 2)
            {
                return Value(intValue == b.intValue);
            }
            else
            {
                return Value(intValue == b.doubleValue);
            }
        }
        else
        {
            if (b.type == 0 || b.type == 2)
            {
                return Value(doubleValue == b.intValue);
            }
            else
            {
                return Value(doubleValue == b.doubleValue);
            }
        }
    }

    Value operator!=(const Value &b)
    {
        if (type == 3 || b.type == 3)
        {
            return Value(stringValue != b.stringValue);
        }
        else if (type == 0 || type == 2)
        {
            if (b.type == 0 || b.type == 2)
            {
                return Value(intValue != b.intValue);
            }
            else
            {
                return Value(intValue != b.doubleValue);
            }
        }
        else
        {
            if (b.type == 0 || b.type == 2)
            {
                return Value(doubleValue != b.intValue);
            }
            else
            {
                return Value(doubleValue != b.doubleValue);
            }
        }
    }
};
class Vars;

class NovExpression;

class NovExpression
{
public:
    virtual Value evaluate(const Vars &vars) const;
    NovExpression(){};
    NovExpression(NovExpression *_e1, string _op, NovExpression *_e2) : e1(_e1), e2(_e2), op(_op){};

protected:
    NovExpression *e1;
    NovExpression *e2;
    string op;
};

class NovConstant : public NovExpression
{
public:
    virtual Value evaluate(const Vars &vars) const;
    NovConstant(Value _value) : value(_value){};
    Value value;
};

class NovIdent : public NovExpression
{
public:
    virtual Value evaluate(const Vars &vars) const;
    NovIdent(string _name) : name(_name){};
    string name;
};

class Vars
{
public:
    Vars() {}
    Value fetch(string identName) const
    {
        if (vars.find(identName) != vars.end())
        {
            return vars.find(identName)->second;
        }
        else
        {
            return Value(0);
        }
    }

    void write(string identName, const Value &value)
    {
        map<string, Value>::iterator iter;
        iter = vars.find(identName);
        if (iter != vars.end())
        {
            vars[identName] = value;
        }
        else
        {
            vars[identName] = value;
        }
    }
    map<string, Value> vars;
};

class NovStatement
{
public:
    virtual void evaluate(Vars &vars);
    NovStatement() {}
};

class NovAssignment : public NovStatement
{
public:
    virtual void evaluate(Vars &vars);
    NovAssignment(string _identName, string _op, NovExpression *_e1) : identName(_identName), e1(_e1), op(_op) {}

protected:
    NovExpression *e1;
    string identName;
    string op;
};

class NovStatementList
{
public:
    void evaluate(Vars &vars);
    void push(NovStatement *stmt)
    {
        stmtList.push_back(stmt);
    }
    NovStatementList() {}
    list<NovStatement *> stmtList;
};

class NovStmtIfElse : public NovStatement
{
public:
    virtual void evaluate(Vars &vars);
    NovStmtIfElse(NovExpression *_condition, NovStatementList *_trueStmtList, NovStatementList *_falseStmtList)
        : condition(_condition), trueStmtList(_trueStmtList), falseStmtList(_falseStmtList) {}

protected:
    NovExpression *condition;
    NovStatementList *trueStmtList;
    NovStatementList *falseStmtList;
};

class NovStmtWhile : public NovStatement
{
public:
    virtual void evaluate(Vars &vars);
    NovStmtWhile(NovExpression *_condition, NovStatementList *_loopStmtList)
        : condition(_condition), loopStmtList(_loopStmtList) {}

protected:
    NovExpression *condition;
    NovStatementList *loopStmtList;
};

class NovStmtFor : public NovStatement
{
public:
    virtual void evaluate(Vars &vars);
    NovStmtFor(string _identName, NovExpression *_from, NovExpression *_to, NovStatementList *_loopStmtList)
        : identName(_identName), from(_from), to(_to), loopStmtList(_loopStmtList) {}

protected:
    string identName;
    NovExpression *from;
    NovExpression *to;
    NovStatementList *loopStmtList;
};

class NovProgram
{
public:
    void evaluate();
    NovProgram(NovStatementList *_statmentList) : statmentList(_statmentList)
    {
    }
    Vars vars;
    NovStatementList *statmentList;
};
#endif