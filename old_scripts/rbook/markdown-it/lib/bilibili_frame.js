// Process block-level custom containers
//
'use strict';

var debug = function(...params){
  //console.log(" ==== debug ====")
  //console.log(...params)
  //console.log(" ==== debug end ====")
  //console.log("\n\n")
}

module.exports = function container_plugin(md, name, options) {

    //const regExp      = /\[<\[\s*((av|BV)?\d+)\s*\]>\]/
    const regExp = /\[<\[\s*.+?\s*\]>\]/

    const attr = {
        'class': "bilibili_iframe",
        //'src': `//player.bilibili.com/player.html?aid=${tokens[idx].info.replace(/[^\d]/g,"")}`,
        scrolling:"no",
        border:"0",
        frameborder:"no",
        framespacing:"0",
        allowfullscreen:"true"
    }

  function validateDefault(src) {
    return regExp.test(src)
  }

  function renderDefault(tokens, idx, _options, env, slf) {

    return slf.renderToken(tokens, idx, _options, env, slf);
  }

  options = options || {};
  var min_markers = 1,
    marker_str  = '[',
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
    markup = "[<["

    debug(`start: ${start} 
start char : ${state.src[start]}
          \n max: ${max} \n src:${state.src}`)


    // Check out the first character quickly,
    // this should filter out most of non-containers
    //
    if (marker_char !== state.src.charCodeAt(start)) { return false; }

    var code = state.src.slice(start,max);
    debug(`code : ${code}`)

    if (!validate(code)) { return false; }
    debug(`code : ok`)

    params = code.match(regExp)[1]

    //old_parent = state.parentType;
    //old_line_max = state.lineMax;
    //state.parentType = 'container';

    // this will prevent lazy continuations from ever going past our end marker
    //state.lineMax = nextLine;

    token        = state.push('bilibili_iframe_open', 'iframe', 1);
    token.markup = markup;
    token.block  = true;
    token.info   = params;

    attr.src = `//player.bilibili.com/player.html?aid=${params.replace(/[^\d]/g,"")}`
    // add a attr to the opening tag
      for( let key in attr){
          token.attrJoin(key,attr[key])
      }


    token        = state.push('bilibili_iframe_close', 'iframe', -1);
    token.markup = "]>]"
    token.block  = true;

    //state.parentType = old_parent;
    //state.lineMax = old_line_max;
    state.line++;

    return true;
  }

  md.block.ruler.before('fence', 'bilibili_iframe', container, {
    alt: [ 'paragraph', 'reference', 'blockquote', 'list' ]
  });

};
