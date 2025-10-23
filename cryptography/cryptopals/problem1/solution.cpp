// solution.cpp
#include <string>
#include <stdexcept>
#include <vector>
#include <cctype>

namespace cryptopals {

// --- Helper: chuyển ký tự hex sang giá trị ---
unsigned char hex_value(char c) {
    if ('0' <= c && c <= '9') return c - '0';
    if ('a' <= c && c <= 'f') return c - 'a' + 10;
    if ('A' <= c && c <= 'F') return c - 'A' + 10;
    throw std::invalid_argument("Invalid hex character");
}

// --- Chuyển chuỗi hex sang bytes ---
std::vector<unsigned char> hex_to_bytes(const std::string& hex) {
    if (hex.size() % 2 != 0)
        throw std::invalid_argument("Hex string length must be even");

    std::vector<unsigned char> bytes;
    bytes.reserve(hex.size() / 2);

    for (size_t i = 0; i < hex.size(); i += 2) {
        unsigned char high = hex_value(hex[i]);
        unsigned char low = hex_value(hex[i + 1]);
        bytes.push_back((high << 4) | low);
    }
    return bytes;
}

// --- Bảng Base64 ---
const char* BASE64_CHARS =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

// --- Mã hoá Base64 ---
std::string base64_encode(const std::vector<unsigned char>& data) {
    std::string out;
    size_t i = 0;
    for (; i + 2 < data.size(); i += 3) {
        unsigned n = (data[i] << 16) | (data[i + 1] << 8) | data[i + 2];
        out.push_back(BASE64_CHARS[(n >> 18) & 63]);
        out.push_back(BASE64_CHARS[(n >> 12) & 63]);
        out.push_back(BASE64_CHARS[(n >> 6) & 63]);
        out.push_back(BASE64_CHARS[n & 63]);
    }

    if (i + 1 < data.size()) {
        unsigned n = (data[i] << 16) | (data[i + 1] << 8);
        out.push_back(BASE64_CHARS[(n >> 18) & 63]);
        out.push_back(BASE64_CHARS[(n >> 12) & 63]);
        out.push_back(BASE64_CHARS[(n >> 6) & 63]);
        out.push_back('=');
    } else if (i < data.size()) {
        unsigned n = (data[i] << 16);
        out.push_back(BASE64_CHARS[(n >> 18) & 63]);
        out.push_back(BASE64_CHARS[(n >> 12) & 63]);
        out.push_back('=');
        out.push_back('=');
    }
    return out;
}

// --- Hàm chính để gọi ---
std::string hex_to_base64(const std::string& hex) {
    auto bytes = hex_to_bytes(hex);
    return base64_encode(bytes);
}

} // namespace cryptopals
