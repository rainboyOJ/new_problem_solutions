#!/usr/bin/env python3
from typing import List


class Solution:
    def solveNQueens(self, n: int) -> List[List[str]]:
        ans, board = [], ["." * n for _ in range(n)]
        col, d1, d2 = [0] * n, [0] * (2 * n - 1), [0] * (2 * n - 1)

        def dfs(r):
            if r == n:
                ans.append(board[:])
                return
            for c in range(n):
                if col[c] or d1[r + c] or d2[r - c + n - 1]:
                    continue
                col[c] = d1[r + c] = d2[r - c + n - 1] = 1
                lst = list(board[r])
                lst[c] = "Q"
                board[r] = "".join(lst)
                dfs(r + 1)
                lst[c] = "."
                board[r] = "".join(lst)
                col[c] = d1[r + c] = d2[r - c + n - 1] = 0

        dfs(0)
        return ans


def main():
    n = int(input())
    for v in Solution().solveNQueens(n):
        for s in v:
            print(s)
        print()


if __name__ == "__main__":
    main()
