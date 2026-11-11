#!/usr/bin/env python3
import itertools
from itertools import accumulate, batched,permutations
import sys



def solve() -> None:
    tokens = sys.stdin.read().split()
    if not tokens:
        return
    _, _, s, *queries = tokens

    prefs  = []
    for p in itertools.permutations("abc"):
        t = [ c != p[i %3] for i, c in enumerate(s) ]
        # prefs.append(t)
        # pre_sum
        # 利用 initial=0 把所有的前缀和后移一位
        prefs.append(list(accumulate(t,initial=0)))
    # print(prefs)

    out = []
    queries = batched(map(int,queries),2)
    for l ,r in queries:
        # print(l,r)
        ans = min([p[r] - p[l-1]  for p in prefs])
        out.append(ans)
    print(*out,sep="\n")

if __name__ == "__main__":
    solve()
