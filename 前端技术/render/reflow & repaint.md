### reflow & repaint

#### 渲染过程

<img1>

<img2>

- 解析HTML树，生成DOM树
- 解析CSS，生成CSSOM树
- dom树和cssom树结合起来，计算出dom树每个节点的样式，获得render object tre
- Layout：获取render object tree每个节点在viewport可视区域位置和占用大小
- Paint：得到每个节点的绘制指令
- Display：在屏幕上展示

#### 什么是reflow
重新layout过程，如果render tree中的一部分(或全部) 因为元素规模尺寸、布局，隐藏等改变而需要重新构建，计算render object几何位置过程。

理解什么是reflow之后，我们可以reflow归因：

- DOM增删
- DOM 大小变化，包括内容变化所影响的变化，还有就是无论是`margin`，`padding`还是`border`，`top`等等
- DOM 位置变化
- resize 事件，浏览器窗口尺寸变化也会触发

#### 什么是repaint
repaint 就是在不影响排版的情况下对这个元素重新绘制的过程。例如改变一个元素的背景颜色、字体颜色等。

#### 渲染流程类型



<center>
  <img src="123"/>
</center>



<center>
<img src="123"/>
</center>



<center>
<img src="123"/>
</center>



reflow对应的渲染流程类型一， 可以看到发生了reflow就一定会重绘和合成。

repaint对应的渲染流程类型二，少了reflow流程

引起页面更新最好的性能是仅仅引起合成步骤，渲染流程类型三是性能最优的

#### 优化reflow和repaint

##### 最小化reflow和repaint

```
const el = document.getElementById('test');
el.style.padding = '5px';
el.style.borderLeft = '1px';
el.style.borderRight = '2px';
```

TO

```
const el = document.getElementById('test');
el.style.cssText += 'border-left: 1px; border-right: 2px; padding: 5px;';
```

##### 批量修改DOM

对dom元素修改的时候让dom节点脱离文档流，修改完毕之后才替换

脱离文档流方式

- 隐藏元素：display:none
- 使用document fragment
- 将原始元素拷贝到一个脱离文档的节点中

##### 避免触发同步布局事件

由于reflow与repaint是个耗时操作，因此chromium浏览器会先保存所有引起reflow和repaint的任务，当到达一定阈值或者一段时间才清空pending的修改，一次性reflow和repaint来减少耗时任务的频率

但当获取布局信息时候，会清空pending的任务，强制reflow和repaint，比如以下方法获取布局信息

```
offsetTop、offsetLeft、offsetWidth、offsetHeight
scrollTop、scrollLeft、scrollWidth、scrollHeight
clientTop、clientLeft、clientWidth、clientHeight
getComputedStyle()
getBoundingClientRect
```

**实验下**

TODO：



#### 独立图层

chromium会将绘制的网页分为多个图层（也就是compositor layer), 每个图层都有自己的绘图上下文，并且会开启硬件加速，有利于性能提升。对于需要多次repaint的元素，我们可以把它提升为单独图层，独立于普通文档流，改动后可以避免整个页面重绘制。下面列举一些特点：

- 合成层的位图，会交给GPU合成，比CPU处理要快
- 当需要repaint，只需要repaint本身，不会影响到其他层
- 对于transform和opacity效果，不会触发layout和paint，也就是渲染流程类型三，提升性能

**生成独立图层的方法**

- `position: fixed`，我们常用于当`app-header`和`app-bar`等等
- video`, `iframe等
- will-change`这个属性就是告诉浏览器将会发生什么，请帮我设成独立图层`
- `3D 或者硬件加速的`2D Canvas
- 3D`transform`



```
function appendDataToElement(appendToElement, data) {
    let li;
    for (let i = 0; i < data.length; i++) {
        li = document.createElement('li');
        li.textContent = 'text';
        appendToElement.appendChild(li);
    }
}

const ul = document.getElementById('list');
const fragment = document.createDocumentFragment();
appendDataToElement(fragment, data);
ul.appendChild(fragment);
```









