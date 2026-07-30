limit = int(input())
factorial = 1
total = 0

for number in range(1, limit + 1):
    factorial *= number
    total += factorial

print(total)
