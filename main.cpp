#include "expr.h"
#include "visitor.h"
#include "iterator.h"

#include <iostream>


double eval(std::shared_ptr<Expr> expr) {
    EvalVisitor visitor;

    for (Iterator it = expr->begin("post-order"); it != expr->end("post-order"); ++it) {
        it->accept(visitor);
    }

    return visitor.result();
}


int main() {
    std::shared_ptr<Expr> expr = Add(Const(10), Const(5));

    std::cout << eval(expr) << std::endl;

    return 0;
}
