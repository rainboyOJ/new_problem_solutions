from __future__ import annotations

from html import unescape
import re
from urllib.parse import parse_qs, urlparse

from .atcoder import extract_tag_with_class, inline_text, section_to_markdown
from .base import BaseFetcher, FetchError, FetchResult, ProblemData, Sample


def extract_pre_text(html: str) -> str:
    text = re.sub(r"<[^>]+>", "", html)
    return unescape(text).replace("\r\n", "\n").replace("\r", "\n").strip("\n")


def parse_h2_texts(html: str) -> list[str]:
    return [
        inline_text(match.group(1))
        for match in re.finditer(r"<h2[^>]*>([\s\S]*?)</h2>", html, flags=re.I)
    ]


def problem_title_from_h2(html: str, problem_id: str) -> str:
    for heading in parse_h2_texts(html):
        match = re.search(r"\bProblem\s+\d+\.\s*(.+)$", heading, flags=re.I)
        if match:
            return match.group(1).strip()
    return problem_id


def contest_title_from_h2(html: str) -> str:
    for heading in parse_h2_texts(html):
        if heading.startswith("USACO ") and "Contest" in heading:
            return heading
    return ""


def div_with_class_pattern(class_name: str) -> re.Pattern[str]:
    return re.compile(
        r"<div\b[^>]*class=[\"'][^\"']*\b"
        + re.escape(class_name)
        + r"\b[^\"']*[\"'][^>]*>[\s\S]*?</div>",
        flags=re.I,
    )


def extract_div_class(html: str, class_name: str) -> str:
    match = div_with_class_pattern(class_name).search(html)
    if not match:
        return ""
    content = match.group(0)
    start = content.find(">")
    end = content.rfind("</div>")
    if start == -1 or end == -1:
        return ""
    return content[start + 1 : end]


def strip_first_h4(html: str) -> str:
    return re.sub(r"^\s*<h4[^>]*>[\s\S]*?</h4>", "", html, count=1, flags=re.I).strip()


def extract_h4_text(html: str) -> str:
    match = re.search(r"<h4[^>]*>([\s\S]*?)</h4>", html, flags=re.I)
    return inline_text(match.group(1)) if match else ""


def normalize_usaco_section_title(heading: str) -> str:
    lower = heading.strip().lower()
    if lower.startswith("scoring") or "测试点" in heading:
        return "测试点性质"
    if lower.startswith("input format") or "输入格式" in heading:
        return "输入格式"
    if lower.startswith("output format") or "输出格式" in heading:
        return "输出格式"
    return heading.strip() or "说明"


def has_cjk_text(html: str) -> bool:
    body = extract_tag_with_class(html, "div", "problem-text") or html
    text = inline_text(body)
    cjk_count = len(re.findall(r"[\u4e00-\u9fff]", text))
    return cjk_count >= 10 and ("输入" in text or "输出" in text)


def canonical_cpid(problem_id: str) -> str:
    match = re.fullmatch(r"(?:cpid)?(\d+)", str(problem_id).strip(), flags=re.I)
    if not match:
        raise FetchError(f"USACO 题号应为 cpid 数字，例如 1515：{problem_id}")
    return match.group(1)


