#include "expr.h"
#include "visitor.h"
#include "iterator.h"

#include <memory>
#include <string>

/* Expr */

Expr::iterator Expr::begin(const std::string& traversal) {
    return iterator(traversal, static_cast<Expr*>(this));
}

Expr::iterator Expr::end(const std::string& traversal) {
    return iterator(traversal, 0);
}

std::shared_ptr<Expr> Expr::left() const {
    return 0;
}

std::shared_ptr<Expr> Expr::right() const {
    return 0;
}

/* UnaryExpr */

UnaryExpr::UnaryExpr(std::shared_ptr<Expr> expr) : m_expr(expr) { }

std::shared_ptr<Expr> UnaryExpr::left() const {
    return m_expr;
}

/* BinaryExpr */

BinaryExpr::BinaryExpr(std::shared_ptr<Expr> left, std::shared_ptr<Expr> right)
        : m_left(left), m_right(right) { }

std::shared_ptr<Expr> BinaryExpr::left() const {
    return m_left;
}

std::shared_ptr<Expr> BinaryExpr::right() const {
    return m_right;
}

/* AddExpr */

AddExpr::AddExpr(std::shared_ptr<Expr> left, std::shared_ptr<Expr> right)
        : BinaryExpr (left, right) { }

void AddExpr::accept(Visitor& visitor) {
    visitor.accept(*this);
}

/* SubExpr */

SubExpr::SubExpr(std::shared_ptr<Expr> left, std::shared_ptr<Expr> right)
        : BinaryExpr(left, right) { }

void SubExpr::accept(Visitor& visitor) {
    visitor.accept(*this);
}

/* MulExpr */

MulExpr::MulExpr(std::shared_ptr<Expr> left, std::shared_ptr<Expr> right)
        : BinaryExpr(left, right) { }

void MulExpr::accept(Visitor& visitor) {
    visitor.accept(*this);
}

/* DivExpr */

DivExpr::DivExpr(std::shared_ptr<Expr> left, std::shared_ptr<Expr> right)
        : BinaryExpr(left, right) { }

void DivExpr::accept(Visitor& visitor) {
    visitor.accept(*this);
}

/* MinusExpr */

MinusExpr::MinusExpr(std::shared_ptr<Expr> expr) : UnaryExpr(expr) { }

void MinusExpr::accept(Visitor& visitor) {
    visitor.accept(*this);
}

/* PlusExpr */

PlusExpr::PlusExpr(std::shared_ptr<Expr> expr) : UnaryExpr(expr) { }

void PlusExpr::accept(Visitor& visitor) {
    visitor.accept(*this);
}

/* ConstExpr */

ConstExpr::ConstExpr(double val) : m_val(val) { }

ConstExpr::operator double() const {
    return m_val;
}

void ConstExpr::accept(Visitor& visitor) {
    visitor.accept(*this);
}

/* VarExpr */

VarExpr::VarExpr(const std::string& name) : m_name(name) { }

VarExpr::operator std::string() const {
    return m_name;
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
