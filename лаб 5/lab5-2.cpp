#include <iostream> 
#include <strings.h>
#define rand_max 0x7fff
#include <time.h>
#include <math.h>

#define NONTYPE 30

using namespace std;

struct Vec2
{
	float x = 0, y = 0;

	// ���������� ��� =
	Vec2& operator=(float value) 
	{ 
		x = y = value;
	    return *this;
	}
	// ���������� ��� ==
	bool operator == (Vec2 b){
		return (sqrt(this->x*this->x + this->y*this->y) == sqrt(b.x*b.x + b.y*b.y));
	}
	// ���������� ��� <=
	bool operator <= (Vec2 b){
		return (sqrt(this->x*this->x + this->y*this->y) < sqrt(b.x*b.x + b.y*b.y));
	}
	// ���������� ��� >=
	bool operator >= (Vec2 b){
		return (sqrt(this->x*this->x + this->y*this->y) > sqrt(b.x*b.x + b.y*b.y));
	}
};

int position(int len){
	int n;
	do{
		cin>>n;
		if ((n > len) or (n < 0)) cout<<("�������� �������!")<<endl;
	}while ((n > len) or (n < 0));
	
	return n;
}

int sortType(){
	short how;
	do{
		cout<<("1 - ���������� �� �����������")<<endl;
		cout<<("2 - ���������� �� ��������")<<endl;
		cin>>how;
		if ((how != 1) and (how != 2)) cout<<("������� ����������!")<<endl;
	}while ((how != 1) and (how != 2));
	return how;
}

//������� �����
template <class T, int maxSize>
class DynArray
{
	public:
		
	T* array;
	int len;
	
	DynArray()
	{
		array = new T[maxSize];
		
		//������� ��������
		for(int i = 0; i < maxSize; ++i) 
			array[i] = 0;
	}
	
	DynArray(DynArray& arr)
	{
		array = new T[maxSize];
		this->setLen(arr.getLen());
		
		for(int i = 0; i < maxSize; ++i){
			array[i] = arr.array[i];
		}
	}
	
	~DynArray()
	{
		delete[] array;
	}
	
	void setLen(int n){	this->len = n;}
	int getLen(){	return len;	}
	
//	int getMaxSize() {
//		return maxSize;
//	}
	
	int chooseOperation(){
		int operation = 0;
		cout<<("����� �������� ��� ����������?")<< endl;
			do{
				cout<<("1 - ����� ���������� � �������")<< endl;
				cout<<("2 - ����������")<< endl;
				cout<<("3 - ����������� ������������ ������ �������")<< endl;
				cout<<("4 - ���������� �������� �� ������� (� ����������� ������� ���������)")<< endl;
				cout<<("5 - �������� �������� �� ������� (� ����������� ������� ���������)")<< endl;
				cout<<("6 - ���������� �������� � ����� �������")<< endl;
				cout<<("7 - ������� ������ ��������� �������� � ������")<< endl;
				cout<<("8 - ��������, ��� � ���� ����������� ������� �������� ��� �������� ������ ��� ������ ��������� ������� �������.")<< endl;
				cout<<("9 - ����� �� ���������")<< endl;
				cin>>operation;
				if ((operation > 9) or (operation < 0)) cout<<("����� �������� �� �������������")<< endl;
			} while ((operation > 9) or (operation < 0));
		cout<<endl;
		return operation;
	}
	
	virtual void sort(bool asc){
		if (asc){
			int i, j;
		    bool swapped;
		    
		    for (i = 0; i < len - 1; i++) {
		        swapped = false;
		        for (j = 0; j < len - i - 1; j++) {
		            if (array[j] >= array[j + 1]) {
		                swap(array[j], array[j + 1]);
		                swapped = true;
		            }
		        }
		 
		        // ���� �� ��������� ����� ������ �� ����������
		        // �� ���������
		        if (swapped == false)
		            break;
		    }
		}
		else{
			int i, j;
		    bool swapped;
		    for (i = 0; i < len - 1; i++) {
		        swapped = false;
		        for (j = 0; j < len - i - 1; j++) {
		            if (array[j] <= array[j + 1]) {
		                swap(array[j], array[j + 1]);
		                swapped = true;
		            }
		        }
		        // ���� �� ��������� ����� ������ �� ����������
		        // �� ���������
		        if (swapped == false)
		            break;
		    }
		}
	}
	
