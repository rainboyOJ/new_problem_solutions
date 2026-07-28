#!/usr/bin/env python3
from typing import List
class Solution:
    def maxProduct(self, nums: List[int]) -> int:
        ans=mx=mn=nums[0]
        for x in nums[1:]:
            a=max(x,mx*x,mn*x); b=min(x,mx*x,mn*x); mx,mn=a,b
            ans=max(ans,mx)
        return ans
def main():
    n=int(input()); a=list(map(int,input().split()))
    print(Solution().maxProduct(a))
if __name__=="__main__": main()
