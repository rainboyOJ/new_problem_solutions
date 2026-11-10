import sys
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)

# 对拍数据 N 在 1 到 10000 之间
n = randint(1, 10000)
io.input_writeln(n)
