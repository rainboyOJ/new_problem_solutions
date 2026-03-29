// 输入数据: html raw string
// 得到的数据:
//      content.md
//          luogu能得到原 markdown
//      link: []
//          原地址
//          vjudge 地址
//      memory
//      time
//      tags
//      

import {join,resolve,extname,isAbsolute} from 'path'
// const {relative: project_dir_relative,absolute:project_dir_absolute} = require("./base_class/pather.js")

import LUOGU  from './luogu.js'
import VJUDGE from './vjudge.js'
import CF from './codeforces.js'

const online_judges= [
    // require("./roj.js"),
    // require("./luogu.js"),
    new LUOGU(),
    new VJUDGE(),
    new CF()
    // require("./noi.openjudge.cn.js"),
    // require("./leetcodecn.js"),
    // require("./vjudge.js"),
]



//根据题目的path
// 例如:roj/1000, luogu/1014,hdu/1014..
// 得到这个题目的相应信息
// exports.get_info_by_problem_path = function get_info_by_problem_path(path) {
//     if( isAbsolute(path) ) path = project_dir_relative(path)
//     return get_match_oj(path).one_info(path);
// }

//通过path 得到对应的id
function get_match_oj(path) {
    if( isAbsolute(path) ) path = project_dir_relative(path)

    // console.log(path)
    for( let oj of ojs) {
        if( oj.match(path)) {
            return oj
        }
    }
    throw 'not match problem by this path : ' + path
}

function dir_to_id(path) {
    if( isAbsolute(path) ) path = project_dir_relative(path)
    return get_match_oj(path).dir_to_id(path)
}

//通过oj的那么得到oj object
function get_oj_by_name(name) {
    for( let oj of ojs) {
        if( oj.name === name ) {
            return oj
        }
    }
    throw 'not match problem by this path : ' + path
}



// 处理problem info 的 pre 信息
// exports.deal_pre_attr = function(info) {

//     function trans_to_id(str) {
//         //1. 得到这个题目的绝对地址
//         if( str.startsWith('..')) //这种情况是地址
//         {
//             const dir = project_dir_absolute(info.path)
//             const pre_problem_dir = join(dir,str)
//             // console.log(str,dir,pre_problem_dir)
//             str = dir_to_id(pre_problem_dir)
//         }
//         // console.log('pre id',str)
//         return str; //本身就是id
//     }


//     if( info.pre) {

//         if( typeof info.pre === 'string')
//         {
//             // return [trans_to_id(info.pre)]
//             info.pre = [trans_to_id(info.pre)]
//         }
//         else if( Array.isArray(info.pre) )
//         {
//             let ret = []
//             for( let str of info.pre) {
//                 ret.push(trans_to_id(str))
//             }
//             // return ret
//             info.pre = ret
//         }
//     }
// }


// online_judges[0].download('P1000')
// online_judges[0].match_by_pwd()

// 命令
let argv = process.argv
if (argv.length == 3 && argv[2].startsWith('http')) {
  for (let oj of online_judges) {
    console.log('check : ' ,oj.name, '...');
    if (oj.match_by_link( argv[2] )) {
      console.log(" match oj by link : " + oj.name)
      oj.download_by_link(argv[2])
      break;
    }
  }
  process.exit(0)
}


if(argv.length != 4) {
  console.log('Usage: node index.js [oj] [id]')
  process.exit(1)
}

let ojName = argv[2]
let id = argv[3]

for ( let oj of online_judges) {
    // console.log( oj.name)
    if( oj.match_by_name(ojName) ) {
        console.log(" match oj : " + oj.name)
        oj.download(id,ojName)
        break;
    }
}