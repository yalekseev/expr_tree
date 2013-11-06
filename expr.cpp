#include "expr.h"
#include "visitor.h"
#include "iterator.h"

#include <memory>
#include <string>

Iterator Expr::begin(const std::string& traversal) {
    return Iterator(traversal, static_cast<Expr*>(this));
}

Iterator Expr::end(const std::string& traversal) {
    return Iterator(traversal);
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

void ConstExpr::accept(Visitor& visitor) {
    visitor.accept(*this);
}
