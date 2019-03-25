## Chromium Module Partition Way

##### WebKit 

Namespace: webcore

WebPage render engine. It's defined in namespace WebCore

##### WebKit glue

Namespace: blink

WebKit embedder, used for transfer the Webkit type to Chromium type, and it's defined in namespace blink. Chromium does not directly access the WebKit, but through WEbKit glue api to indirectly access it.

##### Render/Render host

Namespace: content

Render run in Render process

Render Host run in Browser process

##### WebContents

Namespace: content

Rendering a HTML webpage within multi-process

##### Browser

Represent a browser window. 

It includes multiple WebContent objects

##### Tab Helpers

Attach to WebContent to add extra function, such as InfoBar



### Content Layer

Content layer is the kernel module of Chromium, and it implements the multi-process architect. 

The outside API the content layer offers mainly is WebContents. The browser render the HTML webpage into an area through the WebContents api.

- RenderView or RenderWidget

  RenderView renders the view to exhibit the webcontent

  RenderWidget renders the widget that can receive input

  In browser process: RenderViewHostImpl and RenderWidgetImpl

  In render process: RenderViewImpl and RenderWidgetImpl

- RenderFrame

  Out-of-Process frames 

### WebKit Layer

- WebView and WebWidget

- WebFrame

  Out-of-Process iframes











