## Android WebView resource Load

<>

The green block represents browser process, and the blue block represents render process. 

The whole process show as follow:

- FrameWork layer -> content layer
- Through IPC, dispatch tasks to Webkit layer
- Return from Webkit and back to content layer
- content layer -> net layer, request network resource 

### Key StandPoint 

- Call NavigationControllerAndroid::LoadUrl in C++ layer through JNI nativeLoadUrl
- Browser process send IPC message to render process
- Factory Design Mode to create corresponding resource loader.
- Memory Cache for RawResource, and then call RawResource::load to download the network resource.
- Factory Design Mode for RawResourceFactory, the factory is used for creating RawResource object, and then store the object in memoryCache
- Call WebURLLoaderImpl::loadAsynchronously to asynchronously load thr URL resource through the member function in blink engine
- In ResourceDispatcher::StartAsync, send the IPC message to browser processer and let the Browser process to load URL resource. The receiver is ResourceDispatcherHostImpl object, finally will handle by ResourceDispatcherHostImpl::OnrequestResource
- The final step is ResourceLoader::StartRequestInternal, the deeper call is in network stack
- When load the data successfully, it will read the data, malloc shared memory between process though binding mechanism.