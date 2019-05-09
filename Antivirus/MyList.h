#pragma once

#define MaxLength 200


template <class T>
class MyList
{
	typedef struct Node
	{
		T m_Body;
		Node* m_Next;

	}Node;

	Node* m_Start;
	int m_NumberOfElements;

	public:

	int GetMyNumberOfElements();
	void PushBack(T& Item);
	void PopBack();
	void Delete(int i);
	void Clean();

	MyList();
	~MyList();

	 T& operator[] (int x);
	 bool operator== (MyList<T>&Second);
};


/// Implementation



template <class T>
MyList<T>::MyList()
{
	m_Start = nullptr;
	m_NumberOfElements = 0;
}


template <class T>
MyList<T>::~MyList()
{
	this->Clean();
}


template<class T>
inline T& MyList<T>::operator[](int x)
{
	Node* Aux = m_Start;
	for (int i = 0; i < x && i < m_NumberOfElements - 1; i++)
	{
		Aux = Aux->m_Next;
	}
	return Aux->m_Body;
}


template<class T>
inline bool MyList<T>::operator==(MyList<T>& MyDataBase)
{
	int UpdatedSignatureNumber = this->m_NumberOfElements;
	int SignatureNumberMyDataBase = MyDataBase.m_NumberOfElements;

	if (UpdatedSignatureNumber > SignatureNumberMyDataBase)
	{
		return false;
	}
	else
	{
		int count = 0;

		for (int i = 0; i < UpdatedSignatureNumber; i++)
			for (int j = 0; j < SignatureNumberMyDataBase; j++)
			{
				if ((*this)[i] == MyDataBase[j])
				{
					count++;
				}
			}
		if (count == UpdatedSignatureNumber)
			return true;
	}
	return false;
}


template<class T>
inline int MyList<T>::GetMyNumberOfElements()
{
	return m_NumberOfElements;
}


template<class T>
void MyList<T>::PushBack(T& Item)
{
	try
	{
		if (m_Start == nullptr)
		{
			m_Start = new Node;
			if (m_Start == nullptr)
			{
				throw new Exceptions(MemAllocationFailed, "Error on memory allocation!");
			}
			m_Start->m_Next = nullptr;
			m_Start->m_Body = Item;
			m_NumberOfElements = 1;
		}
		else
		{
			Node* Aux = m_Start;
			while (!(Aux->m_Next == nullptr))
			{
				Aux = Aux->m_Next;
			}
			Aux->m_Next = new Node;
			if (Aux->m_Next == nullptr)
			{
				throw new Exceptions(MemAllocationFailed, "Error on memory allocation!");
			}
			Aux->m_Next->m_Next = nullptr;
			Aux->m_Next->m_Body = Item;
			m_NumberOfElements++;
		}
	}
	catch (Exceptions* Excep)
	{
		Excep->PrintMessage();
		exit(0);
	}
}


template<class T>
inline void MyList<T>::PopBack()
{
	Node* Aux = m_Start;
	Node* Prev = nullptr;

	while (!(Aux->m_Next == nullptr))
	{
		Prev = Aux;
		Aux = Aux->m_Next;
	}

	if (Aux != m_Start)
		Prev->m_Next = nullptr;
	else
	{
		m_Start = nullptr;
	}
	delete Aux;
	
	m_NumberOfElements--;
}


template<class T>
inline void MyList<T>::Delete(int x)
{
	Node *Aux = m_Start;
	Node* Prev = nullptr;

	if (x == 0)
	{
		m_Start = m_Start->m_Next;
		delete[] Aux;
		m_NumberOfElements--;
		return;
	}


	for (int i = 0; i < x && i < m_NumberOfElements - 1; i++)
	{
		Aux = Aux->m_Next;
		Prev = Aux;
	}
	m_NumberOfElements--;

	Prev->m_Next = Aux->m_Next;
	delete[] Aux;
}


template<class T>
inline void MyList<T>::Clean()
{
	while (this->m_Start != nullptr)
	{
		this->PopBack();
	}
}