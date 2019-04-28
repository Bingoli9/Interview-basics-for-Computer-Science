## Head-of_Line Blocking

线头阻塞

队列的首个packet由于它的目的端口正忙而被延迟转发，导致后面的packers被blocked

原因：如果1个switch，使用FIFO队列，就会出现HOL Blocking

优化方案

- 使用Window，即队列前面的n个packer而不是一个packet参与输出端口的竞争，这样会降低blocking的概率。然而，如果这n个包的目的地址相同，也会带来blocking
- 采用virtual input/output queue，每次从n个input队列中选择一个队列，然后转发这个队列的首个packet，这样每个队列后面的packet被bloked概率大大降低