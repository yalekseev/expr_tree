#pragma once

#include "expr.h"
#include "iterator.h"

#include <memory>
#include <stack>

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

class EvalVisitor : public Visitor {
public:
    virtual void accept(const AddExpr& expr) {
        double left = m_stack.top();
        m_stack.pop();

        double right = m_stack.top();
        m_stack.pop();

        m_stack.push(left + right);
    }

    virtual void accept(const SubExpr& expr) {
        double left = m_stack.top();
        m_stack.pop();

        double right = m_stack.top();
        m_stack.pop();

        m_stack.push(left - right);
    }

    virtual void accept(const MulExpr& expr) {
        double left = m_stack.top();
        m_stack.pop();

        double right = m_stack.top();
        m_stack.pop();

        m_stack.push(left * right);
    }

    virtual void accept(const DivExpr& expr) {
        double left = m_stack.top();
        m_stack.pop();

        double right = m_stack.top();
        m_stack.pop();

        m_stack.push(left / right);
    }

    virtual void accept(const MinusExpr& expr) {
        double val = m_stack.top();
        m_stack.pop();

        m_stack.push(-1 * val);
    }

    virtual void accept(const PlusExpr& expr) {
        // do nothing
    }

    virtual void accept(const ConstExpr& expr) {
        m_stack.push(expr);
    }

    virtual void accept(const VarExpr& expr) {
        // do nothing
    }

    double result() const {
        return m_stack.top();
    }

private:
    std::stack<double> m_stack;
};
