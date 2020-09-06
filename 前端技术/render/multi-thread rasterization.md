## multi-thread rasterization

### Problem
1. rasterization works in busy render thread  
2. if javascript change the render tree, we have some 'newly exposed tiles' that the compositor thread    
needs generate to avoid chekcboard and finally generate new render tree   
    - Draw the new tiles with the new render tree, and redraw old tiles with new render tree  

### Solution
The idea is to only capture a display list of the webkit rendering tree on the  maint thread. Then, do   
rasterization on the impl thread.  


Solution
Capture a display list of the webkit rendering tree on the main thread. Then, do rasterization on the impl thread, which is more responsive.  

```c++
------------                     
MainThread  | Web content ==> PictureLayer ==> PicturePile(trace invalidations in SKRegions)  ==commit==> PictureLayerImpl(see below)  
------------                  
------------                
ImplThread  | PictureLayerImpl ==manage=>(1:n) PictureLayerTiling ==AddTo==> rasterization queue  
------------  
```

A Tiling itself takes the layers entire size, not just the visible part and break it up into Tiles.    

Reference:
https://www.chromium.org/developers/design-documents/impl-side-painting  

 