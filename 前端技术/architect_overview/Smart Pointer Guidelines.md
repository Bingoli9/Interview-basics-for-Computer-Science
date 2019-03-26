## Smart Pointer Guidelines

##### unique_ptr\<> & scoped_refptr\<>

The two common smart pointers in Chromium are std::unique_ptr\<> and scoped_refptr\<>. The former is used for single-owned objects, while the latter is used for reference-counted objects.



##### WeakPtr\<>

It's not actually a smart pointer; it functions like a pointer type, but jrather than being used to automatically free objects, it's used to track wherther an object owned elsewhere is still alive. When the object is destroyed, the WeakPtr\<> will be automatically set to null, so you can see that it's no longer alive. (You still need to test for null before dereferencing — a blind dereference of a null WeakPtr<>) is the equivalent of dereferencing null, rather than a no-op).



#### When do we use each smart pointer?

- Single-owned objects - use std::unique_ptr<>
- Non-owned objects - use raw pointers or WeakPtr<>. Note that WeakPtr<>s must only be dereferenced on the same thread where they were created(usually by a WeakPtrFactory<>), and if you need to take some action immediately before or after an object is destroyed, you'd likely be better-served with some sort of callback or notification instead of a `WeakPtr<>`.
- Ref-counted objects -  use `scoped_refptr<>`, but better yet, rethink your design. Reference-counted objects make it difficult to understand ownership and destruction order, especially when multiple threads are involved. There is almost always another way to design your object hierarchy to avoid refcounting. Avoiding refcounting in multithreaded situations is usually easier if you restrict each class to operating on just one thread, and use `PostTask()`and the like to proxy calls to the correct thread. 

