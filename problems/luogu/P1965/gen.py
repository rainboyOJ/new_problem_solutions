import sys
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)

# 暴力对拍规模控制在 k <= 4，保证单次暴力在毫秒级内完成
n = randint(2, 500)
m = randint(1, n - 1)
k = randint(1, 4)
x = randint(0, n - 1)

io.input_writeln(f"{n} {m} {k} {x}")
