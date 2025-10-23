"""
Write-up
em thực hiện các bước sau:
Tạo số nguyên tố → sinh khóa → tính nghịch đảo modular (dung thuật toán euclid mở rộng)
Mã hóa và giải mã bằng lũy thừa modulo.
Chuyển đổi giữa chuỗi và số để xử lý dữ liệu thực tế.
"""
from Crypto.Util import number 



############################################################## Hàm tính nghịch đảo modulo
def egcd(a,b): #hàm số trả về bộ 3 (d,x,y) thỏa: ax+by=d=gcd(a,b)
	if b == 0:
		return (a,1,0)
	else:
		d ,x1 ,y1 = egcd(b, a%b)
		x = y1
		y = x1 - (a//b)*y1
		return (d ,x ,y)

def modInv(a, m):
    """Tính nghịch đảo modulo: tìm x sao cho (a * x) % m == 1"""
    g, x, y = egcd(a, m)
    if g != 1:
        return None  # không tồn tại nghịch đảo modular
    x = (x % m + m) % m  # đảm bảo x dương
    return x
######################################## hàm decryt và encrypt

def encrypt(a, b, c):
	return pow(a, b, c)

def decrypt(a, b, c):
	return pow(a, b, c)

#hàm chuyển từ str sang int và ngược lại 
def str_to_int(text):
	hex_data = text.encode().hex()
	thap_luc_phan = "0x" + hex_data
	number = int(thap_luc_phan,16)
	return number
    
def int_to_str(number):
	text = bytes.fromhex(hex(number)[2:]).decode('utf-8', errors='ignore')    
	return text

#################################################
print("----RSA----")
m = int(input("[+] Nhập số cần mã hóa: "))

so_bit = int(input("[+] Nhập số bit của 2 số nguyên tố:  "))

p = number.getPrime(so_bit)
q = number.getPrime(so_bit)
phi = (p-1)*(q-1)
n = p*q
e = 3
d = modInv(phi, e)

encrypted = encrypt(m, e, n)

print(f'[+] Encrypt 42 --> {encrypted}')

#thử với str
text = str(input("[+] Nhập văn bản cần mã hóa: "))
numbers = str_to_int(text)
Encrypted_text = int_to_str(encrypt(numbers, e, n))
print(f"[+] Encrypted: {Encrypted_text}")
