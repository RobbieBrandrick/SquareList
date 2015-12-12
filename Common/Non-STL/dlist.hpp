#if !defined(GUARD_DLIST_HPP)
#define GUARD_DLIST_HPP

/** @file: dlist.hpp
@author Robbie Brandrick
@author r_brandrick@fanshaweonline.ca
@date 2012-02-24
@version 0.1.0
@note Targets Visual C++ 10.0
@briefs Custom Doubly Linkedlist.
		dlist class declaration and implementation.
		dlist iterator declarations and implementation
		dlist constant iterator declarations and implementation
@invariant dlist will always contain a head node*/

#include <iterator>
#include <algorithm>
#include <cassert>
//Forward Declaration
template<typename T_> class dlist;
template<typename T_> class dlist_iterator;
template<typename T_> class const_dlist_iterator;

template<typename T_>
class dlist_node{
	//Allow The Following class to access dlist_node private members
	template<typename T_> friend class dlist;
	template<typename T_> friend class dlist_iterator;
	template<typename T_> friend class const_dlist_iterator;

public:
	typedef T_				value_type;
	typedef T_&				reference_type;
	typedef T_ const&		const_reference_type;
	typedef dlist_node<T_>*	ptr_type;

	explicit dlist_node(const_reference_type data) : elem_(data), next_(0), prev_(0){ }
	dlist_node(dlist_node<value_type> const& node) :  elem_(node.elem_), next_(node.next_), prev_(node.prev_){ }
	dlist_node() : next_(0), prev_(0){}
	virtual ~dlist_node(){};

	dlist_node& operator=( dlist_node const& node);

private:
	value_type  elem_;
	ptr_type	next_;
	ptr_type	prev_;

};

/*		@fn:		dlist_node& operator=( dlist_node const& rhs);
*		@brief:		Assignment Operator
*		@pram:		dlist_node rhs [in]
*		@return:    newly assigned dlist_node 
*		@pre:		Parameter object must have been constructed 
*		@post:		The lhs or "this" receives the rhs value*/
template <typename T_>
dlist_node<T_>& dlist_node<T_>::operator=(dlist_node const& rhs)
{
	this->next_ = rhs.next_;
	this->prev_ = rhs.prev_;
	this->elem_ = rhds.elem_;

	return *this;
}

template<typename T_>
class dlist{
	//Allow The Following class to access dlist private members
	template<typename T_> friend class dlist_iterator;
	template<typename T_> friend class const_dlist_iterator;
public:
	typedef std::size_t			size_type;
	typedef std::ptrdiff_t		difference_type;
	typedef T_					value_type;
	typedef T_&					reference_type;
	typedef T_ const&			const_reference_type;
	typedef dlist<T_>			ptr_type;
	typedef dlist_node<T_>		node_type;
	typedef dlist_iterator<T_>	iterator;
	typedef const_dlist_iterator<T_> const_iterator;	
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
	
	dlist();
	dlist(dlist<value_type> const& rhs);
	dlist(dlist<value_type> && rhs);
	dlist& operator=( dlist && list);
	virtual ~dlist();
	
	bool operator==(dlist<T_> & rhs);
	bool operator!=(dlist<T_> & rhs);

	iterator begin(){return iterator(head_->next_, this);}
	const_iterator begin()const{return const_iterator(head_->next_, this);}
	const_iterator cbegin() const{return const_iterator(head_->next_, this);}

	reverse_iterator rbegin(){return reverse_iterator(end());}
	const_reverse_iterator rbegin()const{return const_reverse_iterator(cend());}
	const_reverse_iterator crbegin()const{return const_reverse_iterator(cend());}

	iterator end(){return iterator(head_, this);}
	const_iterator end() const{return const_iterator(head_, this);}
	const_iterator cend() const{return const_iterator(head_, this);}
	
	reverse_iterator rend(){return reverse_iterator(begin());}
	const_reverse_iterator rend()const{return const_reverse_iterator(cbegin());}
	const_reverse_iterator crend()const{return const_reverse_iterator(cbegin());}
	
	reference_type front();
	reference_type back();
	size_type size(){return size_;}
	bool empty(){return size_ == 0;}
	void clear();
	void push_back(const_reference_type value);
	void push_front(const_reference_type value);
	void pop_back();
	void pop_front();

	iterator insert( const iterator position, const_reference_type x);
	iterator erase(iterator& position);
private:
	node_type* head_;
	node_type* scanner_;
	size_type size_;

