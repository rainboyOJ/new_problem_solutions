n = int(input())

parts = []
current = 2
total = 0

while total + current <= n:
    parts.append(current)
    total += current
    current += 1

remaining = n - total
index = len(parts) - 1

while remaining > 0:
    parts[index] += 1
    remaining -= 1
    index -= 1
    if index < 0:
        index = len(parts) - 1

answer = 1
for value in parts:
    answer *= value

print(*parts)
print(answer)
