#!/usr/bin/env python3
import sys
import random
from cyaron import IO, randint

def main():
    io = IO(input_file=sys.stdout, disable_output=True)
    
    # 随机选择一种模式以覆盖不同边界
    mode = randint(1, 6)
    
    if mode == 1:
        # 极小规模：T = 1
        n = randint(1, 5)
        t = 1
        io.input_writeln(n, t)
        for _ in range(n):
            l = randint(1, 2)
            r = randint(l, 3)
            io.input_writeln(l, r)
    elif mode == 2:
        # 单区间直接覆盖 [1, T]
        n = randint(1, 8)
        t = randint(2, 15)
        io.input_writeln(n, t)
        io.input_writeln(1, randint(t, t + 5))
        for _ in range(n - 1):
            l = randint(1, t + 2)
            r = randint(l, t + 5)
            io.input_writeln(l, r)
    elif mode == 3:
        # 确定无解：开头断档 (最小 l > 1)
        n = randint(1, 8)
        t = randint(2, 15)
        io.input_writeln(n, t)
        for _ in range(n):
            l = randint(2, t)
            r = randint(l, t + 5)
            io.input_writeln(l, r)
    elif mode == 4:
        # 确定无解：中间断档
        n = randint(2, 8)
        t = randint(5, 15)
        gap = randint(2, t - 1)
        io.input_writeln(n, t)
        # 所有区间要么在 gap 之前，要么在 gap 之后
        for _ in range(n):
            if randint(0, 1) == 0:
                l = randint(1, gap - 1)
                r = randint(l, gap - 1)
            else:
                l = randint(gap + 1, t + 2)
                r = randint(l, t + 5)
            io.input_writeln(l, r)
    elif mode == 5:
        # 构造多段紧密相连的可行覆盖链
        n = randint(3, 10)
        t = randint(5, 15)
        io.input_writeln(n, t)
        cur = 0
        segs = []
        while cur < t:
            l = randint(max(1, cur - 1), cur + 1)
            r = randint(cur + 1, cur + 4)
            segs.append((l, r))
            cur = r
        while len(segs) < n:
            l = randint(1, t + 2)
            r = randint(l, t + 5)
            segs.append((l, r))
        random.shuffle(segs)
        for l, r in segs[:n]:
            io.input_writeln(l, r)
    else:
        # 常规小规模随机测试
        n = randint(1, 10)
        t = randint(1, 15)
        io.input_writeln(n, t)
        for _ in range(n):
            l = randint(1, t + 2)
            r = randint(l, t + 5)
            io.input_writeln(l, r)

if __name__ == "__main__":
    main()