	void dispose();
};
/*		@fn:	    dlist();
*		@brief:		default constructor
*		@pram:		none.
*		@return:	none.
*		@pre:		none.
*		@post:		A dlist object will be constructed.*/
template< typename T_>
dlist<T_>::dlist() : head_(new typename node_type), size_(0){
	head_->next_ = head_;
	head_->prev_ = head_;
}
/*		@fn:		dlist(dlist<value_type> const& rhs);
*		@brief:		rhs constructor
*		@pram:		dlist<T_> const& rhs [in] object to rhs.
*		@return:	none.
*		@pre:		none.
*		@post:		A dlist object will be constructed with the prototype of the parameter*/
template< typename T_>
dlist<T_>::dlist(dlist<T_> const& rhs){
	head_ = new node_type;
	head_->next_ = head_;
	head_->prev_ = head_;
	size_ = 0;
	for(auto iter = rhs.cbegin(); iter != rhs.cend(); iter++){
		push_back(*iter);
	}
}
/*		@fn:		dlist(dlist<value_type> && rhs);
*		@brief:		move constructor
*		@pram:		dlist<T_> && rhs [in] object to move from.
*		@return:	none.
*		@pre:		none.
*		@post:		A dlist object rhs will be  move to this.*/
template< typename T_>
dlist<T_>::dlist(dlist<T_> && rhs) : head_(rhs.head_), scanner_(rhs.scanner_), size_(rhs.size_){
	rhs.head_ = nullptr;
	rhs.scanner_ = nullptr;
	rhs.size_ = 0;

}
/*		@fn:		dlist& operator =(dlist<value_type> && rhs);
*		@brief:		move assignment
*		@pram:		dlist<T_> && rhs [in] object to move from.
*		@return:	dlist<T_>&, reference to the newly initialized object.
*		@pre:		none.
*		@post:		A dlist object 'rhs' will be  move to this*/
template< typename T_>
dlist<T_>& dlist<T_>::operator=(dlist<T_> && rhs){
	dispose();
	this->head_ = rhs.head_;
	rhs.head_ = nullptr;
	
	this->scanner_ = rhs.scanner_;
	rhs.scanner_ = nullptr;
	
	this->size_ = rhs.size_;
	rhs.size_ = 0;

	return *this;
}
/*		@fn:		~dlist();
*		@brief:		destructs the current object and calls the dispose() method.
*		@pram:		none.
*		@return:		none.
*		@pre:		none.
*		@post:		object of dlist will be destructed*/
template< typename T_>
dlist<T_>::~dlist(){
	dispose();
}
/*		@fn:		bool operator==(dlist<T_> const& lhs);
*		@brief:		Equality Operator
*		@pram:		dlist<T_> const& lhs[in] value to compare against
*		@return:	bool indicating whether or not the values are the same
*		@pre:		none.
*		@post:		indication of whether or not the values are the same.*/
template< typename T_>
bool dlist<T_>::operator==(dlist<T_> & rhs){
	return (this->size() == rhs.size() && std::equal(this->cbegin(), this->cend(), rhs.cbegin()));
}
/*		@fn:		bool operator!=(dlist<T_> const& lhs);
*		@brief:		inequality Operator
*		@pram:		dlist<T_> const& lhs[in] value to compare against
*		@return:	bool indicating whether or not the values are different
*		@pre:		none.
*		@post:		indication of whether or not the values are different*/
template< typename T_>
bool dlist<T_>::operator!=(dlist<T_> & rhs){
	return !(*this == rhs);
}
/*		@fn:        void push_back(const_reference_type value);
*		@brief:		Adds a new node to the head_'s prev_ member
*		@pram:		const_reference_type value [in] nodes value to be created.
*		@return:		void.
*		@pre:		the value parameter must be the same type as the dlist
*		@post:		a value node is added to the back of list*/
template< typename T_>
void dlist<T_>::push_back(typename dlist<T_>::const_reference_type value){
	node_type* item = new node_type(value);
	scanner_ = head_->prev_;
	item->next_ = head_;
	item->prev_ = scanner_;
	scanner_->next_ = item;
	head_->prev_ = item;


	++size_;
}
/*		@fn:        void push_front(const_reference_type value);
*		@brief:		Adds a new node to the head_'s next_ member
*		@pram:		const_reference_type value [in] nodes value to be created.
*		@return:		void.
*		@pre:		the value parameter must be the same type as the dlist
*		@post:		a value node is added to the front of list.*/
template< typename T_>
void dlist<T_>::push_front(typename dlist<T_>::const_reference_type value){
	node_type* item = new node_type(value);
	scanner_ = head_->next_;
	item->prev_ = head_;
	item->next_ = scanner_;
	scanner_->prev_ = item;
	head_->next_ = item;

	++size_;
}
/*		@fn:        void :pop_back()
*		@brief:		removes a node from the head_'s prev_ member
*		@pram:		none.
*		@return:		void.
*		@pre:		There must be at least one node, other than the head, in the dlist
*		@post:		a value node is removed from the back of list*/
template< typename T_>
void dlist<T_>::pop_back(){
	assert(!(size_ == 0));
	assert(!(head_->prev_ == head_ || head_->next_ == head_));

	node_type* item = head_->prev_;
	scanner_ = head_->prev_->prev_;
	scanner_->next_ = head_;
	head_->prev_ = scanner_;
	delete item;
	--size_;
}
/*		@fn:        void :pop_front()
*		@brief:		removes a node from the head_'s next_ member
*		@pram:		none.
*		@return:		void.
*		@pre:		There must be at least one node, other than the head, in the dlist
*		@post:		a value node is removed from the front of list*/
template< typename T_>
void dlist<T_>::pop_front(){
	assert(!(size_ == 0));
	assert(!(head_->prev_ == head_ || head_->next_ == head_));

	node_type* item = head_->next_;
	scanner_ = head_->next_->next_;
	scanner_->prev_ = head_;
	head_->next_ = scanner_;
	delete item;
	--size_;
}
/*		@fn:		void dispose()
*		@brief:		Cleans up all the dynamic memory/raw pointers
*		@pram:		none.
*		@return:	void.
*		@pre:		a dlist object must have been created
*		@post:		All the dynamic memory is cleaned up*/
template< typename T_>
void dlist<T_>::dispose(){
	node_type* item = (node_type *)0;

	if(size_ == 0){
		delete head_;
		return;
	}

	scanner_ = head_->next_;
	while ( scanner_ != head_ ) {
		item = scanner_;
		scanner_ = scanner_->next_;
		delete item;
	}
	item = head_;

	delete item;
}
/*		@fn:		void clear()
*		@brief:		Empties all of dlist's nodes
*		@pram:		none.
*		@return:	void.
*		@pre:		a dlist object must have been created
*		@post:		All the dynamic memory is cleaned up and dlist will only 
					contain the head_ node*/
