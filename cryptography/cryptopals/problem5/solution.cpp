#include <string>
#include <sstream>
#include <iomanip>

// ==========================
// Chuyển chuỗi byte sang chuỗi hex
// ==========================
std::string bytes_to_hex(const std::string& input) {
    std::ostringstream oss;
    oss << std::hex << std::setfill('0');

    for (unsigned char c : input) {
        oss << std::setw(2) << static_cast<int>(c);
    }
    return oss.str();
}

// ==========================
// XOR lặp khóa (repeating-key XOR)
// ==========================
std::string repeating_key_xor(const std::string& plaintext, const std::string& key) {
    std::string result;
    result.reserve(plaintext.size());

    for (size_t i = 0; i < plaintext.size(); ++i) {
        // XOR từng ký tự với ký tự tương ứng trong key, lặp lại key nếu cần
        char xored = plaintext[i] ^ key[i % key.size()];
        result.push_back(xored);
    }

    return result;
}

