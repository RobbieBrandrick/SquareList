/** @file: ut_nonstl_squarelist_main.cpp
@author Robbie Brandrick
@author r_brandrick@fanshaweonline.ca
@date 2012-02-24
@version 0.1.0
@note Targets Visual C++ 10.0
@briefs Unit Tests for my squarelist (Non-STL Version)
*/

// unit test library
#define _CRT_SECURE_NO_WARNINGS
#define BOOST_TEST_MODULE squarelist_testing
#include <boost/test/unit_test.hpp>

#define NUM_NODES 1000

//stl
#include <list>
#include <algorithm>
#include <string>
#include <random>
#include <ctime>
#include <iostream>
using namespace std;
//include squarelist library
#include "../Common/Non-STL/squarelist.hpp"

/* Test insert method with sequential unsigned data*/
BOOST_AUTO_TEST_CASE(insert_sequential_numbers){
	squarelist<unsigned> slist;	
	for(unsigned i = 0; i < NUM_NODES; i++){
		slist.insert(i);
		BOOST_CHECK(slist.size() == i + 1);
		BOOST_CHECK(slist.back() == i);
		BOOST_CHECK(slist.front() == 0);
	}

	for(unsigned i = NUM_NODES; i > 0; i--){
		slist.insert(i);
		BOOST_CHECK(slist.size() == ((NUM_NODES * 2) - i) + 1);
		BOOST_CHECK(slist.back() == NUM_NODES);
		BOOST_CHECK(slist.front() == 0);
	}

	slist.clear();
	BOOST_CHECK(slist.empty());
}

/* Test insert method  with random data
 * Ensure that the squarelist is sorted*/
BOOST_AUTO_TEST_CASE(insert_random_numbers){
	mt19937 randomEngine;
	randomEngine.seed((unsigned)time( 0 ));
	uniform_int_distribution<unsigned int> valueDistribution(0,1024);
	auto valueGenerator = bind(valueDistribution, randomEngine);

	squarelist<unsigned> slist;	
	for(unsigned i = 1; i <= NUM_NODES; i++){
		slist.insert(valueGenerator(randomEngine));
		BOOST_CHECK(slist.size() == i);
		BOOST_CHECK(is_sorted(slist.begin(), slist.end()));
	}
}

/* Test  erase method  with sequential data*/
BOOST_AUTO_TEST_CASE(erase_sequential_numbers){
	squarelist<unsigned> slist;	

		for(unsigned i = 1; i <= NUM_NODES; i++){
			slist.insert(i);
			BOOST_CHECK(slist.size() == i );
			BOOST_CHECK(slist.back() == i);
			BOOST_CHECK(slist.front() == 1);
		}

		for(unsigned i = NUM_NODES; i > 0; i--){
			BOOST_CHECK(slist.size() == i);
			BOOST_CHECK(slist.back() == i);
			BOOST_CHECK(slist.front() == 1);
			BOOST_CHECK(is_sorted(slist.begin(), slist.end()));
			if(!slist.erase(i))
				BOOST_FAIL("Value should be erased");
		}

		BOOST_CHECK(slist.size() == 0);

		for(unsigned i = NUM_NODES; i > 0; i--){
			slist.insert(i);
			BOOST_CHECK(slist.size() == (NUM_NODES - i) + 1);
			BOOST_CHECK(slist.back() == NUM_NODES);
			BOOST_CHECK(slist.front() == i);
		}

		for(unsigned i = 1; i <= NUM_NODES; i++){
			BOOST_CHECK(slist.size() == (NUM_NODES - i) + 1);
			BOOST_CHECK(slist.back() == NUM_NODES );
			BOOST_CHECK(slist.front() == i);
			BOOST_CHECK(is_sorted(slist.begin(), slist.end()));
			if(!slist.erase(i))
				BOOST_FAIL("Value should be erased");
		}

		BOOST_CHECK(slist.size() == 0);
		BOOST_CHECK(slist.empty());
	
		if(slist.erase(1234) == true)
			BOOST_FAIL("Value should not have been erased");

}

/* Test  erase method with random data
 * Ensure that the squarelist is sorted*/
