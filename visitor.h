#pragma once

#include "expr.h"

#include <string>
#include <stack>

/* Visitor */

class Visitor {
public:
    virtual ~Visitor() { }

    virtual void accept(const AddExpr& expr) = 0;
    virtual void accept(const SubExpr& expr) = 0;
    virtual void accept(const MulExpr& expr) = 0;
    virtual void accept(const DivExpr& expr) = 0;
    virtual void accept(const PlusExpr& expr) = 0;
    virtual void accept(const MinusExpr& expr) = 0;
    virtual void accept(const ConstExpr& expr) = 0;
    virtual void accept(const VarExpr& expr) = 0;
};

/* EvalVisitor */

class EvalVisitor : public Visitor {
public:
    virtual void accept(const AddExpr& expr);

    virtual void accept(const SubExpr& expr);

    virtual void accept(const MulExpr& expr);

    virtual void accept(const DivExpr& expr);

    virtual void accept(const MinusExpr& expr);

    virtual void accept(const PlusExpr& expr);

    virtual void accept(const ConstExpr& expr);

    virtual void accept(const VarExpr& expr);

    double result() const;

private:
    std::stack<double> m_stack;
};

/* PrintVisitor */

class PrintVisitor : public Visitor {
public:
    virtual void accept(const AddExpr& expr);

    virtual void accept(const SubExpr& expr);

    virtual void accept(const MulExpr& expr);

    virtual void accept(const DivExpr& expr);

    virtual void accept(const MinusExpr& expr);

    virtual void accept(const PlusExpr& expr);

    virtual void accept(const ConstExpr& expr);

    virtual void accept(const VarExpr& expr);

    std::string result() const;

private:
    std::stack<std::string> m_stack;
};
