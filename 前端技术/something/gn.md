## gn

Build and Compile tool.

#### make build

```C++
gn gen out/my_build
```

#### pass compile arguments

```C++
gn args out/my_build
```

And then, we need to set the arguments' value

```C++
is_component_build = true
is_debug = true
```

#### cross-compiling to a target OS or architecture

```C++
gn args out/my_build
```

```c==
target_os = "android"
target_cpu = "arm"
target_cpu = "x64"
```



Chromium uses Ninja as its main build tool along with a tool called GN generate .ninja files. You can create any number of build directories with different configurations .

