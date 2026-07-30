from struct import pack, unpack

# 题目规定读入单精度浮点数，先按 IEEE 754 单精度舍入以匹配 C++ 的 float。
value = unpack("f", pack("f", float(input())))[0]
print(f"{value:.3f}")
