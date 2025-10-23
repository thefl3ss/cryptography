#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <cassert>

#include "solution.cpp" // import toàn bộ phần cài đặt

// Hàm tạo key ngẫu nhiên với độ dài bất kỳ
std::vector<uint8_t> random_key(size_t len) {
    std::vector<uint8_t> key(len);
    std::random_device rd;
    std::mt19937_64 rng(rd());
    std::uniform_int_distribution<int> dist(0, 255);
    for (size_t i = 0; i < len; ++i)
        key[i] = static_cast<uint8_t>(dist(rng));
    return key;
}

int main() {
    bool all_ok = true;

    // =========================
    // Test 1: Tạo và xác minh MAC hợp lệ
    // =========================
    {
        auto key = random_key(16);
        std::string msg_str = "Hello, Cryptopals Set 4 - Challenge 28!";
        std::vector<uint8_t> message(msg_str.begin(), msg_str.end());

        // Tạo MAC
        auto mac = sha1_keyed_mac(key, message);

        // Kiểm tra verify phải đúng
        bool ok = verify_mac(key, message, mac);
        std::cout << "[Test 1] Xác minh MAC hợp lệ: " << (ok ? "PASS" : "FAIL") << "\n";
        if (!ok) all_ok = false;

        std::cout << "  MAC (hex): " << to_hex(mac) << "\n";
    }

    // =========================
    // Test 2: Thay đổi message => verify phải thất bại
    // =========================
    {
        auto key = random_key(16);
        std::string msg_str = "Message original";
        std::vector<uint8_t> message(msg_str.begin(), msg_str.end());
        auto mac = sha1_keyed_mac(key, message);

        // Sửa message (thêm 1 ký tự)
        std::vector<uint8_t> tampered = message;
        tampered.push_back('!');

        bool ok = verify_mac(key, tampered, mac);
        std::cout << "[Test 2] Message bị sửa: " << (!ok ? "PASS" : "FAIL (phải FAIL)") << "\n";
        if (ok) all_ok = false;
    }

    // =========================
    // Test 3: Thay đổi MAC => verify phải thất bại
    // =========================
    {
        auto key = random_key(16);
        std::string msg_str = "Another message";
        std::vector<uint8_t> message(msg_str.begin(), msg_str.end());
        auto mac = sha1_keyed_mac(key, message);

        // Sửa MAC (đảo bit đầu)
        auto bad_mac = mac;
        if (!bad_mac.empty()) bad_mac[0] ^= 0xFF;

        bool ok = verify_mac(key, message, bad_mac);
        std::cout << "[Test 3] MAC bị sửa: " << (!ok ? "PASS" : "FAIL (phải FAIL)") << "\n";
        if (ok) all_ok = false;
    }

    // =========================
    // Test 4: Kiểm tra SHA-1 với vector chuẩn ("abc")
    // =========================
    {
        std::string s = "abc";
        std::vector<uint8_t> data(s.begin(), s.end());
        auto digest = sha1(data);
        std::string hex = to_hex(digest);
        std::string expected = "a9993e364706816aba3e25717850c26c9cd0d89d";
        bool ok = (hex == expected);
        std::cout << "[Test 4] SHA1('abc') == expected: " << (ok ? "PASS" : "FAIL") << "\n";
        if (!ok) {
            std::cout << "  got: " << hex << "\n";
            std::cout << "  expected: " << expected << "\n";
            all_ok = false;
        }
    }

    // =========================
    // Tổng kết kết quả
    // =========================
    if (all_ok) {
        std::cout << "\n✅ Tất cả các test đều PASSED.\n";
        return 0;
    } else {
        std::cout << "\n❌ Có test bị FAIL.\n";
        return 1;
    }
}
