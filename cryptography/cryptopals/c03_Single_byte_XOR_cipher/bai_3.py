#Single-byte XOR cipher
"""
Em chuyển hex thành byte sau đó XOR tất cả 256 key sau đó chọn ra plaint có điểm cao nhất tức có nhiều kí tự giống tiếng anh nhất
"""
hex_data = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736"

#chuyển từ hex thành byte
data = bytes.fromhex(hex_data)


best_score = 0
best_key = 0
best_text = ""

#hàm tính điểm giống từ tiếng anh nhất
def scoring(text):
	common = "ETAOIN SHRDLU" #những chữ cái phổ biến trong tiếng anh
	return sum(c.upper() in common for c in text)

#hàm XOR với từng byte
def single_byte_XOR(cipher_text, key):
	return bytes([b ^ key for b in cipher_text])

for key in range(256): #1byte=8bit
	result = single_byte_XOR(data, key)
	try:
		decoded = result.decode("ascii")
	except:
		continue
	score = scoring(decoded)
	if score > best_score:
		best_score = score
		best_text = decoded
		best_key = key

print(f'Key: {best_key}')
print(f'Text: {best_text}')