#include "expr.h"
#include "visitor.h"
#include "iterator.h"

#include <iostream>


double eval(Expr& expr) {
    EvalVisitor visitor;

    for (auto& expr_node : expr) {
        expr_node.accept(visitor);
    }

    return visitor.result();
}


int main() {
    std::shared_ptr<Expr> expr = Div(Mul(Const(2), Add(Const(10), Const(5))), Mul(Const(2), Const(5)));

    std::cout << eval(*expr) << std::endl;

    return 0;
}
