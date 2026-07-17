from itertools import product

n, torch_count, glowstone_count = map(int, input().split())
lit = set()

for _ in range(torch_count):
    x, y = map(int, input().split())
    lit |= {
        (x + dx, y + dy)
        for dx, dy in product(range(-2, 3), repeat=2)
        if abs(dx) + abs(dy) <= 2 and 1 <= x + dx <= n and 1 <= y + dy <= n
    }

for _ in range(glowstone_count):
    x, y = map(int, input().split())
    lit |= {
        (x + dx, y + dy)
        for dx, dy in product(range(-2, 3), repeat=2)
        if 1 <= x + dx <= n and 1 <= y + dy <= n
    }

print(n * n - len(lit))
