## JS onUnload & onBeforeUnload

onunload，onbeforeunload都是在刷新或关闭时调用，可以在<script>脚本中通过 window.onunload来调用。区别在于onbeforeunload在onunload之前执行，它还可 以阻止onunload的执行。

onbeforeunload 是正要去服务器读 取新的页面时调用，此时还没开始读取；而onunload则已经从服务器上读到了需要加载的新的页面，在即将替换掉当前页面时调用。

