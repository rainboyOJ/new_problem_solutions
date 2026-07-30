category_a = 0

for number in range(1, 1001):
    bits = bin(number)[2:]
    if bits.count("1") > bits.count("0"):
        category_a += 1

print(category_a, 1000 - category_a)
