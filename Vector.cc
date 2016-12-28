// Implementation of the templated Vector class
// ECE4893/8893 lab 3
// YOUR NAME HERE

#include <iostream> // debugging
#include "Vector.h"

// Your implementation here
// Fill in all the necessary functions below
using namespace std;

// Default constructor
template <typename T>
Vector<T>::Vector()
{
																			//Default values of an empty vector
	count=0;
	reserved=0;																//not used in my implementation used in more effecient vectors
	elements=NULL;
}

// Copy constructor
template <typename T>
Vector<T>::Vector(const Vector& rhs)
{

	  
	count=rhs.count; reserved=rhs.reserved;
	elements=(T*)malloc(count * sizeof(T)); 

	for(int i = 0; i < count; i++) {
    	new (&elements[i])T(rhs.elements[i]);                                  //Copy the elements from rhs into the vector
  	}
  	

}

// Assignment operator
template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& rhs)
{
	
	if (this ==  &rhs) return *this;										//Check if equal is pointing to itself.
	  
  	if (elements != NULL) {													//If not then empty out the elements in the lhs of the equal sign.
    	for(int i = 0; i < count; i++) {
    		elements[i].~T();
    	}
    	free(elements);														//Prevent Memory leaks.
  	}

	count=rhs.count; reserved=rhs.reserved;									//once emptied copy the variables and elements over
	elements=(T*)malloc(count * sizeof(T));

	for(int i = 0; i < count; i++) {
    	new (elements + i)T(rhs.elements[i]);       	
  	}
  	elements=rhs.elements;

}

#ifdef GRAD_STUDENT
// Other constructors
template <typename T>
Vector<T>::Vector(size_t nReserved)
{ // Initialize with reserved memory
}

template <typename T>
Vector<T>::Vector(size_t n, const T& t)
{ // Initialize with "n" copies of "t"
}

template <typename T>
void Vector<T>::Reserve(size_t n)
{ // Reserve extra memory
}

#endif

// Destructor
template <typename T>
Vector<T>::~Vector()
{
 for(int i = 0; i < count; i++)											//if count is greater than 0 then we need to remove the elements
  {
    elements[i].~T();													//Deleting all the elements                                          
  }
  
  free(elements);														//Prevent memory leaks                                                         
  count = 0; 
  reserved=0;
}

// Add and access front and back
template <typename T>
void Vector<T>::Push_Back(const T& rhs)
{
	if (reserved == count) {												//In our implementation reserved always equals count
		reserved ++;
		T* t = (T*) malloc(reserved * sizeof(T));							//Malloc memory for new element
		for(int i = 0; i < count; i++) {
			new(&t[i])T(elements[i]);   
			elements[i].~T();
		}
		new(&t[count])T(rhs);

		free(elements);
		elements = t;

		count=reserved;

	}
}

template <typename T>
void Vector<T>::Push_Front(const T& rhs)
{
	if (reserved == count) {												//In our implementation reserved always equals count
		reserved ++;
		T* t = (T*) malloc(reserved * sizeof(T));							//Malloc memory for new element
		for(int i = 0; i < count; i++) {
			new(&t[i+1])T(elements[i]);										//shift elements up 1 index
			elements[i].~T();
		}
		new(&t[0])T(rhs);													//set front value

		free(elements);														//Prevent memory leaks
		elements = t;

		count=reserved;

	}
}

template <typename T>
void Vector<T>::Pop_Back()
{ // Remove last element
if(count != 0){
	count --;																//reduce the count
    elements[count].~T();
    reserved=count;
}
}

template <typename T>
void Vector<T>::Pop_Front()
{ // Remove first element
	if(count != 0) {
		
		reserved -= 1;
		T* t = (T*) malloc(reserved * sizeof(T));							//Malloc memory for new element
		for(int i = 0; i < reserved; i++) {
			new(&t[i])T(elements[i+1]);										//shift elements up 1 index
			elements[i+1].~T();
		}
		elements[0].~T();
		free(elements);														//Prevent memory leaks
		elements = t;

		//elements[0].~T();
		//free(&elements[0]);
		//elements=&elements[1];
		count=reserved;		
	}
}

// Element Access
template <typename T>
T& Vector<T>::Front() const
{
	return elements[0];
}

// Element Access
template <typename T>
T& Vector<T>::Back() const
{
	return elements[count-1];
}

template <typename T>
const T& Vector<T>::operator[](size_t i) const
{ // const element access

  return elements[i];
}

template <typename T>
T& Vector<T>::operator[](size_t i)
{//nonconst element access
  return elements[i];
}

template <typename T>
size_t Vector<T>::Size() const
{
	return count;
}

template <typename T>
bool Vector<T>::Empty() const
{
	if(count == 0) return true;
	return false;
}

// Implement clear
template <typename T>
void Vector<T>::Clear()
{
    for(int i = 0; i < count; i++) {
	//shift elements up 1 index
		elements[i].~T();
	}
	//free(elements);
	count = 0;
	reserved = 0;
}

// Iterator access functions
template <typename T>
VectorIterator<T> Vector<T>::Begin() const
{
  return VectorIterator<T>(elements);
}

template <typename T>
VectorIterator<T> Vector<T>::End() const
{
	return VectorIterator<T>(elements+count-1);
}

#ifdef GRAD_STUDENT
// Erase and insert
template <typename T>
void Vector<T>::Erase(const VectorIterator<T>& it)
{
}

template <typename T>
void Vector<T>::Insert(const T& rhs, const VectorIterator<T>& it)
{
}
#endif

// Implement the iterators

// Constructors
template <typename T>
VectorIterator<T>::VectorIterator()
{
	current = NULL;
}

template <typename T>
VectorIterator<T>::VectorIterator(T* c)
{
	current = c;
}

// Copy constructor
template <typename T>
VectorIterator<T>::VectorIterator(const VectorIterator<T>& rhs)
{
	  current = rhs.current;
}

// Iterator defeferencing operator
template <typename T>
T& VectorIterator<T>::operator*() const
{
	return *current;
}

// Prefix increment
template <typename T>
VectorIterator<T>  VectorIterator<T>::operator++()
{
	++current;
	return this;
}

// Postfix increment
template <typename T>
VectorIterator<T> VectorIterator<T>::operator++(int)
{
  // 2036 knowlege
  VectorIterator<T> current_lineVal= *this;
  current++;
  return current_lineVal;
}

// Comparison operators
template <typename T>
bool VectorIterator<T>::operator !=(const VectorIterator<T>& rhs) const
{
	if (current != rhs.current) return true;
  	else return false;
}
template <typename T>
bool VectorIterator<T>::operator ==(const VectorIterator<T>& rhs) const
{
	if (current == rhs.current) return true;
  	else return false;
}




