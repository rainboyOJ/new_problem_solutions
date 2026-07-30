base_text, exponent_text = input().split()
base = float(base_text)
exponent = int(exponent_text)

power = 1.0
total = 1.0
for _ in range(exponent):
    power *= base
    total += power

print(f"{total:.2f}")
