#!/usr/bin/env python3
from collections import defaultdict, deque
from typing import Optional


class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = self.right = None


class Solution:
    def pathSum(self, root: Optional[TreeNode], targetSum: int) -> int:
        cnt = defaultdict(int)
        cnt[0] = 1
        ans = 0

        def dfs(r, s):
            nonlocal ans
            if not r:
                return
            s += r.val
            ans += cnt[s - targetSum]
            cnt[s] += 1
            dfs(r.left, s)
            dfs(r.right, s)
            cnt[s] -= 1

        dfs(root, 0)
        return ans


def build(arr):
    if not arr:
        return None
    nodes = [TreeNode(v) if v != -1 else None for v in arr]
    q = deque([nodes[0]]) if nodes[0] else deque()
    idx = 1
    while q and idx < len(arr):
        cur = q.popleft()
        if idx < len(arr):
            cur.left = nodes[idx]
            if nodes[idx]:
                q.append(nodes[idx])
            idx += 1
        if idx < len(arr):
            cur.right = nodes[idx]
            if nodes[idx]:
                q.append(nodes[idx])
            idx += 1
    return nodes[0]


def main():
    n, t = map(int, input().split())
    a = list(map(int, input().split()))
    print(Solution().pathSum(build(a), t))


if __name__ == "__main__":
    main()
