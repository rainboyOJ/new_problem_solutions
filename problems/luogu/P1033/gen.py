import sys
from cyaron import IO, randint

def generate():
    io = IO(input_file=sys.stdout, disable_output=True)

    H = randint(2, 50)
    K = randint(1, H)
    S1 = randint(1, 100)
    V = randint(1, 20)
    L = randint(1, 20)
    n = randint(1, 100)

    io.input_writeln(f"{float(H)} {float(S1)} {float(V)} {float(L)} {float(K)} {n}")

if __name__ == "__main__":
    generate()
