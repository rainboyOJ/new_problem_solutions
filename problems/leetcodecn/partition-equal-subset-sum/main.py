#!/usr/bin/env python3
from typing import List
class Solution:
    def canPartition(self, nums: List[int]) -> bool:
        s=sum(nums)
        if s&1: return False
        target=s//2; dp=[False]*(target+1); dp[0]=True
        for x in nums:
            for i in range(target,x-1,-1):
                dp[i]=dp[i] or dp[i-x]
        return dp[target]
def main():
    n=int(input()); a=list(map(int,input().split()))
    print(Solution().canPartition(a))
if __name__=="__main__": main()
