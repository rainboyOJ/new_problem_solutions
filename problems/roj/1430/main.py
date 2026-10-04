# ROJ 1430 家庭作业：反悔贪心（大根学分 + 小根堆反悔）
# 按截止时间排序，逐个尝试接下作业；若当前前 i 个作业数超过第 i 个的截止时间，
# 弹掉学分最小的作业（反悔），保证任意时刻保留的方案合法且学分最大。
import sys
import heapq


def main() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    # (截止时间, 学分)，按截止时间升序
    jobs = sorted((next(data), next(data)) for _ in range(n))
    heap: list[int] = []  # 已接作业的学分（小根堆，堆顶是最可能反悔的）
    for d, w in jobs:
        heapq.heappush(heap, w)
        if len(heap) > d:  # 前 d 天最多做 d 个作业，超了就丢弃学分最小的
            heapq.heappop(heap)
    print(sum(heap))


if __name__ == "__main__":
    main()
