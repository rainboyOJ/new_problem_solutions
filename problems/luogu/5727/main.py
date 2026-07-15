n = int(input())

sequence = [n]
while n != 1:
    if n % 2 == 1:
        n = n * 3 + 1
    else:
        n //= 2
    sequence.append(n)

sequence.reverse()
print(*sequence)
