Phân tích:
   -Mục tiêu viết chương trình mã hóa một đoạn plaintext bằng thuật toán XOR lặp khóa (repeating -key XOR)
  -Mỗi ký tự được XOR với một ký tự trong khóa, nếu khóa ngắn hơn thì lặp lại khóa.
  -Kết quả sau khi XOR phải được chuyển sang dạng mã hex như mẫu của cryptopals 
Các bước thực hiện:
   -Viết hàm bytes_to_hex để duyệt qua từng bytes trong dữ liệu , in mỗi byte dưới dạng 2 chữ số hex.
  -Viết hàm repeating_key_xor nhận vào plaintext và key, lặp qua từng ký tự của plaintext, xor với ký tự tương ứng trong key, gộp kết quả vào chuỗi result chứa các byte xor.
  -Gọi hai hàm trên để mã hóa và chuyển sang hex
  -Kiểm thử trong test_solution.cpp
