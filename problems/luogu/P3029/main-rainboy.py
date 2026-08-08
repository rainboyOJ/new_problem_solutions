
from functools import partial
import sys
from itertools import batched
from collections import Counter
from bisect import bisect_left, bisect_right

data = list(map(int,sys.stdin.buffer.read().split()))
n = data[0]

cnt = Counter()
ans = 2 ** 30


def flow(value, *steps):
    for step in steps:
        value = step(value)
    return value


# cows = list(batched(data[1:],2))
# cows.sort(key=lambda x: x[0])

cows = flow(
        batched(data[1:],2),
        list,
        partial(sorted,key= lambda x : x[0])
        )

# 离散化
dif = flow(
    {id for _ , id in cows},
    list,
    sorted,
    )

nid = lambda id: bisect_left(dif,id)
cows_difed = [(h,nid(id)) for h,id in cows]

# 不同的品种的奶牛的数量
required = len(dif)
# print(dif)
# print(cows_difed)

# 双指针
left = 0

for right in range(len(cows_difed)):
    (pos,id) = cows_difed[right]
    cnt[id] += 1
    while len(cnt) == required:
        ans = min(ans,pos - cows_difed[left][0])
        lid = cows_difed[left][1]
        cnt[lid] -= 1
        if not cnt[lid]:
            del cnt[lid]
        left+=1

print(ans)
