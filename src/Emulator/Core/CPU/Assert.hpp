#pragma once

#include "PCH/CStd.hpp"

#define h_assert(expr, statement) \
  if (!(expr)) {                  \
    statement;                    \
  }
