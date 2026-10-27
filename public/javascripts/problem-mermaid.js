(function () {
  const blocks = document.querySelectorAll('pre.mermaid');

  if (!blocks.length || typeof window.mermaid === 'undefined') return;

  window.mermaid.initialize({
    startOnLoad: false,
    securityLevel: 'strict',
    theme: 'default',
    // 不按容器宽度等比缩图画：宽图保持原始像素，由 .mermaid 的横向滚动接住，
    // 否则节点一多整张 SVG 被压扁，字号小到看不清。
    flowchart: {
      useMaxWidth: false,
      nodeSpacing: 30,
      rankSpacing: 36,
    },
    sequence: { useMaxWidth: false },
    gantt: { useMaxWidth: false },
  });

  window.mermaid.run({ nodes: blocks }).catch((error) => {
    for (const block of blocks) {
      block.classList.add('mermaid-render-failed');
    }
    console.error('Mermaid render failed:', error);
  });
}());
