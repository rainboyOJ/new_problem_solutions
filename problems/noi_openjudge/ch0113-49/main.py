base = int(input())
value = int(input())
power = 1
exponent = 0

while power * base <= value:
    power *= base
    exponent += 1

print(exponent)
