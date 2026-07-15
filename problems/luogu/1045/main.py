from math import log10


p = int(input())
digit_count = int(p * log10(2)) + 1
modulus = 10 ** 500
last_digits = (pow(2, p, modulus) - 1) % modulus
text = str(last_digits).zfill(500)

print(digit_count)
for start in range(0, 500, 50):
    print(text[start:start + 50])