template< typename T_>
void dlist<T_>::clear(){
	if(this->size() == 0)
		return;

	dispose();
	head_ = new node_type();
	head_->next_ = head_;
	head_->prev_ = head_;
	size_ = 0;
}
/*		@fn:		reference_type front()
*		@brief:		Returns the first element in the list
*		@pram:		none.
*		@return:	reference [in] reference to the first element in the list
*		@pre:	    There must be at least one element in the list
*		@post:		The first element is returned to the client.*/
template< typename T_>
typename dlist<T_>::reference_type dlist<T_>::front(){
	assert(!(size_ == 0));
	assert(!(head_->prev_ == head_ || head_->next_ == head_));
	return this->head_->next_->elem_;
}
/*		@fn:		reference_type back()
*		@brief:		Returns the last element in the list
*		@pram:		none.
*		@return:	reference [in] reference to the last element in the list
*		@pre:	    There must be at least one element in the list
*		@post:		The last element is returned to the client
*       @invariant  There is a head node linking all the other nodes.*/
template< typename T_>
typename dlist<T_>::reference_type dlist<T_>::back(){
	assert(!(size_ == 0));
	assert(!(head_->prev_ == head_ || head_->next_ == head_));
	return this->head_->prev_->elem_;
}
/*		@fn:		iterator insert(iterator position, const_reference_type x)
*		@brief:		The list container is extended by inserting new elements before the element at position.
*		@pram:		iterator position [in] Position in the container where the new elements are inserted.
*					const_reference_type x [in] Value to be used to initialize the inserted elements.
*		@return:	iterator that points to the newly inserted element.
*		@pre:	    None
*		@post:		parameter x is added to the list before the parameter position node*/
template< typename T_>
typename dlist<T_>::iterator dlist<T_>::insert(typename const dlist<T_>::iterator position, typename dlist<T_>::const_reference_type x){
	assert(!(this != position.dlist_));
	node_type* item = new node_type(x);
	scanner_ = position.node_->prev_;
	item->prev_ = scanner_;
	scanner_->next_ = item;
	item->next_ = position.node_;
	position.node_->prev_ = item;
	++size_;
	return iterator(item,this);
}
/*		@fn:		iterator erase(iterator position)
*		@brief:		Removes from the list container either a single element
*		@pram:		iterator position [in] Iterator pointing to a single element to be removed from the list.
*		@return:	A bidirectional iterator pointing to the new location of the element that followed 
*						the last element erased by the method call
*		@pre:	    There must be at least one element in the list
*		@post:		parameter position is deleted from the list.*/
template< typename T_>
typename dlist<T_>::iterator dlist<T_>::erase(typename dlist<T_>::iterator &position){
	assert(!(size_ == 0));
	assert(!(head_->prev_ == head_ || head_->next_ == head_));
	assert(!(head_ == position.node_ ));
	assert(!(this != position.dlist_));

	scanner_ = position.node_->next_;
	position.node_->prev_->next_ = scanner_; 
	scanner_->prev_ = position.node_->prev_;
	delete position.node_;
	--size_;
	return iterator(scanner_, this);
}

