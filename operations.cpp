#include "operations.h"
#include "visitor.h"
#include "expr.h"

double eval(Expr& expr) {
    EvalVisitor visitor;

    for (auto& expr_node : expr) {
        expr_node.accept(visitor);
    }

    return visitor.result();
}

std::string print(Expr& expr, const std::string& traversal) {
    PrintVisitor visitor;

    for (auto it = expr.begin(traversal); it != expr.end(traversal); ++it) {
        it->accept(visitor);
    }

    return visitor.result();
}
