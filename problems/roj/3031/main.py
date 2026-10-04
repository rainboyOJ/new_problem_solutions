#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 11:26
# update_at: 2026-10-01 11:26

import sys

LIMIT = 20  # 评测数据只要求前 20 种出栈方案，凑满 20 个即可整树剪枝

# 显式递归帧的阶段编码（含义只在这里解释一次）：
#   0 = 刚进入该状态，还没走任何分支
#   1 = 「出栈」分支已经走完并回溯，接着走「进栈」分支
#   2 = 「进栈」分支已经走完并回溯，该状态整体结束
ENTER, AFTER_POP, AFTER_PUSH = 0, 1, 2


def first_sequences(n: int) -> list[str]:
    """按字典序产出前 LIMIT 个出栈序列。

    每个状态先走「出栈」再走「进栈」——先出栈能让出站序列在第一个分歧位上更小，
    所以 DFS 触达叶子的顺序天然就是字典序，不需要事后排序。
    n 最大 60000，递归深度可达 2n，因此这里用显式帧栈代替真递归。
    """
    found: list[str] = []                      # 已收集的出栈序列（凑够 LIMIT 个即停）
    seq: list[int] = []                        # 已出站的车厢编号
    stack: list[int] = []                      # 站内车厢（栈顶待出）
    frames: list[tuple[int, int]] = [(1, ENTER)]  # 帧 = (下一节待进站编号, 阶段)

    while frames and len(found) < LIMIT:
        next_in, phase = frames[-1]

        if phase == ENTER:
            if next_in > n and not stack:
                found.append(''.join(map(str, seq)))   # 叶子：n 节车厢全部出站
                frames.pop()
            elif stack:                                # 优先「出栈」，字典序更小
                frames[-1] = (next_in, AFTER_POP)
                seq.append(stack.pop())
                frames.append((next_in, ENTER))
            else:                                      # 栈空时只能「进站」
                frames[-1] = (next_in, AFTER_PUSH)
                stack.append(next_in)
                frames.append((next_in + 1, ENTER))
        elif phase == AFTER_POP:
            stack.append(seq.pop())                    # 回溯出栈：车厢回到栈顶
            if next_in <= n:                           # 再试「进站」分支
                frames[-1] = (next_in, AFTER_PUSH)
                stack.append(next_in)
                frames.append((next_in + 1, ENTER))
            else:
                frames.pop()
        else:
            stack.pop()                                # 回溯进站：车厢退回未进站状态
            frames.pop()

    return found


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    print('\n'.join(first_sequences(n)))


if __name__ == "__main__":
    solve()
