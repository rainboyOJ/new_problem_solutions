from __future__ import annotations

from html import unescape
import re

from .atcoder import extract_tag_with_class, inline_text, section_to_markdown
from .base import BaseFetcher, FetchError, FetchResult, ProblemData, Sample


def extract_heading_text(html: str) -> str:
    heading_html = extract_tag_with_class(html, "h1", "book-page-heading")
    return inline_text(heading_html)


def parse_h2_sections(html: str) -> list[tuple[str, str]]:
    matches = list(re.finditer(r"<h2[^>]*>([\s\S]*?)</h2>", html, flags=re.I))
    sections: list[tuple[str, str]] = []
    for index, match in enumerate(matches):
        heading = inline_text(match.group(1))
        start = match.end()
        end = matches[index + 1].start() if index + 1 < len(matches) else len(html)
        sections.append((heading, html[start:end]))
    return sections


def extract_pre_blocks(html: str) -> list[str]:
    blocks: list[str] = []
    for match in re.finditer(r"<pre[^>]*>([\s\S]*?)</pre>", html, flags=re.I):
        text = re.sub(r"<[^>]+>", "", match.group(1))
        blocks.append(unescape(text).strip("\n"))
    return blocks


def extract_sample_tables(html: str) -> list[str]:
    return re.findall(
        r"<table\b[^>]*class=[\"'][^\"']*\bsample\b[^\"']*[\"'][^>]*>([\s\S]*?)</table>",
        html,
        flags=re.I,
    )


def normalized_section_title(heading: str) -> str:
    mapping = {
        "input": "输入格式",
        "output": "输出格式",
        "interaction": "交互说明",
        "scoring": "计分方式",
        "explanation": "样例说明",
        "sample explanation": "样例说明",
        "notes": "说明",
        "note": "说明",
    }
    return mapping.get(heading.strip().lower(), heading.strip())


class KattisFetcher(BaseFetcher):
    name = "kattis"
    aliases = ("openkattis",)
    site_prefixes = ("https://open.kattis.com", "http://open.kattis.com")

    def parse_url(self, url: str) -> tuple[str, str]:
        clean = url.split("?")[0].split("#")[0].rstrip("/")
        match = re.search(r"/problems/([^/]+)$", clean)
        if not match:
            raise FetchError(f"无法从 Kattis URL 解析题号：{url}")
        return self.name, match.group(1)

    def problem_link(self, problem_id: str) -> str:
        return f"https://open.kattis.com/problems/{problem_id}"

    def build_data_from_id(self, oj: str, problem_id: str) -> ProblemData:
        return ProblemData(
            oj=self.name,
            problem_id=problem_id,
            problem_dir_id=problem_id,
            source=self.problem_link(problem_id),
            title=problem_id,
        )

    def fetch(self, oj: str, problem_id: str) -> FetchResult:
        data = self.build_data_from_id(oj, problem_id)
        html = self.http_get(data.source)
        fetched_data = self.parse_html(html, problem_id)
        fetched_data.source = data.source
        return FetchResult(data=fetched_data, fetched=True, warnings=list(fetched_data.warnings))

    def fetch_by_url(self, url: str) -> FetchResult:
        oj, problem_id = self.parse_url(url)
        result = self.fetch(oj, problem_id)
        result.data.source = url
        return result

    def parse_html(self, html: str, problem_id: str) -> ProblemData:
        body = extract_tag_with_class(html, "div", "problembody")
        if not body:
            raise FetchError("未找到 Kattis 题面正文 .problembody。")

        title = extract_heading_text(html) or problem_id
        samples = self.parse_samples(body)
        statement_md = self.problem_statement_markdown(problem_id, title, body, samples)
        return ProblemData(
            oj=self.name,
            problem_id=problem_id,
            problem_dir_id=problem_id,
            source=self.problem_link(problem_id),
            title=title,
            statement_md=statement_md,
            samples=samples,
        )

    def parse_samples(self, body_html: str) -> list[Sample]:
        samples: list[Sample] = []
        for table_html in extract_sample_tables(body_html):
            blocks = extract_pre_blocks(table_html)
            if len(blocks) >= 2:
                samples.append(Sample(input=blocks[0], output=blocks[1]))
        return samples

    def problem_statement_markdown(
        self,
        problem_id: str,
        title: str,
        body_html: str,
        samples: list[Sample],
    ) -> str:
        body_without_samples = re.sub(
            r"<table\b[^>]*class=[\"'][^\"']*\bsample\b[^\"']*[\"'][^>]*>[\s\S]*?</table>",
            "",
            body_html,
            flags=re.I,
        )

        sections = parse_h2_sections(body_without_samples)
        parts: list[str] = [f"# {problem_id} {title}".strip()]

        first_section_start = re.search(r"<h2\b", body_without_samples, flags=re.I)
        intro_html = body_without_samples[: first_section_start.start()] if first_section_start else body_without_samples
        intro = section_to_markdown(intro_html)
        if intro:
            parts.append(f"## 题目描述\n\n{intro}")

        for heading, content in sections:
            body = section_to_markdown(content)
            if body:
                parts.append(f"## {normalized_section_title(heading)}\n\n{body}")

        if samples:
            parts.append(self.samples_markdown(samples))

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
