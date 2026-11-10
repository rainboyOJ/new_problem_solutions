import sys
from cyaron import IO, randint, Vector

io = IO(input_file=sys.stdout, disable_output=True)

# 控制对拍规模：n 在 3 到 8 之间（brute 为 (n-1)! 阶乘级枚举）
n = randint(3, 8)
# 生成单调不降的正整数数组，元素在 1 到 40 之间
arr = Vector.random(n, [1, 40])
arr.sort()

io.input_writeln(n)
io.input_writeln(" ".join(map(str, arr)))
