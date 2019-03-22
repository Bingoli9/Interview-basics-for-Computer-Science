## Chromium Source Code

- V8/js

- Syntax parse 

  - src/parsing
  - Src/ast
  - src/objects

- Third_patry

  - Blink -> render -> core (important, css dom events frame html inputj layout timing)

- IDL

  Layout, dom, bom. Calculation.

- Content

  - browser/render_host. Browser/frame_host
  - Public/common

  Frame_host in browser directory defines render \_frame_message_xxx handler cluster, iPc communication relies on those handlers

- Net