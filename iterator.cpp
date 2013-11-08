#include "iterator.h"
#include "expr.h"

#include <stdexcept>
#include <string>

namespace util {

/* Iterator */

Iterator::Iterator(const std::string& type, Expr* expr) {
    if (type == "pre-order") {
        m_impl.reset(new impl::PreOrderIteratorImpl(expr));
    } else if (type == "in-order") {
        m_impl.reset(new impl::InOrderIteratorImpl(expr));
    } else if (type == "post-order") {
        m_impl.reset(new impl::PostOrderIteratorImpl(expr));
    } else if (type == "level-order") {
        m_impl.reset(new impl::LevelOrderIteratorImpl(expr));
    } else {
        throw std::runtime_error("Unknown iterator type: " + type);
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

namespace impl {

/* PreOrderIteratorImpl */

PreOrderIteratorImpl::PreOrderIteratorImpl(Expr* expr) {
    if (expr != 0) {
        m_stack.push(expr);
    }
}

PreOrderIteratorImpl& PreOrderIteratorImpl::operator++() {
    Expr* node = m_stack.top();
    m_stack.pop();

    if (node->right().get() != 0) {
        m_stack.push(node->right().get());
    }

    if (node->left().get() != 0) {
        m_stack.push(node->left().get());
    }

    return *this;
}

Expr* PreOrderIteratorImpl::operator->() {
    return m_stack.top();
}

Expr& PreOrderIteratorImpl::operator*() {
    return *(m_stack.top());
}

bool PreOrderIteratorImpl::operator==(const IteratorImpl& other) const {
    const PreOrderIteratorImpl* in_order_iterator = dynamic_cast<const PreOrderIteratorImpl*>(&other);
    if (in_order_iterator == 0) {
        return false;
    }

    if (m_stack.empty() && in_order_iterator->m_stack.empty()) {
        return true;
    }

    if (m_stack.empty() || in_order_iterator->m_stack.empty()) {
        return false;
    }

    if (m_stack.top() == in_order_iterator->m_stack.top()) {
        return true;
    }

    return false;
}

bool PreOrderIteratorImpl::operator!=(const IteratorImpl& other) const {
    return !(*this == other);
}

/* InOrderIteratorImpl */

InOrderIteratorImpl::InOrderIteratorImpl(Expr* expr) {
    if (expr != 0) {
        get_next(expr);
    }
}

InOrderIteratorImpl& InOrderIteratorImpl::operator++() {
    Expr* node = m_stack.top();
    m_stack.pop();

    if (node->right().get() != 0) {
        get_next(node->right().get());
    }

    return *this;
}

Expr* InOrderIteratorImpl::operator->() {
    return m_stack.top();
}

Expr& InOrderIteratorImpl::operator*() {
    return *(m_stack.top());
}

bool InOrderIteratorImpl::operator==(const IteratorImpl& other) const {
    const InOrderIteratorImpl* in_order_iterator = dynamic_cast<const InOrderIteratorImpl*>(&other);
    if (in_order_iterator == 0) {
        return false;
    }

    if (m_stack.empty() && in_order_iterator->m_stack.empty()) {
        return true;
    }

    if (m_stack.empty() || in_order_iterator->m_stack.empty()) {
        return false;
    }

    if (m_stack.top() == in_order_iterator->m_stack.top()) {
        return true;
    }

    return false;
}

bool InOrderIteratorImpl::operator!=(const IteratorImpl& other) const {
    return !(*this == other);
}

void InOrderIteratorImpl::get_next(Expr* expr) {
    while (expr->left().get() != 0) {
        m_stack.push(expr);
        expr = expr->left().get();
    }

    m_stack.push(expr);
}

/* PostOrderIteratorImpl */

PostOrderIteratorImpl::PostOrderIteratorImpl(Expr* expr) {
    if (expr != 0) {
        get_next(expr);
    }
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

/* LevelOrderIteratorImpl */

LevelOrderIteratorImpl::LevelOrderIteratorImpl(Expr* expr) {
    if (expr != 0) {
        m_queue.push(expr);
    }
}

LevelOrderIteratorImpl& LevelOrderIteratorImpl::operator++() {
    Expr* node = m_queue.front();
    m_queue.pop();

    if (node->left().get() != 0) {
        m_queue.push(node->left().get());
    }

    if (node->right().get() != 0) {
        m_queue.push(node->right().get());
    }
}

Expr& LevelOrderIteratorImpl::operator*() {
    return *(m_queue.front());
}

Expr* LevelOrderIteratorImpl::operator->() {
    return m_queue.front();
}

bool LevelOrderIteratorImpl::operator==(const IteratorImpl& other) const {
    const LevelOrderIteratorImpl* level_order_iterator = dynamic_cast<const LevelOrderIteratorImpl *>(&other);
    if (level_order_iterator == 0) {
        return false;
    }

    if (m_queue.empty() && level_order_iterator->m_queue.empty()) {
        return true;
    }

    if (m_queue.empty() || level_order_iterator->m_queue.empty()) {
        return false;
    }

    if (m_queue.front() == level_order_iterator->m_queue.front()) {
        return true;
    }

    return false;
}

bool LevelOrderIteratorImpl::operator!=(const IteratorImpl& other) const {
    return !(*this == other);
}

} // namespace impl

} // namespace util
