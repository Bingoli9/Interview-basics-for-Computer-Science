## function call process

### function call
- distribute the function's stack space
- push current state to stack
- push return address to stack
- distribute space for arguments in stack
- distribute space for local variety in stack
- execute the called function

<center>
<img src="https://img-blog.csdn.net/20130911143703578?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvamFja3lzdHVkaW8=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast"/>
<center>

## function return
- pop stack, release the local variety space
- pop stack, release the argument space
- pop stack, get the return address, and jump to the function address
- pop stack, get the state before function call, and restore the state
- release the stack space
<center>
<img src="https://img-blog.csdn.net/20130911145213937?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvamFja3lzdHVkaW8=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast"/>
</center>
