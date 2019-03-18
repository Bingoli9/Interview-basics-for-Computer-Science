#include <stdint.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <emmintrin.h>

class SpinLock 
{
	public:
		SpinLock():_l(false) {}
		virtual ~SpinLock() = default;
		SpinLock(const SpinLock &) = delete;
		SpinLock &operator=(const SpinLock &) = delete;
		
		void _lock() {
			while(!__sync_bool_compare_and_swap(&_l, false, true)) {
				_mm_pause();
			}
			return; 
		} 
		void _unlock() {
			_l = false;
			return; 
		} 
	
	private:
		enum {CACHE_SIZE = 64};
		
		char padding1[CACHE_SIZE/2];
		bool _l;
		char padding2[CACHE_SIZE/2 - sizeof(bool)];
};



