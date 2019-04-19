## Android WebView 实现

<center>
  @<img src = "76db5c9864c4545bc56c48901d31a0fd_e73179d962cd2b19a28848d422498cec_img"/>
</center>



WebViewProvider接口，由实现者决定使用哪种引擎

在ContentAPI之上，Chromium的WebView实现封装新的类AwContents，该类主要基于ContentViewCore类的实现。

<center>
  @<img src = "76db5c9864c4545bc56c48901d31a0fd_87e28e38e47cbec542e010d457182385_img"/>
</center>

WebViewChromium作为WebView的具体实现，以来Chromium项目的AwContets模块

<center>
  @<img src = "76db5c9864c4545bc56c48901d31a0fd_8d9dfbb27e8179f6fea95581d2188449_img"/>
</center>

AwContents基于Content之上，专门针对Android WebView需求进行封装