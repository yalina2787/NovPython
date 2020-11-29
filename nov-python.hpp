#ifndef NOV_PYTHON_H
#define NOV_PYTHON_H
#include <iostream>

using namespace std;

class Value
{
public:
    Value(const Value &value) : intValue(value.intValue), doubleValue(value.doubleValue), type(value.type) {}
    Value(const int value) : intValue(value), type(0) {}
    Value(const double value) : doubleValue(value), type(1) {}
    double doubleValue;
    int intValue;
    int type; // 0: int 1: double

    friend ostream &operator<<(ostream &out, Value &A);

    Value operator+(const Value &b)
    {
        if (type == 0)
        {
            if (b.type == 0)
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
            if (b.type == 0)
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
        if (type == 0)
        {
            if (b.type == 0)
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
            if (b.type == 0)
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
        if (type == 0)
        {
            if (b.type == 0)
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
            if (b.type == 0)
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
        if (type == 0)
        {
            if (b.type == 0)
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
            if (b.type == 0)
            {
                return Value(doubleValue / b.intValue);
            }
            else
            {
                return Value(doubleValue / b.doubleValue);
            }
        }
    }
    Value operator^(const Value &b)
    {
        if (type == 0)
        {
            if (b.type == 0)
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
            if (b.type == 0)
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
        if (type == 0)
        {
            if (b.type == 0)
            {
                return (intValue < b.intValue) ? Value(1) : Value(0);
            }
            else
            {
                return (intValue < b.doubleValue) ? Value(1) : Value(0);
            }
        }
        else
        {
            if (b.type == 0)
            {
                return (doubleValue < b.intValue) ? Value(1) : Value(0);
            }
            else
            {
                return (doubleValue < b.doubleValue) ? Value(1) : Value(0);
            }
        }
    }
};

class NovStatement
{
public:
    NovStatement() {}
};

class NovExpression
{
public:
    virtual Value evaluate() const;
    NovExpression(){};
    NovExpression(NovExpression *_e1, int _op, NovExpression *_e2) : e1(_e1), e2(_e2), op(_op){};

protected:
    NovExpression *e1;
    NovExpression *e2;
    int op;
};

class NovConstant : public NovExpression
{
public:
    virtual Value evaluate() const;
    NovConstant(Value _value) : value(_value)
    {
        cout << "Value::" << value << endl;
    };
    Value value;
};

class NovIdent : public NovExpression
{
public:
    virtual Value evaluate() const;
    NovIdent(string _name) : name(_name)
    {
        cout << "Name::" << name << endl;
    };
    string name;
};

#endif