	virtual void insertToN(T elem, int n){
		
		for (int i = len-1; i >= n; --i)
			swap(array[i+1], array[i]);
		array[n] = elem;
		++len;
	}
	
	virtual void removeFromN(int n){
		array[n] = 0;
		for (int i = n; i < len; ++i)
			swap(array[i+1], array[i]);
		--len;
	}
	
	virtual void insertToEnd(T elem){
		array[len] = elem;
		++len;
	}
	
//	DynArray<T, maxSize>& operator +(const T elem);
	
	void removeFirst(T elem){
		for (int i = 0; i < len; ++i){
			if (array[i] == elem) {
				removeFromN(i);
				break;
			}
		}
	}
	
//	DynArray<T, maxSize>& operator -(const T elem);
	
	T& operator[](int index) 
	{ 
	    return array[index];
	}
	
	virtual bool biggerThenAll( T* arr2, bool bigger){
		bool rez = true;
		if (bigger == true){
			for (int i = 0; i < len; ++i){
				for (int j = 0; j < len; ++j){
					if (array[i] < arr2[j]){
						rez = false;
						break;
					}
				}
			}
		}
		else{
			for (int i = 0; i < len; ++i){
				for (int j = 0; j < len; ++j){
					if (array[i] > arr2[j]){
						rez = false;
						break;
					}
				}
			}
		}
		return rez;			
	}
	
	virtual void print();
	
	int operations(short type){
		short operation = chooseOperation();
				switch (operation){
					case 1:
						{
							print();
							break;
						}
					case 2:
						{
							bool asc;
							short how = sortType();							
							
							(how == 1) ? asc = true : asc = false;
							sort(asc);
							print();
							break;
						}
					case 3:
						{
							cout<<("������������ ����� ������� = ")<<NONTYPE<<endl;
							break;
						}
					case 4:
						{
							T elem;
							string elem1;
							cout<<("������� ������� � �������")<<endl;
							cin>>elem;
							
							int n = position(getLen());				
							
							print();
							insertToN(elem,n);
							print();
							break;
						}
					case 5:
						{
							int n = position(getLen());;
							
							print();
							removeFromN(n);
							print();
							break;
						}
					case 6:
						{
							cout<<("������� ������� ")<<endl;
							T elem;
							cin>>elem;
							*this + elem;
							print();
							break;
						}
					case 7:
						{
							cout<<("������� ������: ")<<endl;
							print();
							
							cout<<("������� ������� ")<<endl;
							T elem;
							cin>>elem;
							
							*this - elem;
							print();
							break;
						}
					case 8:
						{
							switch (type){
								case 1:{
									DynArray<T, NONTYPE> array2;
									array2.setLen(this->getLen());
									
									for (int i = 0; i < len; ++i){
										array2[i] = rand() % 100;
									}
									
									cout<<("�������� ������")<<endl;
									print();
									cout<<("������ ������")<<endl;
									array2.print();
									cout<<this->biggerThenAll(array2.array, true);
									
									break;
								}
								case 2:{
									DynArray<T, NONTYPE> array2;
									array2.setLen(this->getLen());
									
									for (int i = 0; i < len; ++i){
										array2[i] = rand() % 100 + rand() % 100 *0.01;
									}
									break;
								}
								
								}
							break;
						}
					case 9:							
							break;
						
				}
		return operation;
	}
	
};

//����� ��� ������ (�� ���������)
template <class T, int maxSize>
class DynArrayInt : public DynArray<T, maxSize>
{
};
//������������� ��� �����
template <int maxSize>
class DynArrayStr<char*, maxSize> : public DynArray<char*, maxSize>
{
	char** array;
//	int maxSize;
	int len;
	
public:
	
