1️. Giải mã Base64
Trước hết, em đọc file và decode base64 để lấy dữ liệu nhị phân (ciphertext thật sự).

2️. Đoán độ dài khóa (KEYSIZE)
Vì khóa lặp lại, nên mình phải tìm xem mỗi bao nhiêu byte thì khóa lặp lại một vòng.
Cách làm:
Viết hàm Hamming distance để đo sự khác nhau giữa hai chuỗi bit.
So sánh các đoạn liên tiếp của ciphertext (ví dụ 4 đoạn đầu).
Tính (Hamming distance / KEYSIZE) cho từng độ dài khóa từ 2 đến 40.
Độ dài nào cho khoảng cách trung bình nhỏ nhất → có khả năng là KEYSIZE thật.

3️. Chuyển vị dữ liệu (transpose blocks)
Sau khi có KEYSIZE, chia ciphertext thành các block dài bằng KEYSIZE.
Rồi gom:
Tất cả byte đầu tiên của mỗi block → thành block 1
Tất cả byte thứ hai của mỗi block → thành block 2
v.v.
Như vậy, mỗi block mới là dữ liệu được mã hóa bằng cùng một byte khóa.

4️. Giải từng block bằng Single-byte XOR
Giờ mình xử lý từng block độc lập:
Thử XOR với tất cả các byte từ 0–255.
Tính điểm dựa trên tần suất chữ cái tiếng Anh (nếu giải ra nhiều chữ cái thường, space, v.v. thì điểm cao).
Byte nào cho điểm cao nhất → chính là một phần khóa.
Ghép tất cả các byte này lại → thu được khóa hoàn chỉnh.

5️. Giải mã toàn bộ
Dùng khóa vừa tìm được, thực hiện repeating-key XOR ngược lên toàn ciphertext.
Kết quả chính là plaintext gốc.