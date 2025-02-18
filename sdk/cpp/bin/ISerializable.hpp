#ifndef ISERIALIZABLE_HPP
#define ISERIALIZABLE_HPP

#include <vector>
#include <stdexcept>
#include <cstdint>

class ISerializable {
public:
    virtual std::vector<uint8_t> serialize() const {
        throw std::logic_error("Unimplemented serialize method");
    }

    virtual void deserialize(const std::vector<uint8_t>& payload) {
        throw std::logic_error("Unimplemented deserialize method");
    }

    virtual int size() const {
        throw std::logic_error("Unimplemented size method");
    }
};

#endif // ISERIALIZABLE_HPP
