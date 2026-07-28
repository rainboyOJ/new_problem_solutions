#!/usr/bin/env python3
class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        last = {}
        l = ans = 0
        for r, ch in enumerate(s):
            if ch in last:
                l = max(l, last[ch] + 1)
            ans = max(ans, r - l + 1)
            last[ch] = r
        return ans


def main() -> None:
    s = input().strip()
    print(Solution().lengthOfLongestSubstring(s))


if __name__ == "__main__":
    main()
