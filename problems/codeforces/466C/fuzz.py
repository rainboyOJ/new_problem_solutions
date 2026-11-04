import random
from collections import defaultdict
from itertools import accumulate

def fast(a):
    n=len(a); p=list(accumulate(a)); d=defaultdict(int); ans=0
    for i in range(n-2,-1,-1):
        v=p[i]
        if 3*v==p[n-1]: ans+=d[2*v]
        d[v]+=1
    return ans

def brute(a):
    n=len(a); p=[0]
    for x in a: p.append(p[-1]+x)
    tot=p[n]; ans=0
    for i in range(1,n):
        for j in range(i+1,n):
            if p[i]==p[j]-p[i]==tot-p[j]: ans+=1
    return ans

random.seed(1)
bad=0
for t in range(200000):
    n=random.randint(1,10)
    lim=random.choice([0,1,2,3,5,10**9])
    a=[random.randint(-lim,lim) for _ in range(n)]
    f=fast(a); b=brute(a)
    if f!=b:
        print("DIFF",n,a,"got",f,"want",b); bad=1; break
print("bad" if bad else "ALL OK")
