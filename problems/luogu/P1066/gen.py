import sys
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)

# 随机生成 k 在 1 到 7 之间，w 在 2 到 35 之间
k = randint(1, 7)
w = randint(2, 35)

io.input_writeln(f"{k} {w}")
