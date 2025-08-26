#pragma once
template <typename T>
class TStackArray
{
public:
	TStackArray(int size)
		:_bufferSize(size)
	{
		_pData = new T[size];
	}

	~TStackArray()
	{
		delete[] _pData;
	}
	bool Push(const T& data)
	{
		if (IsFull() == true) {
			return false;
		}

		_pData[_top] = data;
		_top = _top + 1;
		return true;
	}

	bool Pop(T& outData)
	{
		if (Top(outData) == false) {
			return false;
		}

		_top = _top - 1;
		return true;
	}

	bool Top(T& outData)
	{
		if (IsEmpty() == true) {
			return false;
		}

		outData = _pData[_top - 1];
		return true;
	}

	bool IsEmpty() const {
		return _top == 0;
	}
	bool IsFull() const {
		return _top == _bufferSize;
	}
	size_t Size() const {
		return _top;
	}
	T& operator[](int idx)
	{
		return _pData[idx];
	}
private:
	T* _pData;
	int	_top;
	int _bufferSize;
};

