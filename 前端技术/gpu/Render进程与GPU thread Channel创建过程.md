## Render进程与GPU thread Channel创建过程

Render thread需要通过GPU来渲染网页时候，需要向Browser请求与GPU thread建立GPU通道，需要GPU的命令以后通过建立起来的GPU channel来通信。

我们忽略GPU Thread创建过程，重点看render thread与GPU thread建联gpu channel过程。大致过程如下：

- brwoser thread：pre-establish gpu channel
- render thread： establish gpu channel
  - 如果之前的pre-establish gpu channel成功，则直接返回通道套接字、gpu info等
  - 如果之前的pre-establish gpu channel失败，等待之前的gpu建联返回结果，结果可能是失败或者成功
    - 成功，则返回套接字
    - 失败，重新建联







