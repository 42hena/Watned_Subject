#pragma once
#include <memory>
template <typename T>
class TVector
{
public:
	TVector()
		:_size(0),
		_capacity(8)
	{
		_data = new T[_capacity];
	}

	TVector(int size)
		:_size(0),
		_capacity(size)
	{
		_data = new T[_capacity];
	}

	void PushFront(const T& data)
	{
		if (Capacity() == Size()) {
			T* temp = new T[Capacity() * 2];
			memcpy(temp, _data, sizeof(T) * Size());
			_capacity = _capacity * 2;
			delete _data;
			_data = temp;
		}

		_size = _size + 1;
		for (int i = _size; i > 0; --i) {
			_data[i] = _data[i - 1];
		}
		_data[0] = data;
	}
	void PushBack(const T& data)
	{
		if (Capacity() == Size()) {
			T* temp = new T[Capacity() * 2];
			memcpy(temp, _data, sizeof(T) * Size());
			_capacity = _capacity * 2;
			delete _data;
			_data = temp;
		}

		_data[_size] = data;
		_size = _size + 1;
	}
	bool PopFront(T& outData)
	{
		if (Front(outData) == false) {
			return false;
		}

		for (int i = 0; i < _size; ++i) {
			_data[i] = _data[i + 1];
		}

		_size = _size - 1;
		return true;
	}
	bool PopBack(T& outData)
	{
		if (Back(outData) == false) {
			return false;
		}
		_size = _size - 1;
		return true;
	}
	

	bool Front(T& outData)
	{
		if (IsEmpty() == true) {
			return false;
		}
		outData = _data[0];
		return true;
	}
	bool Back(T& outData)
	{
		if (IsEmpty() == true) {
			return false;
		}
		outData = _data[_size - 1];
		return true;
	}

	int Capacity()
	{
		return _capacity;
	}
	int Size()
	{
		return _size;
	}
	bool IsEmpty() const
	{
		return _size == 0;
	}


	T& operator[](int idx)
	{
		return _data[idx];
	}

private:
	T* _data;
	int _size;
	int _capacity;

};