	DynArray()
	{
		array = new char*[maxSize];
		
		//������� ��������
		for(int i = 0; i < maxSize; ++i) 
			array[i] = 0;
	}
	
	~DynArray()
	{
		delete[] array;
	}
	
	void setLen(int n){	this->len = n;}
	int getLen(){	return len;	}
	
	int getMaxSize() {
		return maxSize;
	}
	
	int chooseOperation(){
		int operation = 0;
		cout<<("����� �������� ��� ����������?")<< endl;
			do{
				cout<<("1 - ����� ���������� � �������")<< endl;
				cout<<("2 - ����������")<< endl;
				cout<<("3 - ����������� ������������ ������ �������")<< endl;
				cout<<("4 - ���������� �������� �� ������� ")<< endl;
				cout<<("5 - �������� �������� �� ������� ")<< endl;
				cout<<("6 - ���������� �������� � ����� �������")<< endl;
				cout<<("7 - ������� ������ ��������� �������� � ������")<< endl;
				cout<<("8 - ��������, ��� � ���� ����������� ������� �������� ��� �������� ������ ��� ������ ��������� ������� �������.")<< endl;
				cout<<("9 - ����� �� ���������")<< endl;
				cin>>operation;
				if ((operation > 9) or (operation < 0)) cout<<("����� �������� �� �������������")<< endl;
			} while ((operation > 9) or (operation < 0));
		cout<<endl;
		return operation;
	}
	
	void print()
	{
		cout<<"���������� ��������� = "<<len<<endl;
		for(int i = 0; i < len; ++i) 
			cout << array[i] << " ";
		cout << endl;
	}
	
	void sort(bool asc){
		if (asc){
			int i, j;
		    bool swapped;
		    
		    for (i = 0; i < len - 1; i++) {
		        swapped = false;
		        for (j = 0; j < len - i - 1; j++) {
		            if (strlen(array[j]) >= strlen(array[j + 1])) {
		                swap(array[j], array[j + 1]);
		                swapped = true;
		            }
		        }
		 
		        // ���� �� ��������� ����� ������ �� ����������
		        // �� ���������
		        if (swapped == false)
		            break;
		    }
		}
		else{
			int i, j;
		    bool swapped;
		    for (i = 0; i < len - 1; i++) {
		        swapped = false;
		        for (j = 0; j < len - i - 1; j++) {
		            if (strlen(array[j]) <= strlen(array[j + 1])) {
		                swap(array[j], array[j + 1]);
		                swapped = true;
		            }
		        }
		        // ���� �� ��������� ����� ������ �� ����������
		        // �� ���������
		        if (swapped == false)
		            break;
		    }
		}
	}
	
	void insertToN(char* elem, int n){
		for (int i = len; i > n; --i){
			array[i] = new char [strlen(array[i-1])];
			strcpy(array[i], array[i-1]);
		}
		array[n] = new char [strlen(elem)];
		strcpy(array[n], elem);
		++len;
	}
	
	void removeFromN(int n){
		delete[] array[n];
		for (int i = n; i < len - 1; ++i){
			array[i] = new char [strlen(array[i+1])];
			strcpy(array[i], array[i+1]);
		}
		--len;
	}
	
	void insertToEnd(const char* elem){
		array[len] = new char [strlen(elem)];
		strcpy(array[len], elem);
		++len;
	}
	
	DynArray<char*, maxSize>& operator +(const char* elem);
	
	void removeFirst(const char* elem){
		for (int i = 0; i < len; ++i){
			if(not strcmp(array[i],elem)) {
				removeFromN(i);
				cout<<("������� �����")<<endl;
				break;
			}
		}
	}
	
	DynArray<char*, maxSize>& operator -(const char* elem);
	
	char*& operator[](int index) 
	{ 
	    return array[index];
	}
	
