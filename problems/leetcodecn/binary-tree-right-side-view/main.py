#!/usr/bin/env python3
from collections import deque
from typing import List, Optional


class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = self.right = None


class Solution:
    def rightSideView(self, root: Optional[TreeNode]) -> List[int]:
        if not root:
            return []
        ans, q = [], deque([root])
        while q:
            for i in range(len(q)):
                cur = q.popleft()
                if i == 0:
                    ans.append(cur.val)
                if cur.right:
                    q.append(cur.right)
                if cur.left:
                    q.append(cur.left)
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
    n = int(input())
    a = list(map(int, input().split()))
    print(*Solution().rightSideView(build(a)))


if __name__ == "__main__":
    main()
