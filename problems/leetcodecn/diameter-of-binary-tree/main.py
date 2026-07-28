#!/usr/bin/env python3
from typing import Optional


class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class Solution:
    def diameterOfBinaryTree(self, root: Optional[TreeNode]) -> int:
        ans = 0
        def dfs(r):
            nonlocal ans
            if not r:
                return 0
            l = dfs(r.left)
            rd = dfs(r.right)
            ans = max(ans, l + rd)
            return 1 + max(l, rd)
        dfs(root)
        return ans


def build(arr):
    if not arr:
        return None
    nodes = [TreeNode(v) if v != -1 else None for v in arr]
    q = [nodes[0]] if nodes[0] else []
    idx = 1
    while q and idx < len(arr):
        cur = q.pop(0)
        if idx < len(arr):
            cur.left = nodes[idx]
            if nodes[idx]: q.append(nodes[idx])
            idx += 1
        if idx < len(arr):
            cur.right = nodes[idx]
            if nodes[idx]: q.append(nodes[idx])
            idx += 1
    return nodes[0]


def main() -> None:
    n = int(input())
    a = list(map(int, input().split()))
    root = build(a)
    print(Solution().diameterOfBinaryTree(root))


if __name__ == "__main__":
    main()
