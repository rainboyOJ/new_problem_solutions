#!/usr/bin/env python3
from typing import List
class Solution:
    def partition(self, s: str) -> List[List[str]]:
        n=len(s)
        pal=[[False]*n for _ in range(n)]
        for i in range(n-1,-1,-1):
            for j in range(i,n):
                pal[i][j]=s[i]==s[j] and (j-i<2 or pal[i+1][j-1])
        ans,cur=[],[]
        def dfs(i):
            if i==n: ans.append(cur[:]); return
            for j in range(i,n):
                if pal[i][j]: cur.append(s[i:j+1]); dfs(j+1); cur.pop()
        dfs(0)
        return ans
def main():
    s=input().strip()
    for v in Solution().partition(s): print(*v)
if __name__=="__main__": main()
