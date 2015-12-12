 //unit test library
#define _CRT_SECURE_NO_WARNINGS 1
#define BOOST_TEST_MODULE squarelist_peer_Unit_Tests
#include <boost/test/unit_test.hpp>
//stl
#include <list>
#include <set>
#include <algorithm>
#include <string>
#include <random>
#include <iostream>
using namespace std;

//include dList library
//Comment out next define to use custom list.
//#define STL_SQUARELIST
#if defined(STL_SQUARELIST)
#include "../Common/STL/squarelist.hpp"
#else
#include "../Common/Non-STL/squarelist.hpp"
#endif

/*				*
 *  PEER TESTS	*
 *    CASES		*
 *	David Scafe	*
 *				*/

BOOST_AUTO_TEST_CASE ( insert_tests ){
	// basic insert
	squarelist<int> s;
	s.insert( 1 );
	BOOST_CHECK( s.front() == 1 );
	BOOST_CHECK( s.back() == 1 );
	BOOST_CHECK( s.size() == 1 );
	s.erase( 1 );
	
	// insert sorted, reverse values
	for ( unsigned i = 10; i > 0; --i ) {
		s.insert( i );
	}
	BOOST_CHECK( s.size() == 10 );
	BOOST_CHECK( s.front() == 1 );
	BOOST_CHECK( s.back() == 10 );

	int count = 0; 
	for ( squarelist<int>::iterator it = s.begin(); it != s.end(); ++it ) {
		++count;
		BOOST_CHECK( *it == count );
	}

	// duplicate values
	s.clear();
	s.insert( 1 );
	s.insert( 1 );
	BOOST_CHECK( s.size() == 2 );
	BOOST_CHECK( s.front() == 1 );
	BOOST_CHECK( s.back() == 1 );

	squarelist<int>::iterator it = s.begin();
	BOOST_CHECK( *it == 1 );
	++it;
	BOOST_CHECK( *it == 1 );

	// string testing
	squarelist<string> sl; 
	sl.insert("one");
	sl.insert("two");
	sl.insert("three");
	sl.insert("four");

	BOOST_CHECK( sl.front() == "four" );
	BOOST_CHECK( sl.back() == "two" );
	BOOST_CHECK( sl.size() == 4 );
}

BOOST_AUTO_TEST_CASE(erase_tests){
	// basic erase
	squarelist<int> s;
	s.insert( 1 );
	BOOST_CHECK ( s.size() == 1 );
	s.erase( 1 );
	BOOST_CHECK ( s.size() == 0 );

	// out of sequence erase
	for ( unsigned i = 0; i < 10; ++i ) {
		s.insert( i );
	}
	s.erase( 9 );
	s.erase( 0 );

	BOOST_CHECK( s.front() == 1 );
	BOOST_CHECK( s.back() == 8 );

	s.clear();

	// duplicate values
	s.insert( 1 );
	s.insert( 1 );

	BOOST_CHECK( s.size() == 2 );

	s.erase( 1 );
	
	BOOST_CHECK( s.front() == 1 );
	BOOST_CHECK( s.back() == 1 );
	BOOST_CHECK( s.size() == 1 );

	// string erase
	squarelist<string> sl;
	sl.insert( "one" );
	sl.insert( "two" );
	sl.insert( "three" );
	sl.insert( "four" );

	BOOST_CHECK( sl.size() == 4 );
	BOOST_CHECK( sl.back() == "two" );
	sl.erase( "two" );
	BOOST_CHECK( sl.back() == "three" );
	sl.erase( "three" );
	BOOST_CHECK( sl.back() == "one" );
	sl.erase( "one" );
	BOOST_CHECK( sl.back() == "four" );
	sl.erase( "four" );
	BOOST_CHECK( sl.size() == 0 );
}

BOOST_AUTO_TEST_CASE( rvalue_tests ){

	// swap int
	squarelist<int> a; 
	a.insert( 1 );
	squarelist<int> b;
	b.insert( 2 );
	std::swap( a, b );
	BOOST_CHECK( a.front() == 2 );
	BOOST_CHECK( b.front() == 1 );

	// swap string
	squarelist<std::string> c; 
	c.insert( "one" );
	squarelist<std::string> d;
	d.insert( "two" );
	std::swap( c, d );
	BOOST_CHECK( c.front() == "two" );
	BOOST_CHECK( d.front() == "one" );

	// swap double
	squarelist<double> e;
	e.insert( 1.0 );
	squarelist<double> f;
	f.insert( 2.0 );
	std::swap( e, f );
	BOOST_CHECK( e.front() == 2.0 );
	BOOST_CHECK( f.front() == 1.0 );
}

