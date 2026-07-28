#!/usr/bin/env python3
from typing import List
from collections import defaultdict


class Solution:
    def groupAnagrams(self, strs: List[str]) -> List[List[str]]:
        groups = defaultdict(list)
        for s in strs:
            key = "".join(sorted(s))
            groups[key].append(s)
        return list(groups.values())


def main() -> None:
    n = int(input())
    strs = input().split()
    assert len(strs) == n
    ans = Solution().groupAnagrams(strs)
    for g in ans:
        print(" ".join(g))


if __name__ == "__main__":
    main()
