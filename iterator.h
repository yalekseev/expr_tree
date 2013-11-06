#pragma once

#include <memory>
#include <string>
#include <stack>

class Expr;
class IteratorImpl;

class Iterator {
public:
    explicit Iterator(const std::string& type, Expr* expr = 0);

    Iterator& operator++();

    Expr* operator->();

    Expr& operator*();

private:
    std::shared_ptr<IteratorImpl> m_impl;
};

class IteratorImpl {
public:
    virtual ~IteratorImpl() { }

    virtual IteratorImpl& operator++() = 0;

    virtual Expr* operator->() = 0;
    virtual Expr& operator*() = 0;
};

class PostOrderIteratorImpl : public IteratorImpl {
public:
    explicit PostOrderIteratorImpl(Expr* expr = 0);

    void get_next(Expr* expr);

    PostOrderIteratorImpl& operator++();

    virtual Expr& operator*();

    virtual Expr* operator->();

    bool operator==(const PostOrderIteratorImpl& other) const;

private:
    std::stack<Expr*> m_stack;
};
