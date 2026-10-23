(function () {
  const containers = document.querySelectorAll('.graphviz');

  if (!containers.length) return;

  const globalViz = window.Viz;
  if (!globalViz || typeof globalViz.instance !== 'function') {
    console.error('Graphviz runtime is not available.');
    return;
  }

  function renderFailed(container, error) {
    container.classList.add('graphviz-render-failed');

    const pre = container.querySelector('pre.dot');
    if (pre) {
      pre.classList.add('graphviz-source-fallback');
    }

    const message = document.createElement('p');
    message.className = 'graphviz-error';
    message.textContent = `Graphviz render failed: ${error instanceof Error ? error.message : String(error)}`;
    container.prepend(message);
  }

  globalViz.instance()
    .then((viz) => {
      containers.forEach((container) => {
        const pre = container.querySelector('pre.dot');
        if (!pre) return;

        const source = pre.textContent || '';
        const engine = container.dataset.vizEngine || 'dot';

        try {
          const svg = viz.renderSVGElement(source, { engine });
          // 保留 Graphviz 给出的自然尺寸，只限制「不超过容器宽度」。
          // 如果删掉 width/height，SVG 会按容器宽度撑满，窄而高的图（例如
          // 89pt x 332pt）就会被放大到几千像素高。
          svg.style.maxWidth = '100%';
          svg.style.height = 'auto';
          container.replaceChildren(svg);
        } catch (error) {
          renderFailed(container, error);
          console.error('Graphviz render failed:', error);
        }
      });
    })
    .catch((error) => {
      containers.forEach((container) => renderFailed(container, error));
      console.error('Graphviz runtime init failed:', error);
    });
}());
