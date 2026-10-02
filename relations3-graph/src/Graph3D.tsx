import { forwardRef, useCallback, useEffect, useImperativeHandle, useMemo, useRef, useState } from 'react';
import ForceGraph3D, { type ForceGraphMethods } from 'react-force-graph-3d';
import { PerspectiveCamera, Plane, Raycaster, Vector2, Vector3 } from 'three';
import { forceCenter, forceCollide, forceManyBody } from 'd3-force-3d';
import { focusCamera, overviewCenter } from './camera';
import { GraphModel } from './graph-model';
import { GraphObjects, type VisualState } from './graph-objects';
import { projectLabels } from './label-manager';
import { GraphLabelOverlay, type GraphLabel } from './GraphLabelOverlay';
import { browserStorage, clearLayout, loadLayout, saveLayout } from './layout-store';
import { relationFingerprint } from './graph-data';
import { scopedForce } from './layout-policy';
import type { CameraView, Graph3DHandle, Position3D, SimLink, SimNode } from './types';

interface Props {
  visual: VisualState; width: number; height: number; focusRevision: number; restoreCamera?: CameraView;
  onSelect(id: string): void; onHover(id: string): void; onEdgeHover(id: string): void;
  onReady(): void; onError(message: string): void; onLayout(running: boolean): void;
}
interface Controls {
  target: Vector3;
  addEventListener(type: string, listener: () => void): void;
  removeEventListener(type: string, listener: () => void): void;
}
type LinkForce = { strength(value: (edge: SimLink) => number): LinkForce; distance(value: number): LinkForce };

