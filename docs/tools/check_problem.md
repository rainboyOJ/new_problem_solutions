# check_problem.py

位置：

```text
scripts/problem-analysis-tools/check_problem.py
```

作用：检查单个题目目录是否符合当前电子书题目结构规范。

## 基本用法

```bash
python3 scripts/problem-analysis-tools/check_problem.py problems/luogu/P1001
```

## 检查内容

- 是否位于 `problems/<oj>/<problem_id>/`。
- Luogu 数字题目录是否使用规范的 `P` 前缀（例如 `problems/luogu/P1001/`）。
- 是否存在 `index.md`。
- 是否存在正式代码文件 `main.<ext>`，例如 `main.cpp`、`main.rs`、`main.hs`、`main.py`。
- 允许存在抓题生成的 `problem.md` 原题面归档。
- frontmatter 是否包含必要字段。
- frontmatter 是否包含 `description`；缺失为错误，存在但为空为警告。
- `index.md` 是否使用正式代码引用，例如 `@include-code(./main.cpp, cpp)` 或 `@include-code(./main.rs, haskell)`。
- `problem-analysis-workspace/` 或 `duipai-failed/` 是否有已被 Git 跟踪的文件。
- 是否存在旧结构残留，例如有 `1.cpp` 但没有正式代码 `main.<ext>`。

## 退出码

- `0`：没有错误。
- `1`：题目目录不符合规范。
