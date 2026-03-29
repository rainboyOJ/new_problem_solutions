---
title: this is title
foo: bar
---

@[toc]

# demo

## blackboard
::: blackboard

$$1 \leq 2$$

**strong**

*em*

normal text

 - list item 1
 - list item 2
    - list item 2.1
 - list item 3

:::

::: warning
**here be dragons**
:::

::: error
**here be dragons**
:::


::: info
**here be dragons**
:::

::: fold
```c
#include <cstdio>
int main(){
    printf("hello world!\n");
    return 0;
}
```
:::

**居中**

::: center
## 居中
:::


## 一行排列

::: line

```viz-dot
digraph G {
    splines=ortho;
    
    node[shape=box];
    x[shape=point];
    a[label="初始容量网络",shape="Mdiamond"];
    b[label="构造残余网络"];
    c[label="BFS 构造层次网络"];
    d[label="汇点在层次网络中",shape=diamond];

    e[label="DFS 进行增广"]
    f[label="算法结束"]

    a->b->c->d->e;
    e->f[style="invis"];
    
    {
        rank=same;
        x,d,y;
        y[shape=none,label="再次"];
    }
    x:we->d[arrowhead=none,headlabel="否"];

    x:w->f:w[constraint=false];

    e:e->y[constraint=false,arrowhead=none];
    y->c:e[constraint=false];
}
```

