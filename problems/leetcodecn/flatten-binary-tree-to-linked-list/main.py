#!/usr/bin/env python3
from typing import Optional

class TreeNode:
    def __init__(self, x): self.val = x; self.left = self.right = None

class Solution:
    def flatten(self, root: Optional[TreeNode]) -> None:
        prev = None
        def dfs(r):
            nonlocal prev
            if not r: return
            dfs(r.right); dfs(r.left)
            r.right = prev; r.left = None
            prev = r
        dfs(root)

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
    r = build(a); Solution().flatten(r)
    while r: print(r.val, end=" "); r = r.right
if __name__ == "__main__": main()
