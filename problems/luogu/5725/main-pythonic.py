n = int(input())

value = 1
for row in range(n):
    line = []
    for _ in range(n):
        line.append(f"{value:02d}")
        value += 1
    print("".join(line))

print()

value = 1
for row in range(1, n + 1):
    line = ["  " * (n - row)]
    for _ in range(row):
        line.append(f"{value:02d}")
        value += 1
    print("".join(line))
