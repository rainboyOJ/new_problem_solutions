n, capacity = map(int, input().split())

items = []
for _ in range(n):
    weight, value = map(int, input().split())
    items.append((value / weight, weight, value))

items.sort(reverse=True)

answer = 0.0
remaining = capacity

for unit_value, weight, value in items:
    if remaining == 0:
        break
    take = min(remaining, weight)
    answer += take * unit_value
    remaining -= take

print(f"{answer:.2f}")
