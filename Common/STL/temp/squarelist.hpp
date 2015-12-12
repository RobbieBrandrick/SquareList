#if !defined( GUARD_SQUARELIST_HPP_ )
#define GUARD_SQUARELIST_HPP_

/** @file: squarelist.hpp
@author Robbie Brandrick
@author r_brandrick@fanshaweonline.ca
@date 2012-02-24
@version 0.1.0
@note Targets Visual C++ 10.0
@briefs square list class declaration and implementation.
@		square list iterator declarations and implementation
*/
#include <list>
#include <memory>
#include <algorithm>

#pragma region squarelist

//forward declare iterator
template<typename T_> class squarelist_iterator;

/*square list class declaration*/
template<typename T_>
class squarelist{
		friend class squarelist_iterator<T_>;
public:
		//General Typedefs
		typedef std::size_t					size_type;
		typedef T_							value_type;
		typedef T_ &						reference;
		typedef T_ const &					const_reference;
		typedef T_ *						pointer;
		typedef	T_ const *					const_pointer;

		typedef squarelist_iterator<T_>			iterator;
		typedef	squarelist_iterator<T_> const	const_iterator;
		typedef	std::ptrdiff_t	difference_type;

		typedef	std::reverse_iterator<iterator>			reverse_iterator;
		//typedef	std::reverse_iterator<const_iterator>	const_reverse_iterator;
private:
		typedef std::list<T_>				list;
		typedef std::shared_ptr<list>		inner_list;
		typedef std::list<inner_list>	    outter_list;
		typedef std::shared_ptr<outter_list>		squarelist_container;
private:
		squarelist_container		squarelist_;
		size_type					size_;
public:
		squarelist() : squarelist_(squarelist_container( new outter_list())), size_(0){this->squarelist_->push_back(inner_list(new list()));}
		squarelist( squarelist<value_type> & slist ) : squarelist_( slist.squarelist_ ),size_(slist.size_){}
		squarelist( squarelist<value_type> && slist );
		~squarelist(){}

		squarelist<value_type>& operator=(squarelist<value_type> const& other);
		squarelist<value_type>& operator=(squarelist<value_type> && other);

		iterator begin (){return iterator(this->squarelist_->begin(),this->squarelist_->end(),this->squarelist_->front()->begin());}
		reverse_iterator rbegin (){return reverse_iterator(end());}

		//const_iterator cbegin () const{return const_iterator(this->squarelist_->cbegin(),this->squarelist_->cend(),this->squarelist_->front()->cbegin());}

		iterator end (){return iterator(this->squarelist_->end(), this->squarelist_->end(),this->squarelist_->back()->end());}
		//const_iterator cend () const {return const_iterator(this->squarelist_->cend(), this->squarelist_->cend(),this->squarelist_->back()->cend());}
		reverse_iterator rend (){return reverse_iterator(begin());}
		void clear();
		bool empty();
		reference front();
		const_reference front() const;

		reference back();
		const_reference back() const;

		//iterator erase(const_reference  value);
		iterator erase(iterator position);
		void erase (const_reference x );
		void insert (const_reference x );

		size_type size() const;
private:
		void putInVertList(const_reference x);
		bool eraseInVertList(const_reference x);
		iterator eraseInVertList(iterator x);
		void balance();
		void shiftLeft(typename outter_list::iterator iter);
		void shiftRight(typename outter_list::iterator iter);
#if defined(_DEBUG)
		int is_square();
		int is_sorted();
#endif
};

#pragma endregion		

