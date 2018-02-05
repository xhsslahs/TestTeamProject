//�̱���(Singleton) : �ϳ��� ��ü�� �����ؼ� �ϳ��� ��ü�� �ٸ� ��ü����
//���� �����ؼ� ����� �� �ְ� �ϴ� ������ ���� �� �ϳ�
#pragma once

template <typename T>
class SingletoneBase
{
protected:
	static T* singleton; //�������� ����ϱ� ���� static ����
	
public:
	static T* GetSingleton();
	void ReleaseSingleton();
};

//�̱��� �ʱ�ȭ
template <typename T>
T* SingletoneBase<T>::singleton = 0;

//�̱��� �ҷ����� �Լ�
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

