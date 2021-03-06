/*******************************************************************************
 * This file is part of the "Enduro2D"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2018 Matvey Cherevko
 ******************************************************************************/

#pragma once

#include "_base.hpp"

namespace e2d
{
    using f32 = float;
    using f64 = double;

    using i8  = std::int8_t;
    using i16 = std::int16_t;
    using i32 = std::int32_t;
    using i64 = std::int64_t;

    using u8  = std::uint8_t;
    using u16 = std::uint16_t;
    using u32 = std::uint32_t;
    using u64 = std::uint64_t;
}

namespace e2d
{
    template < typename Value
             , std::size_t Size >
    using array = std::array<Value, Size>;

    template < typename Value
             , typename Alloc = std::allocator<Value> >
    using vector = std::vector<Value, Alloc>;

    template < typename Value
             , typename Hash = std::hash<Value>
             , typename Pred = std::equal_to<Value>
             , typename Alloc = std::allocator<Value> >
    using hash_set = std::unordered_set<Value, Hash, Pred, Alloc>;

    template < typename Key
             , typename Value
             , typename Hash = std::hash<Key>
             , typename Pred = std::equal_to<Key>
             , typename Alloc = std::allocator<std::pair<const Key, Value>> >
    using hash_map = std::unordered_map<Key, Value, Hash, Pred, Alloc>;

    template < typename Char
             , typename Alloc = std::allocator<Char> >
    using basic_string = std::basic_string<Char, std::char_traits<Char>, Alloc>;
}
