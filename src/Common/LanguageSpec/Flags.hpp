#pragma once

#include "src/PCH/CStd.hpp"


namespace HyperCPU {
  enum class Mode {
    b8  = 0, b16, b32, b64
  };

  enum class OperandTypes {
    R_R = 0, R_RM, R_M, R_IMM, RM_R, RM_M, RM_IMM,
    M_R, R, M, IMM, NONE
  };
}
