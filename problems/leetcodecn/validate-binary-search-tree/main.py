#!/usr/bin/env python3
from typing import Optional

class TreeNode:
    def __init__(self, x): self.val = x; self.left = self.right = None

class Solution:
    def isValidBST(self, root: Optional[TreeNode]) -> bool:
        def dfs(r, lo, hi):
            if not r: return True
            if r.val <= lo or r.val >= hi: return False
            return dfs(r.left, lo, r.val) and dfs(r.right, r.val, hi)
        return dfs(root, float('-inf'), float('inf'))

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
    print(Solution().isValidBST(build(a)))
if __name__ == "__main__": main()