/*		@fn:		       squarelist( squarelist<value_type> && slist ) 
*		@brief:		Move Constructor
*		@pram:		squarelist<value_type>  [in] squarelist to move from
*		@return:		nothing
*		@pre:		
*		@post:		
*/
template<typename T_>
inline squarelist<T_>::squarelist( squarelist<value_type> && slist ) 
		:	squarelist_( slist.squarelist_ )
		,	size_(slist.size_){
				slist.squarelist_ = nullptr;
				slist.size_ = 0;
}
/*		@fn:		       reference front();
*		@brief:		Get the first element in the square list
*		@pram:		none.
*		@return:		reference to the first element in the square list
*		@pre:		there must be at least one element in the square list
*		@post:		a reference to the first element will be returned. */
template<typename T_>
typename squarelist<T_>::reference squarelist<T_>::front(){ 
		return this->squarelist_->front()->front();
}
/*		@fn:		       const_reference front();
*		@brief:		Get the first element in the square list
*		@pram:		none.
*		@return:		const_reference to the first element in the square list
*		@pre:		there must be at least one element in the square list
*		@post:		a const_reference to the first element will be returned. */
template<typename T_>
typename squarelist<T_>::const_reference squarelist<T_>::front() const{
		return this->squarelist_.front()->front();
}
/*		@fn:		       reference back();
*		@brief:		Get the last element in the square list
*		@pram:		none.
*		@return:		const_reference to the last element in the square list
*		@pre:		there must be at least one element in the square list
*		@post:		a const_reference to the last element will be returned. */
template<typename T_>	
typename squarelist<T_>::reference squarelist<T_>::back(){
		return this->squarelist_->back()->back();
}
/*		@fn:		       const_reference back();
*		@brief:		Get the last element in the square list
*		@pram:		none.
*		@return:		const_reference to the last element in the square list
*		@pre:		there must be at least one element in the square list
*		@post:		a const_reference to the last element will be returned. */
template<typename T_>	
typename squarelist<T_>::const_reference squarelist<T_>::back() const{
		return this->squarelist_->back()->back();
}
/*		@fn:		       size_type size();
*		@brief:		Get the size of the square list
*		@pram:		none.
*		@return:		a size_type of the square list size
*		@pre:		none.
*		@post:		a value type of the squarelist size will be returned. */
template<typename T_>	
typename squarelist<T_>::size_type squarelist<T_>::size() const{ 
		return size_; 
}

/*		@fn:		       void clear();
*		@brief:		clears all the elements in the squarelist
*		@pram:		none.
*		@return:		nothing.
*		@pre:		None.
*		@post:		The squarelist container will not contain elements*/
template<typename T_>
typename void squarelist<T_>::clear() { 
		this->squarelist_->clear(); 
		this->size_ = 0;
}
/*		@fn:		       void empty();
*		@brief:		Checks if the squarelist contains any elements
*		@pram:		none.
*		@return:		bool indicating if the square list container is empty or not.
*		@pre:		None.
*		@post:		whether or not the container is empty*/
template<typename T_>	
typename bool squarelist<T_>::empty() { 
		return this->size_ == 0; 
}
/*		@fn:		       squarelist<value_type>& operator=(squarelist<value_type> const& other);
*		@brief:		Assignment operator
*		@pram:		squarelist<value_type> const& other) [in] squarelist to be assigned to this.
*		@return:		a reference to the squarelist
*		@pre:		None.
*		@post:		The LValue will contain the data of the RValue*/
template<typename T_>
typename squarelist<T_>& squarelist<T_>::operator=(typename squarelist<T_> const& other){
		if(this != &other){
				this->size_ = other.size_;
				this->squarelist_ = other.squarelist_;
		}
		return *this;
}
/*		@fn:		       squarelist<value_type>& operator=(squarelist<value_type> const& other);
*		@brief:		Move Assignment operator
*		@pram:		squarelist<value_type> const&& other) [in] squarelist to be moved to this.
*		@return:		a reference to the squarelist
*		@pre:		None.
*		@post:		The LValue will contain the data of the RValue*/
template<typename T_>
typename squarelist<T_>& squarelist<T_>::operator=(typename squarelist<T_> && other){
		if(this != &other){
				this->size_ = other.size_;
				other.size_ = 0;
				this->squarelist_ = other.squarelist_;
				other.squarelist_ = nullptr;
		}
		return *this;	
}
/*		@fn:		       inner_list putInVertList(const_reference x);
*		@brief:		puts Value X in the square list container
*		@pram:		const_reference x [in] value to be added
*		@return:		void
*		@pre:		None
*		@post:		The ValueX will be added to the container*/
template< typename T_>
typename void squarelist<T_>::putInVertList(typename squarelist<T_>::const_reference x){
		outter_list::iterator nextIter = this->squarelist_->begin();
		outter_list::iterator iter;
		for (iter = this->squarelist_->begin(); iter != this->squarelist_->end(); iter++ ) {
				++nextIter;
				if ( nextIter == this->squarelist_->end() || x <= (*nextIter)->front()) {
						(*iter)->push_back(x);
						(*iter)->sort();
						return;
				}
		}	
}
/*		@fn:		       bool eraseInVertList(const_reference x);
*		@brief:		Finds Value X in the square list container and erases it
*		@pram:		const_reference x [in] value to be found within a the container
*		@return:		bool indicated if the value was deleted or not.
*		@pre:		Parameter x should already be in the list
*		@post:		The x value will be removed form the list*/
template< typename T_>
typename bool squarelist<T_>::eraseInVertList(typename squarelist<T_>::const_reference x){
		for (outter_list::iterator iter = this->squarelist_->begin(); iter != this->squarelist_->end(); iter++ ) {
				auto pos = std::find((*iter)->begin(), (*iter)->end(), x);
				if(pos != (*iter)->end()){
						(*iter)->erase(pos);
						if(squarelist_->size() == 1 && squarelist_->front()->size() == 0) 
								return true;
						else if ((*iter)->size() == 0)
								squarelist_->erase(iter);				

						return true;
				}
		}
		return false;
}

