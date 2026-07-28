#!/usr/bin/env python3
from typing import List
class Solution:
    def rob(self, nums: List[int]) -> int:
        a=b=0
        for x in nums: a,b=b,max(b,a+x)
        return b
def main():
    n=int(input()); a=list(map(int,input().split()))
    print(Solution().rob(a))
if __name__=="__main__": main()
