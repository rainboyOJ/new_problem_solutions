import sys


data = iter(map(int, sys.stdin.buffer.read().split()))
initial = 0
trigger = []
for knob in range(12):
    state = next(data) - 1
    initial |= state << (2 * knob)
    trigger.append(tuple(next(data) - 1 for _ in range(4)))


def change(state, knob, delta):
    shift = 2 * knob
    value = ((state >> shift) + delta) & 3
    return state & ~(3 << shift) | value << shift


def forward(state, knob):
    selected_state = state >> (2 * knob) & 3
    affected = trigger[knob][selected_state]
    return change(change(state, knob, 1), affected, 1)


def backward(state, knob):
    previous_selected = ((state >> (2 * knob)) - 1) & 3
    affected = trigger[knob][previous_selected]
    return change(change(state, knob, -1), affected, -1)


from_start = {initial: (-1, -1)}
to_goal = {0: (-1, -1)}
start_frontier = {initial}
goal_frontier = {0}
meeting = initial if initial == 0 else None

while meeting is None:
    if len(start_frontier) <= len(goal_frontier):
        next_frontier = set()
        for state in start_frontier:
            for knob in range(12):
                next_state = forward(state, knob)
                if next_state in from_start:
                    continue
                from_start[next_state] = state, knob
                next_frontier.add(next_state)
                if next_state in to_goal:
                    meeting = next_state
                    break
            if meeting is not None:
                break
        start_frontier = next_frontier
    else:
        next_frontier = set()
        for state in goal_frontier:
            for knob in range(12):
                previous_state = backward(state, knob)
                if previous_state in to_goal:
                    continue
                to_goal[previous_state] = state, knob
                next_frontier.add(previous_state)
                if previous_state in from_start:
                    meeting = previous_state
                    break
            if meeting is not None:
                break
        goal_frontier = next_frontier

answer = []
state = meeting
while from_start[state][0] != -1:
    state, knob = from_start[state]
    answer.append(knob + 1)
answer.reverse()
state = meeting
while to_goal[state][0] != -1:
    state, knob = to_goal[state]
    answer.append(knob + 1)

print(len(answer))
print(*answer)
