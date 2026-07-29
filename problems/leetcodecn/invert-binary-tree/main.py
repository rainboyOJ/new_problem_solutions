#!/usr/bin/env python3
from collections import deque
from typing import Optional


class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class Solution:
    def invertTree(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        if not root:
            return None
        root.left, root.right = root.right, root.left
        self.invertTree(root.left)
        self.invertTree(root.right)
        return root


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


def print_tree(r):
    if not r:
        return
    q = deque([r])
    while q:
        p = q.popleft()
        if not p:
            print("-1", end=" ")
            continue
        print(p.val, end=" ")
        q.append(p.left)
        q.append(p.right)


def main() -> None:
    n = int(input())
    a = list(map(int, input().split()))
    root = build(a)
    root = Solution().invertTree(root)
    print_tree(root)


if __name__ == "__main__":
    main()
