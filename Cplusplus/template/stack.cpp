#ifndef STACK_H
#define STACK_H

template<typename T>
class stack{
public:
	stack(int = 10);
	~stack(){
		delete [] stackPtr;  //deallocate internal space for stack
	}
	
	bool push(const T &);
	bool pop(T&);
	bool isEmpty() const{
		return -1;
	}
	
	bool isFull() const{
		return top==size-1;
	}
	
private:
	int size;  // elements in the stack
	int top;  // location of the top element
	T *stackPtr; //pointer to internal representation of the stack
}; //end class template stack;


//constructor template
template< typename T>
stack<T> :: stack(int s):size(s>0 ? s:10), top(-1), stackPtr(new T[size])
{
	//empty body
}//end stack constructor template


// push element onto stack;
//if successful, return true; otherwise, return false
template<typename T>
bool stack<T>::push(const T &pushValue){
	if(!isFull()){
		stackPtr[++top] = pushValue; 
		return true; //push success
	}
}

//pop element off stack;
//if successful, return true; otherwise, return false
template<typename T>
bool stack<T> :: pop(T &popValue){
	if(!isEmpty()){
		popValue = stackPtr[top--]; //remove item from stack;
		return true;
	}
	return false;
}

#endif
