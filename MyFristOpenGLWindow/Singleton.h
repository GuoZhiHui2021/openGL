#pragma once
#include <mutex>


class Lock {
private:
	std::mutex mtx;//ª•≥‚¡ø
public:
	void lock() { mtx.lock(); }//º”À¯
	void unlock() { mtx.unlock(); }//Ω‚À¯
};

template<class T>
class Singleton
{
protected:
	Singleton()
	{
		ms_pSingleton_impl = static_cast<T*>(this);
	}
public:
	~Singleton()
	{
		ms_pSingleton_impl = nullptr;
	}
private:
	Singleton(const Singleton<T>&);
	Singleton& operator = (const Singleton<T>&) = delete;
public:
	static T* Instance()
	{
		lock->lock();
		if (!ms_pSingleton_impl)
		{
			new T();
		}
		lock->unlock();
		return ms_pSingleton_impl;
	}
protected:
	static T* ms_pSingleton_impl;
	static Lock* lock;
	

};
#define ms_pSingleton ms_pSingleton_impl;
template<class T>
T* Singleton<T>::ms_pSingleton_impl = nullptr;

template<class T>
Lock* Singleton<T>::lock = new Lock();


