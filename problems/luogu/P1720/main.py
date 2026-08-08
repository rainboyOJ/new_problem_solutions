n = int(input())

previous = 0
current = 1

for _ in range(n):
    previous, current = current, previous + current

print(f"{previous:.2f}")
