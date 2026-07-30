from struct import pack, unpack

# 按题目先读成 C++ float，再用 int 向零截断。
value = unpack("f", pack("f", float(input())))[0]
print(int(value))
