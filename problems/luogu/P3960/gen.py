import sys
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)

# 对拍小规模：n <= 5, m <= 5, q <= 15
n = randint(1, 5)
m = randint(1, 5)
q = randint(1, 15)
io.input_writeln(f"{n} {m} {q}")

for _ in range(q):
    x = randint(1, n)
    y = randint(1, m)
    io.input_writeln(f"{x} {y}")
