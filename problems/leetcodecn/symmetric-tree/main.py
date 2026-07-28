#!/usr/bin/env python3
from typing import Optional


class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class Solution:
    def isSymmetric(self, root: Optional[TreeNode]) -> bool:
        def dfs(a, b):
            if not a and not b:
                return True
            if not a or not b:
                return False
            return a.val == b.val and dfs(a.left, b.right) and dfs(a.right, b.left)
        return dfs(root.left, root.right) if root else True


def build(arr):
    if not arr:
        return None
    nodes = [TreeNode(v) if v != -1 else None for v in arr]
    q = []
    root = nodes[0]
    if root:
        q.append(root)
    idx = 1
    while q and idx < len(arr):
        cur = q.pop(0)
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
    return root


def main() -> None:
    n = int(input())
    a = list(map(int, input().split()))
    root = build(a)
    print(Solution().isSymmetric(root))


if __name__ == "__main__":
    main()
