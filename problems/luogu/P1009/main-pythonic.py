n = int(input())
total = fact = 1
for i in range(2, n + 1):
    fact *= i
    total += fact
print(total)
