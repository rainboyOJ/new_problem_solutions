#!/usr/bin/env python3
class Solution:
    def decodeString(self, s: str) -> str:
        st,num=[],0; cur=""
        for ch in s:
            if ch.isdigit(): num=num*10+int(ch)
            elif ch=='[': st+=[cur,num]; cur=""; num=0
            elif ch==']': p,n=st.pop(),st.pop(); cur=n+cur*p
            else: cur+=ch
        return cur
def main():
    print(Solution().decodeString(input().strip()))
if __name__=="__main__": main()
