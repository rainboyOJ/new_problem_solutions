#!/usr/bin/env python3
from typing import List
class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        mn, ans = float('inf'), 0
        for x in prices: mn = min(mn, x); ans = max(ans, x - mn)
        return ans
def main():
    n=int(input()); a=list(map(int,input().split()))
    print(Solution().maxProfit(a))
if __name__=="__main__": main()
