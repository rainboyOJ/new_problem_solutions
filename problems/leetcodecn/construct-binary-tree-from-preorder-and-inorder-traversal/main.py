#!/usr/bin/env python3
from collections import deque
from typing import List, Optional


class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = self.right = None


class Solution:
    def buildTree(self, preorder: List[int], inorder: List[int]) -> Optional[TreeNode]:
        pos = {v: i for i, v in enumerate(inorder)}
        idx = 0

        def build(l, r):
            nonlocal idx
            if l > r:
                return None
            v = preorder[idx]
            idx += 1
            m = pos[v]
            root = TreeNode(v)
            root.left = build(l, m - 1)
            root.right = build(m + 1, r)
            return root

        return build(0, len(inorder) - 1)


def main():
    n = int(input())
    pre = list(map(int, input().split()))
    ino = list(map(int, input().split()))
    r = Solution().buildTree(pre, ino)
    q = deque([r])
    while q:
        cur = q.popleft()
        if not cur:
            print("-1", end=" ")
            continue
        print(cur.val, end=" ")
        q.append(cur.left)
        q.append(cur.right)


if __name__ == "__main__":
    main()