/*		@fn:		       bool eraseInVertList(const_reference x);
*		@brief:		Finds Value X in the square list container and erases it
*		@pram:		const_reference x [in] value to be found within a the container
*		@return:		boolean indicated if the value was deleted or not.
*		@pre:		Parameter x should already be in the list
*		@post:		The x value will be removed form the list*/
template< typename T_>
typename squarelist<T_>::iterator squarelist<T_>::eraseInVertList(typename squarelist<T_>::iterator x){
		for (outter_list::iterator iter = this->squarelist_->begin(); iter != this->squarelist_->end(); iter++ ) {	 
				if(iter == x.head_){
						auto pos = (*iter)->erase(x.elem_);
						if(squarelist_->size() == 1 && squarelist_->front()->size() == 0)
							return this->end();
						if((*iter)->size() == 0){
								squarelist_->erase(iter);
								return this->end();
						} else 
								return iterator(iter, x.headStop_, pos);
				}
				
		}
		return x;
}
/*		@fn:		       void shiftLeft(typename outter_list::iterator iter);
*		@brief:		Moves the last value on the current list back to the previous list
*		@pram:		squarelist<T_>::outter_list::iterator iter [in] list iterator gather data from
*		@return:		void
*		@pre:		A List iterator with a valid current and previous positions
*		@post:		Moves value the previous list*/
template< typename T_>
void squarelist<T_>::shiftLeft(typename squarelist<T_>::outter_list::iterator iter ){
		auto tempIter = iter++;
		if(iter == squarelist_->end()){
				--iter;
		} else {
				value_type temp = (*iter)->front();
				(*iter)->pop_front();

				if((*iter)->size() == 0){
						squarelist_->erase(iter);
						iter = tempIter;
				}
				else
						--iter;
				(*(iter))->push_back(temp);
		}
}
/*		@fn:		       void shiftLeft(typename outter_list::iterator iter);
*		@brief:		Moves the last value on the current list forward to the next list
*		@pram:		squarelist<T_>::outter_list::iterator iter [in] list iterator gather data from
*		@return:		void
*		@pre:		A List iterator with a valid current and next positions
*		@post:		Moves value the next list*/
template< typename T_>
void squarelist<T_>::shiftRight(typename squarelist<T_>::outter_list::iterator iter ){
		value_type temp = (*iter)->back();
		(*iter++)->pop_back();				
		if(iter == squarelist_->end()){
				this->squarelist_->push_back(inner_list(new list()));
				this->squarelist_->back()->push_front(temp);
				--iter;
		} else {
				(*iter)->push_front(temp);
				--iter;
		}	
}
/*		@fn:		       void balance()
*		@brief:		Balances the square list container to a square or near square form
*		@pram:		None.
*		@return:		void
*		@pre:		None
*		@post:		the square list container will be balanced to a square or near square form*/
template< typename T_>
void squarelist<T_>::balance(){
		size_type maxDepth = static_cast<int>(std::ceil(std::sqrt( size_ * 1.0 )));
		for(outter_list::iterator iter = squarelist_->begin(); iter != squarelist_->end(); iter++){
				if((*iter)->size() == maxDepth){
					continue;
				} else if ((*iter)->size() > maxDepth){
						while((*iter)->size() > maxDepth)
								shiftRight(iter);
				} else if ((*iter)->size() < maxDepth){
					shiftLeft(iter);
				} 		
		}  
}

