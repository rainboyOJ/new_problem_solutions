import sys
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)

# 暴力对拍规模：T <= 50, x <= 1500
t = randint(1, 30)
io.input_writeln(t)

for _ in range(t):
    x = randint(1, 1500)
    io.input_writeln(x)
