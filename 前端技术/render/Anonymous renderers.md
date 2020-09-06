## Anonymous renderers

render object tree 遵守2个准则：

- 在文档流中的块状元素的子节点，要么都是块状元素，要么都是行内元素。
- 在文档流中的行内元素的子节点，只能都是行内元素。

anonymounse renderers（匿名的render object 节点）就是用于处理不遵守这两种规则的代码的，如果出现不符合这两个准则的情况，比如说下面：

1. 若在块状元素里面同时出现了块状元素和行内元素：

```
<div>
  Some text
  <div>
    Some more text
  </div>
</div>
```

上面的代码中，最外层的div节点有两个子节点，第一个子节点是行内元素，第二个子节点是块状元素。render object tree 中会构建一个anonymounse renderer去包裹 text 节点，因此上面的代码变成了下面的：

```
<div>
  <anonymous block>
    Some text
  </anonymous block>
  <div>
   Some more text
  </div>
</div>
```

