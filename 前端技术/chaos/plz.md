// Regression test for https://crbug.com/877239, simulating the following
// scenario:
//
//  1) http://a.com/empty.html is loaded in a main frame.
//  2) Dynamically by JS, a same-site child frame is added:
//       <iframe 'src=http://a.com/title1.html'/>.
//  3) The initial byte of the response for `title1.html` arrives, causing
//     FrameMsg_CommitNavigation to be sent to the same renderer.
//  4) Just before processing this message, however, `main.html` navigates
//     the iframe to http://baz.com/title2.html, which results in mojom::Frame::
//     BeginNavigation being called on the RenderFrameHost.
//  5) Suppose that immediately afterwards, `main.html` enters a busy-loop.
//  6) The cross site navigation in the child frame starts, the first response
//     byte arrives quickly, and thus the navigation commits quickly.
//  6.1) FrameTreeNode::has_committed_real_load is set to true for the child.
//  6.2) The same-site RenderFrame in the child FrameTreeNode is swapped out,
//       i.e. FrameMsg_SwapOut is sent.
//  7) The renderer for site instance `a.com` exits from the busy loop,
//     and starts processing messages in order:
//  7.1) The first being processed is FrameMsg_CommitNavigation, so a
//       provisional load is created and immediately committed to
//       http://a.com/title1.html.
//  7.2) Because at the time the same-site child RenderFrame was created,
//       there had been no real load committed in the child frame, and because
//       the navigation from the initial empty document to the first real
//       document was same-origin, the global object is reused and the
//       RemoteInterfaceProvider of the RenderFrame is not rebound.
//  7.3) The obsoleted load in the same-site child frame commits, calling
//       mojom::Frame::DidCommitProvisionalLoad, however, with
//       |interface_provider_request| being null.
//  8) RenderFrameHostImpl::DidCommitProvisionalLoad sees that a real load was
//     already committed in the frame, but |interface_provider_request| is
//     missing. However, it also sees that the frame was waiting for a swap-out
//     ACK, so ignores the commit, and does not kill the renderer process.
//
// In the simulation of this scenario, we simulate (5) not by delaying
// renderer-side processing of the CommmitNavigation message, but by delaying
// browser-side processing of the response to it, of DidCommitProvisionalLoad.
