import { forwardRef, useEffect, useImperativeHandle, useRef, useState } from 'react';
import { CanvasGraph, type Scene } from './canvas';
import { relationFingerprint, readStored, writeStored, type Point, type RelationGraphResponse } from './model';
import { validPositions } from './layout';

export interface OverviewHandle { fit(): void; zoom(factor: number): void; locate(id: string): void }
export default forwardRef<OverviewHandle, {
  data: RelationGraphResponse; scene: Scene; layoutVersion: number;
  onHover(id: string): void; onSelect(id: string | null): void;
}>(function Overview({ data, scene, layoutVersion, onHover, onSelect }, ref) {
  const canvas = useRef<HTMLCanvasElement>(null);
  const graph = useRef<CanvasGraph | null>(null);
  const callbacks = useRef({ onHover, onSelect }); callbacks.current = { onHover, onSelect };
  const latestScene = useRef(scene); latestScene.current = scene;
  const [positions, setPositions] = useState<Record<string, Point> | null>(null);
  const [error, setError] = useState('');
  const key = `rbook.relations4.layout.v1.${relationFingerprint(data)}`;
  useImperativeHandle(ref, () => ({
    fit: () => graph.current?.fit(), zoom: factor => graph.current?.zoom(factor), locate: id => graph.current?.locate(id),
  }), []);
  useEffect(() => {
    setError(''); setPositions(null);
    const cached = layoutVersion === 0 ? readStored(key) : undefined;
    if (validPositions(cached, data.nodes)) { setPositions(cached); return; }
    let worker: Worker;
    try { worker = new Worker(new URL('./layout.worker.ts', import.meta.url), { type: 'module' }); }
    catch { setError('无法启动布局，请刷新重试。仍可通过搜索和分层浏览题目。'); return; }
    worker.onmessage = event => {
      if (event.data.error || !validPositions(event.data.positions, data.nodes)) {
        setError('布局未完成，请刷新重试。仍可通过搜索和分层浏览题目。');
      } else {
        writeStored(key, event.data.positions); setPositions(event.data.positions);
      }
      worker.terminate();
    };
    worker.onerror = () => { setError('布局线程加载失败，请刷新重试。仍可使用分层视图。'); worker.terminate(); };
    worker.postMessage({ nodes: data.nodes.map(n => ({ id: n.id, isolated: n.isolated })), edges: data.edges.map(e => ({ source: e.source, target: e.target })) });
    return () => worker.terminate();
  }, [data, key, layoutVersion]);
  useEffect(() => {
    if (!positions || !canvas.current) return;
    try {
      const engine = new CanvasGraph(canvas.current, latestScene.current, positions, key, id => callbacks.current.onHover(id), id => callbacks.current.onSelect(id));
      graph.current = engine;
      return () => { engine.destroy(); graph.current = null; };
    } catch (error) { setError(error instanceof Error ? error.message : '画布加载失败'); }
  }, [positions, key]);
  useEffect(() => { graph.current?.update(scene); }, [scene]);
  return <div className="r4-overview" data-layout-running={!positions && !error}>
    <canvas ref={canvas} tabIndex={0} aria-label="题目关系全景。鼠标悬停预览、点击锁定、拖动平移或移动节点、滚轮缩放。键盘方向键平移，加减号缩放，0 适配，Escape 取消选择。也可使用搜索和左侧关系清单。" />
    {!positions && !error && <div className="r4-stage-message" role="status"><span className="r4-spinner" />正在整理题目关系…<small>布局完成后，节点会保持静止</small></div>}
    {error && <div className="r4-stage-message" role="alert">{error}</div>}
    <div className="r4-canvas-tools" aria-label="全景视角">
      <button onClick={() => graph.current?.zoom(1.3)} aria-label="放大">＋</button>
      <button onClick={() => graph.current?.zoom(1 / 1.3)} aria-label="缩小">−</button>
      <button onClick={() => graph.current?.fit()} aria-label="适配全图">⤢</button>
    </div>
    <p className="r4-gesture-hint">悬停看关系 · 点击锁定 · 拖动与缩放</p>
  </div>;
});
