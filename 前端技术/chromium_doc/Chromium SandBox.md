## Chromium SandBox

sandbox本身就意味着程序要使用多进程架构。做到安全的方法就是让可能不安全的代码在被剥夺了部分权限的sandboxed进程（非主进程）上跑，原则上在sandboxed进程中能利用的资源只有CPU和内存。



#### 特点

- Sandbox目录下的代码是独立的（依赖base目录少部分文件），可以供其它项目使用
- 利用操作系统提供的特性来控制进程的权限，如不允许读写文件系统（框架有提供API可以开放指定文件的读写权限）。Linux下有两个级别的sandbox，[Setuid sandbox](https://code.google.com/p/chromium/wiki/LinuxSandboxing#The_setuid_sandbox)（限制大部分资源的访问权限）和[Seccomp-BPF](https://code.google.com/p/chromium/wiki/LinuxSandboxing#The_seccomp-bpf_sandbox)（限制影响到系统内核的资源访问）。
- sandbox进程可以通过IPC跟外部通信。
- Chromium中对Renderer进程进行sandbox，是期望对WebKit输入数据就得到输出渲染好的图，过程中的网络和文件读写操作通过IPC由Browser进程处理。部分插件也运行在独立的sandboxed进程，它崩溃掉并不影响浏览器进程，如Flash

#### 使用方法

```C++
bool InitializeSandbox(scoped_ptr<sandbox::SandboxBPFPolicy> policy) {
  return SandboxSeccompBPF::StartSandboxWithExternalPolicy(policy.Pass());
}
```

