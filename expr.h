#pragma once

#include "iterator.h"

#include <memory>
#include <string>

class Visitor;

class Expr {
public:
    virtual ~Expr() { }

    virtual void accept(Visitor& visitor) = 0;

    Iterator begin(const std::string& traversal = "post-order");

    Iterator end(const std::string& traversal = "post-order");

    virtual std::shared_ptr<Expr> left() const {
        return 0;
    }

    virtual std::shared_ptr<Expr> right() const {
        return 0;
    }
};

class UnaryExpr : public Expr {
public:
    explicit UnaryExpr(std::shared_ptr<Expr> expr) : m_expr(expr) { }

    virtual std::shared_ptr<Expr> right() const {
        return m_expr;
    }

    std::shared_ptr<Expr> m_expr;
};

class BinaryExpr : public Expr {
public:
    BinaryExpr(std::shared_ptr<Expr> left, std::shared_ptr<Expr> right) : m_left(left), m_right(right) { }

    virtual std::shared_ptr<Expr> left() const {
        return m_left;
    }

    virtual std::shared_ptr<Expr> right() const {
        return m_right;
    }

    std::shared_ptr<Expr> m_left;
    std::shared_ptr<Expr> m_right;
};

class ConstExpr : public Expr {
public:
    explicit ConstExpr(double val) : m_val(val) { }

    virtual void accept(Visitor& visitor);

    operator double() const {
        return m_val;
    }

    double m_val;
};

class VarExpr : public Expr {
public:
    explicit VarExpr(const std::string& name) : m_name(name) { }

    virtual void accept(Visitor& visitor);

    std::string m_name;
};

/* Binary expressions */

class AddExpr : public BinaryExpr {
public:
    AddExpr(std::shared_ptr<Expr> left, std::shared_ptr<Expr> right) : BinaryExpr (left, right) { }

    virtual void accept(Visitor& visitor);
};

class SubExpr : public BinaryExpr {
public:
    SubExpr(std::shared_ptr<Expr> left, std::shared_ptr<Expr> right) : BinaryExpr(left, right) { }

    virtual void accept(Visitor& visitor);
};

class MulExpr : public BinaryExpr {
public:
    MulExpr(std::shared_ptr<Expr> left, std::shared_ptr<Expr> right) : BinaryExpr(left, right) { }

    virtual void accept(Visitor& visitor);
};

class DivExpr : public BinaryExpr {
public:
    DivExpr(std::shared_ptr<Expr> left, std::shared_ptr<Expr> right) : BinaryExpr(left, right) { }

    virtual void accept(Visitor& visitor);
};

/* Unary expressions */

class MinusExpr : public UnaryExpr {
public:
    explicit MinusExpr(std::shared_ptr<Expr> expr) : UnaryExpr(expr) { }

    virtual void accept(Visitor& visitor);
};

class PlusExpr : public UnaryExpr {
public:
    explicit PlusExpr(std::shared_ptr<Expr> expr) : UnaryExpr(expr) { }

    virtual void accept(Visitor& visitor);
};

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
