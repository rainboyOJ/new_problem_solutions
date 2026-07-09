from __future__ import annotations

from html import unescape
import re

from .base import BaseFetcher, FetchError, FetchResult, ProblemData, Sample


def strip_tags(html: str) -> str:
    text = re.sub(r"<!--[\s\S]*?-->", "", html)
    text = re.sub(r"<br\s*/?>", "\n", text, flags=re.I)
    text = re.sub(r"</(p|div|section|ul|ol|li)>", "\n", text, flags=re.I)
    text = re.sub(r"<[^>]+>", "", text)
    text = unescape(text)
    lines = [re.sub(r"[ \t\r\f\v]+", " ", line).strip() for line in text.splitlines()]
    return "\n".join(line for line in lines if line).strip()


def inline_text(html: str) -> str:
    return re.sub(r"\s+", " ", strip_tags(html)).strip()


def extract_pre(html: str) -> str:
    match = re.search(r"<pre[^>]*>([\s\S]*?)</pre>", html, flags=re.I)
    if not match:
        return ""
    text = re.sub(r"<[^>]+>", "", match.group(1))
    return unescape(text).strip("\n")


def section_to_markdown(html: str) -> str:
    html = re.sub(
        r"<li[^>]*>([\s\S]*?)</li>",
        lambda match: "\n- " + inline_text(match.group(1)) + "\n",
        html,
        flags=re.I,
    )
    parts: list[str] = []
    pos = 0
    for match in re.finditer(r"<pre[^>]*>([\s\S]*?)</pre>", html, flags=re.I):
        before = strip_tags(html[pos:match.start()])
        if before:
            parts.append(before)
        code = re.sub(r"<[^>]+>", "", match.group(1))
        parts.append("```\n" + unescape(code).strip("\n") + "\n```")
        pos = match.end()
    after = strip_tags(html[pos:])
    if after:
        parts.append(after)
    return "\n\n".join(part for part in parts if part).strip()


def extract_tag_with_class(html: str, tag: str, class_name: str) -> str:
    start_re = re.compile(rf"<{tag}\b[^>]*class=[\"'][^\"']*\b{re.escape(class_name)}\b[^\"']*[\"'][^>]*>", re.I)
    start = start_re.search(html)
    if not start:
        return ""

    token_re = re.compile(rf"</?{tag}\b[^>]*>", re.I)
    depth = 1
    pos = start.end()
    for token in token_re.finditer(html, pos):
        if token.group(0).startswith("</"):
            depth -= 1
            if depth == 0:
                return html[pos:token.start()]
        else:
            depth += 1
    return ""


def parse_title(html: str) -> str:
    match = re.search(r"<title[^>]*>([\s\S]*?)</title>", html, flags=re.I)
    if not match:
        return ""
    return inline_text(match.group(1))


def parse_h3_sections(html: str) -> list[tuple[str, str]]:
    matches = list(re.finditer(r"<h3[^>]*>([\s\S]*?)</h3>", html, flags=re.I))
    sections: list[tuple[str, str]] = []
    for index, match in enumerate(matches):
        heading = inline_text(match.group(1))
        start = match.end()
        end = matches[index + 1].start() if index + 1 < len(matches) else len(html)
        sections.append((heading, html[start:end]))
    return sections


def sample_number(heading: str) -> int:
    match = re.search(r"(\d+)", heading)
    if match:
        return int(match.group(1))
    return 1


def is_input_sample(heading: str) -> bool:
    lower = heading.lower()
    return lower.startswith(("input example", "sample input")) or "入力例" in heading


def is_output_sample(heading: str) -> bool:
    lower = heading.lower()
    return lower.startswith(("output example", "sample output")) or "出力例" in heading


def is_solution_section(heading: str) -> bool:
    lower = heading.lower()
    return lower.startswith("example of ") or "での解答例" in heading


def normalized_section_title(heading: str) -> str:
    mapping = {
        "problem": "题目描述",
        "constraints": "约束",
        "input": "输入格式",
        "output": "输出格式",
        "notice": "说明",
        "notes": "说明",
        "references": "补充说明",
        "問題文": "题目描述",
        "制約": "约束",
        "入力": "输入格式",
        "出力": "输出格式",
        "注意": "说明",
        "補足": "补充说明",
    }
    return mapping.get(heading.strip().lower(), mapping.get(heading.strip(), heading.strip()))


