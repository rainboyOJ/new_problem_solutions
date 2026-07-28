#!/usr/bin/env python3
class Solution:
    def isValid(self, s: str) -> bool:
        st=[]; mp={')':'(','}':'{',']':'['}
        for ch in s:
            if ch in mp.values(): st.append(ch)
            elif not st or st.pop()!=mp[ch]: return False
        return not st
def main():
    print(Solution().isValid(input().strip()))
if __name__=="__main__": main()
