from itertools import combinations

n = int(input())
a = list(map(int, input().split()))
pairs = list(filter(lambda p: a[p[0]] < a[p[1]], combinations(range(n), 2)))
print(*(len([p for p in pairs if p[1] == i]) for i in range(n)))