BOOST_AUTO_TEST_CASE(erase_random_numbers){
	mt19937 randomEngine;
	randomEngine.seed((unsigned)time( 0 ));
	uniform_int_distribution<double> valueDistribution(-1024,1024);
	auto valueGenerator = bind(valueDistribution, randomEngine);

	squarelist<double> slist;
	
	for(unsigned u = 0; u < 10; u++)
	{
			std::list<double> history;
			for(unsigned i = 1; i < NUM_NODES; i++){
				double randomNum = valueGenerator(randomEngine);
				slist.insert(randomNum);
				history.push_back(randomNum);
				BOOST_CHECK(is_sorted(slist.begin(), slist.end()));
			}

			for_each(history.cbegin(), history.cend(),[&slist](double const& v){
					BOOST_CHECK(is_sorted(slist.begin(), slist.end()));
					if(!slist.erase(v))
						BOOST_FAIL("Value should be erased");
			});
			BOOST_CHECK(slist.size() == 0);
			BOOST_CHECK(slist.empty());
	}
}

/*Ensure that the front and back methods are working properly*/
BOOST_AUTO_TEST_CASE(front_back){
		squarelist<unsigned> slist;	
	for(unsigned i = 0; i <= NUM_NODES; i++){
		slist.insert(i);
		BOOST_CHECK(slist.size() == i + 1);
		BOOST_CHECK(slist.back() == i);
		BOOST_CHECK(slist.front() == 0);
	}

	//Ensure that the user cannot change the front and back methods
	//slist.front() = 100;
	//slist.back() = 100;

	unsigned front = slist.front();
	BOOST_CHECK(front == slist.front());
	front = 10;
	BOOST_CHECK(front != slist.front());

	unsigned back = slist.back();
	BOOST_CHECK(back == slist.back());
	back = 10;
	BOOST_CHECK(back != slist.back());
}

/* Test RValue Move Semantics*/
BOOST_AUTO_TEST_CASE( r_value_move_semantics ){
 squarelist<unsigned> list;
 squarelist<unsigned> list2;
 	for(unsigned i = 0; i < 16; i++){  
		list.insert( i );
		list2.insert( i + 8 );
	}

   swap( list, list2 );
   BOOST_CHECK( list.front() == 8 );
   BOOST_CHECK( list.back() == 23 );
   BOOST_CHECK( list2.front() == 0 );
   BOOST_CHECK( list2.back() == 15 );
}

/*Test that the begin method works properly*/
BOOST_AUTO_TEST_CASE(begin_method){
	squarelist<string> slist;
	squarelist<string>::iterator iter = slist.begin();
	BOOST_CHECK(iter == slist.begin());
	BOOST_CHECK(iter == slist.end());

	slist.insert("String1");
	BOOST_CHECK(iter != slist.begin());
	--iter;
	BOOST_CHECK(iter == slist.begin());
	BOOST_CHECK(*iter == "String1");
}

/*Test that the end method works properly*/
BOOST_AUTO_TEST_CASE(end_method){
	squarelist<string> slist;
	squarelist<string>::iterator iter = slist.end();
	BOOST_CHECK(iter == slist.begin());
	BOOST_CHECK(iter == slist.end());

	slist.insert("String1");
	BOOST_CHECK(iter == slist.end());
	--iter;
	BOOST_CHECK(iter != slist.end());
	BOOST_CHECK(*iter == "String1");
}

/*Test that the begin method works properly*/
BOOST_AUTO_TEST_CASE(rbegin_method){
	squarelist<string> slist;
	squarelist<string>::reverse_iterator iter = slist.rbegin();
	BOOST_CHECK(iter == slist.rbegin());
	BOOST_CHECK(iter == slist.rend());

	slist.insert("String1");
	BOOST_CHECK(iter == slist.rbegin());
	BOOST_CHECK(*iter == "String1");
	BOOST_CHECK(++iter == slist.rend());
}

/*Test that the rend method works properly*/
BOOST_AUTO_TEST_CASE(rend_method){
	squarelist<string> slist;
	squarelist<string>::reverse_iterator iter = slist.rend();
	BOOST_CHECK(iter == slist.rend());
	BOOST_CHECK(iter == slist.rbegin());

	slist.insert("String1");
	BOOST_CHECK(iter != slist.rend());
	BOOST_CHECK(*iter == "String1");
	BOOST_CHECK(++iter == slist.rend());
}

/*Test The Iteration's Equality and Inequality Operators*/
BOOST_AUTO_TEST_CASE(equality_Inequality_operators){
	squarelist<string> slist;
	stringstream ss;
	for(unsigned i = 0; i < NUM_NODES; i++){
			ss << "NUM_NODES" << i * NUM_NODES;
			slist.insert(ss.str());
		}
	squarelist<string>::iterator iter = slist.begin();
	squarelist<string>::iterator iter2 = slist.begin();
	while(iter2 != slist.end() && iter != slist.end()){
		BOOST_CHECK(iter++ == iter2);
		BOOST_CHECK(iter != iter2++);
	}

	squarelist<string>::reverse_iterator riter = slist.rbegin();
	squarelist<string>::reverse_iterator riter2 = slist.rbegin();
	while(riter2 != slist.rend() && riter != slist.rend()){
		BOOST_CHECK(riter++ == riter2);
		BOOST_CHECK(riter != riter2++);
	}
}

