# 语言/语法学习题

当用户明确要学习 Haskell、Rust、Python、JavaScript 等语言/语法，且题目只是输入输出、算术或直接模拟，没有值得讲的算法瓶颈，同时暴力只会复制最终行为时，按语言学习文章处理。通常采用直接正解布局，使用真实的最终源文件；不要创建、更新或要求 `brute.cpp`、`gen.py`，也不要伪造“朴素解”。

过程文档的重点改为：

- `02-observation-and-model.md` 记录语言目标，并评估是否需要小表、Mermaid 或 ASCII 解释类型流；
- `03-solution-derivation.md` 解释语法如何映射到代码，而不是暴力瓶颈；
- `04-correctness-and-edge-cases.md` 记录样例/手工运行和语法边界，而不是无意义对拍；
- `05-complexity-and-implementation.md` 解释表达式、类型流、优先级、输入输出习惯和最终代码对应关系。

正文应说明语言构造、表达式优先级、类型流和小例子，再连接回最终代码。例如 Haskell 可讲 `<$>`、`.`、`words`、`map read`；代码引用使用实际文件和语言标签，如 `@include-code(./main.rs, haskell)`。Haskell 文件需要 Rainboy 标准头时，使用 `python3 scripts/problem-analysis-tools/cpp_header.py --style haskell <path>` 更新；不要因扩展名异常而改写文件含义。标签应同时反映题目形态和学习目标，例如 `模拟`、`haskell`。