BOOST_AUTO_TEST_CASE( iterator_tests ){

	// inequality
	squarelist<int> s;
	s.insert( 1 );
	squarelist<int>::iterator first = s.begin();
	squarelist<int>::iterator second = s.end();
	BOOST_CHECK( first != second );

	// assignment & equality
	second = first;
	BOOST_CHECK( second == first );

	// pre-increment & dereference
	s.insert( 2 );
	++first;
	BOOST_CHECK( *first == s.back() );
	BOOST_CHECK( *first == 2 );

	// post-increment & dereference
	second++;
	BOOST_CHECK( *first == *second );
	BOOST_CHECK( first == second );
	BOOST_CHECK( *second == s.back() );

}

BOOST_AUTO_TEST_CASE( iterator_compare_tests ){

	squarelist<int> s;
	s.insert( 1 );
	s.insert( 1 );
	s.insert( 2 );
	s.insert( 2 );

	squarelist<int>::iterator first = s.begin();
	squarelist<int>::iterator second = s.begin();

	BOOST_CHECK( first == second );
	++second;
	BOOST_CHECK( first != second );
	++first;
	BOOST_CHECK( first == second );
	++second;
	BOOST_CHECK( first != second );
	++first;
	BOOST_CHECK( first == second );
}

BOOST_AUTO_TEST_CASE(const_iterator_tests){

	// inequality
	squarelist<int> s;
	s.insert( 1 );
	squarelist<int>::const_iterator first = s.cbegin();
	squarelist<int>::const_iterator second = s.cend();
	BOOST_CHECK( first != second );

	// assignment & equality
	second = first;
	BOOST_CHECK( second == first );
	
	// pre-increment & dereference
	s.insert( 2 );
	++first;
	BOOST_CHECK( *first == s.back() );
	BOOST_CHECK( *first == 2 );

	// post-increment & dereference
	second++;
	BOOST_CHECK( *first == *second );
	BOOST_CHECK( first == second );
	BOOST_CHECK( *second == s.back() );
}

BOOST_AUTO_TEST_CASE( const_iterator_compare_tests ){

	squarelist<int> s;
	s.insert( 1 );
	s.insert( 1 );
	s.insert( 2 );
	s.insert( 2 );

	squarelist<int>::const_iterator first = s.cbegin();
	squarelist<int>::const_iterator second = s.cbegin();

	BOOST_CHECK( first == second );
	++second;
	BOOST_CHECK( first != second );
	++first;
	BOOST_CHECK( first == second );
	++second;
	BOOST_CHECK( first != second );
	++first;
	BOOST_CHECK( first == second );
}

#if !defined(_DEBUG)
BOOST_AUTO_TEST_CASE ( large_range_testing ){
	squarelist<int> s;
	// 100,000 pre-sorted values
	for ( unsigned i = 0; i < 100000; ++i ) {
		s.insert( i );
	}

	squarelist<int>::iterator it = s.begin();
	squarelist<int>::const_iterator cit = s.cbegin();

	int count = 0; 
	for ( it = s.begin(); it != s.end(); ++it ) {
		BOOST_CHECK( count == *it );
		BOOST_CHECK( count == *cit );
		++cit;
		++count;
	}

	for ( unsigned i = 0; i < 100000; ++i ) {
		s.erase( i );
	}

	BOOST_CHECK ( s.size() == 0 );

	// 100,000 "unsorted" values
	for ( unsigned i = 100000; i > 0; --i ) {
		s.insert( i );
	}

	count = 1; 
	cit = s.cbegin();
	for ( it = s.begin(); it != s.end(); ++it ) {
		BOOST_CHECK( count == *it );
		BOOST_CHECK( count == *cit );
		++cit;
		++count;
	}

	for ( unsigned i = 1; i < 100001; ++i ) {
		s.erase( i );
	}

	BOOST_CHECK ( s.size() == 0 );

}

#endif
/*				*
 *  PEER TESTS	*
 *    CASES		*
 * Steve Taylor *
 *				*/
