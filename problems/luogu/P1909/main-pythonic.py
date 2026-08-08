from math import ceil
need = int(input())
print(min(ceil(need / a) * p for a, p in (map(int, input().split()) for _ in range(3))))
