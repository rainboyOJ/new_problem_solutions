from __future__ import annotations

import os
from pathlib import Path
import re

from .base import BaseFetcher, FetchError, FetchResult, ProblemData, Sample, normalize_space

# AcWing 需要登录才能查看题面。Cookie 通过以下两种方式提供（按优先级）：
#   1. 环境变量 ACWING_COOKIE
#   2. 文件 ~/.acwing_cookie（内容为 Cookie 请求头原文）
ACWING_COOKIE_ENV = "ACWING_COOKIE"
ACWING_COOKIE_FILE = "~/.acwing_cookie"


def load_acwing_cookie() -> str:
    cookie = os.environ.get(ACWING_COOKIE_ENV, "").strip()
    if cookie:
        return cookie
    path = Path(ACWING_COOKIE_FILE).expanduser()
    if path.exists():
        cookie = path.read_text(encoding="utf-8").strip()
        # 文件里可能带着 "Cookie: " 前缀，剥掉
        if cookie.lower().startswith("cookie:"):
            cookie = cookie[len("cookie:"):].strip()
    return cookie


class AcWingFetcher(BaseFetcher):
    name = "acwing"
    aliases = ("ac",)
    site_prefixes = ("https://www.acwing.com", "https://acwing.com")

    def problem_link(self, problem_id: str) -> str:
        return f"https://www.acwing.com/problem/content/{problem_id}/"

    def parse_url(self, url: str) -> tuple[str, str]:
        clean = url.split("?")[0].split("#")[0]
        # 题面页形态：/problem/content/<id>/  或  /problem/content/<id>
        match = re.search(r"/problem/content/(\d+)/?$", clean)
        if not match:
            raise FetchError(f"无法从 AcWing URL 解析题号：{url}")
        return self.name, match.group(1)

    def normalize_id(self, problem_id: str) -> str:
        problem_id = problem_id.strip()
        if not problem_id or not problem_id.isdigit():
            raise FetchError(f"无效的 AcWing 题号：{problem_id}")
        return problem_id

    def build_data_from_id(self, oj: str, problem_id: str) -> ProblemData:
        problem_id = self.normalize_id(problem_id)
        return ProblemData(
            oj=self.name,
            problem_id=problem_id,
            problem_dir_id=problem_id,
            source=self.problem_link(problem_id),
            title=problem_id,
        )

    def fetch(self, oj: str, problem_id: str) -> FetchResult:
        data = self.build_data_from_id(oj, problem_id)
        cookie = load_acwing_cookie()
        headers = {"Cookie": cookie} if cookie else None

        html = self.http_get(data.source, headers=headers)

        # 匿名访问会被重定向到登录页（含 login-form / 登录 字样）
        if self._is_login_page(html):
            message = "AcWing 需要登录才能抓取题面"
            if not cookie:
                message += "：请设置环境变量 ACWING_COOKIE 或 ~/.acwing_cookie 文件"
            raise FetchError(message)

        try:
            fetched = self.parse_html(html, problem_id)
        except FetchError as exc:
            raise FetchError(f"AcWing 题面解析失败：{exc}") from exc
        fetched.source = data.source
        return FetchResult(data=fetched, fetched=True, warnings=list(fetched.warnings))

    def fetch_by_url(self, url: str) -> FetchResult:
        oj, problem_id = self.parse_url(url)
        result = self.fetch(oj, problem_id)
        result.data.source = url
        return result

    @staticmethod
    def _is_login_page(html: str) -> bool:
        # 登录页特征：出现登录表单，且没有题目正文容器
        has_login_form = "login-form" in html or "登录" in html[:4000]
        has_content = "problem-content" in html or "题目描述" in html
        return has_login_form and not has_content

    def parse_html(self, html: str, problem_id: str) -> ProblemData:
        title = self.parse_title(html)
        statement = self.parse_statement(html)
        samples = self.parse_samples(html)
        if not statement and not samples:
            raise FetchError("页面中未找到题目正文与样例")
        return ProblemData(
            oj=self.name,
            problem_id=problem_id,
            problem_dir_id=problem_id,
            source=self.problem_link(problem_id),
            title=title or problem_id,
            statement_md=self.statement_markdown(problem_id, title or problem_id, statement, samples),
            samples=samples,
        )

    def parse_title(self, html: str) -> str:
        match = re.search(r"<h1[^>]*>([\s\S]*?)</h1>", html)
        if not match:
            return ""
        return normalize_space(re.sub(r"<[^>]+>", "", match.group(1)))

    def parse_statement(self, html: str) -> str:
        # AcWing 题面主体通常在 problem-content 容器内；按块提取标题与段落文本
        match = re.search(
            r'<div[^>]*class="[^"]*problem-content[^"]*"[^>]*>([\s\S]*?)</div>\s*(?:<div[^>]*class="[^"]*problem-input|$)',
            html,
        )
        if not match:
            # 退而求其次：抓取 <article> 容器
            match = re.search(r"<article[^>]*>([\s\S]*?)</article>", html)
        if not match:
            return ""
        content = match.group(1)
        content = re.sub(r"<script[\s\S]*?</script>", "", content)
        text = re.sub(r"<[^>]+>", "\n", content)
        text = re.sub(r"\n{3,}", "\n\n", text)
        return normalize_space(text)

    def parse_samples(self, html: str) -> list[Sample]:
        # 样例通常是 <pre> 输入 / <pre> 输出 成对出现
        pres = re.findall(r"<pre[^>]*>([\s\S]*?)</pre>", html)
        samples: list[Sample] = []
        for index in range(0, len(pres) - 1, 2):
            input_data = re.sub(r"<[^>]+>", "", pres[index]).strip()
            output_data = re.sub(r"<[^>]+>", "", pres[index + 1]).strip()
            samples.append(Sample(input=input_data, output=output_data))
        return samples

    def statement_markdown(
        self,
        display_id: str,
        title: str,
        statement: str,
        samples: list[Sample],
    ) -> str:
        sections = [f"# {display_id} {title}".strip(), ""]
        if statement:
            sections.append(f"## 题目描述\n\n{statement}")
        if samples:
            sample_parts = []
            for index, sample in enumerate(samples, start=1):
                sample_parts.append(
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
            sections.append("\n\n".join(sample_parts) + "\n")
        return "\n".join(part for part in sections if part != "").rstrip() + "\n"
