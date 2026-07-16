import sys


def main():
    data = sys.stdin.buffer.read().split()
    n = int(data[0])
    words = data[1:n + 1]
    graph = [[] for _ in range(26)]
    indegree = [0] * 26
    outdegree = [0] * 26

    for word in words:
        start, end = word[0] - 97, word[-1] - 97
        graph[start].append(word)
        outdegree[start] += 1
        indegree[end] += 1
    for edges in graph:
        edges.sort(reverse=True)

    starts = []
    ends = []
    for letter in range(26):
        difference = outdegree[letter] - indegree[letter]
        if difference == 1:
            starts.append(letter)
        elif difference == -1:
            ends.append(letter)
        elif difference != 0:
            print("***")
            return

    if len(starts) == len(ends) == 1:
        start = starts[0]
    elif not starts and not ends:
        start = next(letter for letter in range(26) if outdegree[letter])
    else:
        print("***")
        return

    vertex_stack = [start]
    word_stack = []
    route = []
    while vertex_stack:
        node = vertex_stack[-1]
        if graph[node]:
            word = graph[node].pop()
            vertex_stack.append(word[-1] - 97)
            word_stack.append(word)
        else:
            vertex_stack.pop()
            if word_stack:
                route.append(word_stack.pop())

    if len(route) != n:
        print("***")
    else:
        sys.stdout.buffer.write(b".".join(reversed(route)))


if __name__ == "__main__":
    main()
