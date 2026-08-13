#pragma once

#if ROXY_IS_MSVC
#include <intrin.h>
#else
#include <xmmintrin.h>
#endif

#include <RoxyMath/RoxyMathMat.h>

namespace Roxy::Math
{
#if ROXY_ENABLE_SIMD
#endif
}
