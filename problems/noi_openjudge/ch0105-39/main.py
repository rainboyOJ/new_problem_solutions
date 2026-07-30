limit = int(input())
total = 0

for number in range(1, limit + 1):
    if number % 7 != 0 and "7" not in str(number):
        total += number * number

print(total)
