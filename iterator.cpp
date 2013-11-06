#include "iterator.h"
#include "expr.h"

#include <memory>
#include <string>

#include <iostream>

Iterator::Iterator(const std::string& type, Expr* expr) {
    if (type == "post-order") {
        m_impl.reset(new PostOrderIteratorImpl(expr));
    }
}

Iterator& Iterator::operator++() {
    ++(*m_impl);
    return *this;
}

Expr* Iterator::operator->() {
    return m_impl->operator->();
}

Expr& Iterator::operator*() {
    return **m_impl;
}

bool Iterator::operator==(const Iterator& other) const {
    return *m_impl == *(other.m_impl);
}

bool Iterator::operator!=(const Iterator& other) const {
    return !(*this == other);
}

PostOrderIteratorImpl::PostOrderIteratorImpl(Expr* expr) {
    if (expr != 0) {
        get_next(expr);
    }
}

void PostOrderIteratorImpl::get_next(Expr* expr) {
    while (expr->left() || expr->right()) {
        if (expr->left()) {
            m_stack.push(expr);

            expr = &(*(expr->left()));
            continue;
        }

        if (expr->right()) {
            m_stack.push(expr);

            expr = &(*(expr->right()));
            continue;
        }
    }

    m_stack.push(expr);
}

PostOrderIteratorImpl& PostOrderIteratorImpl::operator++() {
    Expr* child = m_stack.top();
    m_stack.pop();

    if (m_stack.empty()) {
        return *this;
    }

    if (child == m_stack.top()->left().get()) {
        // done with the left subtree
        if (m_stack.top()->right() != 0) {
            get_next(m_stack.top()->right().get());
        }
    }
}

Expr& PostOrderIteratorImpl::operator*() {
    return (*m_stack.top());
}

Expr* PostOrderIteratorImpl::operator->() {
    return m_stack.top();
}

bool PostOrderIteratorImpl::operator==(const IteratorImpl& other) const {
    const PostOrderIteratorImpl* post_order_iterator = dynamic_cast<const PostOrderIteratorImpl *>(&other);
    if (post_order_iterator == 0) {
        return false;
    }

    if (m_stack.empty() && post_order_iterator->m_stack.empty()) {
        return true;
    }

    if (m_stack.empty() || post_order_iterator->m_stack.empty()) {
        return false;
    }

    if (m_stack.top() == post_order_iterator->m_stack.top()) {
        return true;
    }

    return false;
}

bool PostOrderIteratorImpl::operator!=(const IteratorImpl& other) const {
    return !(*this == other);
}
