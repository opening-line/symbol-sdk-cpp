#include <cstdint>
#include <array>
#include <stdexcept>
#include <vector>
#include <cstring>
#include <algorithm>

#include "BaseValue.hpp"
#include "ByteArray.hpp"


class Amount : public BaseValue {
public:
    static const int SIZE = 8;

    Amount(int64_t amount = 0) 
        : BaseValue(SIZE, amount) {}

    Amount deserialize (const std::vector<uint8_t>& payload) override {
        if (payload.size() < SIZE) {
            throw std::invalid_argument("Payload size too small for Amount");
        }
        int64_t value = 0;
        for (int i = 0; i < SIZE; ++i) {
            value |= static_cast<uint64_t>(payload[i]) << (i * 8);
        }
        return Amount(value);
    }

    std::vector<uint8_t> serialize() override {
        std::vector<uint8_t> buffer(SIZE, 0);
        for (int i = 0; i < SIZE; ++i) {
            buffer[i] = (value >> (i * 8)) & 0xFF;
        }
        return buffer;
    }
};


class UnresolvedAddress : public ByteArray {
public:
    static const int SIZE = 24;

    explicit UnresolvedAddress(const std::vector<uint8_t>& unresolved_address = std::vector<uint8_t>(SIZE, 0))
        : ByteArray(SIZE, unresolved_address) {}

    int size() const {
        return SIZE;
    }

    UnresolvedAddress deserialize (const std::vector<uint8_t>& payload) override {
        if (payload.size() < SIZE) {
            throw std::invalid_argument("Payload size too small for UnresolvedAddress");
        }
        std::vector<uint8_t> buffer(payload.begin(), payload.begin() + SIZE);
        return UnresolvedAddress(buffer);
    }

    std::vector<uint8_t> serialize() const override {
        return bytes;
    }
};