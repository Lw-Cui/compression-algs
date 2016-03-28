#ifndef _QUEUE_H_
#define _QUEUE_H_
#include <atomic>
#include <functional>
#include <mutex>
#include <algorithm>
#include <vector>
#include <iostream>
namespace queue {
	template<typename T>
	class MobileAtomic
	{
		//template<typename T, std::vector<MobileAtomic<T>>> friend class PriorityQueue;
	public:
		MobileAtomic(){}
		MobileAtomic(const T& data): atom(data) {}
		MobileAtomic(const MobileAtomic& mobile): atom(mobile.atom.load()) {}
		inline MobileAtomic& operator=(const MobileAtomic &mobile) {
			atom.store(mobile.atom.load());
			return *this;
		}
		inline operator T() const {
			return atom.load();
		}
	private:
		std::atomic<T> atom;
	};

	template<typename T, 
		typename Con = std::vector<MobileAtomic<T>>,
		typename Cmp = std::greater<typename Con::value_type>>
	class PriorityQueue {
	public:
		typedef typename Con::const_iterator const_iterator;
		PriorityQueue(const Cmp& c = Cmp()):array(1), compare(c) {}
		inline const_iterator begin() const {return ++array.begin();}
		inline const_iterator end() const {return array.end();}
		inline void push(const T& data) {
			std::lock_guard<std::mutex> guard(protector);
			array.push_back(data);
			up(array.size() - 1);
		}
		inline T top() {
			return array[1];
		}

		inline int size() {
			return array.size() - 1;
		}

		inline void pop() {
			std::lock_guard<std::mutex> guard(protector);
			T data = array[1];
			array[1] = array.back();
			array.pop_back();
			down(1);
		}
		inline int size() const {
			return array.size() - 1;
		}
		inline bool empty() {
			return array.size() <= 1;
		}
	private:
		void up(size_t index) {
			T data(array[index]);
			// index indicates the current position
			while(index != 1) {
				if (compare(data, array[index / 2]))
					array[index] = array[index / 2];
				else
					break;
				index /= 2;
			}
			array[index] = data;
		}
		void down(size_t index) {
			T data(array[index]);
			// index means the possible dist
			while (index * 2 < array.size()) {
				index *= 2;
				if (index + 1 < array.size() && compare(array[index + 1], array[index]))
					index++;
				if (compare(array[index], data))
					array[index / 2] = array[index];
				else
					break;
			}
			if (!compare(array[index], data))
				array[index / 2] = data;
			else
				array[index] = data;
		}
		Con array;
		Cmp compare;
		std::mutex protector;
	};
}

#endif
