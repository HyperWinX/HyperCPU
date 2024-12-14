#pragma once

#include <iostream>


#define h_assert(expr, err_msg) if (!(expr)) { std::cerr << err_msg << '\n'; exit(1); }
