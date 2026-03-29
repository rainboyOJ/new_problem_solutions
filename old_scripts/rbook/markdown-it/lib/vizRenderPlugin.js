// markdown-it-viz.mjs

export default function vizPlugin(md, options = {}) {
  // 从选项中获取已经初始化好的 viz 实例
  const viz = options.viz;

  if (!viz) {
    throw new Error("必须在选项中传入已初始化的 viz 实例: md.use(plugin, { viz: myInstance })");
  }

  // 保存旧的 fence 渲染器（用于处理非 graphviz 的代码块）
  const defaultFence = md.renderer.rules.fence || function(tokens, idx, options, env, self) {
    return self.renderToken(tokens, idx, options);
  };

  // 覆盖 fence 渲染器
  md.renderer.rules.fence = function (tokens, idx, options, env, self) {
    const token = tokens[idx];
    const lang = token.info.trim();

    // 拦截语言标记为 'dot' 或 'graphviz' 的代码块
    if (lang === 'dot' || lang === 'graphviz') {
      try {
        const code = token.content;
        
        // 关键点：viz.renderString 是同步的！可以直接返回！
        // 我们可以直接返回 SVG 字符串
        const svg = viz.renderString(code, { 
            format: "svg",
            engine: "dot" 
        });
        
        return `<div class="viz-graph">${svg}</div>`;
      } catch (e) {
        return `<pre class="viz-error">Graphviz Error: ${e.message}</pre>`;
      }
    }

    // 其他语言交给默认渲染器
    return defaultFence(tokens, idx, options, env, self);
  };
}