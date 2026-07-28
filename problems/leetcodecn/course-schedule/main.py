#!/usr/bin/env python3
from collections import deque
from typing import List

class Solution:
    def canFinish(self, n: int, prerequisites: List[List[int]]) -> bool:
        g = [[] for _ in range(n)]
        indeg = [0] * n
        for a, b in prerequisites:
            g[b].append(a)
            indeg[a] += 1
        q = deque([i for i in range(n) if indeg[i] == 0])
        cnt = 0
        while q:
            u = q.popleft()
            cnt += 1
            for v in g[u]:
                indeg[v] -= 1
                if indeg[v] == 0:
                    q.append(v)
        return cnt == n

def main():
    n, m = map(int, input().split())
    pre = [list(map(int, input().split())) for _ in range(m)]
    print(Solution().canFinish(n, pre))
if __name__ == "__main__": main()
