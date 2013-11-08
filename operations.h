#pragma once

class Expr;

#include <string>

extern double eval(Expr& expr);

extern std::string print(Expr& expr, const std::string& traversal = "post-order");
