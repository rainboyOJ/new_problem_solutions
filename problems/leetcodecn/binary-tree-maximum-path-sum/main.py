#!/usr/bin/env python3
from typing import Optional

class TreeNode:
    def __init__(self, x): self.val = x; self.left = self.right = None

class Solution:
    def maxPathSum(self, root: Optional[TreeNode]) -> int:
        ans = float('-inf')
        def dfs(r):
            nonlocal ans
            if not r: return 0
            l = max(0, dfs(r.left))
            rd = max(0, dfs(r.right))
            ans = max(ans, l + rd + r.val)
            return max(l, rd) + r.val
        dfs(root)
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
    print(Solution().maxPathSum(build(a)))
if __name__ == "__main__": main()