const Graph3D = forwardRef<Graph3DHandle, Props>(function Graph3D(props, ref) {
  const [model] = useState(() => new GraphModel());
  const [objects] = useState(() => new GraphObjects());
  const [labels, setLabels] = useState<GraphLabel[]>([]);
  const fg = useRef<ForceGraphMethods<SimNode, SimLink> | undefined>(undefined);
  const live = useRef(props);
  live.current = props;
  const ready = useRef(false);
  const running = useRef(false);
  const [layoutRequest, setLayoutRequest] = useState(0);
  const [simulating, setSimulating] = useState(false);
  const saveTimer = useRef<ReturnType<typeof setTimeout> | undefined>(undefined);
  const lastDrag = useRef(0);
  const lastFocus = useRef(-1);
  const visualRevision = useRef(0);
  const fingerprint = useMemo(() => relationFingerprint(props.visual.data), [props.visual.data]);
  const reconciliation = useMemo(() => model.reconcile(props.visual.data, loadLayout(browserStorage(), fingerprint, new Set(props.visual.data.nodes.map(n => n.id)))), [model, props.visual.data, fingerprint]);

  const persist = useCallback(() => { saveLayout(browserStorage(), model.snapshot()); }, [model]);
  const schedulePersist = useCallback(() => { clearTimeout(saveTimer.current); saveTimer.current = setTimeout(persist, 250); }, [persist]);
  const freeze = useCallback(() => {
    model.freeze();
    if (running.current) { running.current = false; setSimulating(false); live.current.onLayout(false); schedulePersist(); }
  }, [model, schedulePersist]);
  const cameraView = useCallback((): CameraView | undefined => {
    const graph = fg.current;
    if (!ready.current || !graph) return undefined;
    const camera = graph.camera();
    const controls = graph.controls() as Controls;
    return { position: { x: camera.position.x, y: camera.position.y, z: camera.position.z }, target: { x: controls.target.x, y: controls.target.y, z: controls.target.z } };
  }, []);
  const moveCamera = useCallback((view: CameraView, animate = true) => {
    const graph = fg.current;
    if (!graph) return;
    const camera = graph.camera();
    if (camera instanceof PerspectiveCamera) {
      camera.far = Math.max(10000, camera.position.distanceTo(new Vector3(view.target.x, view.target.y, view.target.z)) * 5, Math.hypot(view.position.x - view.target.x, view.position.y - view.target.y, view.position.z - view.target.z) * 5);
      camera.updateProjectionMatrix();
    }
    graph.cameraPosition(view.position, view.target, animate && !window.matchMedia('(prefers-reduced-motion: reduce)').matches ? 550 : 0);
  }, []);
  const fit = useCallback((reset = false) => {
    const p = live.current;
    const graph = fg.current;
    const current = cameraView();
    if (!graph || !current || !p.width || !p.height) return;
    freeze();
    const ids = p.visual.focus.centerId ? p.visual.focus.nodeIds : p.visual.visibleNodes;
    const points = [...ids].map(id => model.nodes.get(id)).filter((n): n is SimNode => !!n);
    const center = model.nodes.get(p.visual.focus.centerId) || overviewCenter(points);
    if (reset) current.position = { x: current.target.x, y: current.target.y, z: current.target.z + 1000 };
    const camera = graph.camera();
    moveCamera(focusCamera(center, points, current, p.width / p.height, camera instanceof PerspectiveCamera ? camera.getEffectiveFOV() : 50));
  }, [cameraView, freeze, model, moveCamera]);
  const startLayout = useCallback((reset = false) => {
    if (!ready.current) return;
    const p = live.current;
    if (reset) {
      clearLayout(browserStorage(), model.fingerprint);
      model.reset(p.visual.data, p.visual.visibleNodes, Date.now());
    }
    setSimulating(true);
    running.current = true;
    live.current.onLayout(true);
    setLayoutRequest(r => r + 1);
  }, [model]);

  useImperativeHandle(ref, () => ({
    fitVisible: () => fit(), resetView: () => fit(true), relayout: () => startLayout(true), getCameraView: cameraView,
    zoom: factor => { const view = cameraView(); if (view) { freeze(); view.position = { x: view.target.x + (view.position.x - view.target.x) * factor, y: view.target.y + (view.position.y - view.target.y) * factor, z: view.target.z + (view.position.z - view.target.z) * factor }; moveCamera(view); } },
  }), [fit, startLayout, cameraView, freeze, moveCamera]);

  const nodeObject = useCallback((n: SimNode) => objects.node(n), [objects]);
  const edgeObject = useCallback((e: SimLink) => objects.edge(e), [objects]);
  const onEngineStop = useCallback(() => {
    if (!running.current) return;
    freeze();
    fit();
  }, [freeze, fit]);
  const onNodeClick = useCallback((n: SimNode) => {
    if (Date.now() - lastDrag.current < 250) return;
    freeze(); live.current.onSelect(n.id);
  }, [freeze]);
  useEffect(() => { objects.update(props.visual); visualRevision.current++; }, [objects, props.visual]);

  useEffect(() => {
    let active = true;
    let frame = 0;
    let frameCount = 0;
    let cleanup = () => {};
    // The package digests graphData asynchronously. Wait for its DOM/camera to exist.
    const initialize = () => {
      const graph = fg.current;
      if (!active || !graph) return;
      if (++frameCount < 3) { frame = requestAnimationFrame(initialize); return; }
      try {
        const renderer = graph.renderer();
        renderer.setPixelRatio(Math.min(window.devicePixelRatio || 1, 1.5));
        const canvas = renderer.domElement;
        const controls = graph.controls() as Controls;
        const cancelCamera = () => {
          const view = cameraView();
          if (view) graph.cameraPosition(view.position, view.target, 0);
        };
        const loseContext = (e: Event) => { e.preventDefault(); live.current.onError('3D 画布连接已中断，请重试。'); };
        // Capture mouse node drags before OrbitControls. Touch keeps native camera
        // gestures, with an explicit tap hit-test because touch has no hover state.
        const raycaster = new Raycaster();
        const pointer = new Vector2();
        const activeTouches = new Set<number>();
        let tap: { id: string; pointerId: number; x: number; y: number } | null = null;
        let suppressTouchClick = false;
        let drag: { id: string; pointerId: number; initial: Vector3; hit: Vector3; plane: Plane; x: number; y: number; moved: boolean } | null = null;
        const setRay = (e: PointerEvent) => {
          const rect = canvas.getBoundingClientRect();
          pointer.set((e.clientX - rect.left) / rect.width * 2 - 1, -(e.clientY - rect.top) / rect.height * 2 + 1);
          raycaster.setFromCamera(pointer, graph.camera());
        };
        const pointerDown = (e: PointerEvent) => {
          if (e.pointerType === 'touch') {
            activeTouches.add(e.pointerId); tap = null;
            if (activeTouches.size === 1) {
              setRay(e);
              const hit = raycaster.intersectObjects([...objects.nodes.values()].filter(n => n.group.visible).map(n => n.sphere), false)[0];
              const id = hit?.object.userData.nodeId as string | undefined;
              if (id) tap = { id, pointerId: e.pointerId, x: e.clientX, y: e.clientY };
            }
            return;
          }
          if (e.button !== 0 || e.pointerType !== 'mouse' || !window.matchMedia('(pointer: fine)').matches) return;
          setRay(e);
          const hit = raycaster.intersectObjects([...objects.nodes.values()].filter(n => n.group.visible).map(n => n.sphere), false)[0];
          const id = hit?.object.userData.nodeId as string | undefined;
          const node = id && model.nodes.get(id);
          if (!node || !id) return;
          const initial = new Vector3(node.x, node.y, node.z);
          const plane = new Plane().setFromNormalAndCoplanarPoint(graph.camera().getWorldDirection(new Vector3()), initial);
          const intersection = raycaster.ray.intersectPlane(plane, new Vector3());
          if (!intersection) return;
          freeze(); cancelCamera();
          (controls as Controls & { enabled: boolean }).enabled = false;
          drag = { id, pointerId: e.pointerId, initial, hit: intersection, plane, x: e.clientX, y: e.clientY, moved: false };
          canvas.setPointerCapture(e.pointerId);
          canvas.style.cursor = 'grabbing';
          e.preventDefault(); e.stopImmediatePropagation();
        };
        const pointerMove = (e: PointerEvent) => {
          if (tap?.pointerId === e.pointerId && Math.hypot(e.clientX - tap.x, e.clientY - tap.y) > 8) tap = null;
          if (!drag || drag.pointerId !== e.pointerId) return;
          setRay(e);
          const hit = raycaster.ray.intersectPlane(drag.plane, new Vector3());
          if (!hit) return;
          drag.moved ||= Math.hypot(e.clientX - drag.x, e.clientY - drag.y) > 4;
          if (drag.moved) {
            const point = drag.initial.clone().add(hit.sub(drag.hit));
            const node = model.nodes.get(drag.id)!;
            node.x = point.x; node.y = point.y; node.z = point.z;
            model.freezeNode(node);
            objects.nodes.get(drag.id)?.group.position.copy(point);
            // Engine is stopped: update incident link geometry directly, without reheating.
            for (const link of model.links.values()) if (link.sourceId === drag.id || link.targetId === drag.id) objects.updateEdge(link.id, model.nodes.get(link.sourceId)!, model.nodes.get(link.targetId)!);
            visualRevision.current++;
          }
          e.preventDefault(); e.stopImmediatePropagation();
        };
        const pointerEnd = (e: PointerEvent) => {
          if (e.pointerType === 'touch') {
            activeTouches.delete(e.pointerId);
            if (tap?.pointerId === e.pointerId) {
              if (e.type === 'pointerup') { suppressTouchClick = true; lastDrag.current = Date.now(); freeze(); live.current.onSelect(tap.id); }
              tap = null;
            }
            return;
          }
          if (!drag || drag.pointerId !== e.pointerId) return;
          const finished = drag; drag = null;
          if (canvas.hasPointerCapture(e.pointerId)) canvas.releasePointerCapture(e.pointerId);
          (controls as Controls & { enabled: boolean }).enabled = true;
          canvas.style.cursor = '';
          lastDrag.current = Date.now();
          if (finished.moved) { model.pin(finished.id); schedulePersist(); }
          else if (e.type === 'pointerup') live.current.onSelect(finished.id);
          e.preventDefault(); e.stopImmediatePropagation();
        };
        // Opening the drawer resizes the stage before the browser's synthetic click.
        // Cancel that click so it cannot land on the newly moved drawer toggle.
        const touchEnd = (e: TouchEvent) => { if (suppressTouchClick) { e.preventDefault(); suppressTouchClick = false; } };
        controls.addEventListener('start', cancelCamera);
        canvas.addEventListener('webglcontextlost', loseContext);
        canvas.addEventListener('pointerdown', pointerDown, true);
        canvas.addEventListener('pointermove', pointerMove, true);
        canvas.addEventListener('pointerup', pointerEnd, true);
        canvas.addEventListener('pointercancel', pointerEnd, true);
        canvas.addEventListener('touchend', touchEnd, { capture: true, passive: false });
        cleanup = () => {
          controls.removeEventListener('start', cancelCamera); canvas.removeEventListener('webglcontextlost', loseContext);
          canvas.removeEventListener('pointerdown', pointerDown, true); canvas.removeEventListener('pointermove', pointerMove, true);
          canvas.removeEventListener('pointerup', pointerEnd, true); canvas.removeEventListener('pointercancel', pointerEnd, true);
          canvas.removeEventListener('touchend', touchEnd, true);
        };
        ready.current = true;
        lastFocus.current = live.current.focusRevision;
        objects.update(live.current.visual);
        live.current.onReady();
        if (reconciliation.needsLayout) startLayout();
        else fit();
      } catch (e) { live.current.onError(e instanceof Error ? e.message : '无法初始化 3D 画布'); }
    };
    frame = requestAnimationFrame(initialize);
    return () => { active = false; const wasReady = ready.current; ready.current = false; cancelAnimationFrame(frame); cleanup(); clearTimeout(saveTimer.current); if (wasReady) { model.freeze(); persist(); } };
    // Own one lifecycle; later data changes are reconciled without remounting the renderer.
  }, [cameraView, fit, freeze, model, objects, persist, schedulePersist, startLayout]);

  useEffect(() => {
    if (!layoutRequest || !fg.current) return;
    const graph = fg.current;
    const ids = new Set(live.current.visual.visibleNodes);
    const edgeIds = new Set(live.current.visual.visibleEdges);
    model.release(ids);
    graph.d3Force('charge', scopedForce(forceManyBody<SimNode>().strength(-500), ids));
    graph.d3Force('center', scopedForce(forceCenter<SimNode>(0, 0, 0), ids));
    graph.d3Force('collide', scopedForce(forceCollide<SimNode>(14).iterations(2), ids));
    const link = graph.d3Force('link') as unknown as LinkForce | undefined;
    link?.distance(150).strength(e => edgeIds.has(e.id) ? 0.65 : 0);
    graph.d3ReheatSimulation();
  }, [layoutRequest, model]);

  useEffect(() => {
    if (!ready.current) return;
    // Reconciliation is driven by data, never by query, center, or theme.
    if (reconciliation.changed && reconciliation.needsLayout) startLayout();
  }, [reconciliation, startLayout]);

  useEffect(() => {
    if (!ready.current || lastFocus.current === props.focusRevision) return;
    lastFocus.current = props.focusRevision;
    freeze();
    if (props.restoreCamera) moveCamera(props.restoreCamera);
    else fit();
  }, [props.focusRevision, props.restoreCamera, props.width, props.height, fit, freeze, moveCamera]);

  useEffect(() => {
    if (ready.current && !running.current && live.current.visual.focus.centerId) fit();
  }, [props.width, props.height, fit]);

  useEffect(() => {
    let frame = 0;
    let signature = '';
    const context = document.createElement('canvas').getContext('2d')!;
    context.font = '12px sans-serif';
    const labels = () => {
      const graph = fg.current;
      const p = live.current;
      if (ready.current && graph) {
        const camera = graph.camera();
        const next = `${camera.matrixWorld.elements.join(',')}:${p.width}:${p.height}:${visualRevision.current}`;
        if (camera instanceof PerspectiveCamera && (next !== signature || running.current)) {
          signature = next;
          setLabels(projectLabels(model, p.visual, camera, p.width, p.height, text => context.measureText(text).width));
        }
      }
      frame = requestAnimationFrame(labels);
    };
    frame = requestAnimationFrame(labels);
    const saveOnHide = () => { if (ready.current) { model.freeze(); persist(); } };
    window.addEventListener('pagehide', saveOnHide);
    return () => { cancelAnimationFrame(frame); window.removeEventListener('pagehide', saveOnHide); };
  }, [model, objects, persist]);

  return <><ForceGraph3D<SimNode, SimLink>
    ref={fg} graphData={model.graphData} width={props.width} height={props.height}
    controlType="orbit" backgroundColor="#000011" showNavInfo={false}
    nodeThreeObject={nodeObject} linkThreeObject={edgeObject}
    linkPositionUpdate={(_object, coords, edge) => objects.updateEdge((edge as unknown as SimLink).id, coords.start, coords.end)}
    nodeLabel={() => ''} linkLabel={() => ''} linkDirectionalArrowLength={0}
    cooldownTicks={simulating ? 180 : 0} cooldownTime={6000} d3AlphaDecay={0.04} d3VelocityDecay={0.45}
    onEngineStop={onEngineStop} onNodeClick={onNodeClick}
    onNodeHover={n => live.current.onHover(n?.id || '')} onLinkHover={e => live.current.onEdgeHover(e?.id || '')}
    enableNodeDrag={false}
  /><GraphLabelOverlay labels={labels} /></>;
});
export default Graph3D;
