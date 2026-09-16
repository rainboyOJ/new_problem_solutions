---
description: 创建或审查可信的小数据暴力解 brute.cpp，作为随机对拍的独立正确性基准
---
题目目录：优先用用户消息里给出的路径；消息里没给就用当前工作目录。

目标：创建或改进题目目录里的 `brute.cpp`，得到一份按题意定义直接求解、适合小数据对拍的可信基准程序。

先读：

- `.agents/skills/oj-cpp-competitive-style/SKILL.md`
- `.agents/skills/oj-problem-analysis-writer/references/brute-force.md`
- 题目目录内的 `problem.md`、已有 `brute.cpp`、`main.*`、`gen.py` 和 `problem-analysis-workspace/*.md`

只允许修改 `brute.cpp`。不要修改 `main.*`、`gen.py`、`index.md` 或题面。已有 `brute.cpp` 优先审查和保留；只有它不完整、不可信、输入输出不匹配或并非真正的独立暴力时才修改。

要求：

1. 严格按题目定义实现最直接的枚举、模拟或朴素算法，正确性和可人工核验性优先，不追求满分数据效率。
2. 不复制 `main.*` 的关键优化、状态压缩或数据结构，避免暴力与正解共享同一个错误。可以读取 `main.*` 核对输入输出，但不能把它当作正确性依据。
3. 输入输出格式必须和题目及 `main.*` 完全一致，包括多测、精度、空格和换行。
4. 明确说明暴力能承受的数据规模及复杂度。适合选择序列时，按 C++ 竞赛风格 skill 的 01 序列 / 选择序列写法实现。
5. 新建 C++ 文件必须使用仓库规定的信息头和 C++17 风格；不用 lambda、structured binding 或复杂模板。
6. 用样例和人工可计算的最小边界验证结果。若已有 `gen.py`，把对拍报告和失败数据写入 `/tmp` 后做短轮次自检；没有生成器时如实报告，不能声称已对拍通过。

完成后报告：是否新建或修改了 `brute.cpp`、朴素算法、复杂度、可承受规模、验证命令和未验证项。