![test](https://img-blog.csdnimg.cn/20190124150454972.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2Nwb25nbzE=,size_16,color_FFFFFF,t_70 =100x100)


![test](https://img-blog.csdnimg.cn/20190124150454972.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2Nwb25nbzE=,size_16,color_FFFFFF,t_70 =100x100)
:::


## Math

$1+1=2$

$$
1+1=2
$$

this some word$ 1+1^1=2 $123123

## viz

```viz-dot
digraph G {
    splines=ortho;
    
    node[shape=box];
    x[shape=point];
    a[label="初始容量网络",shape="Mdiamond"];
    b[label="构造残余网络"];
    c[label="BFS 构造层次网络"];
    d[label="汇点在层次网络中",shape=diamond];

    e[label="DFS 进行增广"]
    f[label="算法结束"]

    a->b->c->d->e;
    e->f[style="invis"];
    
    {
        rank=same;
        x,d,y;
        y[shape=none,label="再次"];
    }
    x:we->d[arrowhead=none,headlabel="否"];

    x:w->f:w[constraint=false];

    e:e->y[constraint=false,arrowhead=none];
    y->c:e[constraint=false];
}
```

## Code highlight

```
#include <cstdio>
int main(){
    printf("hello world!\n");
    return 0;
}
```

```c
#include <cstdio>
int main(){
    printf("hello world!\n");
    return 0;
}
```

```plaintext
#include <cstdio>
int main(){
    printf("hello world!\n");
    return 0;
}
```

# h1 Heading 8-)
## h2 Heading
### h3 Heading
#### h4 Heading
##### h5 Heading
###### h6 Heading


## Horizontal Rules

___

---

***

**hello owrld**

1233123124 **hello owrld[]** sbdbfadfam

## Typographic replacements

Enable typographer option to see result.

(c) (C) (r) (R) (tm) (TM) (p) (P) +-

test.. test... test..... test?..... test!....

!!!!!! ???? ,,  -- ---

"Smartypants, double quotes" and 'single quotes'


## Emphasis

**This is bold text**

__This is bold text__

*This is italic text*

_This is italic text_

~~Strikethrough~~

## kbd

there are some words [[ctrl]] + [[x]]

## Blockquotes


> Blockquotes can also be nested...
>> ...by using additional greater-than signs right next to each other...
> > > ...or with spaces between arrows.


## Lists

Unordered

+ Create a list by starting a line with `+`, `-`, or `*`
+ Sub-lists are made by indenting 2 spaces:
  - Marker character change forces new list start:
    * Ac tristique libero volutpat at
    + Facilisis in pretium nisl aliquet
    - Nulla volutpat aliquam velit
+ Very easy!

Ordered

1. Lorem ipsum dolor sit amet
2. Consectetur adipiscing elit
3. Integer molestie lorem at massa


1. You can use sequential numbers...
1. ...or keep all the numbers as `1.`

Start numbering with offset:

57. foo
1. bar



## Task Lists

 - [ ] task One
   - foo
   - bar
 - [x] task two

## Code

Inline `code`

Indented code

    // Some comments
    line 1 of code
    line 2 of code
    line 3 of code


Block code "fences"

```
Sample text here...
```

Syntax highlighting

``` js
var foo = function (bar) {
  return bar++;
};

console.log(foo(5));
```

## Tables

| Option | Description |
| ------ | ----------- |
| data   | path to data files to supply the data that will be passed into templates. |
| engine | engine to be used for processing templates. Handlebars is the default. |
| ext    | extension to be used for dest files. |

Right aligned columns

| Option | Description |
| ------:| -----------:|
| data   | path to data files to supply the data that will be passed into templates. |
| engine | engine to be used for processing templates. Handlebars is the default. |
| ext    | extension to be used for dest files. |

Mulitmd Tables
|             |          Grouping           ||
First Header  | Second Header | Third Header |
 ------------ | :-----------: | -----------: |
Content       |          *Long Cell*        ||
Content       |   **Cell**    |         Cell |
                                              
New section   |     More      |         Data |
And more      | With an escaped '\\|'       ||


## Links

[link text](http://dev.nodeca.com)

[link with title](http://nodeca.github.io/pica/demo/ "title text!")

Autoconverted link https://github.com/nodeca/pica (enable linkify to see)


## Images

![Minion](https://octodex.github.com/images/minion.png)

::: center
![Minion](https://octodex.github.com/images/minion.png =100x100)
:::

![Stormtroopocat](https://octodex.github.com/images/stormtroopocat.jpg "The Stormtroopocat")

Like links, Images also have a footnote style syntax

![Alt text][id]

With a reference later in the document defining the URL location:

[id]: https://octodex.github.com/images/dojocat.jpg  "The Dojocat"


## Plugins

The killer feature of `markdown-it` is very effective support of
[syntax plugins](https://www.npmjs.org/browse/keyword/markdown-it-plugin).


### [Emojies](https://github.com/markdown-it/markdown-it-emoji)

> Classic markup: :wink: :crush: :cry: :tear: :laughing: :yum:
>
> Shortcuts (emoticons): :-) :-( 8-) ;)

see [how to change output](https://github.com/markdown-it/markdown-it-emoji#change-output) with twemoji.


### [Subscript](https://github.com/markdown-it/markdown-it-sub) / [Superscript](https://github.com/markdown-it/markdown-it-sup)

- 19^th^
- H~2~O


### [ins and del](https://github.com/WenTingZhu/markdown-it-ins-del)

++Inserted text++

~~del text~~

### [inline-comments](https://github.com/jay-hodgson/markdown-it-inline-comments)

```
<!-- comments will be remove -->
```

<!-- comments will be remove -->

### [mark](https://github.com/markdown-it/markdown-it-mark)

==Marked text==




### [Abbreviations](https://github.com/markdown-it/markdown-it-abbr)

This is HTML abbreviation example.

It converts "HTML", but keep intact partial entries like "xxxHTMLyyy" and so on.

*[HTML]: Hyper Text Markup Language

## footnote

Here is a footnote reference,[^1] and another.[^longnote]

[^1]: Here is the footnote.

[^longnote]: Here's one with multiple blocks.

    Subsequent paragraphs are indented to show that they
belong to the previous footnote.

## bilibili video iframe

::: center
[<[ av11525610 ]>]
:::

## viz-gallery


<<<< viz-gallery(title="demo",engine="dot")

```
graph G{
  a--b;
}
```

``` neato 这是 log
graph G{
  a--b;
}
```
<<<<
