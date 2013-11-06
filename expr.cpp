#include "expr.h"
#include "visitor.h"
#include "iterator.h"

#include <memory>
#include <string>

Iterator Expr::begin(const std::string& traversal) {
    return Iterator(traversal, static_cast<Expr*>(this));
}

Iterator Expr::end(const std::string& traversal) {
    return Iterator(traversal, 0);
}

void AddExpr::accept(Visitor& visitor) {
    visitor.accept(*this);
}

void SubExpr::accept(Visitor& visitor) {
    visitor.accept(*this);
}

void MulExpr::accept(Visitor& visitor) {
    visitor.accept(*this);
}

void DivExpr::accept(Visitor& visitor) {
    visitor.accept(*this);
}

void MinusExpr::accept(Visitor& visitor) {
    visitor.accept(*this);
}

void PlusExpr::accept(Visitor& visitor) {
    visitor.accept(*this);
}

void ConstExpr::accept(Visitor& visitor) {
    visitor.accept(*this);
}

void VarExpr::accept(Visitor& visitor) {
    visitor.accept(*this);
}

/* Helper functions for binary expressions */

std::shared_ptr<Expr> Add(std::shared_ptr<Expr> left, std::shared_ptr<Expr> right) {
    return std::shared_ptr<Expr>(new AddExpr(left, right));
}

std::shared_ptr<Expr> Sub(std::shared_ptr<Expr> left, std::shared_ptr<Expr> right) {
    return std::shared_ptr<Expr>(new SubExpr(left, right));
}

std::shared_ptr<Expr> Mul(std::shared_ptr<Expr> left, std::shared_ptr<Expr> right) {
    return std::shared_ptr<Expr>(new MulExpr(left, right));
}

std::shared_ptr<Expr> Div(std::shared_ptr<Expr> left, std::shared_ptr<Expr> right) {
    return std::shared_ptr<Expr>(new DivExpr(left, right));
}

/* Helper functions for unary expressions */

std::shared_ptr<Expr> Minus(std::shared_ptr<Expr> expr) {
    return std::shared_ptr<Expr>(new MinusExpr(expr));
}

std::shared_ptr<Expr> Plus(std::shared_ptr<Expr> expr) {
    return std::shared_ptr<Expr>(new PlusExpr(expr));
}

std::shared_ptr<Expr> Const(double val) {
    return std::shared_ptr<Expr>(new ConstExpr(val));
}

std::shared_ptr<Expr> Var(const std::string& name) {
    return std::shared_ptr<Expr>(new VarExpr(name));
}
