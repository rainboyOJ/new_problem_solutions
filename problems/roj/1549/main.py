#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 17:36
# update_at: 2026-09-30 17:36

import sys


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    op_count, mod = int(next(data)), int(next(data))

    # 在线 ST 表：st[k][j] 表示以下标 j + 2^k - 1 结尾、长度 2^k 的区间的最大值。
    # 第 k 层只在序列够长（下标 >= 2^k - 1）后才存在，故存下标 = 位置 - 2^k + 1。
    st: list[list[int]] = [[]]
    out: list[str] = []
    size = 0        # 当前序列长度
    last_ans = 0    # 上一次询问的答案 a，还没询问过时为 0

    for _ in range(op_count):
        op = next(data)
        arg = int(next(data))

        if op == b'A':
            st[0].append((arg + last_ans) % mod)   # 长度 1 的区间就是新元素本身
            pos = size                             # 新元素的下标
            size += 1

            k = 1
            while (1 << k) <= size:                # 区间必须整体落在序列内
                if k == len(st):                   # 序列长度越过 2^k，新建一层
                    st.append([])
                half = 1 << (k - 1)
                # 前半段 [pos-2*half+1, pos-half] 与后半段 [pos-half+1, pos] 各取最大再合并
                st[k].append(max(st[k - 1][pos - 2 * half + 1], st[k - 1][pos - half + 1]))
                k += 1
        else:
            # 询问最后 L 个数：用首尾两段长 2^k <= L 的区间夹住 [size-L, size-1]
            k = arg.bit_length() - 1
            span = 1 << k
            tail = st[k][size - span]               # 以末尾结尾的 2^k 段
            head = st[k][size - arg]                # 从询问左端起的 2^k 段
            last_ans = max(tail, head)
            out.append(str(last_ans))

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
