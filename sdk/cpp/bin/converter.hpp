#ifndef CONVERTER_HPP
#define CONVERTER_HPP

#include <string>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <cstdint>
#include <regex>
#include <algorithm>

// 定数
const size_t RIPMD160_SIZE = 20;
const size_t SYMBOL_ADDRESS_DECODED = 24;
const size_t NEM_ADDRESS_DECODED = 25;
const size_t SYMBOL_ADDRESS_ENCODED = 39;
const size_t NEM_ADDRESS_ENCODED = 40;
const size_t KEY_SIZE = 32;
const size_t CHECKSUM_SIZE = 3;

// Utility functions

// 整数を16進文字列に変換
inline std::string intToHex(uint64_t num) {
    std::ostringstream oss;
    oss << std::uppercase << std::hex << std::setw(16) << std::setfill('0') << num;
    return oss.str();
}

// バイト列を16進文字列に変換
inline std::string bytesToHex(const std::vector<uint8_t>& bytes) {
    std::ostringstream oss;
    for (auto byte : bytes) {
        oss << std::uppercase << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    }
    return oss.str();
}

// 16進文字列をバイト列に変換
inline std::vector<uint8_t> hexToBytes(const std::string& hexString) {
    if (hexString.length() % 2 != 0) {
        throw std::invalid_argument("Invalid hex string length");
    }

    std::vector<uint8_t> bytes;
    bytes.reserve(hexString.size() / 2);

    for (size_t i = 0; i < hexString.size(); i += 2) {
        bytes.push_back(static_cast<uint8_t>(std::stoi(hexString.substr(i, 2), nullptr, 16)));
    }

    return bytes;
}

// BigInt をバイト列に変換
inline std::vector<uint8_t> bigintToUint8List(uint64_t value) {
    std::vector<uint8_t> result(8, 0);
    for (size_t i = 0; i < 8; ++i) {
        result[i] = static_cast<uint8_t>((value >> (8 * i)) & 0xFF);
    }
    return result;
}

// 整数をバイト列に変換
inline std::vector<uint8_t> intToBytes(uint64_t value, size_t byteSize) {
    if (byteSize != 1 && byteSize != 2 && byteSize != 4 && byteSize != 8) {
        throw std::invalid_argument("byteSize not supported");
    }

    std::vector<uint8_t> bytes(byteSize);

    switch (byteSize) {
        case 1:
            bytes[0] = static_cast<uint8_t>(value);
            break;
        case 2:
            for (size_t i = 0; i < 2; ++i) {
                bytes[i] = static_cast<uint8_t>((value >> (8 * i)) & 0xFF);
            }
            break;
        case 4:
            for (size_t i = 0; i < 4; ++i) {
                bytes[i] = static_cast<uint8_t>((value >> (8 * i)) & 0xFF);
            }
            break;
        case 8:
            for (size_t i = 0; i < 8; ++i) {
                bytes[i] = static_cast<uint8_t>((value >> (8 * i)) & 0xFF);
            }
            break;
    }

    return bytes;
}

// バイト列をBigIntに変換
inline uint64_t uint8ListToBigInt(const std::vector<uint8_t>& data) {
    uint64_t result = 0;
    for (size_t i = 0; i < data.size(); ++i) {
        result |= static_cast<uint64_t>(data[i]) << (8 * i);
    }
    return result;
}

// バイト列を整数に変換
inline uint64_t bytesToInt(const std::vector<uint8_t>& input, size_t size) {
    if (size != 1 && size != 2 && size != 4 && size != 8) {
        throw std::invalid_argument("byteSize not supported");
    }

    if (input.size() < size) {
        throw std::invalid_argument("Input size is smaller than requested byte size");
    }

    uint64_t result = 0; // 最大 8 バイトの整数を格納
    switch (size) {
        case 1:
            result = input[0]; // 最初の1バイトを取得
            break;
        case 2:
            result = static_cast<uint16_t>(input[0]) |
                     (static_cast<uint16_t>(input[1]) << 8); // リトルエンディアンで結合
            break;
        case 4:
            for (size_t i = 0; i < 4; ++i) {
                result |= static_cast<uint32_t>(input[i]) << (8 * i); // リトルエンディアン
            }
            break;
        case 8:
            for (size_t i = 0; i < 8; ++i) {
                result |= static_cast<uint64_t>(input[i]) << (8 * i); // リトルエンディアン
            }
            break;
    }

    return result;
}

// 符号なし整数を符号付き整数に変換
inline int64_t intToUnsignedInt(int64_t value) {
    if (value < 0) {
        return value + (1ULL << 64);
    }
    return value;
}

// // 文字列をアドレスに変換
// inline std::vector<uint8_t> stringToAddress(const std::string& encoded) {
//     if (encoded.size() == SYMBOL_ADDRESS_ENCODED) {
//         // Base32デコードを実装する必要あり
//         throw std::runtime_error("Base32 decoding not implemented");
//     }
//     if (encoded.size() == NEM_ADDRESS_ENCODED) {
//         return std::vector<uint8_t>(encoded.begin(), encoded.end());
//     }
//     throw std::invalid_argument(encoded + " does not represent a valid encoded address");
// }

// // アドレスを文字列に変換
// inline std::string addressToString(const std::vector<uint8_t>& decoded) {
//     if (decoded.size() == SYMBOL_ADDRESS_DECODED) {
//         // Base32エンコードを実装する必要あり
//         throw std::runtime_error("Base32 encoding not implemented");
//     }
//     if (decoded.size() == NEM_ADDRESS_DECODED) {
//         return std::string(decoded.begin(), decoded.end());
//     }
//     throw std::invalid_argument("Bytes to Hex function is not implemented yet");
// }

// 文字列が16進文字列かを判定
inline bool isHexString(const std::string& value) {
    const std::regex hexPattern("^[0-9a-fA-F]+$", std::regex::icase);
    return std::regex_match(value, hexPattern);
}

// 16進文字列であるかをチェックし、エラーをスロー
inline void tryHexString(const std::string& value) {
    if (!isHexString(value)) {
        throw std::invalid_argument("Value was not a valid hex string");
    }
}

// String utf8ToHex(String input) {
//   List<int> bytes = utf8.encode(input);
//   return bytes.map((byte) => byte.toRadixString(16).padLeft(2, '0')).join().toUpperCase();
// }

// Uint8List utf8ToBytes(String input) {
//   return utf8.encode(input);  
// }

#endif // CONVERTER_HPP
