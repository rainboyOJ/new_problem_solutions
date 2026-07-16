number = int(input())
print((number >> 16) | ((number & 0xFFFF) << 16))
