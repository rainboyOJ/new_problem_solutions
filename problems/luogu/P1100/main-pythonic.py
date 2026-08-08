x = int(input())
print((x >> 16) | ((x & 0xFFFF) << 16))
