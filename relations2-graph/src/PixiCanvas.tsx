import { forwardRef, useEffect, useImperativeHandle, useRef } from 'react';
import { PixiGraphRenderer, type PixiGraphHandlers, type PixiGraphOptions } from './pixi-renderer';
import type { Position, PositionMap, RelationEdge, RelationNode } from './types';

export interface PixiCanvasHandle {
  zoomIn: () => void;
  zoomOut: () => void;
  fitToNodes: () => void;
  resetViewport: () => void;
  focusNode: (id: string) => void;
}

interface PixiCanvasProps {
  nodes: RelationNode[];
  edges: RelationEdge[];
  positions: PositionMap;
  options: PixiGraphOptions;
  onReady: () => void;
  onError: (message: string) => void;
  onNodeSelect: (node: RelationNode) => void;
  onNodeOpen: (node: RelationNode) => void;
  onNodeHover: (node: RelationNode | null) => void;
  onEdgeHover: (edge: RelationEdge | null, x: number, y: number) => void;
  onNodePosition: (id: string, position: Position) => void;
}

const PixiCanvas = forwardRef<PixiCanvasHandle, PixiCanvasProps>(function PixiCanvas(props, ref) {
  const hostRef = useRef<HTMLDivElement | null>(null);
  const rendererRef = useRef<PixiGraphRenderer | null>(null);
  const propsRef = useRef(props);
  propsRef.current = props;

  useImperativeHandle(ref, () => ({
    zoomIn: () => rendererRef.current?.zoomIn(),
    zoomOut: () => rendererRef.current?.zoomOut(),
    fitToNodes: () => rendererRef.current?.fitToNodes(),
    resetViewport: () => rendererRef.current?.resetViewport(),
    focusNode: (id: string) => rendererRef.current?.focusNode(id),
  }), []);

  useEffect(() => {
    const host = hostRef.current;
    if (!host) return undefined;
    const handlers: PixiGraphHandlers = {
      onNodeSelect: (node) => propsRef.current.onNodeSelect(node),
      onNodeOpen: (node) => propsRef.current.onNodeOpen(node),
      onNodeHover: (node) => propsRef.current.onNodeHover(node),
      onEdgeHover: (edge, x, y) => propsRef.current.onEdgeHover(edge, x, y),
      onNodePosition: (id, position) => propsRef.current.onNodePosition(id, position),
    };
    const renderer = new PixiGraphRenderer(handlers);
    rendererRef.current = renderer;
    let cancelled = false;
    renderer.mount(host, propsRef.current.options)
      .then(() => {
        if (cancelled) return;
        propsRef.current.onReady();
        renderer.update(propsRef.current.nodes, propsRef.current.edges, propsRef.current.positions, propsRef.current.options);
      })
      .catch((error: unknown) => {
        if (!cancelled) propsRef.current.onError(error instanceof Error ? error.message : 'PixiJS 初始化失败');
      });
    return () => {
      cancelled = true;
      renderer.destroy();
      rendererRef.current = null;
    };
  }, []);

  useEffect(() => {
    rendererRef.current?.update(props.nodes, props.edges, props.positions, props.options);
  }, [props.nodes, props.edges, props.positions, props.options]);

  return <div ref={hostRef} className="relations2-canvas-host" aria-label="Canvas 题目关系图" />;
});

export default PixiCanvas;
