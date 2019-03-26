## Out-of-Process iframes (OOPIFs)

OOPIF allows a child frame of a page to be rendered by a different process than its parent frame. OOPIFs were motivated by security goals like the **Site Isolation** project.



### Architecture Overview

#### Frame Representation

Much of the logic in the content module has moved from being tab-specific to frame-specific, since each frame may be rendered in different processes over its lifttime.

#### Proxies

Documents that have referencees to each other(e.g., from the frame tree, window.opener, or named windows) can interact via JavaScript. When the documents are same-site, they must live in the same process to allow synchronous access. When they are cross-site, they can live in differnet processes but need a way to route messages to each other, for calls like postMessage. Same-site documents with references to each other are grouped together using the SiteInstance class

<center>
  <img src = "https://www.chromium.org/_/rsrc/1366228626421/developers/design-documents/oop-iframes/Cross%20Process%20Tabs%20%28for%20posting%29.png?height=329&width=400"/>
</center>

To support cross-process interactions like postMessage on a document's DOMWindow, Chromium must keep a proxy for the DOMWindow in each of the other processes that can reach it.  As shown in the diagram at right, this allows a document from site A to find a proxy in its own process for a DOMWindow that is currently active on site B.  The proxy can then forward the postMessage call to the browser and then to the correct document in the process for site B.

OOPIFs require each renderer process to keep track of proxy DOMWindows for all reachable frames, both main frames and subframes.

#### Browser Process

Chromium keeps track of the full frame tree for each tab in the browser process.  WebContents hosts a tree of FrameTreeNode objects, mirroring the frame tree of the current page.  Each FrameTreeNode contains frame-specific information (e.g., the frame's name, origin, etc).  Its RenderFrameHostManager is responsible for cross-process navigations in the frame, and it supports replicating state and routing messages from proxies in other processes to the active frame.

#### Renderer Process

In each renderer process, Chromium tracks of proxy DOMWindows for each reachable frame, allowing JavaScript code to find frames and send messages to them.  We try to minimize the overhead for each of the proxy DOMWindows by not having a document, widget, or full V8 context for them.

Frame-specific logic in the content module's RenderView and RenderViewHost classes has moved into routable RenderFrame and RenderFrameHost classes.  We have one full RenderFrame (in some process) for every frame in a page, and we have a corresponding but slimmed down RenderFrameProxy as a placeholder in the other processes that can reference it.  These proxies are shown with dashed lines in the diagram below, which depicts one BrowsingInstance (i.e., group of related windows) with two tabs, containing two subframes each.

<center>
  <img src = "https://www.chromium.org/_/rsrc/1445448026552/developers/design-documents/oop-iframes/Frame%20Trees%202015%20%28for%20posting%29.png"/>
</center>



<center>
  <img src = "https://www.chromium.org/_/rsrc/1445448006392/developers/design-documents/oop-iframes/Frame%20DOMWindow%20Document%202015%20%28for%20posting%29.png"/>
</center>

RemoteDOMWindow classes for the proxies that live in other renderer processes.  The remote classes have very little state: generally only what is needed to service synchronous operations.  A RemoteDOMWindow does not have a Document object or a widget.
LocalFrame and RemoteFrame inherit from the Frame interface.  While downcasts from Frame to LocalFrame are possible, this will likely cause bugs with OOPIFs unless extra care is taken.  LocalFrame corresponds to WebLocalFrame (in the public API) and content::RenderFrame, while RemoteFrame corresponds to WebRemoteFrame and content::RenderFrameProxy.



Blink has the ability to swap any frame between the local and remote versions.  (This replaces the old "swapped out RenderViewHost" implementation that Chromium used for cross-process navigations.)

#### Rendering

To render an iframe in a different process than its parent frame, the browser process passes information back and forth between the renderer processes and helps the GPU process composite the images together in the correct sizes and locations. ß

