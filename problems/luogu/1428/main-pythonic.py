from itertools import combinations
n=int(input())
a=list(map(int,input().split()))
pairs=[p for p in combinations(range(n),2) if a[p[0]]<a[p[1]]]
print(*(sum(p[1]==i for p in pairs) for i in range(n)))