/*		@fn:		       void insert(const_reference x)
*		@brief:		Inserts an element to the squqre list while keeping it sorted and balanced 
*						in a square or near square form.
*		@pram:		const_reference x [in] value to be added
*		@return:		void
*		@pre:		A squarelist object must be created and a valid type must be passed in to this method
*		@post:		value will be added and the squarelist will be sorted and squared*/
template<typename T_>
void squarelist<T_>::insert(typename squarelist<T_>::const_reference x ){
#if defined (_DEBUG)
		assert(is_sorted());
		assert(is_square());
#endif
		if(size_ == 0) {
				this->squarelist_->front()->push_back(x);
		}else{
				putInVertList( x );
		}		
		++size_;
		balance();
#if defined (_DEBUG)
		assert(is_sorted());
		assert(is_square());
#endif
} 

/*		@fn:		       void erase(const_reference x)
*		@brief:		erase an element to the squqre list while keeping it sorted and balanced 
*						in a square or near square form.
*		@pram:		const_reference x [in] value to be erased
*		@return:		void
*		@pre:		A squarelist object must be created and a valid type must be passed in to this method
*		@post:		value will be erased and the squarelist will be sorted and squared*/
template<typename T_>
void squarelist<T_>::erase(typename squarelist<T_>::const_reference x ){
#if defined (_DEBUG)
		assert(is_sorted());
		assert(is_square());
#endif
		if(size_ == 0) {
				return;
		}else{
				eraseInVertList(x);
		}		
		--size_;
		balance();
#if defined (_DEBUG)
		assert(is_sorted());
		assert(is_square());
#endif
}

/*		@fn:		       void erase(iterator x)
*		@brief:		erase an element to the squqre list while keeping it sorted and balanced 
*						in a square or near square form.
*		@pram:		iterator x [in] value to be erased
*		@return:		void
*		@pre:		A squarelist object must be created and a valid type must be passed in to this method
*		@post:		value will be erased and the squarelist will be sorted and squared*/
template<typename T_>
typename squarelist<T_>::iterator squarelist<T_>::erase(typename squarelist<T_>::iterator x ){
#if defined (_DEBUG)
		assert(is_sorted());
		assert(is_square());
#endif
		iterator pos;
		if(size_ == 0) {
				return end();
		}else{
				pos = eraseInVertList(x);
		}		
		--size_;
		balance();
#if defined (_DEBUG)
		assert(is_sorted());
		assert(is_square());
#endif

		return pos;
}

