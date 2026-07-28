#!/usr/bin/env python3
from collections import deque
from typing import List, Optional

class TreeNode:
    def __init__(self, x): self.val = x; self.left = self.right = None

class Solution:
    def levelOrder(self, root: Optional[TreeNode]) -> List[List[int]]:
        if not root: return []
        ans, q = [], deque([root])
        while q:
            ans.append([])
            for _ in range(len(q)):
                cur = q.popleft()
                ans[-1].append(cur.val)
                if cur.left: q.append(cur.left)
                if cur.right: q.append(cur.right)
        return ans

def build(arr):
    if not arr: return None
    nodes = [TreeNode(v) if v != -1 else None for v in arr]
    q = [nodes[0]] if nodes[0] else []; idx = 1
    while q and idx < len(arr):
        cur = q.pop(0)
        if idx < len(arr): cur.left = nodes[idx]; (nodes[idx] and q.append(nodes[idx])); idx += 1
        if idx < len(arr): cur.right = nodes[idx]; (nodes[idx] and q.append(nodes[idx])); idx += 1
    return nodes[0]

def main():
    n = int(input()); a = list(map(int, input().split()))
    for row in Solution().levelOrder(build(a)): print(*row)
if __name__ == "__main__": main()
