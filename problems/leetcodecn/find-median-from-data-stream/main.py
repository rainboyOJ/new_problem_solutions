#!/usr/bin/env python3
import heapq


class MedianFinder:
    def __init__(self):
        self.lo = []
        self.hi = []

    def addNum(self, n):
        heapq.heappush(self.lo, -n)
        heapq.heappush(self.hi, -heapq.heappop(self.lo))
        if len(self.lo) < len(self.hi):
            heapq.heappush(self.lo, -heapq.heappop(self.hi))

    def findMedian(self):
        return float(-self.lo[0]) if len(self.lo) > len(self.hi) else (-self.lo[0] + self.hi[0]) / 2


def main():
    q = int(input())
    mf = MedianFinder()
    for _ in range(q):
        op = input().split()
        if op[0] == "add":
            mf.addNum(int(op[1]))
        else:
            print(mf.findMedian(), end=" ")


if __name__ == "__main__":
    main()
