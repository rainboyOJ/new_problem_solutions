#!/usr/bin/env python3
from typing import List
class Solution:
    def combinationSum(self, candidates: List[int], target: int) -> List[List[int]]:
        ans, cur = [], []
        def dfs(i, left):
            if left == 0: ans.append(cur[:]); return
            if i == len(candidates) or left < 0: return
            dfs(i+1, left)
            cur.append(candidates[i])
            dfs(i, left - candidates[i])
            cur.pop()
        dfs(0, target)
        return ans

def main():
    n, t = map(int, input().split()); a = list(map(int, input().split()))
    for v in Solution().combinationSum(a, t): print(*v)
if __name__ == "__main__": main()
