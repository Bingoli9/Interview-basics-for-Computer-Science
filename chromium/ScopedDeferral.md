## ScopedDeferral
在栈上分配的用于实现简单状态机的helper class  

调用构造函数时保存宿主类的状态和宿主类指针,调用block方法  

当ScopedDeferral类超出其作用范围,判断其析构函数  

在ScopedDeferral析构函数内判断宿主类当前状态来决定是否步入下一个状态(调用resume函数)  

resume函数是状态机实现类  


```C++
// Helper class.  Sets the stage of a ResourceLoader to DEFERRED_SYNC on
// construction, and on destruction does one of the following:
// 1) If the ResourceLoader has a deferred stage of DEFERRED_NONE, sets the
// ResourceLoader's stage to the stage specified on construction and resumes it.
// 2) If the ResourceLoader still has a deferred stage of DEFERRED_SYNC, sets
// the ResourceLoader's stage to the stage specified on construction.  The
// ResourceLoader will be resumed at some point in the future.


class ResourceLoader::ScopedDeferral {
 public:
  ScopedDeferral(ResourceLoader* resource_loader,
                 ResourceLoader::DeferredStage deferred_stage)
      : resource_loader_(resource_loader), deferred_stage_(deferred_stage) {
    resource_loader_->deferred_stage_ = DEFERRED_SYNC;
  }

  ~ScopedDeferral() {
    DeferredStage old_deferred_stage = resource_loader_->deferred_stage_;
    // On destruction, either the stage is still DEFERRED_SYNC, or Resume() was
    // called once, and it advanced to DEFERRED_NONE.
    DCHECK(old_deferred_stage == DEFERRED_NONE ||
           old_deferred_stage == DEFERRED_SYNC)
        << old_deferred_stage;
    resource_loader_->deferred_stage_ = deferred_stage_;
    // If Resume() was called, it just advanced the state without doing
    // anything. Go ahead and resume the request now.
    if (old_deferred_stage == DEFERRED_NONE)
      resource_loader_->Resume(false /* called_from_resource_controller */);
  }

  ```


```C++
void ResourceLoader::StartRequest() {
TRACE_EVENT_WITH_FLOW0("loading", "ResourceLoader::StartRequest", this,
TRACE_EVENT_FLAG_FLOW_OUT);

ScopedDeferral scoped_deferral(this, DEFERRED_START);
handler_->OnWillStart(request_->url(), base::MakeUnique<Controller>(this));
}
```


```C++
void ResourceLoader::Resume(bool called_from_resource_controller) {
DCHECK(!is_transferring_);

DeferredStage stage = deferred_stage_;
deferred_stage_ = DEFERRED_NONE;
switch (stage) {
case DEFERRED_NONE:
NOTREACHED();
break;
case DEFERRED_SYNC:
DCHECK(called_from_resource_controller);
// Request will be resumed when the stack unwinds.
break;
case DEFERRED_START:
// URLRequest::Start completes asynchronously, so starting the request now
// won't result in synchronously calling into a ResourceHandler, if this
// was called from Resume().
StartRequestInternal();
break;
case DEFERRED_REDIRECT:
// URLRequest::Start completes asynchronously, so starting the request now
// won't result in synchronously calling into a ResourceHandler, if this
// was called from Resume().
FollowDeferredRedirectInternal();
break;
case DEFERRED_ON_WILL_READ:
// Always post a task, as synchronous resumes don't go through this
// method.
base::ThreadTaskRunnerHandle::Get()->PostTask(
FROM_HERE, base::BindOnce(&ResourceLoader::ReadMore,
weak_ptr_factory_.GetWeakPtr(),
false /* handle_result_asynchronously */));
break;
case DEFERRED_READ:
if (called_from_resource_controller) {
// TODO(mmenke):  Call PrepareToReadMore instead?  Strange that this is
// the only case which calls different methods, depending on the path.
// ResumeReading does check for cancellation. Should other paths do that
// as well?
base::ThreadTaskRunnerHandle::Get()->PostTask(
FROM_HERE, base::BindOnce(&ResourceLoader::ResumeReading,
weak_ptr_factory_.GetWeakPtr()));
} else {
// If this was called as a result of a handler succeeding synchronously,
// force the result of the next read to be handled asynchronously, to
// avoid blocking the IO thread.
PrepareToReadMore(true /* handle_result_asynchronously */);
}
break;
case DEFERRED_RESPONSE_COMPLETE:
if (called_from_resource_controller) {
base::ThreadTaskRunnerHandle::Get()->PostTask(
FROM_HERE, base::BindOnce(&ResourceLoader::ResponseCompleted,
weak_ptr_factory_.GetWeakPtr()));
} else {
ResponseCompleted();
}
break;
case DEFERRED_FINISH:
if (called_from_resource_controller) {
// Delay self-destruction since we don't know how we were reached.
base::ThreadTaskRunnerHandle::Get()->PostTask(
FROM_HERE, base::BindOnce(&ResourceLoader::CallDidFinishLoading,
weak_ptr_factory_.GetWeakPtr()));
} else {
CallDidFinishLoading();
}
break;
}
}

```
