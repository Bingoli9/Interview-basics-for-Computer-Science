## Google test开源测试框架

### gtest资料
1. gtest代码托管：https://github.com/google/googletest
2. 使用gtest构建测试用例指导：https://github.com/google/googletest/tree/master/googletest
3. gtest英文文档： https://github.com/google/googletest/blob/master/googletest/docs/Documentation.md
4. gtest英文译文：https://www.cnblogs.com/jycboy/p/6057677.html#autoid-9-0-0
5. gtest中文博客： 玩转Google开源C++单元测试框架Google Test系列。
6. gmock使用文档：https://github.com/google/googletest/blob/master/googlemock/docs/Documentation.md

gtest项目中包含了两个框架，一个gtest测试框架，一个是gmock框架。gtest类似于java里面的junit，用来做单元测试的；gmock主要是用来mock待测试模块依赖的一些对象，帮助你在测试中去除不必要的依赖，类似与java的jMock和EasyMock。
