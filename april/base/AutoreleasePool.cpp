
#include "base/AutoreleasePool.h"

#include "base/BaseMacros.h"

namespace april {

AutoreleasePool::AutoreleasePool()
    : _name("")
#if defined(COCOS2D_DEBUG) && (COCOS2D_DEBUG > 0)
      ,
      _isClearing(false)
#endif
{
  _managedObjectArray.reserve(150);
  PoolManager::getInstance()->push(this);
}

AutoreleasePool::AutoreleasePool(const std::string& name)
    : _name(name)
#if defined(COCOS2D_DEBUG) && (COCOS2D_DEBUG > 0)
      ,
      _isClearing(false)
#endif
{
  _managedObjectArray.reserve(150);
  PoolManager::getInstance()->push(this);
}

AutoreleasePool::~AutoreleasePool() {
  printf("deallocing AutoreleasePool: %p", this);
  clear();

  PoolManager::getInstance()->pop();
}

void AutoreleasePool::addObject(Ref* object) {
  _managedObjectArray.push_back(object);
}

void AutoreleasePool::clear() {
#if defined(COCOS2D_DEBUG) && (COCOS2D_DEBUG > 0)
  _isClearing = true;
#endif
  std::vector<Ref*> releasings;
  releasings.swap(_managedObjectArray);
  for (const auto& obj : releasings) {
    obj->release();
  }
#if defined(COCOS2D_DEBUG) && (COCOS2D_DEBUG > 0)
  _isClearing = false;
#endif
}

bool AutoreleasePool::contains(Ref* object) const {
  for (const auto& obj : _managedObjectArray) {
    if (obj == object) return true;
  }
  return false;
}

void AutoreleasePool::dump() {
  printf("autorelease pool: %s, number of managed object %d\n", _name.c_str(),
         static_cast<int>(_managedObjectArray.size()));
  printf("%20s%20s%20s", "Object pointer", "Object id", "reference count");
  for (const auto& obj : _managedObjectArray) {
    printf("%20p%20u\n", obj, obj->getReferenceCount());
  }
}

PoolManager* PoolManager::s_singleInstance = nullptr;

PoolManager* PoolManager::getInstance() {
  if (s_singleInstance == nullptr) {
    s_singleInstance = new (std::nothrow) PoolManager();
    // Add the first auto release pool
    new AutoreleasePool("cocos2d autorelease pool");
  }
  return s_singleInstance;
}

void PoolManager::destroyInstance() {
  delete s_singleInstance;
  s_singleInstance = nullptr;
}

PoolManager::PoolManager() { _releasePoolStack.reserve(10); }

PoolManager::~PoolManager() {
  printf("deallocing PoolManager: %p", this);

  while (!_releasePoolStack.empty()) {
    AutoreleasePool* pool = _releasePoolStack.back();

    delete pool;
  }
}

AutoreleasePool* PoolManager::getCurrentPool() const {
  return _releasePoolStack.back();
}

bool PoolManager::isObjectInPools(Ref* obj) const {
  for (const auto& pool : _releasePoolStack) {
    if (pool->contains(obj)) return true;
  }
  return false;
}

void PoolManager::push(AutoreleasePool* pool) {
  _releasePoolStack.push_back(pool);
}

void PoolManager::pop() {
  assert(!_releasePoolStack.empty());
  _releasePoolStack.pop_back();
}

}  // namespace april
