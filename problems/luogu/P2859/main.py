import sys
import heapq


def main():
    data = sys.stdin.buffer.read().split()
    n = int(data[0])

    cows = []
    pos = 1
    for i in range(1, n + 1):
        l = int(data[pos])
        r = int(data[pos + 1])
        pos += 2
        cows.append((l, r, i))

    # 按开始时间排序，开始时间相同则结束早的在前
    cows.sort()

    ans = [0] * (n + 1)
    heap = []  # 小根堆，元素是 (这类牛棚的结束时间, 牛棚编号)
    cnt = 0

    for l, r, i in cows:
        # 端点也算占用，所以结束时间必须严格小于 l 才能复用
        if heap and heap[0][0] < l:
            _, stall = heapq.heappop(heap)
            ans[i] = stall
            heapq.heappush(heap, (r, stall))
        else:
            cnt += 1
            ans[i] = cnt
            heapq.heappush(heap, (r, cnt))

    out = [str(cnt)]
    for i in range(1, n + 1):
        out.append(str(ans[i]))
    sys.stdout.write("\n".join(out) + "\n")


main()
