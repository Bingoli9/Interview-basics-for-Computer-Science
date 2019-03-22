## Browser Render Process

<>

1. The browser parse following content
   - HTML/SVG/XHTML -> DOM tree
   - CSS -> CSS tree
   - JavaScript -> operate DOM tree and CSS Rule tree with DOM API and CSSOM API.
2. Browser construct rendering tree with DOM tree and CSS Rule tree
3. Paint the page with Native GUI

### Rendering Process

- Calculate CSS style
- Construct Render Tree
- Layout
- Paint

<>