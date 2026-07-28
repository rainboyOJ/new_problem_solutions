#!/usr/bin/env python3
import bisect
from typing import List
class Solution:
    def lengthOfLIS(self, nums: List[int]) -> int:
        tails=[]
        for x in nums:
            i=bisect.bisect_left(tails,x)
            if i==len(tails): tails.append(x)
            else: tails[i]=x
        return len(tails)
def main():
    n=int(input()); a=list(map(int,input().split()))
    print(Solution().lengthOfLIS(a))
if __name__=="__main__": main()
