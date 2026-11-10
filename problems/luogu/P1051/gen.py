import sys
from cyaron import IO, randint, String, choice

def generate():
    io = IO(input_file=sys.stdout, disable_output=True)

    n = randint(1, 20)
    io.input_writeln(n)

    for i in range(n):
        name = f"Stu{i}_{String.random(4, charset='abcdefghijklmnopqrstuvwxyz')}"
        score = randint(70, 100)
        class_score = randint(70, 100)
        is_cadre = choice(['Y', 'N'])
        is_west = choice(['Y', 'N'])
        papers = randint(0, 3)
        io.input_writeln(f"{name} {score} {class_score} {is_cadre} {is_west} {papers}")

if __name__ == "__main__":
    generate()
