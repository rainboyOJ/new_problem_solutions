import sys
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)

# 控制对拍数据在 n in [1, 3] 保证两份代码在数毫秒内跑出
n = randint(1, 3)
io.input_writeln(n)
