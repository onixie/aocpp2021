#ifndef _LIB_HPP_
#define _LIB_HPP_

#include <cstdint>
#include <vector>
#include <iostream>
#include <bitset>
#include <optional>

using BITStream=std::vector<std::uint8_t>;

std::istream& operator>>(std::istream&, BITStream&);
std::ostream& operator<<(std::ostream&, BITStream const&);
BITStream operator<<(BITStream const &stream, size_t shift);

template<class TYPE, int SIZE, bool constraint = (SIZE <= sizeof(TYPE)*8)>
struct BITS;

template<class TYPE, int SIZE>
struct BITS<TYPE, SIZE, true> {
    using store_type = BITStream::value_type;
    static constexpr size_t store_size = sizeof(store_type)*8;

    std::bitset<SIZE> parse(BITStream const& stream, size_t& index) {
        std::bitset<SIZE> res;

        auto start = stream.cbegin() +  index / store_size;
        auto end   = stream.cbegin() + (index + SIZE) / store_size + 1;
        
        auto left = index % store_size;
        auto pos = 0;
        for(auto curr = start; curr < end && pos < SIZE; curr++) {
            store_type value = *curr<<left;
            if (curr + 1 < end)
                value |= *(curr+1)>>(store_size-left);
                
            for(int i=store_size-1;i>=0;i--) {
                if (pos < SIZE) {
                    res.set(SIZE-(pos++)-1, 0x1&(value>>i));
                } else {
                    break;
                }
            }
        }

        index += SIZE;
        this->value = res.to_ullong();
        return res;
    }

    TYPE value;
};

struct BITSVer : BITS<std::uint32_t, 3> {};
struct BITSTyp : BITS<std::uint32_t, 3> {};
struct BITSLit : BITS<std::uint32_t, 5> {};
struct BITSMod : BITS<std::uint32_t, 1> {};

struct BITSLitPac : BITS<std::uint64_t, 0> {
    std::string parse(BITStream const& stream, size_t& index) {
        std::string res;
        size_t idx;
        BITSVer ver;
        BITSTyp typ;

        res+=ver.parse(stream, idx).to_string();
        res+=typ.parse(stream, idx).to_string();

        value = 0;
        if (typ.value == 4) {
            BITSLit lit;
            do {
                auto litp = lit.parse(stream, idx);
                res+=litp.to_string();
                value = (value<<4) + (0x0F&lit.value);
                if (!litp.test(4))
                    break;
            } while (true);

            index = idx;
            return res;
        } else {
            return "";
        }
    }
};

#endif