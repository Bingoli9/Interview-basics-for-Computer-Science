## HTTP Cache

Http Cache receives the request and load the data from fast cache or from network. As a part of the network stack, the HTTP cache is used in browser process.  

The Blink cache is in render process.

HttpCache::Transaction is used for most of URLRequestJob transaction



Each config file or each isolate application has one HttpCache instance. In fact, config file includes two cache instance: one is used for common request, the other one is used for media request

HttpCache is responsible for providing network request instance from disk_cache::Backend or network.  If HttpCache is destroyed, the disk backend and network layer will be destroyed

#### HTTP Cache Operation

- Create and manage disk cache backend
- Create HttpCache::Transactions
- Create and manage ActivityEntries to interact with disk backend
- ActivityEntry is a small object, representing disk cache entry and transaction that can access it
- Cache lock; One Writer and multiple reader. Cache lock means that we can get the same resource without consume extra bandwidth. But on other hand, there's force request wait until pre-request finish download(write) and finally read the resource, which it's troubleosme for long-term request.

Most HTTP cache is implement by cache transaction

#### Sparse Entries

Sparse Entries is universally used by media resource (thinking big media or music file). General thought is store part of resource and return from disk.