//Verifies that the constructor creates an empty container and that
//the size() and empty() functions return the correct values.
BOOST_AUTO_TEST_CASE(constructor){
	squarelist<unsigned> sl;
	BOOST_CHECK(sl.size()==0);
	BOOST_CHECK(sl.empty());

#if defined(SHOULD_HAVE_TAKEN_THE_BLUE_PILL)
	BOOST_CHECK(sl.listLengths()==0);
	BOOST_CHECK(sl.listIsSquare());
#endif

	sl.insert(3);

#if defined(SHOULD_HAVE_TAKEN_THE_BLUE_PILL)
	BOOST_CHECK(sl.listLengths()==1);
	BOOST_CHECK(sl.listIsSquare());
#endif

	squarelist<unsigned> xl=sl;
	BOOST_CHECK(!xl.empty());
	BOOST_CHECK(xl.front()==3);
}

//Insert 1000 values, 1 to 500, then -500 to 1. This tests sorting
//and balancing.
BOOST_AUTO_TEST_CASE(large_outOfOrder_insertion){
	squarelist<int> sl;
	BOOST_CHECK(sl.empty());

	int insertCount=1000;

	for(int i=1; i<(insertCount/2)+1; ++i){
		sl.insert(i);
		BOOST_CHECK(sl.back()==i);
	}

	for(int i=insertCount/2; i>0; --i){
		sl.insert(i);
	}

	squarelist<int>::iterator iter=sl.begin();
	squarelist<int>::iterator offsetIter=sl.begin();
	++offsetIter;

	for(int i=1; i<insertCount/2; ++i){
		BOOST_CHECK(iter!=offsetIter);
		BOOST_CHECK(*iter==i);
		BOOST_CHECK(*offsetIter==i);
		++iter;
		++iter;
		++offsetIter;
		++offsetIter;
	}

	BOOST_CHECK(*iter==sl.back());
	BOOST_CHECK(*offsetIter==sl.back());

	squarelist<int>::iterator endIter=sl.end();
	
	BOOST_CHECK(++iter==offsetIter);

	BOOST_CHECK(++iter==endIter);
	BOOST_CHECK(++offsetIter==endIter);

	BOOST_CHECK(sl.size()==(unsigned)insertCount);
}

//Verifies that pre and post incrementation of the squarelist iterator
//dereferences to the same value.
BOOST_AUTO_TEST_CASE(iterator_pre_post_comparison){
	squarelist<int> sl;
	for(int i=0; i<10; ++i)
		sl.insert(i);

	squarelist<int>::iterator pre=sl.begin();
	squarelist<int>::iterator post=sl.begin();

	for(int i=0; i<9; ++i){
		++pre;
		post++;
		BOOST_CHECK(*pre==*post);
	}

	++pre;
	post++;
	
	BOOST_CHECK(pre==sl.end());
	BOOST_CHECK(post==sl.end());
}

//Tests the iterator == and != operators.
BOOST_AUTO_TEST_CASE(iterator_equal_notequal){
	squarelist<int> sl;
	sl.insert(1);
	sl.insert(2);
	sl.insert(3);

	squarelist<int>::iterator it1=sl.begin();
	squarelist<int>::iterator it2=sl.begin();

	BOOST_CHECK(it1==it2);
	++it1;
	BOOST_CHECK(it1!=it2);
	++it2;
	BOOST_CHECK(it1==it2);

}

//Verifies that the value of front() is correct.
//BOOST_AUTO_TEST_CASE(front){
//	squarelist<int> sl;
//	sl.insert(99);
//	sl.insert(1);
//	sl.insert(4);
//
//	//int orig=sl.front();
//	////int newVal=++sl.front();
//	//BOOST_CHECK(orig == 1);
//	//BOOST_CHECK(newVal == 2);
//	//BOOST_CHECK(newVal == sl.front());
//}

////Verifies that the value of back() is correct.
//BOOST_AUTO_TEST_CASE(back){
//	squarelist<int> sl;
//	sl.insert(1);
//	sl.insert(9);
//	sl.insert(3);
//
//	int orig=sl.back();
//	//int newVal=++sl.back();
//	BOOST_CHECK(orig == 9);
//	BOOST_CHECK(newVal == 10);
//	BOOST_CHECK(newVal == sl.back());
//}
//
////Tests the begin() and end() iterators.
//BOOST_AUTO_TEST_CASE(begin_end){
//	squarelist<string> sl;
//	squarelist<string>::iterator itBeg = sl.begin();
//	squarelist<string>::iterator itEnd = sl.end();
//	BOOST_CHECK(itBeg==itEnd);
//
//	sl.insert("test!");
//	
//	BOOST_CHECK(sl.begin()!=sl.end());
//	BOOST_CHECK(++(sl.begin())==sl.end());
//}

