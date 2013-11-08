#pragma once

#include <string>

namespace util {

class Expr;

extern double eval(Expr& expr);

extern std::string print(Expr& expr, const std::string& traversal = "post-order");

} // namespace util
