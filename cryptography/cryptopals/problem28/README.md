Phân tích:
*Nguyên lý hoạt động của hàm băm sha1
 -input là chuỗi dữ liệu bất kì 
 -Output là chuỗi 20 byte cố định, thường biểu diễn dưới dạng 40 kí tự hex
 -Các bước hoạt động của sha1:
     +Dữ liệu đầu vào được chuyển sang chuỗi bit
     +Thêm bit 1 vào cuối dữ liệu, rồi thêm các bit không sao cho tổng độ dài của chuỗi bit đồng dư 448 modulo 512
    +Sau khi padding, thêm vào 64 biểu diễn độ dài ban đầu của dữ liệu, khi đó tổng độ dài của chuỗi bit sẽ là một bội số của 512
   + Chia khối dữ liệu đó ra thành các khối 512 bit, mỗi khối sẽ được xử lý độc lập. Nếu dữ lại dài , sha1 sẽ lặp lại quy trình cho từng khối
  + Mỗi khối 512 bit sẽ được chia thành 16 phần mỗi phần 32 bit, sau đó mở rộng thành 80 từ 
theo công thức W[i] = (W[i-3] XOR W[i-8] XOR W[i-14] XOR W[i-16]) <<< 1
Khởi tạo 5 thanh ghi (h0,h1,h2,h3,h4) dùng giá trị ban đầu cố định (theo chuẩn SHA-1)
80 vòng lặp tính toán sẽ được thực hiện với các hàm f và các hằng số k mỗi hàm f và mỗi hàm số sẽ được dùng cho 20 vòng. Sau khi xử lý 80 vòng cộng kết quả vào h0,h1,h2,h3,h4.
Ghép 5 thanh ghi tạo ra hash 160 bit.
+Nếu còn các khối sao các khối đó sẽ có các thanh ghi khởi tạo ban đầu là h0,h1,h2,h3,h4 đã tính được ở khối được và lặp lại quá trình này.
*Solution.cpp
     Ta sẽ viết chương trình dựa trên cách hoạt động của thuật toán theo các bước:
Khởi tạo 5 giá trị ban đầu (h0-h4)
Tính chiều dài ban đầu của dữ liệu
Padding dữ liệu
Chia dữ liệu thành từng khối 512 bit
Tạo mảng 80 từ 32 bit
Khởi tạo a,b,c,d,e=h0…h4 đây là 5 thanh ghi tạm thời cho từng khối
Vòng lặp 80 bước
Cộng kết quả vào tổng (h0…h4)
Ghép 5 giá trị h0…h4 tạo thành output
Tạo MAC bằng cách dùng thuật toán sha1 cho chuỗi key+message
Kiểm tra xem MAC có hợp lệ không
