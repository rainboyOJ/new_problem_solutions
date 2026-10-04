from heapq import heapify, heappop, heappush


def main() -> None:
    data = open(0).read().split()
    n = int(data[0])
    heap = [int(x) for x in data[1:1 + n]]
    # 哈夫曼合并：每次取出最小的两堆合并，代价累加；小根堆维护
    heapify(heap)
    total = 0
    for _ in range(n - 1):
        a = heappop(heap)
        b = heappop(heap)
        total += a + b
        heappush(heap, a + b)
    print(total)


main()