template<typename T_>
class dlist_iterator : public std::iterator<std::bidirectional_iterator_tag, T_>
{
	//Allow The Following class to access dlist_iterator private members
	template<typename T_> friend class dlist;
	template<typename T_> friend class const_dlist_iterator;
public:
	typedef dlist_node<T_>* node_ptr;
	typedef dlist<T_>* dlist;

	dlist_iterator(){ }
	dlist_iterator(node_ptr node, dlist myList ) : dlist_(myList), node_(node){}
	dlist_iterator(dlist_iterator<T_> const& iter) : dlist_(iter.dlist_), node_(iter.node_){}
	~dlist_iterator();
	
	dlist_iterator<T_>& operator=(dlist_iterator<T_> const& lhs);
	dlist_iterator& operator++();
	dlist_iterator operator++(int);
	dlist_iterator& operator--();
	dlist_iterator operator--(int);
	
	reference operator*();
	const reference operator*() const;
	bool operator==(dlist_iterator<T_> const& lhs) const;
	bool operator!=(dlist_iterator<T_> const& lhs) const;

private:
	node_ptr node_;
	dlist dlist_;
};
/*		@fn:		~dlist_iterator()
*		@brief:		Sets the pointers to nullptr on destruction
*		@pram:		None
*		@return:	none.
*		@pre:		none.
*		@post:		Object is destructed*/
template<typename T_>
dlist_iterator<T_>::~dlist_iterator(){
	node_ = nullptr;
	dlist_ = nullptr;
}
/*		@fn:		dlist_iterator& operator=(dlist_iterator const& lhs);
*		@brief:		Assignment Operator
*		@pram:		dlist_iterator const& lhs [in] value to assign this from
*		@return:	dlist_iterator& newly assigned object
*		@pre:		None
*		@post:		this contains the private members of lhs*/
template<typename T_>
typename dlist_iterator<T_>& dlist_iterator<T_>::operator=(typename dlist_iterator<T_> const& lhs){
	this->dlist_ = lhs.dlist_;
	this->node_ = lhs.node_;
	return *this;
}
/*		@fn:		dlist_iterator<T_> operator++(); 
*		@brief:		Prefix increments the squarelist_iterator object
*		@pram:		none - prefix indicator.
*		@return:	dlist_iterator<T_> of the incremented iterator.
*		@pre:		There must be a next element in the connecting aggregate.
*		@post:		object is incremented*/
template<typename T_>
typename dlist_iterator<T_>& dlist_iterator<T_>::operator++(){
	assert(!(node_ == dlist_->head_));
	node_ = node_->next_;
	return *this;
}
/*		@fn:		dlist_iterator<T_> operator++(int); 
*		@brief:		Prefix increments the squarelist_iterator object
*		@pram:		none - postfix indicator.
*		@return:	dlist_iterator<T_> of the incremented iterator.
*		@pre:		There must be a next element in the connecting aggregate.
*		@post:		object is incremented*/
template<typename T_>
typename dlist_iterator<T_> dlist_iterator<T_>::operator++(int){
	dlist_iterator<T_> temp = *this;
	++*this;
	return (temp);
}
/*		@fn:		dlist_iterator<T_> operator--(); 
*		@brief:		Prefix decrement the squarelist_iterator object
*		@pram:		int [in] prefix indicator.
*		@return:	dlist_iterator<T_> of the decremented iterator.
*		@pre:		There must be a next element in the connecting aggregate.
*		@post:		object is decremented*/
template<typename T_>
typename  dlist_iterator<T_>& dlist_iterator<T_>::operator--(){
	assert(!(node_ == dlist_->head_->next_));
	node_ = node_->prev_;
	return *this;
}
/*		@fn:		dlist_iterator<T_> operator--(int); 
*		@brief:		Prefix decrement the squarelist_iterator object
*		@pram:		int [in] postfix indicator.
*		@return:	dlist_iterator<T_> of the decremented iterator.
*		@pre:		There must be a next element in the connecting aggregate.
*		@post:		object is decremented*/
template<typename T_>
typename dlist_iterator<T_> dlist_iterator<T_>::operator--(int){
	dlist_iterator<T_> temp = *this;
	--*this;
	return (temp);
}
/*		@fn:		reference operator*();
*		@brief:		Returns a reference to the value type
*		@pram:		None
*		@return:	a reference to the value type
*		@pre:		Parameter object must have been constructed
*		@post:		Returns a reference to the value type*/
template<typename T_>
typename dlist_iterator<T_>::reference dlist_iterator<T_>::operator*(){
	assert(!(node_ == dlist_->head_));
	return node_->elem_;
}
/*		@fn:		const reference operator*() const;
*		@brief:		Returns a constant reference to the value type
*		@pram:		None
*		@return:	a constant reference to the value type
*		@pre:		Parameter object must have been constructed 
*		@post:		Returns a constant reference to the value type*/
template<typename T_>
typename const dlist_iterator<T_>::reference dlist_iterator<T_>::operator*() const{
	assert(!(node_ == dlist_->head_));
	return node_->elem_;
}
/*		@fn:		bool operator-=(dlist_iterator<T_> const& rhs) const
*		@brief:		Checks if the rhs is equal to this
*		@pram:		dlist_iterator<T_> const& rhs) [in] object to compare against
*		@return:	bool indicating if they are the same
*		@pre:		Parameter object must have been constructed
*		@post:		client receives bool indicating if they are the same*/
template<typename T_>
bool dlist_iterator<T_>::operator==(typename dlist_iterator<T_> const& lhs) const{
	return this->node_->elem_ == lhs.node_->elem_ && this->node_ == lhs.node_ && this->dlist_ == lhs.dlist_ ;
}
/*		@fn:		bool operator!=(dlist_iterator<T_> const& rhs) const
*		@brief:		Checks if the rhs is not equal to this
*		@pram:		dlist_iterator<T_> const& rhs) [in] object to compare against
*		@return:	bool indicating if they are different
*		@pre:		Parameter object must have been constructed
*		@post:		client receives bool indicating if they are different*/
template<typename T_>
bool dlist_iterator<T_>::operator!=(typename dlist_iterator<T_> const& lhs) const{
	return !(*this == lhs);
}
template<typename T_>
class const_dlist_iterator : public std::iterator<std::bidirectional_iterator_tag, T_, std::ptrdiff_t, const T_*, const T_&>
{
public:
	typedef const dlist_node<T_>* node_ptr;
	typedef const dlist<T_>* dlist;
	const_dlist_iterator(){ }
	const_dlist_iterator(node_ptr node, dlist myList ) : dlist_(myList), node_(node){}
	const_dlist_iterator( const_dlist_iterator<T_> const& iter) : dlist_(iter.dlist_), node_(iter.node_){}
	const_dlist_iterator( dlist_iterator<T_> const& iter) : dlist_(iter.dlist_), node_(iter.node_){}
	~const_dlist_iterator();
	const_dlist_iterator<T_>& operator=(const_dlist_iterator<T_> const& lhs);
	const_dlist_iterator& operator++();
	const_dlist_iterator operator++(int);
	const_dlist_iterator& operator--();
	const_dlist_iterator operator--(int);
	const reference operator*() const;
	bool operator==(const_dlist_iterator<T_> const& lhs) const;
	bool operator!=(const_dlist_iterator<T_> const& lhs) const;

private:
	node_ptr node_;
	dlist dlist_;
};
/*		@fn:		~const_dlist_iterator()
*		@brief:		Sets the internal pointers to nullptr on destruction
*		@pram:		None
*		@return:	none.
*		@pre:		none.
*		@post:		Object is destructed*/
template<typename T_>
const_dlist_iterator<T_>::~const_dlist_iterator(){
	node_ = nullptr;
	dlist_ = nullptr;
}
/*		@fn:		const_dlist_iterator& operator=(const_dlist_iterator const& lhs);
*		@brief:		Assignment Operator
*		@pram:		const_dlist_iterator const& lhs [in] value to assign this from
*		@return:	const_dlist_iterator& newly assigned object
*		@pre:		None
*		@post:		this contains the private members of lhs*/
template<typename T_>
typename const_dlist_iterator<T_>& const_dlist_iterator<T_>::operator=(typename const_dlist_iterator<T_> const& lhs){
	this->dlist_ = lhs.dlist_;
	this->node_ = lhs.node_;
	return *this;
}
/*		@fn:		const_dlist_iterator<T_> operator++(); 
*		@brief:		Prefix increments the squarelist_iterator object
*		@pram:		none - prefix indicator.
*		@return:	const_dlist_iterator<T_> of the incremented iterator.
*		@pre:		There must be a next element in the connecting aggregate.
*		@post:		object is incremented*/
template<typename T_>
typename const_dlist_iterator<T_>& const_dlist_iterator<T_>::operator++(){
	assert(!(node_ == dlist_->head_));
	node_ = node_->next_;
	return *this;
}
/*		@fn:		const_dlist_iterator<T_> operator++(int); 
*		@brief:		Prefix increments the squarelist_iterator object
*		@pram:		none - postfix indicator.
*		@return:	const_dlist_iterator<T_> of the incremented iterator.
*		@pre:		There must be a next element in the connecting aggregate.
*		@post:		object is incremented*/
template<typename T_>
typename const_dlist_iterator<T_> const_dlist_iterator<T_>::operator++(int){
	const_dlist_iterator<T_> temp = *this;
	++*this;
	return (temp);
}
/*		@fn:		const_dlist_iterator<T_> operator--(); 
*		@brief:		Prefix decrement the squarelist_iterator object
*		@pram:		int [in] prefix indicator.
*		@return:	const_dlist_iterator<T_> of the decremented iterator.
*		@pre:		There must be a next element in the connecting aggregate.
*		@post:		object is decremented*/
template<typename T_>
typename  const_dlist_iterator<T_>& const_dlist_iterator<T_>::operator--(){
	assert(!(node_ == dlist_->head_->next_));
	node_ = node_->prev_;
	return *this;
}
/*		@fn:		const_dlist_iterator<T_> operator--(int); 
*		@brief:		Prefix decrement the squarelist_iterator object
*		@pram:		int [in] postfix indicator.
*		@return:	const_dlist_iterator<T_> of the decremented iterator.
*		@pre:		There must be a next element in the connecting aggregate.
*		@post:		object is decremented*/
template<typename T_>
typename const_dlist_iterator<T_> const_dlist_iterator<T_>::operator--(int){
	const_dlist_iterator<T_> temp = *this;
	--*this;
	return (temp);
}
/*		@fn:		const reference operator*() const;
*		@brief:		Returns a constant reference to the value type
*		@pram:		None
*		@return:	a constant reference to the value type
*		@pre:		Parameter object must have been constructed 
*		@post:		Returns a constant reference to the value typee*/
template<typename T_>
typename const const_dlist_iterator<T_>::reference const_dlist_iterator<T_>::operator*() const{
	assert(!(node_ == dlist_->head_));
	return node_->elem_;
}
/*		@fn:		bool operator-=(const_dlist_iterator<T_> const& rhs) const
*		@brief:		Checks if the rhs is equal to this
*		@pram:		const_dlist_iterator<T_> const& rhs) [in] object to compare against
*		@return:	bool indicating if they are the same
*		@pre:		Parameter object must have been constructed
*		@post:		client receives bool indicating if they are the same*/
template<typename T_>
bool const_dlist_iterator<T_>::operator==(typename const_dlist_iterator<T_> const& lhs) const{
	return this->node_->elem_ == lhs.node_->elem_ && this->node_ == lhs.node_ &&  this->dlist_ == lhs.dlist_ ;
}
/*		@fn:		bool operator!=(const_dlist_iterator<T_> const& rhs) const
*		@brief:		Checks if the rhs is not equal to this
*		@pram:		const_dlist_iterator<T_> const& rhs) [in] object to compare against
*		@return:	bool indicating if they are different
*		@pre:		Parameter object must have been constructed
*		@post:		client receives bool indicating if they are different*/
template<typename T_>
bool const_dlist_iterator<T_>::operator!=(typename const_dlist_iterator<T_> const& lhs) const{
	return !(*this == lhs);
}
#endif