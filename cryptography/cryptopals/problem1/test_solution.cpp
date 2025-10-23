// test_solution.cpp
#include <cassert>
#include <iostream>
#include "solution.cpp"  // include trực tiếp để biên dịch cùng

using namespace cryptopals;

int main() {
    std::cout << "Running tests for Cryptopals Challenge 1...\n";

    // Test 1: ví dụ từ Cryptopals
    std::string input =
        "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573"
        "206d757368726f6f6d";
    std::string expected =
        "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";
    assert(hex_to_base64(input) == expected);

    // Test 2: chuỗi ngắn
    assert(hex_to_base64("4869") == "SGk="); // “Hi”

    // Test 3: lỗi độ dài lẻ
    try {
        hex_to_base64("abc");
        assert(false && "Should have thrown an exception");
    } catch (const std::invalid_argument&) {}

    // Test 4: ký tự không hợp lệ
    try {
        hex_to_base64("zz");
        assert(false && "Should have thrown an exception");
    } catch (const std::invalid_argument&) {}

    std::cout << "✅ All tests passed!\n";
    return 0;
}
