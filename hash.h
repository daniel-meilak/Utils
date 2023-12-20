#pragma once

template <typename T>
void hash_combine(std::size_t& seed, const T& v) {
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
}

//------------------------------------------------------------------------------
// Tuple hash
//------------------------------------------------------------------------------

template <typename Tuple, std::size_t Index = std::tuple_size<Tuple>::value - 1>
struct HashValueImpl {
    static void apply(size_t& seed, const Tuple& tuple) {
        HashValueImpl<Tuple, Index-1>::apply(seed, tuple);
        hash_combine(seed, std::get<Index>(tuple));
    }
};

template <typename Tuple>
struct HashValueImpl<Tuple, 0> {
    static void apply(size_t& seed, const Tuple& tuple) {
        hash_combine(seed, std::get<0>(tuple));
    }
};

template <typename... TT>
struct TupleHash {
    size_t operator()(const std::tuple<TT...>& tt) const {
        size_t seed = 0;
        HashValueImpl<std::tuple<TT...>>::apply(seed, tt);
        return seed;
    }
};

//------------------------------------------------------------------------------
// Pair hash
//------------------------------------------------------------------------------

template <typename T1, typename T2>
struct PairHash {
    size_t operator()(const std::pair<T1, T2>& p) const {
        size_t seed = 0;
        hash_combine(seed, p.first);
        hash_combine(seed, p.second);
        return seed;
    }
};