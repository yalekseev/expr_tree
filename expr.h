#pragma once

#include "iterator.h"

#include <memory>
#include <string>

class Visitor;

class Expr {
public:
    typedef Iterator iterator;

    virtual ~Expr() { }

    virtual void accept(Visitor& visitor) = 0;

    iterator begin(const std::string& traversal = "post-order");

    iterator end(const std::string& traversal = "post-order");

    virtual std::shared_ptr<Expr> left() const;

    virtual std::shared_ptr<Expr> right() const;
};

class UnaryExpr : public Expr {
public:
    explicit UnaryExpr(std::shared_ptr<Expr> expr);

    virtual std::shared_ptr<Expr> right() const;

private:
    std::shared_ptr<Expr> m_expr;
};

class BinaryExpr : public Expr {
public:
    BinaryExpr(std::shared_ptr<Expr> left, std::shared_ptr<Expr> right);

    virtual std::shared_ptr<Expr> left() const;

    virtual std::shared_ptr<Expr> right() const;

private:
    std::shared_ptr<Expr> m_left;
    std::shared_ptr<Expr> m_right;
};

class ConstExpr : public Expr {
public:
    explicit ConstExpr(double val);

    virtual void accept(Visitor& visitor);

    operator double() const;

private:
    double m_val;
};

class VarExpr : public Expr {
public:
    explicit VarExpr(const std::string& name);

    virtual void accept(Visitor& visitor);

    operator std::string() const;

private:
    std::string m_name;
};

/* Binary expressions */

class AddExpr : public BinaryExpr {
public:
    AddExpr(std::shared_ptr<Expr> left, std::shared_ptr<Expr> right);

    virtual void accept(Visitor& visitor);
};

class SubExpr : public BinaryExpr {
public:
    SubExpr(std::shared_ptr<Expr> left, std::shared_ptr<Expr> right);

    virtual void accept(Visitor& visitor);
};

class MulExpr : public BinaryExpr {
public:
    MulExpr(std::shared_ptr<Expr> left, std::shared_ptr<Expr> right);

    virtual void accept(Visitor& visitor);
};

class DivExpr : public BinaryExpr {
public:
    DivExpr(std::shared_ptr<Expr> left, std::shared_ptr<Expr> right);

    virtual void accept(Visitor& visitor);
};

/* Unary expressions */

class MinusExpr : public UnaryExpr {
public:
    explicit MinusExpr(std::shared_ptr<Expr> expr);

    virtual void accept(Visitor& visitor);
};

class PlusExpr : public UnaryExpr {
public:
    explicit PlusExpr(std::shared_ptr<Expr> expr);

    virtual void accept(Visitor& visitor);
};

/* Helper functions for binary expressions */

extern std::shared_ptr<Expr> Add(std::shared_ptr<Expr> left, std::shared_ptr<Expr> right);

extern std::shared_ptr<Expr> Sub(std::shared_ptr<Expr> left, std::shared_ptr<Expr> right);

extern std::shared_ptr<Expr> Mul(std::shared_ptr<Expr> left, std::shared_ptr<Expr> right);

extern std::shared_ptr<Expr> Div(std::shared_ptr<Expr> left, std::shared_ptr<Expr> right);

/* Helper functions for unary expressions */

extern std::shared_ptr<Expr> Minus(std::shared_ptr<Expr> expr);

extern std::shared_ptr<Expr> Plus(std::shared_ptr<Expr> expr);

extern std::shared_ptr<Expr> Const(double val);

extern std::shared_ptr<Expr> Var(const std::string& name);
