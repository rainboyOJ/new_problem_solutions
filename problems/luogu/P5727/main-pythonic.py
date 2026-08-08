n = int(input())
sequence = [n]
while n != 1:
    n = n * 3 + 1 if n % 2 else n // 2
    sequence.append(n)
print(*sequence[::-1])
