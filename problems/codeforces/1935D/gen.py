import sys
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)
t = randint(1, 5)
io.input_writeln(t)

for _ in range(t):
    c = randint(1, 60)
    max_n = min(c + 1, 12)
    n = randint(1, max_n)
    io.input_writeln(f"{n} {c}")

    all_vals = list(range(c + 1))
    import random
    selected = sorted(random.sample(all_vals, n))
    io.input_writeln(" ".join(map(str, selected)))
