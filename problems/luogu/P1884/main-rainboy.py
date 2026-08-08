from functools import partial
from itertools import batched
import sys
from collections import Counter

# 1. 读取数据
def flow(value, *steps):
    for step in steps:
        value = step(value)
    return value

data = flow(sys.stdin.buffer.read().split() , partial(map,int),list)
n = data[0]
data = flow(batched(data[1:],4),list)

events = []

for x1, y1, x2, y2 in data:
    if y1 > y2:
        y1, y2 = y2, y1

    events.append((x1, 1, y1, y2))
    events.append((x2, -1, y1, y2))

events.sort()

cnt = Counter()
ans = 0

def covered_length():
    tot = 0
    right = None

    for (left,end),count in sorted(cnt.items()) :
        if not count:
            continue
        if right is None or left > right:
            tot += end-left
            right = end
        elif end > right:
            tot += end - right
            right = end
    return tot


# 主

previous_x = events[0][0]
i = 0
while i < len(events):
    x = events[i][0]

    ans += (x-previous_x) *covered_length()

    # 改变 扫描线的数据
    # 优化, 多个事件的都在x,那么就不用计算 面积
    while i < len(events) and events[i][0] == x:
        _,change,low,height = events[i]
        cnt[low,height] += change
        i+=1


    previous_x = x

print(ans)
