#!/usr/bin/env python3
from typing import List
class Solution:
    def searchRange(self, nums: List[int], target: int) -> List[int]:
        def bs(lo,hi,left):
            while lo<=hi:
                m=(lo+hi)//2
                if nums[m]>target or (left and nums[m]==target)): hi=m-1
                else: lo=m+1
            return lo
        n=len(nums)
        l=bs(0,n-1,True)
        if l==n or nums[l]!=target: return [-1,-1]
        return [l,bs(0,n-1,False)-1]
def main():
    n,t=map(int,input().split()); a=list(map(int,input().split()))
    print(*Solution().searchRange(a,t))
if __name__=="__main__": main()
