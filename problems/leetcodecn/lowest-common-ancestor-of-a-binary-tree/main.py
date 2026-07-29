#!/usr/bin/env python3
from collections import deque
from typing import Optional


class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = self.right = None


class Solution:
    def lowestCommonAncestor(
        self, root: TreeNode, p: TreeNode, q: TreeNode
    ) -> TreeNode:
        if not root or root is p or root is q:
            return root
        l = self.lowestCommonAncestor(root.left, p, q)
        r = self.lowestCommonAncestor(root.right, p, q)
        if l and r:
            return root
        return l or r


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
    n, pv, qv = map(int, input().split())
    a = list(map(int, input().split()))
    r = build(a)
    # find nodes
    st = [r]
    p = q = None
    while st:
        cur = st.pop()
        if not cur:
            continue
        if cur.val == pv:
            p = cur
        if cur.val == qv:
            q = cur
        st.append(cur.left)
        st.append(cur.right)
    print(Solution().lowestCommonAncestor(r, p, q).val)


if __name__ == "__main__":
    main()
