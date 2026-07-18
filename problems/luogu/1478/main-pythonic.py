import sys

def main():
    data = list(map(int, sys.stdin.buffer.read().split()))
    n, strength = data[0], data[1]
    chair, arm = data[2], data[3]
    reachable_height = chair + arm

    costs = []
    pos = 4
    for _ in range(n):
        height, cost = data[pos], data[pos + 1]
        pos += 2
        if height <= reachable_height:
            costs.append(cost)

    costs.sort()

    answer = 0
    for cost in costs:
        if strength < cost:
            break
        strength -= cost
        answer += 1

    print(answer)

if __name__ == "__main__":
    main()