#if defined(_DEBUG)
/*		@fn:		       int is_sorted()
*		@brief:		determines if the square list is sorted
*		@pram:		None.
*		@return:		int for determining if the square list is sorted
*		@pre:		A squarelist object must be created and the compiler must be in debug mode
*		@post:		verifies with a 0 if the square list is sorted*/
template<typename T_>
int squarelist<T_>::is_sorted(){
		if(squarelist_->size() == 1 && squarelist_->front()->size() == 0) return 1;
		for(auto iter = squarelist_->cbegin(); iter != this->squarelist_->cend(); iter++){
				auto lhs = (*iter)->cbegin();
			
				for(auto rhs = ++(*iter)->cbegin(); rhs != (*iter)->cend();rhs++){
						if((*lhs) > (*rhs))
								return 0;
				}	
		}
		return 1;
}
/*		@fn:		       int is_squared()
*		@brief:		determines if the square list is squared
*		@pram:		None.
*		@return:		int for determining if the square list is squared
*		@pre:		A squarelist object must be created and the compiler must be in debug mode
*		@post:		verifies with a 0 if the square list is squared*/
template<typename T_>
int squarelist<T_>::is_square(){
		if(squarelist_->size() == 1 && squarelist_->front()->size() == 0) return 1;
		
		std::size_t maxDepth = static_cast<int>(std::ceil(std::sqrt( size_ * 1.0 )));

		if( this->squarelist_->size() > maxDepth)
				return 0;
		for(auto iter = this->squarelist_->cbegin(); iter != this->squarelist_->cend(); iter++){
				if((*iter)->size() > maxDepth)
						return 0;
		}

		return 1;
}
#endif

template<typename T_>
class squarelist_iterator : public std::iterator<std::bidirectional_iterator_tag, T_, std::ptrdiff_t, T_ *, T_ &>{
		friend class squarelist<T_>;
public:
		squarelist_iterator(typename squarelist<value_type>::outter_list::iterator outter, typename squarelist<value_type>::outter_list::iterator outterStop, typename squarelist<value_type>::list::iterator inner):head_(outter), headStop_(outterStop), elem_(inner){}
		squarelist_iterator(squarelist_iterator<value_type> const& slistIter) :head_(slistIter.head_), headStop_(slistIter.headStop_), elem_(slistIter.elem_){}
		squarelist_iterator(squarelist_iterator<value_type> && slist);
		squarelist_iterator(){}
		~squarelist_iterator(){}
		reference operator*() const;
		const squarelist_iterator<T_>& operator++();
		const squarelist_iterator<T_> operator++(int); 
		const squarelist_iterator<T_>& operator--();
		const squarelist_iterator<T_> operator--(int);

		squarelist_iterator& operator=(squarelist_iterator const& lhs);
		bool operator==(squarelist_iterator<T_> const& rhs) const;
		bool operator!=(squarelist_iterator<T_> const& rhs) const;
private:
		typename squarelist<value_type>::outter_list::iterator head_;
		typename squarelist<value_type>::outter_list::iterator headStop_;
		typename squarelist<value_type>::list::iterator elem_;
};
/*		@fn:		       squarelist( squarelist<value_type> && slist ) 
*		@brief:		Move Constructor
*		@pram:		squarelist<value_type>  [in] squarelist to move from
*		@return:		nothing
*		@pre:		
*		@post:		
*/
template<typename T_>
inline squarelist_iterator<T_>::squarelist_iterator( typename squarelist_iterator<value_type> && slistIter ) 
		: head_(slistIter.head_), headStop_(slistIter.headStop_), 
				elem_(slistIter.elem_){
					//	slistIter.head_ = nullptr;
					//	slistIter.headStop_ = nullptr;
					//	slistIter.elem_ = nullptr;
				}
