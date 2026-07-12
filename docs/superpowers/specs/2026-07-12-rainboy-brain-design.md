# rainboy-brain Skill Design

> Historical design snapshot. The canonical maintainer-facing document now lives at `/home/rainboy/mycode/rainboy-brain-skill/docs/design.md`.

## Context

The repository already separates OJ explanation work into focused skills:

- `oj-problem-analysis-writer` writes complete problem explanations.
- `oj-problem-analysis-reviewer` audits whether an existing explanation teaches the solution clearly.
- `oj-problem-format-spec` defines the final `index.md` structure.
- `oj-cpp-competitive-style` governs C++ changes.

These skills cover writing, review, formatting, and code style, but they do not isolate the step that turns a correct algorithm into a human-discoverable line of reasoning. Existing explanations can therefore name an algorithm or restate code without explaining which constraint suggests the method, where the real conceptual jump occurs, or why the decisive choice is correct.

`rainboy-brain` fills that gap. The name identifies a set of Rainboy's preferred reasoning and teaching habits. The skill does not impersonate Rainboy or claim Rainboy's personal experience.

## Goal

Create a conversational OJ reasoning skill that helps a student understand:

- what the problem is really asking them to notice;
- how a person can move naturally from the statement and constraints to the solution;
- which step is the true conceptual bottleneck;
- why the central observation or choice is correct;
- which broader contest-thinking or discrete-math idea is useful for transferring the insight.

The first version prioritizes correctness, evidence, identification of the real bottleneck, and justification of the key step. Polished prose and automatic trigger coverage are secondary.

## Non-Goals

- Do not write a complete problem explanation from scratch.
- Do not replace `oj-problem-analysis-writer` or `oj-problem-analysis-reviewer`.
- Do not generate, repair, or refactor solution code.
- Do not edit frontmatter or restructure a complete `index.md`.
- Do not force every problem into a fixed five-section response.
- Do not attach discrete-math terminology when it does not improve understanding.
- Do not simulate Rainboy's first-person voice or make biographical claims.
- Do not build separate, exhaustive workflows for every algorithm family in the first version.

## Primary Interaction Model

The first version is a conversational thinking coach. It should answer the user's actual question directly rather than always producing a report.

Typical requests include:

- "这题本质是什么？"
- "这个做法应该怎么想到？"
- "真正的关键观察是什么？"
- "这个贪心为什么正确？"
- "这里对应什么离散数学思想？"
- "不要翻译代码，把它讲成人脑的思考过程。"

The skill may make a focused edit to `index.md` only when the user explicitly asks it to write the explanation into the article.

## Architecture

The skill uses four conceptual layers. These are reasoning boundaries, not separate programs or required output headings.

### Evidence Layer

Collect and distinguish the available sources:

1. problem statement and constraints;
2. final solution code;
3. brute-force code, when present;
4. existing `index.md`;
5. `problem-analysis-workspace` notes, when present;
6. facts stated directly by the user.

The skill must distinguish problem facts, code behavior, existing explanation, and its own inference. A claimed essence, bottleneck, or proof must be traceable to these sources.

### Reasoning Layer

Reconstruct the solution as a discoverable path:

- identify the most direct correct approach;
- identify which constraint makes that approach insufficient or simplifies it;
- locate the observation that changes the model or complexity;
- separate conceptual difficulty from implementation detail;
- justify the decisive observation or choice.

The reasoning should not invent a sudden insight by reading the final algorithm backward. It should show a plausible transition from information visible in the problem.

### Abstraction Layer

Map the reasoning to a reusable idea only when the mapping helps the student recognize the pattern later. Examples include predicates, complements, multiplication rules, invariants, exchange arguments, necessity and sufficiency, monotonicity, dependency order, and contradiction.

This layer is optional. Plain language is the correct result when a formal term would add ceremony rather than understanding.

### Expression Layer

Render the verified reasoning in the form that matches the request:

- a direct conversational answer for a narrow question;
- a systematic analysis for a broad request;
- a concise paragraph suitable for an existing explanation;
- a focused `index.md` edit when explicitly requested.

## Reasoning Workflow

For each concrete problem, the skill follows this sequence:

1. **Identify the problem object.** Read the available problem materials. If the request is abstract, decide whether the supplied context supports a concrete conclusion.
2. **Build a fact summary.** State the goal, decisive constraints, actual behavior of the final solution, and the explanation already present.
3. **Recover the direct approach.** Explain the natural or naive method before discussing the optimized solution.
4. **Find the turning observation.** Identify the condition that lets the direct method be simplified, accelerated, or replaced.
5. **Locate the real bottleneck.** Name the part whose truth or discovery controls the solution, rather than merely naming the most complicated code.
6. **Verify the explanation.** Use the proof tool appropriate to the claim, such as a counterexample check, boundary analysis, exchange argument, induction, invariant, or necessary-and-sufficient reasoning.
7. **Abstract only when useful.** Add contest-thinking or discrete-math terminology only if it improves transfer.
8. **Adapt the response.** Answer at the shortest level that still resolves the user's question.

The skill must complete the evidence and verification steps internally even when the final response is short.

## Adaptive Output

### Direct Answer

Use for a narrow question. Lead with the conclusion, then give the shortest reasoning chain that supports it. Do not add unrelated headings.

### Systematic Analysis

Use when the user asks for a complete thinking model. The following headings are available, but a heading may be omitted when it has no useful content:

```markdown
## 一句话本质

## 人脑思考路径

## 关键卡点

## 离散数学 / 竞赛思维映射

## 可写入题解的文案
```

