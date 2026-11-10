import sys
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)

# 对拍 n 取值在 1 到 4 之间
n = randint(1, 4)
io.input_writeln(n)
