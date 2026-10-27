import sys

from cyaron import IO, randint

# 生成器没有输入，stdout 就是一组测试数据。
# 前四种小规模用来和暴力对拍，最后一种用来测边界。
io = IO(input_file=sys.stdout, disable_output=True)

kind = randint(1, 5)

if kind == 1:
    n = randint(1, 6)
    q = randint(1, 8)
    vmax = 3
elif kind == 2:
    n = randint(1, 30)
    q = randint(1, 40)
    vmax = 10
elif kind == 3:
    n = randint(1, 200)
    q = randint(1, 200)
    vmax = 1000
elif kind == 4:
    # 大量 0 与正数混杂：t 正好落在若干 0 之后的情况最容易写错。
    n = randint(1, 40)
    q = randint(1, 40)
    vmax = 5
else:
    n = randint(1, 2000)
    q = randint(1, 2000)
    vmax = 10**9

if kind == 4:
    a = [0 if randint(0, 2) else randint(1, vmax) for _ in range(n)]
else:
    a = [randint(0, vmax) for _ in range(n)]

io.input_writeln(n, q)
io.input_writeln(" ".join(map(str, a)))

total = sum(a)

for _ in range(q):
    op = randint(1, 3)
    if op == 1:
        i = randint(1, n)
        x = 0 if (kind == 4 and randint(0, 2)) else randint(0, vmax)
        a[i - 1] = x
        total = sum(a)
        io.input_writeln(1, i, x)
    elif op == 2:
        l = randint(1, n)
        # 一半把 t 设成可能达到的范围，一半设成必定越界，覆盖“不存在”。
        if randint(0, 1):
            t = randint(1, max(1, total + 3))
        else:
            t = randint(1, max(1, total // 2))
        if kind == 2:
            t = 10**15
        io.input_writeln(2, l, t)
    else:
        r = randint(1, n)
        if randint(0, 1):
            t = randint(1, max(1, total + 3))
        else:
            t = randint(1, max(1, total // 2))
        if kind == 2:
            t = 10**15
        io.input_writeln(3, r, t)
