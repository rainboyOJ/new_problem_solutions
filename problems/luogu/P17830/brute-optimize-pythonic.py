import sys


def solve():
    # 一次读入再解包：第一个值 n 用不上（len(a) 就是），用 _ 丢掉；*a 吃掉剩下的全部
    _, m, *a = map(int, sys.stdin.buffer.read().split())
    n = len(a)

    # last[v]：点数 v 在序列里最后一次出现的位置（从左往右扫，最后赋的值就是最后一次）
    last = [0] * (m + 1)
    for i, v in enumerate(a):
        last[v] = i

    # 一局游戏 = 一条跳跃链 i -> last[a[i]] + 1 -> ...，链上的点数都留在桌面上。
    # 所以不需要「桌面」这个栈：走到哪张牌，就给它对应的点数记一次。
    ans = [0] * (m + 1)
    for s in range(n):                      # 第 s 局：从位置 s 开始
        i = s
        while i < n:                        # last[a[i]] + 1 > n 时链就断了，等价于 i >= n
            v = a[i]
            ans[v] += 1
            i = last[v] + 1

    print(*ans[1:])                         # 点数从 1 开始，ans[0] 不用


if __name__ == "__main__":
    solve()
