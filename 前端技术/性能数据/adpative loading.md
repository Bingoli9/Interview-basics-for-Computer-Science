## adaptive loading

We do not need to give the same user experience in the   
web app. There are some reasons for this as follows.  
Most importantly, low level grade mobile can be very hard to display   
the web caused by vast calculation, pool netowrk, or other factors.  
If we offer those  devices high level web page, user may hardly to see the page.  
That's why we should have adaptive loading.  


There are three important factor we need to consider in low level devices: memory, cpu and network;

#### memory
- try use less memory 
- optimize memory-high-loaiding resource
- switch low level animation


#### cpu
- limit cpu-high-loading javascript
- avoid loading vast of cpu widgets
- limit cpu-high-loading code 


#### network
- recognize poor network
- adjust data transport
- reduce network bandwidth utilization

### pratices from baidu
- Adaptive media loading
- Network-aware resource loading
- Data-Saver-aware resource loading
- Memory-aware resource loading
- Adaptive Code-Spliting
- network-aware code Spliting



### how to classfy devices level
- User Agent String
- Cpu benchmark



