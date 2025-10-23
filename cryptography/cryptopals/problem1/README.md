*Phân tích
Để chuyển chuỗi ký tự từ thập lục phân sang base64 ta cần làm các bước sau:
-Bước 1: Chuyển chuỗi ký tự từ hệ thập lục phân sang hệ thập phân (hàm)
    +Mỗi ký tự hex sẽ chuyển chuyển thành số nguyên tương ứng từ 0 đến 15.
     +Hai ký tự hex sẽ ứng với một byte.
-Bước 2 : Chuyển các số nguyên trong hệ thập phân sang bytes (hàm)
Mỗi cặp ký tự hex tao có thể biểu diễn được dưới dạng 2 số nguyên, mỗi số nguyên này có thể biểu diễn dưới dạng 4 bit , 4 bit ứng với số nguyên đầu tiên là 4 bit cao, 4 bit ứng với số nguyên còn lại là 4 bit thấp, ta sử dụng phép dịch trái 4 bit cho 4 bit cao và sử nguyên 4 bit thấp, dùng phép gộp để gộp thành một byte(8 bit).
–Bước 3 : Chuyển từ bytes sang base64 (hàm)
Cứ gom mỗi ba byte lại ta sẽ có được một chuỗi 24 bit, tách chuỗi 24 bit này ra thành 4 phần mỗi phần 6 bit, mỗi phần 6 bit này sẽ được chuyển sang ký tự base64 tương ứng
Lúc này phần dữ liệu còn lại sẽ có thể không đủ nhóm 3 byte tức là thiếu 1 byte hoặc 2 byte thì thiếu một byte sẽ được mã hóa tình một dấu “=”, thiếu hai byte sẽ được mã hóa thành hai dấu “=”.
-Bước 4 : Trong hàm main gọi các hàm và in ra kết quả
