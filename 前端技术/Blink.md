## Blink

Blink: Web platform tender engine

- Define the HTML standard
- can run the javaScript
- Request network resource through network layer
- Construct DOM tree
- calculate the style and composing
- Paint the webpage

<>

### Multi-process architecture

One browser process and multiple isolate render process.

The communication between browser process and render process is Mojo technique.

<>

### Threads in Blink

Blink has one main thread and N worker threads and some internal threads

Nearly almost main activities will run in main thread, including all javascript calling, DOM, CSS and so on.

For communication between threads, it's suggested that use PostTask API to communicate.

<>

### Directory Structure

//third_party/blink/ 

- Platform/  Low level function of Blink, including geometry and graphics
- Core/ and modules/  Function to design web platform peculiarity
- Controller/ capsulate APIs in core and modules, and offer high level library.

### WTF

The base library of Blink. Locating in platform/wrf/, and perform high efficiency function and container for Blink.



### Memory Manage

- PartitionAlloc
- Olipan (Blink GC)
- malloc



### Task Schedule

To improve the render engine response, it's suggested to perform blink tasks asynchronously. Synchronous IPC/Mojo or other time-consuming task should be avoid.



### Page/Frame/Document/DOMWindow

Conception: Main object in Blink engine

- Page represents the label page in browser. Every render process has multiple label
- Frame represents the frame in one web page. One Page can include multiple frames and construct the frame tree.
- DOMWindow is the window object in javascript codes. One frame has only one DOMWindow
- Document is the window.document object in javascript codes



### OOPIF

Site isolation can guarantee the security of webPage. 

One render process only has one site.



### Blink Render Process

<>



