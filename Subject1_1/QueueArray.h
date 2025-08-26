#pragma once
template<typename T>
class TQueueArray
{
public:
	TQueueArray(int size)
		:_bufferSize(size)
	{
		_pData = new T[size];
	}

	~TQueueArray()
	{
		delete[] _pData;
	}

	bool Push(const T& data)
	{
		if (IsFull() == true) {
			return false;
		}

		_pData[_rear] = data;
		_rear = (_rear + 1) % _bufferSize;
		_size += 1;
		return true;
	}

	bool Pop(T& outData)
	{
		if (Front(outData) == false) {
			return false;
		}

		_front = (_front + 1) % _bufferSize;
		_size -= 1;
		return true;
	}

	bool Front(T& outData)
	{
		if (IsEmpty() == true) {
			return false;
		}

		outData = _pData[_front];
		return true;
	}

	bool IsEmpty() const {
		return _front == _rear;
	}
	bool IsFull() const {
		return (_rear + 1) % _bufferSize == _front;
	}
	int Size() const
	{
		return _size;
	}

	T*	_pData;
	int	_rear;
	int	_front;
	int _size = 0;
	int _bufferSize;
};

