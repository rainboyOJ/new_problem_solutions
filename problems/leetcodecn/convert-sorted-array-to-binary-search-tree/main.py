#!/usr/bin/env python3
from typing import List, Optional
class TreeNode:
    def __init__(self, x): self.val = x; self.left = self.right = None

class Solution:
    def sortedArrayToBST(self, nums: List[int]) -> Optional[TreeNode]:
        def build(l, r):
            if l > r: return None
            m = (l + r) // 2
            return TreeNode(nums[m], build(l, m-1), build(m+1, r))
        return build(0, len(nums)-1)

def inorder(r):
    if not r: return []
    return inorder(r.left) + [r.val] + inorder(r.right)

def main():
    n = int(input()); a = list(map(int, input().split()))
    print(*inorder(Solution().sortedArrayToBST(a)))
if __name__ == "__main__": main()
