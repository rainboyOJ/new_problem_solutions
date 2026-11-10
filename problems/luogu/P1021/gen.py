import sys
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)

# 生成合法满足 N + K <= 9 的测试数据以保证暴力在 2s 内完成
n = randint(1, 5)
k = randint(1, min(5, 9 - n))

io.input_writeln(n, k)