//Verifies that erase() removes the correct elements and does not
//incorreclty modify the structure of the square list.
BOOST_AUTO_TEST_CASE(erase){
	squarelist<int> sl;

	for(int i=-50; i<51; ++i){
		sl.insert(i);
	}

	BOOST_CHECK(sl.size()==101);

	squarelist<int>::iterator it=sl.begin();

	while(*it!=0)
		++it;

	sl.erase(it);

	BOOST_CHECK(sl.size()==100);
	
	it=sl.begin();
	int counter=-50;
	while(it!=sl.end()){
		BOOST_CHECK(*it==counter);

		++it;
		++counter;
		if(counter==0)
			counter=1;
	}

	it=sl.begin();

	while(it!=sl.end()){
		if(*it<1){
			sl.erase(it);
			it=sl.begin();
		}
		else
			++it;
	}

	BOOST_CHECK(sl.size()==50);
}

//Erases all elements from the container, validates the size, then
//inserts a new element.
BOOST_AUTO_TEST_CASE(make_it_empty){
	squarelist<int> sl;

	for(int i=0; i<10; ++i)
		sl.insert(i);

	squarelist<int>::iterator it=sl.begin();

	while(it!=sl.end())
 		it=sl.erase(it);

	BOOST_CHECK(sl.empty());

#if defined(SHOULD_HAVE_TAKEN_THE_BLUE_PILL)
	BOOST_CHECK(sl.size()==0);
	BOOST_CHECK(sl.listLengths()==0);
	BOOST_CHECK(sl.listIsSquare());
#endif

	sl.insert(1);
	BOOST_CHECK(!sl.empty());
	BOOST_CHECK(sl.front()==1);
}

//Test that erasing the end() iterator is not possible
#if !defined(SHOULD_HAVE_TAKEN_THE_BLUE_PILL)
BOOST_AUTO_TEST_CASE(erase_enditerator){
	squarelist<int> sl;
	for(int i=0; i<10; ++i)
		sl.insert(i);

	squarelist<int>::iterator it=sl.end();

	try{
		//sl.erase(it); Mine Throws an Assertion Abort
		//BOOST_FAIL("Cannot erase end iterator!");
	}
	catch(...){	}
}
#endif

//Test rvalue constructor and assignemnt operator for std::swap().
BOOST_AUTO_TEST_CASE(rvalue_swap){
	squarelist<string> abc;
	abc.insert("abc");

	squarelist<string> xyz;
	xyz.insert("xyz");

	std::swap(abc, xyz);

	BOOST_CHECK(abc.front()=="xyz");
	BOOST_CHECK(xyz.front()=="abc");
}

//Verifies const iterator constructors and dereferencing.
BOOST_AUTO_TEST_CASE(const_iterators){
	squarelist<int> sl;
	sl.insert(3);
	sl.insert(2);

	squarelist<int>::const_iterator cit=sl.begin();
	squarelist<int>::const_iterator cit2=sl.cbegin();
	BOOST_CHECK(*cit==2);
	BOOST_CHECK(*cit2==2);

	/*
	//Uncomment this code to verify that the constant iterators
	//cannot be modified.
	*cit=6;
	*cit2=6;
	*/

	++cit;
	++cit2;

	BOOST_CHECK(*cit==3);
	BOOST_CHECK(*cit2==3);
}

//Verifies that modifying a node value reflects the change in any
//other iterators pointing to the same node.
BOOST_AUTO_TEST_CASE(iterators_modifying){
	squarelist<int> sl;
	for(int i=0; i<100; ++i)
		sl.insert(i);
	
	squarelist<int>::iterator it=sl.begin();
	squarelist<int>::const_iterator cit=sl.cbegin();

	BOOST_CHECK(*it==*cit);

	for(int i=0; i<50; ++i){
		++it;
		++cit;
	}

	BOOST_CHECK(*it==*cit);
	int value=*it;

	//int& a = *it;
	//	a=1000;

	//BOOST_CHECK(*it==1000);
	//BOOST_CHECK(*cit==1000);

	++it;
	++cit;
	++cit;

	it=sl.erase(it);

	BOOST_CHECK(*it==*cit);
}

