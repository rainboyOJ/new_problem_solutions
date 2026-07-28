#!/usr/bin/env python3
from typing import Optional


class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class Solution:
    def maxDepth(self, root: Optional[TreeNode]) -> int:
        if not root:
            return 0
        return 1 + max(self.maxDepth(root.left), self.maxDepth(root.right))


def build(arr):
    if not arr:
        return None
    nodes = [TreeNode(v) if v != -1 else None for v in arr]
    for i in range(len(nodes)):
        if nodes[i] is None:
            continue
        l, r = 2 * i + 1, 2 * i + 2
        if l < len(nodes):
            nodes[i].left = nodes[l]
        if r < len(nodes):
            nodes[i].right = nodes[r]
    return nodes[0]


def main() -> None:
    n = int(input())
    a = list(map(int, input().split()))
    root = build(a)
    print(Solution().maxDepth(root))


if __name__ == "__main__":
    main()
