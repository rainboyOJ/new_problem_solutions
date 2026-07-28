#!/usr/bin/env python3
from typing import Optional
class TreeNode:
    def __init__(self, x): self.val = x; self.left = self.right = None

class Solution:
    def kthSmallest(self, root: Optional[TreeNode], k: int) -> int:
        st, cur = [], root
        while cur or st:
            while cur: st.append(cur); cur = cur.left
            cur = st.pop()
            k -= 1
            if k == 0: return cur.val
            cur = cur.right
        return -1

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
    n, k = map(int, input().split()); a = list(map(int, input().split()))
    print(Solution().kthSmallest(build(a), k))
if __name__ == "__main__": main()
