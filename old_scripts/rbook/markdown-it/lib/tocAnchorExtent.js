
var title=`<div class="toc-title">
        <h3>目录</h3>
</div>
<div class="toc-content">`

export default (md)=>{
  md.renderer.rules.toc_open = () => "<div class=toc-body>"+title;
  md.renderer.rules.toc_close = () => "</div></div>";
}
