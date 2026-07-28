#!/usr/bin/env python3
class Solution:
    def longestCommonSubsequence(self, a: str, b: str) -> int:
        m,n=len(a),len(b); dp=[0]*(n+1)
        for i in range(1,m+1):
            prev=0
            for j in range(1,n+1):
                tmp=dp[j]
                if a[i-1]==b[j-1]: dp[j]=prev+1
                else: dp[j]=max(dp[j],dp[j-1])
                prev=tmp
        return dp[n]
def main():
    a=input().strip(); b=input().strip()
    print(Solution().longestCommonSubsequence(a,b))
if __name__=="__main__": main()
