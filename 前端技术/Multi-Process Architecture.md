## Multi-Process Architecture 

<>



#### Render Process

Each rendering process has global RenderProcess object to communicate with browser process and matin global state.   

Browser process maintain correspond RenderProcessHost object to manage the communication and the browser state of render process.

#### RenderView

Each RenderView represents one content tab, and each RenderView has one RenderViewHost to manage the context.

RenderProcessHost manages multiple RenderViewHost.

#### kernel module and interface

In render process:

- Using RenderProcessHost to handle IPC

In browser process:

- Browser object represents the top browser window
- RenderProcessHost is communication channel between Render Process and Browser Process
- RenderWidgetHost handles the input and painting request from RenderWidget

#### Shared Render Process

Usually, it will create new Render process for new window or tab. 

Sometimes we can share the render processs.



#### Detect the crash or unusual Render



#### SandBox Render

To improve the security of render process or browser process