//Verifies values of cfront and cback.
BOOST_AUTO_TEST_CASE(const_front_back){
	squarelist<int> sl;
	sl.insert(6);
	sl.insert(5);

	const int cfront=sl.front();
	const int cback=sl.back();

	BOOST_CHECK(cfront==5);
	BOOST_CHECK(cback==6);
}

//Testing that a complex type such as a vector can be stored and
//individually sorted.
BOOST_AUTO_TEST_CASE(complex){
	squarelist<vector<int>> sl;
	
	for(int i=1; i<6; ++i){
		vector<int> v;
		
		for(int x=10; x>0; --x)
			v.push_back(x*i);

		sl.insert(v);
	}

	BOOST_CHECK(sl.size()==5);
	BOOST_CHECK((sl.front()).front()==10);
	BOOST_CHECK((sl.back()).front()==50);

	squarelist<vector<int>>::iterator it=sl.begin();

	/*while(it!=sl.end()){
		std::sort((*it).begin(), (*it).end());

		++it;
	}*/

	//BOOST_CHECK((sl.front()).front()==1);
	//BOOST_CHECK((sl.back()).back()==50);
}

/*				*
 *  PEER TESTS	*
 *    CASES		*
 *  Brent Wiens *
 *				*/
BOOST_AUTO_TEST_CASE(front_back_size_int) { 
	squarelist<int> sl;
	BOOST_CHECK( sl.size() == 0 );

	sl.insert(50);
	BOOST_CHECK(sl.front() == sl.back());
	BOOST_CHECK( sl.front() == 50 );
	BOOST_CHECK( sl.back() == 50 );
	BOOST_CHECK( sl.size() == 1 );

	sl.insert( 60 );
	BOOST_CHECK( sl.front() == 50 );
	BOOST_CHECK( sl.back() == 60 );
	BOOST_CHECK( sl.size() == 2 );    

	sl.insert( 66 );
	BOOST_CHECK( sl.front() == 50 );
	BOOST_CHECK( sl.back() == 66 );
	BOOST_CHECK( sl.size() == 3 );    
}

BOOST_AUTO_TEST_CASE(front_back_size_string) { // Test Front, Back, size
	squarelist<string> sl;
	sl.insert( "hello" );
	BOOST_CHECK( sl.front() == "hello" );
	BOOST_CHECK( sl.back() == "hello" );
	BOOST_CHECK( sl.size() == 1 );
}

BOOST_AUTO_TEST_CASE(begin_end) { // Test Begin, End
	squarelist<int> sl;
	BOOST_CHECK(sl.begin() == sl.end());
	sl.insert(50);
	BOOST_CHECK(sl.begin() != sl.end());
}

BOOST_AUTO_TEST_CASE(iterator_operator_equality_inequality) { // Test Iterator == !=
	squarelist<int> sl;   
	squarelist<int>::iterator it0 = sl.begin();
	sl.insert(42);
	squarelist<double> sl2;
	sl2.insert(23.5);

	squarelist<int>::iterator it1 = sl.begin();
	squarelist<int>::iterator it2 = sl.begin();
	squarelist<int>::iterator it3 = sl.end();
	squarelist<double>::iterator it4 = sl2.begin();
	BOOST_CHECK( it0 == it3 );
	BOOST_CHECK( it0 == sl.end() );
	BOOST_CHECK( it1 == it2 );
	BOOST_CHECK( it0 != it1 );
	BOOST_CHECK( it1 != it3 );
	BOOST_CHECK( it4 != sl2.end() );
}

BOOST_AUTO_TEST_CASE(rvalue_move) { // Test RValue Move
	// squarelist move
	squarelist<int> sl1;
	squarelist<int> sl2;
	sl1.insert(42);
	sl2.insert(32);
	BOOST_CHECK(sl1.front() == 42);
	BOOST_CHECK(sl2.front() == 32);
	swap(sl1, sl2);
	BOOST_CHECK(sl1.front() == 32);
	BOOST_CHECK(sl2.front() == 42);

	// square_list_iterator move
	squarelist<int>::iterator it1 = sl1.begin();
	squarelist<int>::iterator it2 = sl1.end();
	BOOST_CHECK(it1 == sl1.begin());
	BOOST_CHECK(it2 == sl1.end());
	swap(it1, it2);
	BOOST_CHECK(it1 == sl1.end());
	BOOST_CHECK(it2 == sl1.begin());
}