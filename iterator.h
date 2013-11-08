#pragma once

#include <memory>
#include <string>
#include <queue>
#include <stack>

namespace util {

class Expr;

namespace impl {
class IteratorImpl;
}

/*! \brief Iterator class used directly by user */
class Iterator final {
public:
    Iterator() = delete;

    Iterator(const std::string& type, Expr* expr);

    Iterator& operator++();

    Expr* operator->();

    Expr& operator*();

    bool operator==(const Iterator& other) const;

    bool operator!=(const Iterator& other) const;

private:
    std::shared_ptr<impl::IteratorImpl> m_impl;
};

namespace impl {

/*! \brief A base class of concrete iterators hierarchy */
class IteratorImpl {
public:
    virtual ~IteratorImpl() { }

    virtual IteratorImpl& operator++() = 0;

    virtual Expr* operator->() = 0;

    virtual Expr& operator*() = 0;

    virtual bool operator==(const IteratorImpl& other) const = 0;

    virtual bool operator!=(const IteratorImpl& other) const = 0;
};

/*! \brief Implementation of pre-order iterator */
class PreOrderIteratorImpl : public IteratorImpl {
public:
    explicit PreOrderIteratorImpl(Expr* expr = 0);

    virtual PreOrderIteratorImpl& operator++();

    virtual Expr* operator->();

    virtual Expr& operator*();

    virtual bool operator==(const IteratorImpl& other) const;

    virtual bool operator!=(const IteratorImpl& other) const;

    std::stack<Expr*> m_stack;
};

/*! \brief Implementation of in-order iterator */
class InOrderIteratorImpl : public IteratorImpl {
public:
    explicit InOrderIteratorImpl(Expr* expr = 0);

    virtual InOrderIteratorImpl& operator++();

    virtual Expr* operator->();

    virtual Expr& operator*();

    virtual bool operator==(const IteratorImpl& other) const;

    virtual bool operator!=(const IteratorImpl& other) const;

private:
    void get_next(Expr* expr);

    std::stack<Expr*> m_stack;
};

/*! \brief Implementation of post-order iterator */
class PostOrderIteratorImpl : public IteratorImpl {
public:
    explicit PostOrderIteratorImpl(Expr* expr = 0);

    virtual PostOrderIteratorImpl& operator++();

    virtual Expr& operator*();

    virtual Expr* operator->();

    virtual bool operator==(const IteratorImpl& other) const;

    virtual bool operator!=(const IteratorImpl& other) const;

private:
    void get_next(Expr* expr);

    std::stack<Expr*> m_stack;
};

/*! \brief Implementation of level-order iterator */
class LevelOrderIteratorImpl : public IteratorImpl {
public:
    explicit LevelOrderIteratorImpl(Expr* expr = 0);

    virtual LevelOrderIteratorImpl& operator++();

    virtual Expr& operator*();

    virtual Expr* operator->();

    virtual bool operator==(const IteratorImpl& other) const;

    virtual bool operator!=(const IteratorImpl& other) const;

private:
    std::queue<Expr*> m_queue;
};

} // namespace impl

} // namespace util
