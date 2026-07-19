from itertools import combinations
n = int(input())
a = list(map(int, input().split()))
pairs = [(j, i) for j, i in combinations(range(n), 2) if a[j] < a[i]]
print(*(sum(i == t for _, i in pairs) for t in range(n)))
