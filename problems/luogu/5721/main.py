n = int(input())
current = 1
lines = []

for width in range(n, 0, -1):
    row = []
    for _ in range(width):
        row.append(f"{current:02d}")
        current += 1
    lines.append("".join(row))

print("\n".join(lines), end="")
