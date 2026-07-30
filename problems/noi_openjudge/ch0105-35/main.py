limit = int(input())
factorial = 1
total = 1.0

for number in range(1, limit + 1):
    factorial *= number
    total += 1 / factorial

print(f"{total:.10f}")
