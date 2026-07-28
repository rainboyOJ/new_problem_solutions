#!/usr/bin/env python3
from typing import List
class Solution:
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        d=set(wordDict); n=len(s); dp=[False]*(n+1); dp[0]=True
        for i in range(1,n+1):
            for j in range(i):
                if dp[j] and s[j:i] in d: dp[i]=True; break
        return dp[n]
def main():
    s=input().strip(); m=int(input())
    d=[input().strip() for _ in range(m)]
    print(Solution().wordBreak(s,d))
if __name__=="__main__": main()
