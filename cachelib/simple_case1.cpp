#include <cachelib/allocator/CacheAllocator.h>
#include <iostream>
#include <string>
#include <memory>

using Cache = facebook::cachelib::LruAllocator; // using LRU as caching strategy
using CacheConfig = facebook:cachelib::LruAllocator::Config;

int main() {
    // create a CacheAllocator config
    CacheConfig config;
    config.setCacheSize(10 * 1024 * 1024); // set cache size 10 MB
    config.setAccessConfig({10, 1});
    // set persistent storage
    config.enableCachePersistence("/tmp/cachelib_persistence");  
    // set visiting depth: 10 LRU list, depth 1
    Cache cache{config};

    // Attach to a new cache
    cache.attach();

    // try to recover from the persistent storage
    if (!cache.recover()) {
        std::cout << "No existing cache found, creating a new one." << std::endl;
    } else {
        std::cout << "Recover from persistent storage!" << std::endl;
    }

    // insert kv to cache
    // key: hello, value: world, size = 5 bytes for world
    // 512 is the space we set for this kv. we can change accordingly
    auto handle = cache.allocate(512, "Hello", "World", 5);
    cache.insertorReplace(handle); // insert to cache

    // obatin and output caching value
    auto result = cache.find("Hello");
    if (result) {
        std::cout << "Cached value for 'Hello': " << result->getMemory() << std::endl;

    } else {
        std::cout << "'Hello' not found in cache" << std::endl;
    }
    cache.persist(); // put to persistency
    // destroy cache
    cache.detach();
    return 0;
}