/*Dereferencing Iterator Test*/
BOOST_AUTO_TEST_CASE(dreferencing_iterator){
	mt19937 randomEngine;
	randomEngine.seed((unsigned)time( 0 ));
	uniform_int_distribution<double> valueDistribution(-1024,1024);
	auto valueGenerator = bind(valueDistribution, randomEngine);

	squarelist<double> slist;
	std::list<double> history;
	for(unsigned i = 1; i < NUM_NODES; i++){
		double randomNum = valueGenerator(randomEngine);
		slist.insert(randomNum);
		history.push_back(randomNum);
	}

	history.sort();
	std::list<double>::iterator listIter = history.begin();
	std::list<double>::iterator listIterEnd = history.end();

	for(auto iter = slist.begin(); iter!=slist.end();iter++){
			BOOST_CHECK(*iter == *listIter++);
		}

	//NOTE: THIS SHOULD NOT COMPILE. 
	//WE WOULD NOT WANT TO CHANGE THE VALUES OF A SORTED CONTAINER
	//BECAUSE IT WELL RESULT IN THE DATA BEING UNSORTED.
	//Change all the values in the iterator to 0
	//for(auto iter = slist.begin(); iter!=slist.end();iter++){
	//	*iter = 0;
	//	BOOST_CHECK(*iter == 0);
	//}
}

/*Test Forward Iterations*/
BOOST_AUTO_TEST_CASE(forward_iterator){
	mt19937 randomEngine;
	randomEngine.seed((unsigned)time( 0 ));
	uniform_int_distribution<double> valueDistribution(-1024,1024);
	auto valueGenerator = bind(valueDistribution, randomEngine);

	squarelist<double> slist;
	std::list<double> history;
	for(unsigned i = 1; i < NUM_NODES; i++){
		double randomNum = valueGenerator(randomEngine);
		slist.insert(randomNum);
		history.push_back(randomNum);
	}

	history.sort();
	std::list<double>::iterator hisIter = history.begin();
	std::for_each(slist.begin(), slist.end(),[&hisIter](double const& i){
			BOOST_CHECK(i == *hisIter++);
	});
}

/*Test Forward constant Iterations*/
BOOST_AUTO_TEST_CASE(forward_const_iterator){
	mt19937 randomEngine;
	randomEngine.seed((unsigned)time( 0 ));
	uniform_int_distribution<double> valueDistribution(-1024,1024);
	auto valueGenerator = bind(valueDistribution, randomEngine);

	squarelist<double> slist;
	std::list<double> history;
	for(unsigned i = 1; i < NUM_NODES; i++){
		double randomNum = valueGenerator(randomEngine);
		slist.insert(randomNum);
		history.push_back(randomNum);
	}

	squarelist<double>::const_iterator slistBegin = slist.begin();
	squarelist<double>::const_iterator sliestEnd = slist.end();
	BOOST_CHECK(slistBegin == slist.cbegin());
	BOOST_CHECK(slistBegin != slist.end());
	BOOST_CHECK(sliestEnd == slist.end());

	history.sort();
	std::list<double>::iterator hisIter = history.begin();
	std::for_each(slist.cbegin(), slist.cend(),[&hisIter](double const& i){
			BOOST_CHECK(i == *hisIter++);
	});
}

/*Test Bidirectional Constant Iterations*/
BOOST_AUTO_TEST_CASE(bidirectional_const_iterator){
	mt19937 randomEngine;
	randomEngine.seed((unsigned)time( 0 ));
	uniform_int_distribution<double> valueDistribution(-1024,1024);
	auto valueGenerator = bind(valueDistribution, randomEngine);

	squarelist<double> slist;
	std::list<double> history;
	for(unsigned i = 0; i < NUM_NODES; i++){
		double randomNum = valueGenerator(randomEngine);
		slist.insert(randomNum);
		history.push_back(randomNum);
		BOOST_CHECK( std::distance( slist.cbegin(), slist.cend()) == std::ptrdiff_t(i + 1) );
	}

	squarelist<double>::const_reverse_iterator slistrBegin = slist.rbegin();
	squarelist<double>::const_reverse_iterator sliestrEnd = slist.rend();
	BOOST_CHECK(slistrBegin == slist.crbegin());
	BOOST_CHECK(slistrBegin != slist.crend());
	BOOST_CHECK(sliestrEnd == slist.crend());

	history.sort();
	std::list<double>::const_reverse_iterator hisIter = history.crbegin();
	std::for_each(slist.crbegin(), slist.crend(),[&hisIter](double const& i){
			BOOST_CHECK(i == *hisIter++);
	});
}

