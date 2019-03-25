## Chromium Source Code Directory 

### High-level Overview

Chromium is separated into two parts: the browser and the renderer(which includes Blink). The browser is the main process and represents all the UI and I/O. The renderer is the per-tab sub-process that is driven by the browser. It embeds Blink to do layout and rendering

- Android_view: Provides a facade over src/content suitable for integration into the android platform.
- Apps: Chrme packaged apps
- Base: Common code shared between all sub-projects. 
- breakpad: Google's open source crash reporting project
- Build: Build-related configuration shared by all projects
- Cc: The Chromium compositor implementation
- Chrome: The Chromium browser
- Chrome/test/data: Data files for running certain tests
- Components: directory for components that have the Content Module as the upppermost layer they depend on
- Content: The core code needed for a multi-process sandboxed browser.
- Device: Cross-platform abstractions of common low-level hardware APIs
- net: The network library developed for chromium. This can be used separately  from Chromium when running our simple test_shell in the webkit repository.
- Sandbox: The sandbox project which tries to prevent a hacked renderer from modifying the system
- Skia + third_party/skia: Google's Skia graphics library
- Sql: wrap around sqlite
- Testing: Contains Google's open-sourced Test code which used for unit testing
- Third-party: 200+ small and large "external" libraries such as image decoders, compression libraries and the web engine Blink.
- tools
- Ui/gfx: Shared graphics classes
- ui/views A simple framework for doing UI development, providing rendering, layout and event handling.
- Url: Google's open source URL parsing and canonicalization library
- V8: The V8 Javascript library

<center>
  <img src = "http://dev.chromium.org/_/rsrc/1308680092356/developers/how-tos/getting-around-the-chrome-source-code/Content.png"/>
</center>



### Directory tree under "content/"

- Browser: The backend for the application which handles all I/O and communication with the child processes. This talks to the renderer to manage web pages
- Common: Files shared between the multiple processes.
- Gpu: Code for the GPU process, which is used for 3D composition and 3D APIs
- Plugin: Code for running browser plugins in other processes
- Ppapi_plugin: Code for the Peppper plugin processes
- Renderer: Code for the subprocess in each tab
- Utility: Code for running random operations in a sandboxed process. The browser process uses it when it wants to run an operation on untrusted data
- Worker: Code for running HTML5 Web Worker

### Directory tree under "chrome/"

- App:the  "app" is the most basic level of the program. It is run on startup, and dispatches to either the browser or render code depending on which capabilities the current processes is in. It contains the projects for chrome.exe and chrome.dll.
- browser: The frontend including the main window, UI, and the backend for the application whch handles all I/O and storage. This talks to the renderer to manage web pages
- common: Files shared between the browsers and the renderer that is specific to the Chrome module
- installer: Source files and projects for making the installer
- renderer: Chrome specific code that runs in the renderer process. This adds Chrome features like autofill, translate etc to the content module
- test
- Third_party: Third party libraries that are specific to Chromium. Some other third party libraries are in the top-level third-party library
- tools
  - Build: Tools and random stuff related to building
    - Builbot: BuildBot configuration. BuildBot manages out automated build system.
    - Win: Windows build stuff, including some .vsprops files used for project
  - Memory: Tools for memory stuff.
  - Perf/dashboard: Code for converting performance ops into data and graphs
  - Profiles: Generator for random history data. 