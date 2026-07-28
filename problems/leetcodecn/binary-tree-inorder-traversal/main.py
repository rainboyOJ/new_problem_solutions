#!/usr/bin/env python3
from typing import List, Optional


class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class Solution:
    def inorderTraversal(self, root: Optional[TreeNode]) -> List[int]:
        ans, stack = [], []
        cur = root
        while cur or stack:
            while cur:
                stack.append(cur)
                cur = cur.left
            cur = stack.pop()
            ans.append(cur.val)
            cur = cur.right
        return ans


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
    print(*Solution().inorderTraversal(root))


if __name__ == "__main__":
    main()