	int operations(short type){
		short operation = chooseOperation();
				switch (operation){
					case 1:
						{
							print();
							break;
						}
					case 2:
						{
							bool asc;
							short how = sortType();							
							
							(how == 1) ? asc = true : asc = false;
							sort(asc);
							print();
							break;
						}
					case 3:
						{
							cout<<("������������ ����� ������� = ")<<getMaxSize()<<endl;
							break;
						}
					case 4:
						{
							cout<<("������� ������� ")<<endl;
							cin.clear();
							fflush(stdin);
							
							char *elem = new char[20];
							cin.getline(elem,20);
							
							cout<<("������� �������")<<endl;
							
							int n = position(getLen());				
							
							print();
							insertToN(elem,n);
							print();
							break;
						}
					case 5:
						{
							cout<<("������� �������")<<endl;
							int n = position(getLen());;
							
							print();
							removeFromN(n);
							print();
							break;
						}
					case 6:
						{
							cout<<("������� ������� ")<<endl;
							cin.clear();
							fflush(stdin);
							
							char *elem = new char[20];
							cin.getline(elem,20);
							
//							insertToEnd(elem);
							*this + elem;
							print();
							break;
						}
					case 7:
						{
							cout<<("������� ������: ")<<endl;
							print();
							
							cout<<("������� ������� ")<<endl;
							cin.clear();
							fflush(stdin);
							
							char *elem = new char[20];
							cin.getline(elem,20);
							*this - elem;
							print();
							break;
						}
					case 8:
						{
							
							break;
						}
					case 9:							
							break;
						
				}
		return operation;
	}
	
};

//������������� ��� ��������
template <int maxSize>
class DynArrayVec<Vec2, maxSize> : public DynArray<Vec2, maxSize>
{
	public:
		
	Vec2* array;
	int len;
	
	DynArray()
	{
		array = new Vec2[maxSize];
		
		//������� ��������
		for(int i = 0; i < maxSize; ++i) 
			array[i] = 0;
	}
	
	DynArray(DynArray& arr)
	{
		array = new Vec2[maxSize];
		this->setLen(arr.getLen());
		
		for(int i = 0; i < maxSize; ++i){
			array[i] = arr.array[i];
//			cout<<array[i]<<endl;
		}
	}
	
	~DynArray()
	{
		delete[] array;
	}
	
	void setLen(int n){	this->len = n;}
	int getLen(){	return len;	}
	
	int getMaxSize() {
		return maxSize;
	}
	
	int chooseOperation(){
		int operation = 0;
		cout<<("����� �������� ��� ����������?")<< endl;
			do{
				cout<<("1 - ����� ���������� � �������")<< endl;
				cout<<("2 - ����������")<< endl;
				cout<<("3 - ����������� ������������ ������ �������")<< endl;
				cout<<("4 - ���������� �������� �� ������� (� ����������� ������� ���������)")<< endl;
				cout<<("5 - �������� �������� �� ������� (� ����������� ������� ���������)")<< endl;
				cout<<("6 - ���������� �������� � ����� �������")<< endl;
				cout<<("7 - ������� ������ ��������� �������� � ������")<< endl;
				cout<<("8 - ��������, ��� � ���� ����������� ������� �������� ��� �������� ������ ��� ������ ��������� ������� �������.")<< endl;
				cout<<("9 - ����� �� ���������")<< endl;
				cin>>operation;
				if ((operation > 9) or (operation < 0)) cout<<("����� �������� �� �������������")<< endl;
			} while ((operation > 9) or (operation < 0));
		cout<<endl;
		return operation;
	}
	
	void sort(bool asc){
		if (asc){
			int i, j;
		    bool swapped;
		    
		    for (i = 0; i < len - 1; i++) {
		        swapped = false;
		        for (j = 0; j < len - i - 1; j++) {
		            if (array[j].x >= array[j + 1].x) {
		                swap(array[j], array[j + 1]);
		                swapped = true;
		            }
		        }
		 
		        // ���� �� ��������� ����� ������ �� ����������
		        // �� ���������
		        if (swapped == false)
		            break;
		    }
		}
		else{
			int i, j;
		    bool swapped;
		    for (i = 0; i < len - 1; i++) {
		        swapped = false;
		        for (j = 0; j < len - i - 1; j++) {
		            if (array[j] <= array[j + 1]) {
		                swap(array[j], array[j + 1]);
		                swapped = true;
		            }
		        }
		        // ���� �� ��������� ����� ������ �� ����������
		        // �� ���������
		        if (swapped == false)
		            break;
		    }
		}
	}
	
