## memory prefetch

vtune分析程序性能瓶颈，发现一些内存访问的地方竟然成了cpu热点。

大数组非连续位置访问的引起，因为像这样局部性很差的内存访问逻辑，对cache是很不友好的。

x86的cpu提供了prefetch系列指令，用于将指定地址内存预取到cahce。如“prefetch0(%rax)将$rax所保存的值为地址的内存所在cache line载入每一级cache。在适当位置加了prefetch之后，程序里相应的cpu热点果然得以消除，程序性能得到提升.









