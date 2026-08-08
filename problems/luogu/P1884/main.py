import sys
from collections import Counter


# ---------- 1. 读入所有矩形，生成左右竖边事件 ----------
data = iter(map(int, sys.stdin.buffer.read().split()))
events = []                     # 每个事件: (x坐标, 类型, y下界, y上界)
for _ in range(next(data)):     # 循环 N 次
    x1, y1, x2, y2 = (next(data) for _ in range(4))
    low, high = sorted((y1, y2))   # y1(上) > y2(下)，统一为 [下界, 上界]
    # 左边界 +1（进入），右边界 -1（离开）
    events += [(x1, 1, low, high), (x2, -1, low, high)]
events.sort()                   # 按 x 坐标从小到大排序
# ------------------------------------------------


# ---- 2. 计算当前活跃 y 区间的并集总长度 ----
def covered_length(active):
    """
    active : Counter{(y下界, y上界): 覆盖层数}
    返回这些区间合并后的总长度
    """
    total = 0
    right = None                # 当前合并段的右端点
    # 按左端点排序，贪心合并重叠区间
    for (left, end), count in sorted(active.items()):
        if not count:           # 层数为 0 → 实际已不活跃
            continue
        if right is None or left > right:
            total += end - left     # 新的不连续段，直接加整段
            right = end
        elif end > right:
            total += end - right    # 和当前段重叠但伸得更远，只加超出的部分
            right = end
    return total


# ---------- 3. 扫描线主循环 ----------
active = Counter()              # 当前在扫描线"内部"的 y 区间
answer = 0
previous_x = events[0][0]       # 上一个处理到的 x 坐标
i = 0

while i < len(events):
    x = events[i][0]            # 当前这一批事件的 x 坐标

    # 从 previous_x 到 x 这一条，y 方向覆盖不变
    # 面积 = 宽度 × y 方向被覆盖的总长度
    answer += (x - previous_x) * covered_length(active)

    # 处理 x 处的所有事件（可能有多个矩形同时开始/结束）
    while i < len(events) and events[i][0] == x:
        _, change, low, high = events[i]
        active[low, high] += change   # +1 进入，-1 离开
        i += 1

    previous_x = x

print(answer)
