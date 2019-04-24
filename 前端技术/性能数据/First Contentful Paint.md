## First Contentful Paint

从navigation time 到浏览器第一次渲染DOM数据时候。FCP反馈页面正在加载。



#### Recommendations

- HTTP Cache来加速重复请求
- 优化text类型的资源，具体在编码优化和传输大小上
- 优化JavaScript的启动。减少Javascript的负载，具体方法是tree shaking或者code splitting上。目标是减少javascript的加载。
- Render-Blocking CSS 和 Loading Third-Party JavaScript