class AtCoderFetcher(BaseFetcher):
    name = "atcoder"
    aliases = ("at",)
    site_prefixes = ("https://atcoder.jp", "http://atcoder.jp")

    def parse_url(self, url: str) -> tuple[str, str]:
        clean = url.split("?")[0].split("#")[0]
        match = re.search(r"/contests/([^/]+)/tasks/([^/]+)$", clean)
        if not match:
            raise FetchError(f"无法从 AtCoder URL 解析 contest/task：{url}")
        return self.name, f"{match.group(1)}/{match.group(2)}"

    def split_problem_id(self, problem_id: str) -> tuple[str, str | None]:
        if "/" in problem_id:
            contest, task = problem_id.split("/", 1)
            return task, contest
        return problem_id, None

    def problem_link(self, problem_id: str) -> str:
        task, contest = self.split_problem_id(problem_id)
        if contest:
            return f"https://atcoder.jp/contests/{contest}/tasks/{task}"
        return "https://atcoder.jp"

    def build_data_from_id(self, oj: str, problem_id: str) -> ProblemData:
        task, _contest = self.split_problem_id(problem_id)
        return ProblemData(
            oj=self.name,
            problem_id=task,
            problem_dir_id=task,
            source=self.problem_link(problem_id),
            title=task,
        )

    def fetch(self, oj: str, problem_id: str) -> FetchResult:
        task, contest = self.split_problem_id(problem_id)
        if not contest:
            raise FetchError("AtCoder 原站抓取需要使用题目 URL，或使用 problem_id 形如 contest/task。")

        source = self.problem_link(problem_id)
        html = self.http_get(source)
        data = self.parse_html(html, problem_id)
        data.source = source
        return FetchResult(data=data, fetched=True, warnings=list(data.warnings))

    def fetch_by_url(self, url: str) -> FetchResult:
        oj, problem_id = self.parse_url(url)
        result = self.fetch(oj, problem_id)
        result.data.source = url
        return result

    def parse_html(self, html: str, problem_id: str) -> ProblemData:
        task, _contest = self.split_problem_id(problem_id)
        lang_html = extract_tag_with_class(html, "span", "lang-en")
        if not lang_html:
            lang_html = extract_tag_with_class(html, "span", "lang-ja")
        if not lang_html:
            raise FetchError("未找到 AtCoder 题面语言块。")

        title = parse_title(html) or task
        sections = parse_h3_sections(lang_html)
        if not sections:
            raise FetchError("未能解析 AtCoder 题面小节。")
        samples = self.parse_samples(sections)
        statement_md = self.problem_statement_markdown(task, title, sections, samples)
        return ProblemData(
            oj=self.name,
            problem_id=task,
            problem_dir_id=task,
            source=self.problem_link(problem_id),
            title=title,
            statement_md=statement_md,
            samples=samples,
        )

    def parse_samples(self, sections: list[tuple[str, str]]) -> list[Sample]:
        inputs: dict[int, str] = {}
        outputs: dict[int, str] = {}
        for heading, content in sections:
            if is_input_sample(heading):
                inputs[sample_number(heading)] = extract_pre(content)
            elif is_output_sample(heading):
                outputs[sample_number(heading)] = extract_pre(content)

        samples: list[Sample] = []
        for index in sorted(set(inputs) | set(outputs)):
            samples.append(Sample(input=inputs.get(index, ""), output=outputs.get(index, "")))
        return samples

    def problem_statement_markdown(
        self,
        task: str,
        title: str,
        sections: list[tuple[str, str]],
        samples: list[Sample],
    ) -> str:
        parts = [f"# {task} {title}".strip()]
        sample_written = False
        for heading, content in sections:
            if is_solution_section(heading):
                break
            if is_input_sample(heading) or is_output_sample(heading):
                if not sample_written and samples:
                    parts.append(self.samples_markdown(samples))
                    sample_written = True
                continue
            body = section_to_markdown(content)
            if body:
                parts.append(f"## {normalized_section_title(heading)}\n\n{body}")
        return "\n\n".join(part.rstrip() for part in parts if part.strip()).rstrip() + "\n"

    def samples_markdown(self, samples: list[Sample]) -> str:
        parts: list[str] = []
        for index, sample in enumerate(samples, start=1):
            parts.append(
                "\n".join(
                    [
                        f"## 输入输出样例 #{index}",
                        "",
                        f"### 输入 #{index}",
                        "",
                        "```",
                        sample.input.rstrip(),
                        "```",
                        "",
                        f"### 输出 #{index}",
                        "",
                        "```",
                        sample.output.rstrip(),
                        "```",
                    ]
                )
            )
        return "\n\n".join(parts) + "\n"
