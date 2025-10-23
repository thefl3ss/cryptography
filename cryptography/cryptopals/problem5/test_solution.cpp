#include <iostream>
#include <string>
#include <cassert>

// Khai báo lại hàm từ solution.cpp
std::string bytes_to_hex(const std::string& input);
std::string repeating_key_xor(const std::string& plaintext, const std::string& key);

int main() {
    std::string plaintext =
        "Burning 'em, if you ain't quick and nimble\n"
        "I go crazy when I hear a cymbal";
    std::string key = "ICE";

    std::string expected_hex =
        "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272"
        "a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f";

    // Thực hiện XOR lặp khóa
    std::string encrypted = repeating_key_xor(plaintext, key);
    std::string hex_output = bytes_to_hex(encrypted);

    // Kiểm tra kết quả với output chuẩn
    assert(hex_output == expected_hex);

    std::cout << "✅ Test passed! Output matches the expected ciphertext." << std::endl;
    return 0;
}
