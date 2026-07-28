#!/usr/bin/env python3
from typing import List
class Solution:
    def findMin(self, nums: List[int]) -> int:
        l,r=0,len(nums)-1
        while l<r:
            m=(l+r)//2
            if nums[m]<nums[r]: r=m
            else: l=m+1
        return nums[l]
def main():
    n=int(input()); a=list(map(int,input().split()))
    print(Solution().findMin(a))
if __name__=="__main__": main()
