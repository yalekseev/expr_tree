#include "visitor.h"
#include "expr.h"

/* EvalVisitor */

void EvalVisitor::accept(const AddExpr& expr) {
    double right = m_stack.top();
    m_stack.pop();

    double left = m_stack.top();
    m_stack.pop();

    m_stack.push(left + right);
}

void EvalVisitor::accept(const SubExpr& expr) {
    double right = m_stack.top();
    m_stack.pop();

    double left = m_stack.top();
    m_stack.pop();

    m_stack.push(left - right);
}

void EvalVisitor::accept(const MulExpr& expr) {
    double right = m_stack.top();
    m_stack.pop();

    double left = m_stack.top();
    m_stack.pop();

    m_stack.push(left * right);
}

void EvalVisitor::accept(const DivExpr& expr) {
    double right = m_stack.top();
    m_stack.pop();

    double left = m_stack.top();
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

/* PrintVisitor */

void PrintVisitor::accept(const AddExpr& expr) {
    os << " + ";
}

void PrintVisitor::accept(const SubExpr& expr) {
    os << " - ";
}

void PrintVisitor::accept(const MulExpr& expr) {
    os << " * ";
}

void PrintVisitor::accept(const DivExpr& expr) {
    os << " / ";
}

void PrintVisitor::accept(const MinusExpr& expr) {
    os << "-";
}

void PrintVisitor::accept(const PlusExpr& expr) {
    os << "+";
}

void PrintVisitor::accept(const ConstExpr& expr) {
    os << " " << std::to_string(static_cast<double>(expr)) << " ";
}

void PrintVisitor::accept(const VarExpr& expr) {
    // do nothing
}

std::string PrintVisitor::result() const {
    return os.str();
}
