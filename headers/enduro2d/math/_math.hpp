/*******************************************************************************
 * This file is part of the "Enduro2D"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2018 Matvey Cherevko
 ******************************************************************************/

#pragma once

#include "../base/_all.hpp"

namespace e2d { namespace math
{
    //
    // numeric cast
    //

    namespace impl
    {
        // f -> f
        template < typename To, typename From >
        std::enable_if_t<
            std::is_floating_point<From>::value && std::is_floating_point<To>::value
        , bool>
        check_numeric_cast(From v) noexcept {
            const To l = std::numeric_limits<To>::lowest();
            const To m = std::numeric_limits<To>::max();
            return v >= l && v <= m;
        }

        // i/u -> f
        template < typename To, typename From >
        std::enable_if_t<
            std::is_integral<From>::value && std::is_floating_point<To>::value
        , bool>
        check_numeric_cast(From) noexcept {
            return true;
        }

        // f -> i/u
        template < typename To, typename From >
        std::enable_if_t<
            std::is_floating_point<From>::value && std::is_integral<To>::value
        , bool>
        check_numeric_cast(From v) noexcept {
            const To l = std::numeric_limits<To>::lowest();
            const To m = std::numeric_limits<To>::max();
            return
                v >= static_cast<From>(l) &&
                v <= static_cast<From>(m);
        }

        // i -> i, u -> u
        template < typename To, typename From >
        std::enable_if_t<
            std::is_signed<From>::value == std::is_signed<To>::value &&
            std::is_integral<From>::value && std::is_integral<To>::value
        , bool>
        check_numeric_cast(From v) noexcept {
            const To l = std::numeric_limits<To>::lowest();
            const To m = std::numeric_limits<To>::max();
            return v >= l && v <= m;
        }

        // i -> u
        template < typename To, typename From >
        std::enable_if_t<
            std::is_signed<From>::value && std::is_unsigned<To>::value &&
            std::is_integral<From>::value && std::is_integral<To>::value
        , bool>
        check_numeric_cast(From v) noexcept {
            const To m = std::numeric_limits<To>::max();
            return v >= 0 && static_cast<std::make_unsigned_t<From>>(v) <= m;
        }

        // u -> i
        template < typename To, typename From >
        std::enable_if_t<
            std::is_unsigned<From>::value && std::is_signed<To>::value &&
            std::is_integral<From>::value && std::is_integral<To>::value
        , bool>
        check_numeric_cast(From v) noexcept {
            const To m = std::numeric_limits<To>::max();
            return v <= static_cast<std::make_unsigned_t<To>>(m);
        }
    }

    template < typename To, typename From >
    std::enable_if_t<
        std::is_arithmetic<From>::value &&
        std::is_arithmetic<To>::value, To>
    numeric_cast(From v) noexcept {
        E2D_ASSERT(impl::check_numeric_cast<To>(v));
        return static_cast<To>(v);
    }

    //
    // default precision
    //

    template < typename T >
    std::enable_if_t<std::is_integral<T>::value, T>
    default_precision() noexcept {
        return T(0);
    }

    template < typename T >
    std::enable_if_t<std::is_same<T, f32>::value, T>
    default_precision() noexcept {
        return 0.00001f;
    }

    template < typename T >
    std::enable_if_t<std::is_same<T, f64>::value, T>
    default_precision() noexcept {
        return 0.0000001;
    }

    //
    // power of two
    //

    template < typename T >
    std::enable_if_t<std::is_unsigned<T>::value, bool>
    is_power_of_2(T v) noexcept {
        return v && !(v & (v - 1));
    }

    template < typename T >
    std::enable_if_t<std::is_unsigned<T>::value, T>
    max_power_of_2() noexcept {
        return T(1) << (sizeof(T) * 8 - 1);
    }

    template < typename T >
    std::enable_if_t<std::is_unsigned<T>::value, T>
    next_power_of_2(T v) noexcept {
        E2D_ASSERT(v <= max_power_of_2<T>());
        if ( v == T(0) ) {
            return T(1);
        }
        --v;
        u32 i = 1;
        do {
            v |= v >> i;
            i <<= 1;
        } while (v & (v + 1));
        return v + 1;
    }

    //
    // abs
    //

    template < typename T >
    std::enable_if_t<std::is_signed<T>::value, T>
    abs(T v) noexcept {
        return v < T(0) ? -v : v;
    }

    template < typename T >
    std::enable_if_t<std::is_unsigned<T>::value, T>
    abs(T v) noexcept {
        return v;
    }

    //
    // sqrt
    //

    template < typename T >
    std::enable_if_t<std::is_floating_point<T>::value, T>
    sqrt(T v) noexcept {
        return std::sqrt(v);
    }

    //
    // ceil/floor/round
    //

    template < typename T >
    std::enable_if_t<std::is_integral<T>::value, T>
    ceil(T v) noexcept {
        return v;
    }

    template < typename T >
    std::enable_if_t<std::is_integral<T>::value, T>
    floor(T v) noexcept {
        return v;
    }

    template < typename T >
    std::enable_if_t<std::is_integral<T>::value, T>
    round(T v) noexcept {
        return v;
    }

    template < typename T >
    std::enable_if_t<std::is_floating_point<T>::value, T>
    ceil(T v) noexcept {
        return std::ceil(v);
    }

    template < typename T >
    std::enable_if_t<std::is_floating_point<T>::value, T>
    floor(T v) noexcept {
        return std::floor(v);
    }

    template < typename T >
    std::enable_if_t<std::is_floating_point<T>::value, T>
    round(T v) noexcept {
        return std::round(v);
    }

    //
    // min/max
    //

    template < typename T >
    std::enable_if_t<std::is_arithmetic<T>::value, T>
    min(T v) noexcept {
        return v;
    }

    template < typename T1, typename T2, typename... Ts >
    std::common_type_t<T1, T2, Ts...> min(T1 v1, T2 v2, Ts... vs) noexcept {
        return min(v1 < v2 ? v1 : v2, vs...);
    }

    template < typename T >
    std::enable_if_t<std::is_arithmetic<T>::value, T>
    max(T v) noexcept {
        return v;
    }

    template < typename T1, typename T2, typename... Ts >
    std::common_type_t<T1, T2, Ts...> max(T1 v1, T2 v2, Ts... vs) noexcept {
        return max(v1 < v2 ? v2 : v1, vs...);
    }

    //
    // clamp
    //

    template < typename T >
    std::enable_if_t<std::is_arithmetic<T>::value, T>
    clamp(T v, T vmin, T vmax) noexcept {
        E2D_ASSERT(vmin <= vmax);
        return min(max(v, vmin), vmax);
    }

    template < typename T >
    std::enable_if_t<std::is_arithmetic<T>::value, T>
    clamp01(T v) noexcept {
        return clamp(v, T(0), T(1));
    }

    //
    // is_near_zero
    //

    template < typename T >
    std::enable_if_t<std::is_arithmetic<T>::value, bool>
    is_near_zero(T v, T precision = default_precision<T>()) noexcept {
        return abs(v) <= precision;
    }

    //
    // approximately
    //

    template < typename T >
    std::enable_if_t<std::is_arithmetic<T>::value, bool>
    approximately(T l, T r, T precision = default_precision<T>()) noexcept {
        return l < r
            ? (r - l) <= precision
            : (l - r) <= precision;
    }
}}
