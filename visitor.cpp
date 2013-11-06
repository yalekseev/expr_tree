#include "visitor.h"
#include "expr.h"


void EvalVisitor::accept(const AddExpr& expr) {
    double left = m_stack.top();
    m_stack.pop();

    double right = m_stack.top();
    m_stack.pop();

    m_stack.push(left + right);
}

void EvalVisitor::accept(const SubExpr& expr) {
    double left = m_stack.top();
    m_stack.pop();

    double right = m_stack.top();
    m_stack.pop();

    m_stack.push(left - right);
}

void EvalVisitor::accept(const MulExpr& expr) {
    double left = m_stack.top();
    m_stack.pop();

    double right = m_stack.top();
    m_stack.pop();

    m_stack.push(left * right);
}

void EvalVisitor::accept(const DivExpr& expr) {
    double left = m_stack.top();
    m_stack.pop();

    double right = m_stack.top();
    m_stack.pop();

    m_stack.push(left / right);
}

void EvalVisitor::accept(const MinusExpr& expr) {
    double val = m_stack.top();
    m_stack.pop();

    m_stack.push(-1 * val);
}

void EvalVisitor::accept(const PlusExpr& expr) {
    // do nothing
}

void EvalVisitor::accept(const ConstExpr& expr) {
    m_stack.push(expr);
}

void EvalVisitor::accept(const VarExpr& expr) {
    // do nothing
}

double EvalVisitor::result() const {
    return m_stack.top();
}