The terminology section must not be filled merely to complete the template. It may explicitly say that no additional terminology is needed when plain reasoning is clearer.

### Article Text

When the user asks for reusable wording but not a file edit, output a concise paragraph that can fit naturally inside `### 思路` or a closely related subsection. It should preserve the language level and terminology of the existing article.

## Focused Edit Mode

Focused edit mode is entered only after an explicit request to modify `index.md`.

Rules:

- Read the current article and solution code before editing.
- Change only `### 思路` or the explicitly named reasoning subsection.
- Preserve correct and useful existing teaching content.
- Keep the inserted text concise and consistent with the surrounding voice.
- Do not change code, frontmatter, article structure, unrelated wording, or relation metadata.
- Verify that the new explanation agrees with the code, claimed complexity, and surrounding text.
- If the requested result requires a complete rewrite, new brute-force code, or structural repair, stop the focused edit and direct that work to `oj-problem-analysis-writer`.

## Lightweight Algorithm Prompts

The first version uses one shared workflow with a small set of optional prompts. These prompts help investigation; they are not answer templates.

| Problem shape | Useful questions |
| --- | --- |
| Counting | Is direct counting overlapping? Is the complement independent or easier to classify? |
| Greedy | What decision becomes irreversible? Why can an alternative optimum be exchanged into this choice? |
| Dynamic programming | Which repeated decision needs memory? What information is sufficient to describe the future? |
| Graph | What do vertices and edges mean in the original problem? Which relation makes graph traversal or optimization valid? |
| Search | What is the complete choice sequence? Which pruning condition is necessary and provably safe? |
| Mathematics | Which equation, equivalence, divisibility condition, bound, or integrality constraint removes blind enumeration? |
| Simulation | What invariant or order dependency makes the process deterministic? Is a named abstraction actually necessary? |

The skill must not decide the explanation solely from an algorithm label. It uses these questions only after reading the evidence.

## Error Handling

### Missing Context

If the user asks for the essence of an unspecified problem, request the problem statement, directory, link, or relevant code. A generic framework may be offered, but it must not be presented as a conclusion about the missing problem.

### Conflicting Sources

If the statement, article, final code, or brute-force code disagree, identify the conflict before extracting a thinking model. Do not silently choose the source that makes the explanation easiest.

### Suspected Incorrect Solution

If the core algorithm appears incorrect or cannot be justified, report the uncertainty and the failing case or missing proof obligation. Do not produce polished teaching text that presents the claim as established.

### No Useful Formal Mapping

Explain the reasoning in plain language and omit the formal mapping. This is a valid outcome, not an analysis failure.

## Trigger Boundaries

The skill description should actively match requests about a problem's essence, discovery path, key observation, conceptual bottleneck, proof of a greedy or structural choice, human-thinking explanation, and useful discrete-math or contest-thinking mapping.

It should not activate by itself for requests limited to:

- writing a full explanation;
- generating or fixing code;
- formatting frontmatter;
- general article review;
- downloading a statement;
- committing, pushing, or deployment.

When a request combines reasoning analysis with a full article or code task, `rainboy-brain` owns only the reasoning analysis. The existing specialized skill owns the remaining work.

## Evaluation

The first version uses manual prompt evaluation rather than introducing a new evaluation framework.

### Representative Problems

- `problems/usaco/1515`: predicates, complement counting, and multiplication rule.
- `problems/usaco/1467`: dependency order and the justification for the greedy placement choice.
- `problems/luogu/8814`: algebraic transformation, discriminant or square constraints, and integer-solution conditions.

### Transfer Problems

Evaluate at least one dynamic-programming problem and one graph or search problem from the repository. The response must derive the model from constraints and a direct approach rather than replacing one algorithm label with another.

### Negative Cases

- The problem context is missing.
- The user only asks to repair code.
- A simple simulation does not benefit from discrete-math terminology.
- The article and final code disagree.
- The user asks one narrow question that does not justify a five-section report.
- The user requests an `index.md` change whose scope would become a complete rewrite.

### Rubric

Evaluate each response on:

1. correctness of the stated algorithm and problem interpretation;
2. grounding in the materials actually read;
3. identification of the real conceptual bottleneck;
4. justification of the central observation or choice;
5. whether a student could reproduce the reasoning path;
6. restraint in terminology and compliance with editing boundaries.

The first four criteria are hard gates. A response fails if any of them fails, regardless of prose quality. Record whether each failure comes from trigger selection, missing evidence, reasoning, proof, expression, or example bias so later revisions target the actual cause.

## Initial Implementation Scope

The initial implementation is a standalone skill rooted at:

```text
/home/rainboy/mycode/rainboy-brain-skill/
├── SKILL.md
└── evals/
    └── evals.json
```

The directory itself is the skill root; do not add another nested `rainboy-brain` directory. `SKILL.md` contains the workflow and examples, while `evals/evals.json` records the representative and negative manual evaluation prompts. The first version does not create per-algorithm reference files, automated graders, new repository scripts, or changes to the existing writer and reviewer skills.

The current examples for USACO 1515 and USACO 1467 may be reused as concise demonstrations, but they must illustrate the workflow rather than dominate it. Additional examples should be added only after evaluation reveals a specific reasoning gap.

## Success Criteria

The first version succeeds when it consistently:

- derives its explanation from real problem evidence;
- identifies why the solution can be discovered, not only what algorithm it uses;
- isolates and justifies the true conceptual bottleneck;
- answers narrow questions naturally and expands only when requested;
- uses formal terminology only when it improves transfer;
- produces concise, compatible article text when asked;
- stays within its focused edit boundary.
