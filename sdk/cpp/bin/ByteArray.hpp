#ifndef BYTEARRAY_HPP
#define BYTEARRAY_HPP

#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include "converter.hpp" // isHexString, hexDecode, stringToAddress, addressToString を提供

class ByteArray {
public:
    std::vector<uint8_t> bytes;

    ByteArray(int fixedSize, const std::string& arrayInput) 
        : bytes(fixedSize, 0) {
        std::vector<uint8_t> rawBytes;

        try {
            if (isHexString(arrayInput)) {
                rawBytes = hexDecode(arrayInput); // 16進文字列をデコード
            } else {
                rawBytes = stringToAddress(arrayInput); // アドレス文字列をバイト列に変換
            }
        } catch (const std::exception&) {
            throw std::invalid_argument("bytes was not a valid hex or address string");
        }

        if (rawBytes.size() != fixedSize) {
            throw std::out_of_range("bytes was size " + std::to_string(rawBytes.size()) +
                                    " but must be " + std::to_string(fixedSize));
        }

        bytes = std::move(rawBytes);
    }

    std::string toString() const override {
        try {
            return addressToString(bytes); // バイト列をアドレス文字列に変換
        } catch (const std::exception&) {
            return hexEncode(bytes); // バイト列を16進文字列に変換
        }
    }

    // isDefault メソッド
    bool isDefault() const {
        return std::all_of(bytes.begin(), bytes.end(), [](uint8_t byte) { return byte == 0; });
    }
};

#endif // BYTEARRAY_HPP
