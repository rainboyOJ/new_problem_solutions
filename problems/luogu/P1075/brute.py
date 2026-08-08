n = int(input())

for factor in range(n - 1, 1, -1):
    if n % factor == 0:
        print(factor)
        break
