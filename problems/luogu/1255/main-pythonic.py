n = int(input())

if n <= 2:
    print(n)
else:
    previous = 1
    current = 2
    for _ in range(3, n + 1):
        previous, current = current, previous + current
    print(current)
