import sys
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)
n = randint(1, 14)
m = randint(2, 200)
io.input_writeln(f"{n} {m}")

a = [randint(1, 1000) for _ in range(n)]
io.input_writeln(" ".join(map(str, a)))
