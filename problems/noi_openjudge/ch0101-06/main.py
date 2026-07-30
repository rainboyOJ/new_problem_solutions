from struct import pack, unpack

character = input()
integer = int(input())
# 第三个数按 C++ 的 float 读入，先做一次单精度舍入。
single_precision = unpack("f", pack("f", float(input())))[0]
double_precision = float(input())

print(f"{character} {integer} {single_precision:.6f} {double_precision:.6f}")
