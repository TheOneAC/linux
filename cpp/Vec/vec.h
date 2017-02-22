#ifndef _VEC_
#define _VEC_
#include <iostream>
#include <cstddef>
#include <memory>
#include <algorithm>

template <class T, class A = std::allocator<T> >
class vec{
	//traits tricks
	typedef T* iterator;
	typedef const T* const_iterator;
	typedef size_t size_type;
	typedef T value_type;
	typedef std::ptrdiff_t difference_type;
	typedef T& reference;
	typedef const T& const_reference;

	vec(){create();}
	explicit vec(size_type n, const T& val = T()){
		create(n,val);
	}
	vec(const vec&v){
		create(v.begin(),v.end());
	}
	vec & operator= (const vec& rhs){
		if( &rhs != this){
			uncreate();
			create(rhs.begin(),rhs.end());
		}
		return *this;
	};
	~vec(){
		uncreate();
	}
	size_type size()const{
		return avail - data;
	}
	size_type capacity() const{
		return (data == 0 ? 0 : limit - data);
	}
	T& operator[](size_type index){
		return data[index];
	}
	const T& operator[](size_type index)const{
		return data[index];
	}
	iterator begin(){return data;}
	const_iterator begin()const{return data;}
	iterator end(){ return avail;}
	const_iterator end()const{return avail;}
	void push_back(const T& val){
		if(avail == limit)
			grow();
		unchecked_append(val);
	} 
	void clear(){
		uncreate();
	}
	bool empty(){return data == avail;}

private:	
	iterator data;
	iterator avail;
	iterator limit;


	A alloc;
	void create(){
		data = avail = limit = 0;
	};
	void create(size_type n ,const T& val){
		data = alloc.allocate(n);
		limit = avail = data + n;
		std::uninitialized_fill(data,limit,avail);
	};
	void create(const_iterator s , const_iterator e){
		data = alloc.allocate(e - s);
		limit = avail = std::uninitialized_copy(s, e,data);
	};
	void uncreate(){
		if( data ){
			iterator it = avail;
			while(it != data){
				alloc.destroy(--it);
			}
			alloc.deallocate(data, limit - data);
		}
		data = avail = limit = 0;
	};
	void grow(){
		size_type new_size = std::max(2* (limit - data), ptrdiff_t(1));
		iterator new_data = alloc.allocate(new_size);
		iterator new_avail = std::uninitialized_copy(data,avail,new_data);
		uncreate();
		data = new_data;
		avail = new_avail;
		limit = data + new_size;
	};
	void unchecked_append(const T& val){
		alloc.construct(avail++,val);
	};

};

#endif