#include "operations.h"
#include "expr.h"

#include <iostream>
#include <memory>

int main() {
    std::shared_ptr<Expr> expr = Div(Mul(Const(2), Add(Const(10), Const(5))), Mul(Const(2), Const(5)));

    std::cout << eval(*expr) << std::endl;

    std::cout << print(*expr, "pre-order") << std::endl;
    std::cout << print(*expr, "in-order") << std::endl;
    std::cout << print(*expr, "post-order") << std::endl;

    return 0;
}
