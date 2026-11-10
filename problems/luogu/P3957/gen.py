import sys
from cyaron import IO, randint

def generate():
    io = IO(input_file=sys.stdout, disable_output=True)

    n = randint(3, 15)
    d = randint(2, 6)
    k = randint(1, 30)

    io.input_writeln(f"{n} {d} {k}")

    cur_x = 0
    for _ in range(n):
        cur_x += randint(1, 5)
        score = randint(-5, 10)
        io.input_writeln(f"{cur_x} {score}")

if __name__ == "__main__":
    generate()
