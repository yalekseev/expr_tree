#include "operations.h"
#include "expr.h"

#include <iostream>
#include <memory>

int main() {
    using util::Div;
    using util::Mul;
    using util::Add;
    using util::Const;

    std::shared_ptr<util::Expr> expr = Div(Mul(Const(2), Add(Const(10), Const(5))), Mul(Const(2), Const(5)));

    std::cout << util::eval(*expr) << std::endl;

    std::cout << util::print(*expr, "pre-order") << std::endl;
    std::cout << util::print(*expr, "in-order") << std::endl;
    std::cout << util::print(*expr, "post-order") << std::endl;
    std::cout << util::print(*expr, "level-order") << std::endl;

    return 0;
}
