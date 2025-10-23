#ifndef SOLUTION_CPP
#define SOLUTION_CPP

#include <cstdint>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>
#include <iomanip>

// ========================
//  HÀM HỖ TRỢ CƠ BẢN
// ========================

// Hàm xoay trái 32-bit (dùng trong SHA-1)
static inline uint32_t leftrotate(uint32_t x, unsigned n) {
    return (x << n) | (x >> (32 - n));
}

// ========================
//  CÀI ĐẶT THUẬT TOÁN SHA-1
// ========================
// Thuật toán SHA-1 tiêu chuẩn, xuất ra 20 byte (160 bit)
// Input: dữ liệu bất kỳ (vector<uint8_t>)
// Output: 20 byte băm (digest)
std::vector<uint8_t> sha1(const std::vector<uint8_t>& data) {
    // Giá trị khởi tạo theo chuẩn SHA-1
    uint32_t h0 = 0x67452301;
    uint32_t h1 = 0xEFCDAB89;
    uint32_t h2 = 0x98BADCFE;
    uint32_t h3 = 0x10325476;
    uint32_t h4 = 0xC3D2E1F0;

    // Độ dài ban đầu tính bằng bit
    uint64_t original_bit_len = static_cast<uint64_t>(data.size()) * 8ULL;

    // Tạo bản sao dữ liệu để padding
    std::vector<uint8_t> padded = data;
    padded.push_back(0x80);  // thêm bit '1'

    // Padding thêm các byte 0x00 cho đến khi (độ dài % 64) = 56
    while ((padded.size() % 64) != 56) {
        padded.push_back(0x00);
    }

    // Thêm độ dài gốc (64-bit big-endian)
    for (int i = 7; i >= 0; --i) {
        padded.push_back(static_cast<uint8_t>((original_bit_len >> (8 * i)) & 0xFF));
    }

    // Chia dữ liệu thành từng khối 512-bit (64 byte)
    const size_t chunks = padded.size() / 64;
    for (size_t chunk = 0; chunk < chunks; ++chunk) {
        uint32_t w[80];

        // Chia 512-bit thành 16 từ 32-bit (big-endian)
        for (int i = 0; i < 16; ++i) {
            size_t base = chunk * 64 + i * 4;
            w[i] = (static_cast<uint32_t>(padded[base]) << 24)
                 | (static_cast<uint32_t>(padded[base + 1]) << 16)
                 | (static_cast<uint32_t>(padded[base + 2]) << 8)
                 | (static_cast<uint32_t>(padded[base + 3]));
        }

        // Mở rộng 16 từ thành 80 từ (theo công thức SHA-1)
        for (int i = 16; i < 80; ++i) {
            w[i] = leftrotate(w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16], 1);
        }

        // Khởi tạo giá trị a,b,c,d,e cho vòng lặp
        uint32_t a = h0;
        uint32_t b = h1;
        uint32_t c = h2;
        uint32_t d = h3;
        uint32_t e = h4;

        // Vòng lặp chính (80 bước)
        for (int i = 0; i < 80; ++i) {
            uint32_t f, k;
            if (i <= 19) {
                f = (b & c) | ((~b) & d);
                k = 0x5A827999;
            } else if (i <= 39) {
                f = b ^ c ^ d;
                k = 0x6ED9EBA1;
            } else if (i <= 59) {
                f = (b & c) | (b & d) | (c & d);
                k = 0x8F1BBCDC;
            } else {
                f = b ^ c ^ d;
                k = 0xCA62C1D6;
            }
            uint32_t temp = leftrotate(a, 5) + f + e + k + w[i];
            e = d;
            d = c;
            c = leftrotate(b, 30);
            b = a;
            a = temp;
        }

        // Cộng kết quả khối này vào tổng
        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
        h4 += e;
    }

    // Ghép 5 giá trị h0..h4 thành output 20 byte
    std::vector<uint8_t> digest(20);
    uint32_t hs[5] = {h0, h1, h2, h3, h4};
    for (int i = 0; i < 5; ++i) {
        digest[i*4 + 0] = (hs[i] >> 24) & 0xFF;
        digest[i*4 + 1] = (hs[i] >> 16) & 0xFF;
        digest[i*4 + 2] = (hs[i] >> 8) & 0xFF;
        digest[i*4 + 3] = (hs[i]) & 0xFF;
    }
    return digest;
}

// ========================
//  HÀM MAC: SHA1(key || message)
// ========================

std::vector<uint8_t> sha1_keyed_mac(const std::vector<uint8_t>& key,
                                    const std::vector<uint8_t>& message) {
    std::vector<uint8_t> data;
    data.reserve(key.size() + message.size());
    data.insert(data.end(), key.begin(), key.end());
    data.insert(data.end(), message.begin(), message.end());
    return sha1(data);
}

// Hàm kiểm tra tính hợp lệ của MAC
bool verify_mac(const std::vector<uint8_t>& key,
                const std::vector<uint8_t>& message,
                const std::vector<uint8_t>& mac) {
    std::vector<uint8_t> expected = sha1_keyed_mac(key, message);
    if (expected.size() != mac.size()) return false;

    // So sánh theo kiểu constant-time để tránh timing attack
    uint8_t diff = 0;
    for (size_t i = 0; i < mac.size(); ++i) {
        diff |= (expected[i] ^ mac[i]);
    }
    return diff == 0;
}

// ========================
//  HÀM PHỤ: Chuyển đổi HEX
// ========================

// Chuyển vector<uint8_t> sang chuỗi hex
std::string to_hex(const std::vector<uint8_t>& data) {
    std::ostringstream oss;
    oss << std::hex << std::setfill('0');
    for (uint8_t b : data) {
        oss << std::setw(2) << static_cast<int>(b);
    }
    return oss.str();
}

// Chuyển chuỗi hex sang vector<uint8_t>
std::vector<uint8_t> from_hex(const std::string& hex) {
    std::vector<uint8_t> out;
    out.reserve(hex.size() / 2);
    for (size_t i = 0; i + 1 < hex.size(); i += 2) {
        unsigned int byte;
        std::istringstream iss(hex.substr(i, 2));
        iss >> std::hex >> byte;
        out.push_back(static_cast<uint8_t>(byte));
    }
    return out;
}

#endif // SOLUTION_CPP
