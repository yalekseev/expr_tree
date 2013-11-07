#pragma once

#include <memory>
#include <string>
#include <stack>

class Expr;
class IteratorImpl;

class Iterator final {
public:
    Iterator(const std::string& type, Expr* expr);

    Iterator& operator++();

    Expr* operator->();

    Expr& operator*();

    bool operator==(const Iterator& other) const;

    bool operator!=(const Iterator& other) const;

private:
    std::shared_ptr<IteratorImpl> m_impl;
};

class IteratorImpl {
public:
    virtual ~IteratorImpl() { }

    virtual IteratorImpl& operator++() = 0;

    virtual Expr* operator->() = 0;

    virtual Expr& operator*() = 0;

    virtual bool operator==(const IteratorImpl& other) const = 0;

    virtual bool operator!=(const IteratorImpl& other) const = 0;
};

/* PostOrderIteratorImpl */

class PostOrderIteratorImpl : public IteratorImpl {
public:
    explicit PostOrderIteratorImpl(Expr* expr = 0);

    void get_next(Expr* expr);

    PostOrderIteratorImpl& operator++();

    virtual Expr& operator*();

    virtual Expr* operator->();

    bool operator==(const IteratorImpl& other) const;

    bool operator!=(const IteratorImpl& other) const;

private:
    std::stack<Expr*> m_stack;
};

/* InOrderIteratorImpl */

class InOrderIteratorImpl : public IteratorImpl {

};
