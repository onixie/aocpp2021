#ifndef _LIB_HPP_
#define _LIB_HPP_

#include <cstddef>
#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <bitset>
#include <functional>

using BITStream=std::vector<std::uint8_t>;

std::istream& operator>>(std::istream&, BITStream&);
std::ostream& operator<<(std::ostream&, BITStream const&);
BITStream operator<<(BITStream const &stream, size_t shift);

template<class TYPE, int SIZE, bool constraint = (SIZE <= sizeof(TYPE)*8)>
struct BITS;

template<class TYPE, int SIZE>
struct BITS<TYPE, SIZE, true> {
    protected:
    using store_type = BITStream::value_type;
    static constexpr size_t store_size = sizeof(store_type)*8;
    public:
    std::bitset<SIZE> bits;
    TYPE value;
    auto operator()(BITStream const& stream, size_t& index) {
        bits.reset();
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
                    bits.set(SIZE-(pos++)-1, 0x1&(value>>i));
                } else {
                    break;
                }
            }
        }

        index += SIZE;
        this->value = bits.to_ullong();
        return bits;
    }
};

struct BITSVer : BITS<std::uint32_t, 3> {};
struct BITSTyp : BITS<std::uint32_t, 3> {};
struct BITSLit : BITS<std::uint32_t, 5> {};
struct BITSMod : BITS<std::uint32_t, 1> {};

struct BITSPacBase {
    enum Pack {
        Invalid,
        Op,
        Lv,
    } pack = Invalid;
    virtual std::string operator()(BITStream const& stream, size_t& index) = 0;
    std::string bits;
    BITSVer ver;
    BITSTyp typ;
};

struct BITSLvPac : BITSPacBase {
    std::uint64_t value = 0;
    std::string raw_value;
    std::string operator()(BITStream const& stream, size_t& index);
};

struct BITSOpPac : BITSPacBase {
    BITSMod mod;
    std::vector<std::unique_ptr<BITSPacBase>> subpacs = {};
    std::string operator()(BITStream const& stream, size_t& index);
};

std::unique_ptr<BITSPacBase> parse(BITStream const& stream, size_t& index);
void print(std::unique_ptr<BITSPacBase>& pac, std::ostream& out=std::cerr);

std::ostream& operator<<(std::ostream&, BITSLvPac const&);
std::ostream& operator<<(std::ostream&, BITSOpPac const&);

std::string add_bits(std::string const&, std::string const&);
std::string mul_bits(std::string const&, std::string const&);
bool operator>(std::string const&, std::string const&);
//bool operator==(std::string const& bits1, std::string const& bits2);
bool operator<(std::string const& bits1, std::string const& bits2);
#endif