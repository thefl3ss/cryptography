"""
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
"""
import base64
from itertools import combinations

# ====== 1. Hàm tính Hamming distance ======
def hamming_distance(b1, b2):
    """Tính số bit khác nhau giữa 2 bytes object"""
    assert len(b1) == len(b2)
    dist = 0
    for x, y in zip(b1, b2):
        diff = x ^ y
        dist += bin(diff).count("1")
    return dist


# ====== 2. Hàm đoán độ dài khóa ======
def guess_keysize(cipher, min_k=2, max_k=40):
    distances = []
    for keysize in range(min_k, max_k + 1):
        # Lấy 4 block đầu để tính trung bình
        blocks = [cipher[i:i+keysize] for i in range(0, keysize*4, keysize)]
        pairs = list(combinations(blocks, 2))
        dists = [hamming_distance(p[0], p[1]) / keysize for p in pairs]
        avg_dist = sum(dists) / len(dists)
        distances.append((keysize, avg_dist))
    # Sắp xếp theo khoảng cách nhỏ nhất
    return sorted(distances, key=lambda x: x[1])


# ====== 3. Hàm tách và chuyển vị block 
def transpose_blocks(cipher, keysize):
    blocks = [cipher[i:i+keysize] for i in range(0, len(cipher), keysize)]
    transposed = []
    for i in range(keysize):
        block = bytearray()
        for b in blocks:
            if i < len(b):
                block.append(b[i])
        transposed.append(block)
    return transposed


# ====== 4. Giải mã single-byte XOR 
def single_byte_xor(data, key):
    return bytes([b ^ key for b in data])


def score_english(text):
    """Tính điểm dựa trên tần suất ký tự tiếng Anh"""
    freq = b"ETAOIN SHRDLU"
    return sum([text.upper().count(c) for c in freq])


def break_single_byte_xor(data):
    candidates = []
    for key in range(256):
        decoded = single_byte_xor(data, key)
        score = score_english(decoded)
        candidates.append((key, score, decoded))
    return max(candidates, key=lambda x: x[1])  # chọn key có score cao nhất


# ====== 5. Ghép lại khóa và giải mã ======
def repeating_key_xor(cipher, key):
    out = bytearray()
    for i in range(len(cipher)):
        out.append(cipher[i] ^ key[i % len(key)])
    return bytes(out)


# ====== 6. Chương trình chính ======
def main():
    # Đọc file ciphertext (base64)
    with open("cipher.txt", "r") as f:
        data = base64.b64decode(f.read())

    # Đoán độ dài khóa
    possible_keysizes = guess_keysize(data)
    print("Top KEYSIZE candidates:", possible_keysizes[:5])

    # Thử keysize tốt nhất
    best_keysize = possible_keysizes[0][0]
    transposed = transpose_blocks(data, best_keysize)

    # Tìm từng byte khóa
    key = bytes([break_single_byte_xor(block)[0] for block in transposed])
    print("Recovered key:", key)

    # Giải mã plaintext
    plaintext = repeating_key_xor(data, key)
    print("\n--- PLAINTEXT ---")
    print(plaintext.decode(errors="ignore"))


if __name__ == "__main__":
    main()
