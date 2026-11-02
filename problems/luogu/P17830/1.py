import sys
from collections import Counter

n, m, *a = map(int, sys.stdin.buffer.read().split())    # n 用不上，len(a) 就是
last = {v: i for i, v in enumerate(a)}
nxt = {k: v +1 for k,v in last.items() }
cnt = Counter()


for s in range(n):
    i = s
    while i < n:
        cnt[a[i]] += 1
        i  = nxt[a[i]]

print( *[cnt[v] for v in range(1,m+1)] )
