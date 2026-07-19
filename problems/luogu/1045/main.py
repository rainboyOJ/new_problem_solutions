from math import log10


KEEP_DIGITS = 500
LINE_WIDTH = 50

p = int(input())
digit_count = int(p * log10(2)) + 1
modulus = 10 ** KEEP_DIGITS
last_digits = (pow(2, p, modulus) - 1) % modulus
text = str(last_digits).zfill(KEEP_DIGITS)

output = [str(digit_count)]
for start in range(0, KEEP_DIGITS, LINE_WIDTH):
    output.append(text[start:start + LINE_WIDTH])

print("\n".join(output))
