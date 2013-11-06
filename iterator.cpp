#include "iterator.h"
#include "expr.h"

#include <memory>
#include <string>

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
    return (*m_impl).operator->();
}

Expr& Iterator::operator*() {
    return **m_impl;
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

bool PostOrderIteratorImpl::operator==(const PostOrderIteratorImpl& other) const {
    return m_stack == other.m_stack;
}
