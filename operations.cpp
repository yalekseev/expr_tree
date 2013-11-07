#include "operations.h"
#include "visitor.h"
#include "expr.h"

#include <iostream>

double eval(Expr& expr) {
    EvalVisitor visitor;

    for (auto& expr_node : expr) {
        expr_node.accept(visitor);
    }

    return visitor.result();
}

std::string print(Expr& expr) {
    PrintVisitor visitor;

    for (auto& expr_node : expr) {
        expr_node.accept(visitor);
    }

    return visitor.result();
}
