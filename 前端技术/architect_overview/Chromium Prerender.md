## Chromium Prerender

#### Overview

Prerender is triggered by \<link real = "prerender" /\> . Prerender will create hidden page and this page will load all resource backend and run Javascript. If user navigate to this page, the hidden page will exchange to current tab.

<center>
  <img src = "https://upload-images.jianshu.io/upload_images/3768281-928b84a5c6db684a.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/697/format/webp" />
</center>

#### The problem

- Resource conflict reduce
- Handle dynamic media
- Cancel page
- Minimize service point
- Share the local store variation



#### Prerender Use situation

- Call the TabContents::NavigateToPending entry. For example, user input the new URL and accesses it.
- Call the TabContents::DidNavigate and users click the url link.

In those situation, it will check the PrerenderManager in current config file and check the matching with target URL



#### Visible API

Add the visible API to expose current webPage visible state, such as pre-visible, hidden and  visible.



#### Reduce resource conflict

Because of resource conflict, prerender will cause negative influence to other page loading. 

To minimize  network resource conflict between prerender and current page render, it will minimize the priority of prerendeFr to get the network resource

To handle CPU usage ratio, it will reduce the priority of rendering of page which includes prerender page.

To handle memory usage ratio, it will limit the number of prerender page below 3.



Problem:

Not handle GPU usage ratio yet

Not handle disk cache usage raito yet

#### Handle Dynamic Media

- Package delay

  If the page is in prerender state, the package instantiation will delay until the page is triggered

- HTML5 media elements

  The media play delay

#### Share the local storage variation

In idea situation, before user trigger the page, prerender's variation is indifferent with other tab, but other tab's variation can be detected by prerender page.

#### Minimize the service side effect

Only if use **GET** to search top page will trigger prerender.