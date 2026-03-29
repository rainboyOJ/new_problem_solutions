// Process block-level custom containers
//
'use strict';

var debug = function(...params){
    //console.log(" ==== debug ====")
    //console.log(...params)
    //console.log(" ==== debug end ====")
    //console.log("\n\n")
}



export default function container_plugin(md, name, options) {

  function validateDefault(params) {
    return /^viz-gallery/.test(params.trim())
  }
  
  function get_viz_string(str){
    const accept_engine = ['circo','dot','fdp','neato','osage','twopi']
    const regexp_g = /```(.*?)\n([\s\S]*?)\n```/g
    const regexp = /```(.*?)\n([\s\S]*?)\n```/
    let viz = []
    let viz_src_s = str.match(regexp_g)
    //console.log(viz_src_s)
    for( let src of viz_src_s){
      let res = src.match(regexp)
      let engine = null
      let log = null
      if( res[1].trim().length > 0){
        let arr = res[1].trim().split(' ');
        [arr.shift(),arr.join(' ')].map( (t)=>{
          if( !t || t.length == 0) return
          if( accept_engine.indexOf(t) != -1)
            engine =t
          else
            log = t
        })
      }

      viz.push({
        engine, log,
        src:res[2]
      })
    }
    return JSON.stringify(viz)
  }

  function renderDefault(tokens, idx, _options, env, slf) {

    // add a class to the opening tag
    if (tokens[idx].nesting === 1) {
      tokens[idx].attrJoin('class', name);
    }

    return slf.renderToken(tokens, idx, _options, env, slf);
  }

  options = options || {};

  var min_markers = 4,
      marker_str  = options.marker || '<',
      marker_char = marker_str.charCodeAt(0),
      marker_len  = marker_str.length,
      validate    = options.validate || validateDefault,
      render      = options.render || renderDefault;

  function container(state, startLine, endLine, silent) {
    var pos, nextLine, marker_count, markup, params, token,
        old_parent, old_line_max,
        auto_closed = false,
        start = state.bMarks[startLine] + state.tShift[startLine],
        max = state.eMarks[startLine];

      debug(`start: ${start} 
start char : ${state.src[start]}
          \n max: ${max} \n src:${state.src}`)


    // Check out the first character quickly,
    // this should filter out most of non-containers
    //
    if (marker_char !== state.src.charCodeAt(start)) { return false; }

    // Check out the rest of the marker string
    //
    for (pos = start + 1; pos <= max; pos++) {
      if (marker_str[(pos - start) % marker_len] !== state.src[pos]) {
        break;
      }
    }

    marker_count = Math.floor((pos - start) / marker_len);
    if (marker_count < min_markers) { return false; }
    pos -= (pos - start) % marker_len;

    markup = state.src.slice(start, pos);
    params = state.src.slice(pos, max);
    if (!validate(params)) { return false; }
    debugger

    // Since start is found, we can report success here in validation mode
    //
    if (silent) { return true; }

    // Search for the end of the block
    //
    nextLine = startLine;

    for (;;) {
      nextLine++;
      if (nextLine >= endLine) {
        // unclosed block should be autoclosed by end of document.
        // also block seems to be autoclosed by end of parent
        break;
      }

      start = state.bMarks[nextLine] + state.tShift[nextLine];
      max = state.eMarks[nextLine];

      if (start < max && state.sCount[nextLine] < state.blkIndent) {
        // non-empty line with negative indent should stop the list:
        // - ```
        //  test
        break;
      }

      if (marker_char !== state.src.charCodeAt(start)) { continue; }

      if (state.sCount[nextLine] - state.blkIndent >= 4) {
        // closing fence should be indented less than 4 spaces
        continue;
      }

      for (pos = start + 1; pos <= max; pos++) {
        if (marker_str[(pos - start) % marker_len] !== state.src[pos]) {
          break;
        }
      }

      // closing code fence must be at least as long as the opening one
      if (Math.floor((pos - start) / marker_len) < marker_count) { continue; }

      // make sure tail has spaces only
      pos -= (pos - start) % marker_len;
      pos = state.skipSpaces(pos);

      if (pos < max) { continue; }

      // found!
      auto_closed = true;
      break;
    }

    old_parent = state.parentType;
    old_line_max = state.lineMax;
    state.parentType = 'container';

    // this will prevent lazy continuations from ever going past our end marker
    state.lineMax = nextLine;

    // get viz-data
    let content_start = state.bMarks[startLine+1] + state.tShift[startLine+1];
    let content_max = state.eMarks[nextLine-1];
    let content = state.src.substring(content_start,content_max)
    let viz_data = get_viz_string(content)

    token        = state.push('viz-gallery-open', 'viz-gallery', 1);
    token.markup = markup;
    token.block  = true;
    token.info   = params;
    token.map    = [ startLine, nextLine ];
    //console.log(viz_data)
    token.attrPush(['data',viz_data])
    /* another attrs */
    {
      let raw = params.substring( params.indexOf('(')+1, params.lastIndexOf(')'))
      let params_list = raw.split(',')
      for( let p of params_list){
        let arr = p.trim().replace(/"/g,"").split('=')
        token.attrPush(arr)
      }
    }


    //state.md.block.tokenize(state, startLine + 1, nextLine);


    token        = state.push('viz-gallery-close', 'viz-gallery', -1);
    token.markup = state.src.slice(start, pos);
    token.block  = true;

    state.parentType = old_parent;
    state.lineMax = old_line_max;
    state.line = nextLine + (auto_closed ? 1 : 0);

    return true;
  }

  md.block.ruler.before('fence', 'container_' + name, container, {
    alt: [ 'paragraph', 'reference', 'blockquote', 'list' ]
  });
  md.renderer.rules['container_' + name + '_open'] = render;
  md.renderer.rules['container_' + name + '_close'] = render;
};
