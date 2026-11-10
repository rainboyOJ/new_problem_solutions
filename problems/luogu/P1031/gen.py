import sys
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)

# n 在 1 到 100 之间
n = randint(1, 100)
# 随机指定一个平均值
avg = randint(1, 1000)

# 生成 n-1 个随机偏差，最后一个偏差用于保证总和为 0
diffs = [randint(-500, 500) for _ in range(n - 1)]
diffs.append(-sum(diffs))

# 将偏差加到平均值上，并确保每个 a_i >= 1
min_val = min(avg + d for d in diffs)
if min_val < 1:
    offset = 1 - min_val
    avg += offset

a = [avg + d for d in diffs]

io.input_writeln(n)
io.input_writeln(" ".join(map(str, a)))
