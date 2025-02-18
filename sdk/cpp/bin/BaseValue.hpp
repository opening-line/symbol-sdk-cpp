#ifndef BASEVALUE_HPP
#define BASEVALUE_HPP

#include <string>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <typeinfo>

#include "converter.hpp"

class BaseValue {
private:
    std::vector<void*> _tag; // Dartの`_tag`に相当

public:
    int size;
    uint64_t value;

    BaseValue(int size, uint64_t value, void* tag = nullptr, bool is_signed = false)
        : size(size), value(value) {
        _tag.push_back(tag);

        int bit_size = size * 8, upper_bound, lower_bound;
        if (is_signed) {
            upper_bound = (1 << (bit_size-1)) - 1;
            lower_bound = -upper_bound - 1;
        } else {
            upper_bound = (1 << bit_size) - 1;
            lower_bound = 0;
        }

        if (value < lower_bound || value > upper_bound) {
            std::ostringstream oss;
            oss << value << " must be in range [" << lower_bound << ", " << upper_bound
                << "] for " << size << " bytes";
            throw std::out_of_range(oss.str());
        }
    }

    // not override, ok?
    template <typename T>
    bool operator==(const T& other) const {
        if (typeid(T) != typeid(BaseValue)) {
            return false;
        }
        return value == other.value && _tag == other._tag;
    }

    int hashCode() const override {
        return std::hash<uint64_t>()(value) ^ std::hash<void*>()(_tag[0]);
    }

    std::string toString() const override{
        std::ostringstream oss;
        oss << "0x" << std::uppercase << std::setfill('0') << std::setw(size * 2)
            << std::hex << value;
        return oss.str();
    }

    bool isDefault() const {
        return value == 0;
    }

    int bitmask(int bitsnumber) const {
        return (1 << bitsnumber) - 1;
    }

    int unsignedToSigned(int value, int byteSize) const {
        int bitSize = byteSize * 8;
        int mask =(1 << bitSize) - 1;
        int signBit = 1 << (bitSize - 1);
        if ((value & bitSize) != 0) {
            return value | ~mask;
        } else {
            return value & mask;
        }
    }
};

#endif // BASEVALUE_HPP

