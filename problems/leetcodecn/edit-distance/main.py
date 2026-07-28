#!/usr/bin/env python3
class Solution:
    def minDistance(self, word1: str, word2: str) -> int:
        m,n=len(word1),len(word2)
        dp=list(range(n+1))
        for i in range(1,m+1):
            prev=dp[0]; dp[0]=i
            for j in range(1,n+1):
                tmp=dp[j]
                if word1[i-1]==word2[j-1]: dp[j]=prev
                else: dp[j]=1+min(dp[j],dp[j-1],prev)
                prev=tmp
        return dp[n]
def main():
    a=input().strip(); b=input().strip()
    print(Solution().minDistance(a,b))
if __name__=="__main__": main()