/*		@fn:		       const reference operator*() const;
*		@brief:		Returns a constant reference to the value type
*		@pram:		None
*		@return:		a constant reference to the value type
*		@pre:		Parameter object must have been constructed using the three arg constructor
*		@post:		Returns a constant reference to the value type*/
template<typename T_>
typename squarelist_iterator<T_>::reference squarelist_iterator<T_>::operator*() const{
		return (*this->elem_);
}
/*		@fn:		       bool operator==(squarelist_iterator<T_> const& rhs) const
*		@brief:		Checks if the rhs is equal to this object
*		@pram:		squarelist_iterator<T_> const& rhs) [in] object to compare against
*		@return:		bool indicating if they are the same
*		@pre:		Parameter object must have been constructed using the three arg constructor
*		@post:		bool indicating if they are the same*/
template<typename T_>
bool squarelist_iterator<T_>::operator==(typename squarelist_iterator<T_> const& rhs) const{
	return this->head_ == rhs.head_ && this->elem_ == rhs.elem_;
}
/*		@fn:		       bool operator!=(squarelist_iterator<T_> const& rhs) const
*		@brief:		Checks if the rhs is not equal to this
*		@pram:		squarelist_iterator<T_> const& rhs) [in] object to compare against
*		@return:		bool indicating if they are different
*		@pre:		Parameter object must have been constructed using the three arg constructor
*		@post:		bool indicating if they are different*/
template<typename T_>
bool squarelist_iterator<T_>::operator!=(typename squarelist_iterator<T_> const& rhs) const{
	return !(*this == rhs);
}
/*		@fn:		       const squarelist_iterator<T_> operator++(); 
*		@brief:		Prefix increments if the squarelist_iterator object
*		@pram:		none - prefix indicator.
*		@return:		squarelist_iterator<T_> of the incremented iterator.
*		@pre:		There must be a next element in the connecting aggregate.
*		@post:		object is incremented*/
template<typename T_>
const squarelist_iterator<T_>& squarelist_iterator<T_>::operator++(){
		++elem_;
		if(elem_ == (*head_)->end()){
				++head_;
				if(head_ != headStop_)
						elem_ = (*head_)->begin();
		}
		return *this;
}
/*		@fn:		       const squarelist_iterator<T_> operator++(int); 
*		@brief:		Postfix increments if the squarelist_iterator object
*		@pram:		int - postfix indicator.
*		@return:		squarelist_iterator<T_>  of the previous iterator object.
*		@pre:		There must be a next element in the connecting aggregate.
*		@post:		object is incremented*/
template<typename T_>
const squarelist_iterator<T_> squarelist_iterator<T_>::operator++(int){
		squarelist_iterator<T_> temp = *this;
		++*this;
		return temp;
}	
/*		@fn:		       const squarelist_iterator<T_> operator--(); 
*		@brief:		Prefix decrement of the squarelist_iterator object
*		@pram:		none - prefix indicator.
*		@return:		squarelist_iterator<T_>  of the decremented iterator.
*		@pre:		There must be a previous element in the connecting aggregate.
*		@post:		object is decremented*/
template<typename T_>
const squarelist_iterator<T_>& squarelist_iterator<T_>::operator--(){
		if(head_ == headStop_){
			--head_;
		    elem_ = --(*head_)->end();
		} else if( elem_ == (*head_)->begin()){
			--head_;
			elem_ = --(*head_)->end();
		} else {
				--elem_;
		}
		return *this;
}
/*		@fn:		       const squarelist_iterator<T_> operator--(int); 
*		@brief:		Postfix decrements if the squarelist_iterator object
*		@pram:		int - postfix indicator.
*		@return:		squarelist_iterator<T_>  of the previous iterator object.
*		@pre:		There must be a previous element in the connecting aggregate.
*		@post:		object is decremented*/
template<typename T_>
const squarelist_iterator<T_> squarelist_iterator<T_>::operator--(int){
		squarelist_iterator<T_> temp = *this;
		--*this;
		return temp;
}
/*		@fn:		       squarelist_iterator& operator=(squarelist_iterator const& lhs);
*		@brief:		squarelist_iterator assignment operator
*		@pram:		 squarelist_iterator<T_> const& lhs [in] value to gather properties from
*		@return:		squarelist_iterator<T_>  of the newly assigned object
*		@pre:		The parameter's object must be created.
*		@post:		The current squarelist_iterator<T_> object contains the values of the parameter */
template<typename T_>
inline typename squarelist_iterator<T_>& squarelist_iterator<T_>::operator=(typename  squarelist_iterator<T_> const& lhs){
		this->head_ = lhs.head_;
		this->headStop_ = lhs.headStop_;
		this->elem_ = lhs.elem_;
		return *this;
}
#endif