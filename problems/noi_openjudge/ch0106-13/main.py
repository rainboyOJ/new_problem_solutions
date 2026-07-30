number = input().strip()
divisors = []

for divisor in range(2, 10):
    remainder = 0
    for digit in number:
        remainder = (remainder * 10 + int(digit)) % divisor
    if remainder == 0:
        divisors.append(str(divisor))

print(" ".join(divisors) if divisors else "none")
