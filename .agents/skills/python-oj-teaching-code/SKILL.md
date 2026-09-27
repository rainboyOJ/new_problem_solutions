---
name: python-oj-teaching-code
description: >-
  Write self-contained Python 3.15 teaching solutions for OJ readers who know
  Python but need to understand the algorithm, accepting Python TLE/MLE. Use
  for requests such as Python 教学代码、用 Python 描述思想、允许 TLE、容易手写
  or 容易理解. The underlying algorithm must remain correct and suitable for an
  accepted C++ implementation. Do not use for ordinary submit-ready Python
  solutions, intentionally brute-force checkers, or C++-only requests.
---

# Python OJ Teaching Code

Create a self-contained executable explanation for readers who know common
Python syntax and containers but do not yet understand the algorithm. Prioritize
understanding over brevity or ease of handwriting; do not teach basic syntax.

## Correctness and complexity boundary

- The program must compute the exact answer, including boundaries and special
  cases.
- Choose an algorithm whose time and space complexity fit the stated limits in
  a normal C++ contest implementation.
- Python may exceed time or memory limits because of language and container
  overhead. Handle runtime hazards such as recursion depth separately; prefer
  iterative traversal when deep recursion cannot be made reliable.
- Do not replace the intended algorithm with exponential search, full
  enumeration, or a worse asymptotic algorithm merely because TLE/MLE is allowed.
- Analyze the actual Python operations, including slicing, copying, container
  operations, and repeated checks. Extra asymptotic work or storage is not a
  language constant.
- A reasonable C++ rewrite must preserve the same state model and transitions;
  it may replace Python containers with arrays, encode tuple states as integers,
  and reduce constant factors. Any precomputation needed to meet the intended
  complexity must also be present in the Python algorithm.

## Establish the solution

Read the statement, constraints, samples, and relevant files in the problem
directory. If a known-correct `main.cpp` or other reference solution exists,
use it to identify the invariant and complexity, then reorganize the idea for
clarity. Do not mechanically translate individual lines and do not modify the
reference solution.

When several algorithms qualify, choose the one with the clearest reasoning
and fewest bookkeeping rules. Follow the natural discovery path: start from a
key observation, invariant, or structure. Introduce brute force and its bottleneck
only when they help explain the final algorithm.

## Write the teaching program

Use Python 3.15. Produce a complete runnable program with input, output, and all
boundary handling.

- Begin with a concise module docstring explaining the key observation, why the
  chosen model follows, and how the algorithm works, without assuming the reader
  has read a separate solution. Briefly note relevant Python TLE/MLE risks.
- Explain the essential correctness argument where it helps: why a state retains
  enough information, why transitions neither miss nor double-count answers, or
  why a greedy choice is safe. Select what applies; do not require a full formal
  proof or a fixed explanation template. Use a small example when it clarifies
  a difficult step.
- Use ordinary functions with names that match the algorithmic concepts.
- Prefer tuples, lists, dictionaries, sets, sentinels, slicing, unpacking,
  `enumerate()`, and direct loops when they expose the idea.
- It is acceptable to replace packed integer states or fixed arrays with tuple
  keys and dictionaries when the number of logical states remains appropriate.
- Use one clear rule for boundaries when sentinels or padding can remove
  unrelated special cases.
- Keep important transitions expanded and use meaningful intermediate variables
  even when this takes more lines. Avoid complex classes, decorators,
  nested comprehensions, clever one-liners, and advanced syntax used only to
  shorten the file.
- Connect comments to the reasoning: what the state remembers, why a transition
  is valid, when an answer contribution becomes final, and why a non-obvious
  boundary is handled that way. Do not merely restate operations or repeat the
  opening explanation.

Use the filename requested by the user. If none is given, create
`main-teaching.py` in the problem directory. Do not overwrite an existing file
or modify `index.md` unless the user explicitly asks for that change.

## Verify

Run every provided sample. When a trusted C++ solution or brute-force program
is available, run fixed-seed random differential tests on small cases. If no
reference exists, write a temporary brute checker when it is short and useful;
otherwise report the unverified cases and remaining risk.

Verification must establish correctness, not performance. Do not claim that a
local match is an official accepted submission.

## Report

After creating the file, briefly report:

- the output path and central invariant;
- the algorithmic time and space complexity;
- sample and differential-test results;
- relevant Python TLE/MLE risks;
- which mechanical changes make the same algorithm practical in C++.

Default to creating only the teaching code and this concise report. Write or
revise a full problem explanation only when the user requests it.