	void insertToN(Vec2 elem, int n){
		
		for (int i = len-1; i >= n; --i)
			swap(array[i+1], array[i]);
		array[n] = elem;
		++len;
	}
	
	void removeFromN(int n){
		array[n] = 0;
		for (int i = n; i < len; ++i)
			swap(array[i+1], array[i]);
		--len;
	}
	
	void insertToEnd(Vec2 elem){
		array[len] = elem;
		++len;
	}
	
	DynArray<Vec2, maxSize>& operator +(const Vec2 elem);
	
	void removeFirst(Vec2 elem){
		for (int i = 0; i < len; ++i){
			if (array[i] == elem) {
				removeFromN(i);
				break;
			}
		}
	}
	
	DynArray<Vec2, maxSize>& operator -(const Vec2 elem);
	
	Vec2& operator[](int index) 
	{ 
	    return array[index];
	}
	
	bool biggerThenAll( Vec2* arr2, bool bigger){
		bool rez = true;
		if (bigger == true){
			for (int i = 0; i < len; ++i){
				for (int j = 0; j < len; ++j){
					if (array[i] <= arr2[j]){
						rez = false;
						break;
					}
				}
			}
		}
		else{
			for (int i = 0; i < len; ++i){
				for (int j = 0; j < len; ++j){
					if (array[i] >= arr2[j]){
						rez = false;
						break;
					}
				}
			}
		}
		return rez;			
	}
	
	void print();
	
	int operations(short type){
		short operation = chooseOperation();
				switch (operation){
					case 1:
						{
							print();
							break;
						}
					case 2:
						{
							bool asc;
							short how = sortType();							
							
							(how == 1) ? asc = true : asc = false;
							sort(asc);
							print();
							break;
						}
					case 3:
						{
							cout<<("������������ ����� ������� = ")<<NONTYPE<<endl;
							break;
						}
					case 4:
						{
							Vec2 elem;
							string elem1;
							cout<<("������� ������� (X, Y) � �������")<<endl;
							cin>>elem.x>>elem.y;
							
							int n = position(getLen());				
							
							print();
							insertToN(elem,n);
							print();
							break;
						}
					case 5:
						{
							cout<<("������� �������")<<endl;
							int n = position(getLen());;
							
							print();
							removeFromN(n);
							print();
							break;
						}
					case 6:
						{
							cout<<("������� ������� (X, Y)")<<endl;
							Vec2 elem;
							cin>>elem.x>>elem.y;
							*this + elem;
							print();
							break;
						}
					case 7:
						{
							cout<<("������� ������: ")<<endl;
							print();
							
							cout<<("������� ������� (X, Y)")<<endl;
							Vec2 elem;
							cin>>elem.x>>elem.y;
							
							*this - elem;
							print();
							break;
						}
					case 8:
						{
							
							break;
						}
					case 9:							
							break;
						
				}
		return operation;
	}
	
};

// ���������� ������ ��� �������� ������-�������
template <typename T, int maxSize>
void DynArray<T, maxSize>::print()
{
	cout<<"���������� ��������� = "<<len<<endl;
	for(int i = 0; i < len; ++i) 
		cout << array[i] << " ";
	cout << endl;
}

template < int maxSize>
void DynArray<Vec2, maxSize>::print()
{
	cout<<"���������� ��������� = "<<len<<endl;
	for(int i = 0; i < len; ++i) 
		cout << " vec: "<< array[i].x << ";"<< array[i].y << " ";
	cout << endl;
}

// ���������� ��������� << ������ ostream ��� ���� ����� 
// Vec2 ����� ���� �������� � ����������� ������ ������ cout
//ostream& operator<<(ostream& os, const Vec2& vec) 
//{ 
//    return os << " vec: " << vec.x << " " << vec.y;
//}

