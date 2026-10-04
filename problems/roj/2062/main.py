#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 05:45
# update_at: 2026-10-01 05:45

import sys

# 设置递归上限以支持 R <= 1023 深度递归
sys.setrecursionlimit(2000)


def can_fulfill(mid: int, boards: list[int], req: list[int], pref_req: list[int], total_board: int) -> bool:
    """判定是否能用现有木料切出最小的 mid 根需求木料。"""
    if mid == 0:
        return True
    if pref_req[mid] > total_board:
        return False

    b = sorted(boards)
    min_req = req[0]
    total_waste = 0
    max_waste = total_board - pref_req[mid]

    def dfs(idx: int, start_board: int) -> bool:
        nonlocal total_waste
        if idx < 0:
            return True

        curr_req = req[idx]
        for i in range(start_board, len(b)):
            if b[i] >= curr_req:
                b[i] -= curr_req
                waste_added = b[i] if b[i] < min_req else 0
                total_waste += waste_added

                if total_waste <= max_waste:
                    nxt_start = i if idx > 0 and req[idx - 1] == curr_req else 0
                    if dfs(idx - 1, nxt_start):
                        return True

                total_waste -= waste_added
                b[i] += curr_req

                # 对称性剪枝：如果当前木板还原后剩余与上一根相同，没必要再试同样的剩余
                if b[i] == curr_req:  # 刚好用完这根木板，后续木板不可能更好
                    break
        return False

    return dfs(mid - 1, 0)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data, None)
    if n is None:
        return

    boards = [next(data) for _ in range(n)]
    r = next(data)
    req = sorted(next(data) for _ in range(r))

    total_board = sum(boards)
    pref_req = [0] * (r + 1)
    for i in range(r):
        pref_req[i + 1] = pref_req[i] + req[i]

    low, high, ans = 0, r, 0
    while low <= high:
        mid = (low + high) // 2
        if can_fulfill(mid, boards, req, pref_req, total_board):
            ans = mid
            low = mid + 1
        else:
            high = mid - 1

    print(ans)


if __name__ == "__main__":
    solve()
