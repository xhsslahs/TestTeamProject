//싱글톤(Singleton) : 하나의 객체를 생성해서 하나의 객체로 다른 객체들이
//쉽게 접근해서 사용할 수 있게 하는 디자인 패턴 중 하나
#pragma once

template <typename T>
class SingletoneBase
{
protected:
	static T* singleton; //전역으로 사용하기 위한 static 선언
	
public:
	static T* GetSingleton();
	void ReleaseSingleton();
};

//싱글톤 초기화
template <typename T>
T* SingletoneBase<T>::singleton = 0;

//싱글톤 불러오는 함수
template <typename T>
T* SingletoneBase<T>::GetSingleton()
{
	if (!singleton)
	{
		singleton = new T;
	}

	return singleton;
}

template<typename T>
void SingletoneBase<T>::ReleaseSingleton()
{
	if (singleton)
	{
		delete singleton;

		singleton = NULL;
	}
}

