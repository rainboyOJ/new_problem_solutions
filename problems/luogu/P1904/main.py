import sys
from collections import defaultdict
from heapq import heappop, heappush


starts = defaultdict(list)
positions = set()
data = list(map(int, sys.stdin.buffer.read().split()))

# 按所有空白读取，再把每三个整数作为一幢建筑。
for i in range(0, len(data), 3):
    left, height, right = data[i], data[i + 1], data[i + 2]
    # heapq 是最小堆，保存负高度后，堆顶就是最高建筑。
    starts[left].append((-height, right))
    # 天际线只可能在建筑的左右端点发生变化。
    positions.update((left, right))

heap = []
answer = []
last_height = 0

for x in sorted(positions):
    # 扫描到左端点时，将这里开始的所有建筑加入堆。
    for building in starts[x]:
        heappush(heap, building)

    # 惰性删除已经在当前位置结束的建筑。
    while heap and heap[0][1] <= x:
        heappop(heap)

    height = -heap[0][0] if heap else 0
    # 最高高度改变时，当前位置才是轮廓折点。
    if height != last_height:
        answer.extend((x, height))
        last_height = height

print(*answer)