class USACOFetcher(BaseFetcher):
    name = "usaco"
    aliases = ("usa",)
    site_prefixes = ("https://usaco.org", "http://usaco.org", "https://www.usaco.org", "http://www.usaco.org")

    def parse_url(self, url: str) -> tuple[str, str]:
        parsed = urlparse(url)
        query = parse_qs(parsed.query)
        cpid_values = query.get("cpid") or []
        if not cpid_values:
            raise FetchError(f"无法从 USACO URL 解析 cpid：{url}")
        return self.name, canonical_cpid(cpid_values[0])

    def problem_link(self, problem_id: str) -> str:
        cpid = canonical_cpid(problem_id)
        return f"https://usaco.org/index.php?page=viewproblem2&cpid={cpid}"

    def problem_link_with_lang(self, problem_id: str, lang: str) -> str:
        return f"{self.problem_link(problem_id)}&lang={lang}"

    def build_data_from_id(self, oj: str, problem_id: str) -> ProblemData:
        cpid = canonical_cpid(problem_id)
        return ProblemData(
            oj=self.name,
            problem_id=cpid,
            problem_dir_id=cpid,
            source=self.problem_link(cpid),
            title=cpid,
        )

    def fetch(self, oj: str, problem_id: str) -> FetchResult:
        cpid = canonical_cpid(problem_id)
        source = self.problem_link(cpid)
        english_html = self.http_get(source)
        selected_html = english_html
        selected_lang = "en"
        warnings: list[str] = []

        # USACO 页面实际下拉框常用 lang=zh；用户历史链接里也可能出现 zh-cn。
        # 两者都尝试，但只有检测到中文正文时才采用，避免把英文回退页误认为中文。
        for lang in ("zh-cn", "zh"):
            try:
                candidate = self.http_get(self.problem_link_with_lang(cpid, lang))
            except FetchError as exc:
                warnings.append(f"USACO {lang} 题面请求失败：{exc}")
                continue
            if has_cjk_text(candidate):
                selected_html = candidate
                selected_lang = lang
                break

        data = self.parse_html(selected_html, cpid)
        data.source = source
        if selected_lang == "en":
            warnings.append("未发现可用中文题面，已使用英文题面。")
        return FetchResult(data=data, fetched=True, warnings=list(dict.fromkeys(warnings + data.warnings)))

    def fetch_by_url(self, url: str) -> FetchResult:
        _oj, problem_id = self.parse_url(url)
        return self.fetch(self.name, problem_id)

    def parse_html(self, html: str, problem_id: str) -> ProblemData:
        cpid = canonical_cpid(problem_id)
        body = extract_tag_with_class(html, "div", "problem-text")
        if not body:
            raise FetchError("未找到 USACO 题面正文 .problem-text。")

        title = problem_title_from_h2(html, cpid)
        contest = contest_title_from_h2(html)
        samples = self.parse_samples(body)
        statement_md = self.problem_statement_markdown(cpid, title, contest, body, samples)
        return ProblemData(
            oj=self.name,
            problem_id=cpid,
            problem_dir_id=cpid,
            source=self.problem_link(cpid),
            title=title,
            statement_md=statement_md,
            samples=samples,
        )

    def parse_samples(self, body_html: str) -> list[Sample]:
        inputs = [
            extract_pre_text(match.group(1))
            for match in re.finditer(
                r"<pre\b[^>]*class=[\"'][^\"']*\bin\b[^\"']*[\"'][^>]*>([\s\S]*?)</pre>",
                body_html,
                flags=re.I,
            )
        ]
        outputs = [
            extract_pre_text(match.group(1))
            for match in re.finditer(
                r"<pre\b[^>]*class=[\"'][^\"']*\bout\b[^\"']*[\"'][^>]*>([\s\S]*?)</pre>",
                body_html,
                flags=re.I,
            )
        ]
        samples: list[Sample] = []
        for index in range(max(len(inputs), len(outputs))):
            samples.append(
                Sample(
                    input=inputs[index] if index < len(inputs) else "",
                    output=outputs[index] if index < len(outputs) else "",
                )
            )
        return samples

    def problem_statement_markdown(
        self,
        cpid: str,
        title: str,
        contest: str,
        body_html: str,
        samples: list[Sample],
    ) -> str:
        parts: list[str] = [f"# {cpid} {title}".strip()]
        if contest:
            parts.append(f"## 赛事信息\n\n{contest}")

        input_match = div_with_class_pattern("prob-in-spec").search(body_html)
        output_match = div_with_class_pattern("prob-out-spec").search(body_html)
        intro_end = input_match.start() if input_match else len(body_html)
        intro = section_to_markdown(body_html[:intro_end])
        if intro:
            parts.append(f"## 题目描述\n\n{intro}")

        input_html = extract_div_class(body_html, "prob-in-spec")
        input_body = section_to_markdown(strip_first_h4(input_html))
        if input_body:
            parts.append(f"## 输入格式\n\n{input_body}")

        output_html = extract_div_class(body_html, "prob-out-spec")
        output_body = section_to_markdown(strip_first_h4(output_html))
        if output_body:
            parts.append(f"## 输出格式\n\n{output_body}")

        if samples:
            parts.append(self.samples_markdown(samples))

        sample_out_matches = list(
            re.finditer(
                r"<pre\b[^>]*class=[\"'][^\"']*\bout\b[^\"']*[\"'][^>]*>[\s\S]*?</pre>",
                body_html,
                flags=re.I,
            )
        )
        first_problem_section = div_with_class_pattern("prob-section").search(body_html)
        if sample_out_matches:
            explanation_start = sample_out_matches[-1].end()
            explanation_end = first_problem_section.start() if first_problem_section else len(body_html)
            explanation = section_to_markdown(body_html[explanation_start:explanation_end])
            if explanation:
                parts.append(f"## 样例说明\n\n{explanation}")

        for match in div_with_class_pattern("prob-section").finditer(body_html):
            section_html = match.group(0)
            heading = extract_h4_text(section_html)
            body = section_to_markdown(strip_first_h4(extract_div_class(section_html, "prob-section")))
            if body:
                parts.append(f"## {normalize_usaco_section_title(heading)}\n\n{body}")

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
