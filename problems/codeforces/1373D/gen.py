import sys
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)

# 生成 1 到 5 组测试数据
t = randint(1, 5)
io.input_writeln(t)

for _ in range(t):
    n = randint(1, 50)
    io.input_writeln(n)
    if randint(1, 2) == 1:
        low, high = 1, 20
    else:
        low, high = 1, 10**9
    nums = [randint(low, high) for _ in range(n)]
    io.input_writeln(nums)
