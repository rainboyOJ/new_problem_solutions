def repeated(char, count):
    return char * count

def alternating(count):
    return "o*" * count

def build_states(depth):
    if depth == 4:
        tail = alternating(n - 4)
        states.append("oooo****--" + tail)
        states.append("ooo--***o*" + tail)
        states.append("ooo*o**--*" + tail)
        states.append("o--*o**oo*" + tail)
        states.append("o*o*o*--o*" + tail)
        states.append("--o*o*o*o*" + tail)
        return

    tail_count = n - depth
    states.append(repeated("o", depth) + repeated("*", depth) + "--" + alternating(tail_count))
    states.append(repeated("o", depth - 1) + "--" + repeated("*", depth - 1) + alternating(tail_count + 1))
    build_states(depth - 1)

n = int(input())
states = []
build_states(n)
print("\n".join(states))
