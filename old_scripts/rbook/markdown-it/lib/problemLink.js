/**
 * 
 *  [[problem: ojname,id]] 解析成 </a><a href="ojname/id">ojname/id</a>
 */

// const ProblemInfo =
import ProbClass from '../../../problemlib.js'
const Prob = new ProbClass({auto_load:false})
Prob.load_problems();

function problemLinkPlugin(md) {
  
  // 也可以使用更精确的解析方式，避免影响其他文本
  md.inline.ruler.after('text', 'problem_link', function(state, silent) {
    const pos = state.pos;
    const max = state.posMax;
    
    // console.log("==>",state.src.substr(pos, 10),'<-');
    // console.log(state.src.substr(pos, 10) !== '[[problem:' )
    // 检查是否以 [[problem: 开头
    if (pos + 11 >= max || state.src.substr(pos, 10) !== '[[problem:') {
      return false;
    }
    // console.log("==>",state.src.substr(pos, 11));
    
    // 查找结束的 ]]
    const endPos = state.src.indexOf(']]', pos + 10);
    if (endPos === -1) {
      return false;
    }
    
    // 提取内容
    const content = state.src.slice(pos + 11, endPos);
    const match = content.match(/^\s*([^,\]]+),\s*([^,\]]+)\s*$/);
    
    if (!match) {
      return false;
    }
    
    if (silent) {
      state.pos = endPos + 2;
      return true;
    }
    
    const ojname = match[1].trim();
    const id = match[2].trim();
    let Pinfo = Prob.find(ojname,id);
    if( Pinfo == null ) {
      throw new Error(`Problem ${ojname}/${id} not found, ${state.env.filePath}`);
      return false;
    }
    let title = Pinfo.title;

    const href = Prob.problem_url(ojname,id);
    
    // 创建 token
    const token = state.push('link_open', 'a', 1);
    token.attrSet('href', href);
    token.attrSet('class', 'problem-link');
    token.attrSet('target', '_blank');
    
    const textToken = state.push('text', '', 0);
    let tags = 'tags: [' + Pinfo.tags.join(',') + ']';
    textToken.content = `${ojname}-${id} ${title} ${tags}`;
    // TODO tags? show
    
    state.push('link_close', 'a', -1);
    
    state.pos = endPos + 2;
    return true;
  });
};

export default problemLinkPlugin;