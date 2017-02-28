#pragma once

#include <vector>
#include <stdexcept>

template<class T>
class Pool
{
private:
	std::vector<T*> _objects;
	std::vector<T*>* _activeObjectsGetter;
	int _index;

public:
	Pool() {
		_index = 0;
		_activeObjectsGetter = new std::vector<T*>();
	}

	template<class T2>
	void Init(int size) {
		_objects.reserve(size);

		for (int i = 0; i < size; i++) {
			T* o = new T2();
			o->SetID(i);
			_objects.push_back(o);
		}
	}

	virtual ~Pool() {
		for (auto o : _objects) {
			delete o;
		}
		_objects.clear();
	}

	T* GetNext() {
		return _objects[_index++];
	}

	T* GetObjectOfID(int id) {
		if (id == -1)
			return nullptr;

		for (auto o : _objects) {
			if (o->GetID() == id)
				return o;
		}

		return nullptr;
	}

	std::vector<T*>* GetActiveObjects() {
		_activeObjectsGetter->clear();
		_activeObjectsGetter->reserve(_index);

		typename std::vector<T*>::iterator o = _objects.begin();
		for (int i = 0; i < _index; i++, o++)
			_activeObjectsGetter->push_back((*o));

		return _activeObjectsGetter;
	}
};