/*Test Bidirectional Iterations*/
BOOST_AUTO_TEST_CASE(bidirectional_iterator){
	mt19937 randomEngine;
	randomEngine.seed((unsigned)time( 0 ));
	uniform_int_distribution<double> valueDistribution(-1024,1024);
	auto valueGenerator = bind(valueDistribution, randomEngine);

	squarelist<double> slist;
	std::list<double> history;
	for(unsigned i = 0; i < NUM_NODES; i++){
		double randomNum = valueGenerator(randomEngine);
		slist.insert(randomNum);
		history.push_back(randomNum);
		BOOST_CHECK( std::distance( slist.begin(), slist.end()) == std::ptrdiff_t(i + 1) );
	}

	history.sort();
	std::list<double>::reverse_iterator hisIter = history.rbegin();
	std::for_each(slist.rbegin(), slist.rend(),[&hisIter](double const& i){
			BOOST_CHECK(i == *hisIter++);
	});
}

/*Test the erase method with overloaded iterator parameter
 *Ensure that the squarelist is sorted*/
BOOST_AUTO_TEST_CASE(erase_iterator){
	mt19937 randomEngine;
	randomEngine.seed((unsigned)time( 0 ));
	uniform_int_distribution<double> valueDistribution(-1024,1024);
	auto valueGenerator = bind(valueDistribution, randomEngine);

	squarelist<double> slist;
	for(unsigned i = 0; i < NUM_NODES; i++){
		double randomNum = valueGenerator(randomEngine);
		slist.insert(randomNum);

		BOOST_CHECK(is_sorted(slist.begin(), slist.end()));
		BOOST_CHECK( std::distance( slist.begin(), slist.end()) == std::ptrdiff_t(i + 1) );
	}

	squarelist<double>::iterator iterErase = slist.begin();
	while((iterErase = slist.erase(iterErase)) != slist.end()){
			BOOST_CHECK(is_sorted(slist.begin(), slist.end()));
	}

	BOOST_CHECK(slist.empty());

	for(unsigned i = 0; i < NUM_NODES; i++){
		double randomNum = valueGenerator(randomEngine);
		slist.insert(randomNum);

		BOOST_CHECK(is_sorted(slist.begin(), slist.end()));
		BOOST_CHECK(std::distance( slist.begin(), slist.end()) == std::ptrdiff_t(i + 1) );
	}

	for(auto iter = slist.begin(); iter != slist.end(); ){
		BOOST_CHECK(is_sorted(slist.begin(), slist.end()));
		iter = slist.erase(iter);
	}
}

/*General test to test an arbitrary situation*/
BOOST_AUTO_TEST_CASE(general_test1){

	squarelist<unsigned> sl;

	for(int i=0; i<25;++i){
			sl.insert(i);
	}

	BOOST_CHECK(sl.size()==25);
	BOOST_CHECK(sl.back()==24);

	for(int i=24; i>=0; --i){
			squarelist<unsigned>::iterator it=sl.begin();
			for(int x=0; x<i; ++x){
					++it;
			}
			sl.erase(it);
			sl.insert(i);
	}

	BOOST_CHECK(sl.size()==25);
	squarelist<unsigned>::iterator iter=sl.begin();
	for(unsigned i=0; i<25; ++i){
			BOOST_CHECK(*iter == i);
			++iter;
	}
}

/* Failure Test: Ensure that two different squarelist aggregates cannot use each other iterators*/
BOOST_AUTO_TEST_CASE(different_iterator){
	mt19937 randomEngine;
	randomEngine.seed((unsigned)time( 0 ));
	uniform_int_distribution<double> valueDistribution(-1024,1024);
	auto valueGenerator = bind(valueDistribution, randomEngine);

	squarelist<double> slist;
	squarelist<double> slist2;
	for(unsigned i = 0; i < NUM_NODES; i++){
		double randomNum = valueGenerator(randomEngine);
		slist.insert(randomNum);
		slist2.insert(randomNum);
	}

	squarelist<double>::iterator iter1 = slist.begin();
	squarelist<double>::iterator iter2 = slist2.begin();
	//slist.erase(iter2);
	//slist2.erase(iter1);
	slist.erase(iter1);
	slist2.erase(iter2);
}