#!/usr/bin/env python3
from typing import List


class Solution:
    def partitionLabels(self, s: str) -> List[int]:
        last = {ch: i for i, ch in enumerate(s)}
        ans = []
        start = end = 0
        for i, ch in enumerate(s):
            end = max(end, last[ch])
            if i == end:
                ans.append(end - start + 1)
                start = i + 1
        return ans


def main():
    s = input().strip()
    print(*Solution().partitionLabels(s))


if __name__ == "__main__":
    main()
