import sys
from cyaron import IO, randint, choice

def generate():
    io = IO(input_file=sys.stdout, disable_output=True)

    t = randint(1, 3)
    io.input_writeln(f"1 {t}")

    for _ in range(t):
        n = randint(2, 6)
        m = randint(1, 8)
        io.input_writeln(f"{n} {m}")

        ops = ['T', 'F', 'U', '+', '-']
        for _ in range(m):
            op = choice(ops)
            if op in ['T', 'F', 'U']:
                i = randint(1, n)
                io.input_writeln(f"{op} {i}")
            else:
                i = randint(1, n)
                j = randint(1, n)
                io.input_writeln(f"{op} {i} {j}")

if __name__ == "__main__":
    generate()
