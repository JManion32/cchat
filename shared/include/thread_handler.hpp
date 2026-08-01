#pragma once

#include <thread>

typedef std::thread ThreadType;

template <typename Func, typename... Args>
ThreadType thread_create(Func &&func, Args &&...args) {
  return std::thread(std::forward<Func>(func), std::forward<Args>(args)...);
}

inline void thread_detach(ThreadType &t) { t.detach(); }