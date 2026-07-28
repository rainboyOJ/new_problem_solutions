#!/usr/bin/env python3
from typing import List
class Solution:
    def dailyTemperatures(self, temps: List[int]) -> List[int]:
        n=len(temps); ans=[0]*n; st=[]
        for i in range(n):
            while st and temps[st[-1]]<temps[i]:
                ans[st.pop()]=i-st[-1]
            st.append(i)
        return ans
def main():
    n=int(input()); a=list(map(int,input().split()))
    print(*Solution().dailyTemperatures(a))
if __name__=="__main__": main()
