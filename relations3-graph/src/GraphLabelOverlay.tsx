import React from 'react';
export interface GraphLabel { id: string; text: string; left: number; top: number; priority?: number }
export function GraphLabelOverlay({ labels }: { labels: GraphLabel[] }) {
  return <div className="relations3-label-overlay" aria-hidden="true">{labels.map(label => <span key={label.id} className={label.priority === 0 ? 'is-center' : ''} style={{ transform: `translate3d(${label.left}px,${label.top}px,0)` }}>{label.text}</span>)}</div>;
}
