import sys
from collections import Counter

_, m, *a = map(int, sys.stdin.buffer.read().split())    # n 用不上，len(a) 就是
last = {v: i for i, v in enumerate(a)}                  # 每个点数最后一次出现的位置
cnt = Counter()

for s in range(len(a)):                                 # 第 s 局：从位置 s 开始走跳跃链
    i = s
    while i < len(a):
        cnt[a[i]] += 1
        i = last[a[i]] + 1                              # 跳过被整段收走的牌

print(*(cnt[v] for v in range(1, m + 1)))
