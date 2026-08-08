from itertools import product

w, d, h = map(int, input().split())
q = int(input())
removed = set()
for _ in range(q):
    x1, y1, z1, x2, y2, z2 = map(int, input().split())
    removed |= set(product(range(x1, x2 + 1), range(y1, y2 + 1), range(z1, z2 + 1)))
print(w * d * h - len(removed))