// ���������� ��������� >> ������ ostream ��� ���� ����� 
// Vec2 ����� ���� ������� � ����������� ������ ������ cin
//istream& operator>> (istream& is, const Vec2& vec)
//{
//    is>> vec;
//    return is;
//}

template<typename T, int maxSize>
DynArray<T, maxSize>& DynArray<T, maxSize>::operator +(const T elem){
	this->insertToEnd(elem);
	return *this;
}
template<typename T, int maxSize>
DynArray<T, maxSize>& DynArray<T, maxSize>::operator -(const T elem){
	this->removeFirst(elem);
	return *this;
}

template<int maxSize>
DynArray<char*, maxSize>& DynArray<char*, maxSize>::operator +(const char* elem){
	this->insertToEnd(elem);
	return *this;
}

template<int maxSize>
DynArray<char*, maxSize>& DynArray<char*, maxSize>::operator -(const char* elem){
	this->removeFirst(elem);
	return *this;
}

template<int maxSize>
DynArray<Vec2, maxSize>& DynArray<Vec2, maxSize>::operator +(const Vec2 elem){
	this->insertToEnd(elem);
	return *this;
}

template<int maxSize>
DynArray<Vec2, maxSize>& DynArray<Vec2, maxSize>::operator -(const Vec2 elem){
	this->removeFirst(elem);
	return *this;
}

int main(int argc, char** argv) 
{
	system("chcp 1251");
	srand(time(0));
	
	int len = 0;
	int type;
	
	cout<<("� ����� ����� ������ ������ ��������?")<< endl;
	do{
		cout<<("1 - ����� �����")<< endl;
		cout<<("2 - ����� � ��������� ������")<< endl;
		cout<<("3 - ������")<< endl;
		cout<<("4 - ������� vec(float x; float y)")<< endl;
		cin>>type;
		if ((type > 4) or (type <= 0)) cout<<("����� ������� �� ������������!")<< endl;
	} while ((type > 4) or (type <= 0));
	cout << endl;
	
	cout<<("������� ����� �������")<< endl;
	do{
		cin>>len;
		if (len > 20) cout<<("����� ������ ����������! ��������� ����")<< endl;
		if (len < 1) cout<<("����� ������ ����������! ��������� ����")<< endl;
	}while ((len > 20) or (len <= 0));
	cout << endl;
	
	switch (type){
		case 1:
			{
				cout<<("��������������� ��� ������ int")<< endl;
				DynArrayInt<int, NONTYPE> array;
				array.setLen(len);
				
				for (int i = 0; i < len; ++i){
					array[i] = rand() % 100;
				}
				
				int oper = array.operations(1);	
				
				break;
			}
		case 2:
			{
				cout<<("��������������� ��� ������ float")<< endl;
				DynArrayInt<float, NONTYPE> array;			
				array.setLen(len);
				
				for (int i = 0; i < len; ++i){
					array[i] = rand() % 100 + rand() % 100 *0.01 ;
				}
				
				int oper = array.operations(2);
				
				break;
			}
		case 3:
			{
				cout<<("��������������� ��� ������ char*")<< endl;
				DynArrayStr<char*, NONTYPE> array;
				array.setLen(len);
				
				for (int i = 0; i < len; ++i){
					short a = rand() % 7 + 1;
					char *temp = new char[a];
					strcpy(temp,"");
					array[i] = new char[a];
					char const *s = "S";
					for (int j = 0; j < a; ++j){
						strcat(temp, s);
					}
					strcpy(array[i], temp);
					cout<<array[i]<< endl;
					delete[] temp;
				}
				
				int oper = array.operations(3);
				
				break;
			}
		case 4:
			{
				cout<<("��������������� ��� ������ Vec2")<< endl;
				DynArrayVec<Vec2, NONTYPE> array;
				array.setLen(len);
				
				for (int i = 0; i < len; ++i){
					array[i].x = rand() % 100;
					array[i].y = rand() % 100;
				}
				
				int oper = array.operations(4);
				
				break;
			}
	}	
	return 0;
}

