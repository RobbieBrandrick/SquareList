/** @file: ut_dlist_main.cpp
@author Robbie Brandrick
@author r_brandrick@fanshaweonline.ca
@date 2012-02-24
@version 0.1.0
@note Targets Visual C++ 10.0
@briefs Unit Tests for my dlist
*/

// unit test library
#define _CRT_SECURE_NO_WARNINGS
#define BOOST_TEST_MODULE ut_dlist
#include <boost/test/unit_test.hpp>

#define NUM_NODES 1000

//stl
#include <list>
#include <algorithm>
#include <string>
#include <random>
#include <ctime>
using namespace std;
//include dlist library
#include "../Common/Non-STL/dlist.hpp"

/*Test the default constructor*/
BOOST_AUTO_TEST_CASE(default_constructor){
		dlist<unsigned> list;
}

/*Ensure the Copy Constructor is working correctly*/
BOOST_AUTO_TEST_CASE(copy_constructor){
		dlist<unsigned> myList;
		
		std::size_t sizeCount = 0;

		/*Memory Leak Test*/
		for(unsigned i = 1; i <= NUM_NODES; i++){
				myList.push_front(i);
				BOOST_CHECK(myList.front() == i);

				BOOST_CHECK(myList.size() == ++sizeCount);

				myList.push_back(i + 1);
				BOOST_CHECK(myList.back() == i + 1);

				BOOST_CHECK(myList.size() == ++sizeCount);
		}

		dlist<unsigned> myList2(myList); 

		BOOST_CHECK(myList2.back() == NUM_NODES + 1);
		BOOST_CHECK(myList2.front() == NUM_NODES);
		BOOST_CHECK(myList2.size() == sizeCount);
		BOOST_CHECK(myList.back() == NUM_NODES + 1);
		BOOST_CHECK(myList.front() == NUM_NODES);
		BOOST_CHECK(myList2.size() == sizeCount);
}

/*Ensure the Move Constructor is working correctly*/
BOOST_AUTO_TEST_CASE(move_constructor){
		dlist<unsigned> myList;
		
		std::size_t sizeCount = 0;

		for(unsigned i = 1; i <= NUM_NODES; i++){
				myList.push_front(i);
				BOOST_CHECK(myList.front() == i);

				BOOST_CHECK(myList.size() == ++sizeCount);

				myList.push_back(i + 1);
				BOOST_CHECK(myList.back() == i + 1);

				BOOST_CHECK(myList.size() == ++sizeCount);
		}

		dlist<unsigned> myList2; 
		std::size_t sizeCount2 = 0;
		for(unsigned i = NUM_NODES; i >= 1; i--){
				myList2.push_front(i);
				BOOST_CHECK(myList2.front() == i);

				BOOST_CHECK(myList2.size() == ++sizeCount2);

				myList2.push_back(i + 1);
				BOOST_CHECK(myList2.back() == i + 1);

				BOOST_CHECK(myList2.size() == ++sizeCount2);
		}

		BOOST_CHECK(myList2.back() == 2);
		BOOST_CHECK(myList2.front() == 1);
		BOOST_CHECK(myList2.size() == sizeCount2);
		BOOST_CHECK(myList.back() == NUM_NODES + 1);
		BOOST_CHECK(myList.front() == NUM_NODES);
		BOOST_CHECK(myList.size() == sizeCount);

		std::swap(myList, myList2);
		BOOST_CHECK(myList.back() == 2);
		BOOST_CHECK(myList.front() == 1);
		BOOST_CHECK(myList.size() == sizeCount2);
		BOOST_CHECK(myList2.back() == NUM_NODES + 1);
		BOOST_CHECK(myList2.front() == NUM_NODES);
		BOOST_CHECK(myList2.size() == sizeCount);
}

/*Test the dlist's push_back method*/
BOOST_AUTO_TEST_CASE(push_back_simple){
		dlist<unsigned> myList;
		
		BOOST_CHECK(myList.size() == 0);

		/*Memory Leak Test*/
		for(unsigned i = 1; i <= NUM_NODES; i++){
				myList.push_back(i);
				BOOST_CHECK(myList.back() == i);
				BOOST_CHECK(myList.front() == 1);
				BOOST_CHECK(myList.size() == i);
		}

}

/*Test the dlist's push_front method*/
BOOST_AUTO_TEST_CASE(push_front_simple){
		dlist<unsigned> myList;
		
		BOOST_CHECK(myList.size() == 0);

		/*Memory Leak Test*/
		for(unsigned i = 1; i <= NUM_NODES; i++){
				myList.push_front(i);
				BOOST_CHECK(myList.front() == i);
				BOOST_CHECK(myList.back() == 1);
				BOOST_CHECK(myList.size() == i);
		}

}

/*Test the dlist's push_front and push_back methods together*/
BOOST_AUTO_TEST_CASE(push_front_and_push_back_simple){
		dlist<unsigned> myList;
		
		std::size_t sizeCount = 0;

		/*Memory Leak Test*/
		for(unsigned i = 1; i <= NUM_NODES; i++){
				myList.push_front(i);
				BOOST_CHECK(myList.front() == i);

				BOOST_CHECK(myList.size() == ++sizeCount);

				myList.push_back(i + 1);
				BOOST_CHECK(myList.back() == i + 1);

				BOOST_CHECK(myList.size() == ++sizeCount);
		}

}

/*Test the dlist's push_front and push_back methods together with added complexity*/
BOOST_AUTO_TEST_CASE(push_and_pop_back_test_complex){
	
	unsigned flag = 0;
	dlist<unsigned> dlist;
	unsigned i;	
	while(flag < NUM_NODES)
	{

		for( i = 0; i < 100; i++)
			dlist.push_back(i);

		BOOST_CHECK(dlist.size() == i);
		BOOST_CHECK(!dlist.empty());
		BOOST_CHECK(dlist.front() == 0);
		BOOST_CHECK(dlist.back() == 99);

		for( i = 0; i < 100; i++)
			dlist.pop_back();
		
		BOOST_CHECK(dlist.size() == 0);
		BOOST_CHECK(dlist.empty());

		flag++;
	}
	for( i = 0; i < NUM_NODES; i++)
		dlist.push_back(i);

		BOOST_CHECK(dlist.size() == NUM_NODES);
		BOOST_CHECK(!dlist.empty());
		BOOST_CHECK(dlist.front() == 0);
		BOOST_CHECK(dlist.back() == NUM_NODES - 1);
}

/*Test the dlist's pop_back method*/
BOOST_AUTO_TEST_CASE(pop_back_simple){
		dlist<unsigned> myList;
		
		BOOST_CHECK(myList.size() == 0);

		/*Memory Leak Test*/
		for(unsigned i = 1; i <= NUM_NODES; i++){
				myList.push_back(i);
				BOOST_CHECK(myList.back() == i);
				BOOST_CHECK(myList.front() == 1);
				BOOST_CHECK(myList.size() == i);
		}

		for(unsigned i = NUM_NODES; i >= 1; i--){
				myList.pop_back();
		}

}

/*Test the dlist's pop_front method*/
BOOST_AUTO_TEST_CASE(pop_front_simple){
		dlist<unsigned> myList;
		
		BOOST_CHECK(myList.size() == 0);

		/*Memory Leak Test*/
		for(unsigned i = 1; i <= NUM_NODES; i++){
				myList.push_front(i);
				BOOST_CHECK(myList.back() == 1);
				BOOST_CHECK(myList.front() == i);
				BOOST_CHECK(myList.size() == i);
		}

		for(unsigned i = NUM_NODES; i >= 1; i--){
				myList.pop_front();
		}

}

/*Test the dlist's size method*/
BOOST_AUTO_TEST_CASE(size_method){
	//Positive Tests
	dlist<unsigned> dlist;
	BOOST_CHECK(dlist.size() == 0);

	unsigned i;
	for( i = 0; i < NUM_NODES; i++)
		dlist.push_back(i);

	BOOST_CHECK(dlist.size() == i);

	//Negative Tests 
	BOOST_CHECK(dlist.size() != i - 1);
	BOOST_CHECK(dlist.size() != i + 1);
}

/*Test the dlist's empty method*/
BOOST_AUTO_TEST_CASE(empty_method){
	//Positive Tests
	dlist<string> dlist;
	BOOST_CHECK(dlist.empty());

	//Negative Tests
	dlist.push_back("NEGATIVE BOOST_AUTO_TEST_CASE!!!");
			BOOST_CHECK(!dlist.empty());

	dlist.push_back("NEGATIVE BOOST_AUTO_TEST_CASE TWO!!!");
	BOOST_CHECK(!dlist.empty());
}

/*Test the dlist's clear method*/
BOOST_AUTO_TEST_CASE(clear_method){
	//Positive Tests
	dlist<unsigned> dlist;
		int flag = 0;
	while(flag < 10)
	{
		unsigned i;
		for( i = 0; i < NUM_NODES; i++)
			dlist.push_back(i);

		BOOST_CHECK(dlist.size() == i);
		dlist.clear();
		BOOST_CHECK(dlist.size() == 0);
		++flag;
	}
}

/*Test dlists equality and inequality operators*/
BOOST_AUTO_TEST_CASE(equality_and_inquality_test){
		dlist<int> myList;
		dlist<int> myList2;

		//Populate The Lists and make them in sync
		for(int i = 0; i < NUM_NODES; i ++)
		{
			    BOOST_CHECK(myList == myList2);
				
				myList.push_back(i);
				BOOST_CHECK(myList != myList2);
				
				myList2.push_back(i);
				BOOST_CHECK(myList == myList2);

				//Perform checks to ensure that they are in sync
				BOOST_CHECK(myList.back() == myList2.back());
				BOOST_CHECK(myList.front() == myList2.front());
				BOOST_CHECK(myList.size() == myList2.size());
				BOOST_CHECK(myList.back() == i);
		}

		BOOST_CHECK(myList == myList2);
		myList.push_front(NUM_NODES);
		BOOST_CHECK(myList != myList2);
		myList2.push_front(NUM_NODES);
}

/*Test the dlist's Iterator's forward iteration*/
BOOST_AUTO_TEST_CASE(forward_iterator){
	//Compare My custom list stl's list
	dlist<int> myList;
	list<int> stlList;

	dlist<int>::iterator dlIter = myList.begin();
	dlist<int>::iterator dlIterEnd = myList.end();
	BOOST_CHECK(dlIter == dlIterEnd);

	//Populate The Lists and make them in sync
	for(int i = 0; i < NUM_NODES; i ++)
	{
			myList.push_back(i);
			stlList.push_back(i);

			BOOST_CHECK(myList.back() == stlList.back());
			BOOST_CHECK(myList.front() == stlList.front());
			BOOST_CHECK(myList.size() == stlList.size());
			BOOST_CHECK(myList.back() == i);
	}

	//Forward Iterate the lists to ensure that they are in sync
	list<int>::iterator stlIter = stlList.begin(), stlIterEnd = stlList.end();
	while(dlIter != dlIterEnd && stlIter != stlList.end()) {
			BOOST_CHECK(*dlIter++ == *stlIter++);
	}

	//Forward Iterate the lists to ensure that they are in sync
	stlIter = stlList.begin();
	std::for_each(myList.begin(),  myList.end(), [&stlIter]( int const& i)
	{ 
			BOOST_CHECK(i == *stlIter++);
	});

	//Eliminate Half the nodes from the list
	for(int i = 0; i < NUM_NODES / 2; i ++)
	{
			myList.pop_back();
			stlList.pop_back();

			BOOST_CHECK(myList.back() == stlList.back());
			BOOST_CHECK(myList.front() == stlList.front());
			BOOST_CHECK(myList.size() == stlList.size());
			BOOST_CHECK(myList.back() == NUM_NODES - ( i + 2));
	}

	//Forward Iterate the lists to ensure that they are in sync
	stlIter = stlList.begin();
	std::for_each(myList.begin(),  myList.end(), [&stlIter]( int const& i){BOOST_CHECK(i == *stlIter++);});

	stlIter = stlList.begin();
	std::for_each(myList.begin(),  myList.end(), [&stlIter]( int const& i){BOOST_CHECK(i == *stlIter++);});

	//Ensure That the my custom list Iterator is transversing all the nodes.
	double y = 0;
	for(dlist<int>::iterator iter = myList.begin(); iter != myList.end(); iter++)
			y +=1;

	for(;y != 0; y--)
			myList.pop_back();

	BOOST_CHECK(myList.empty());

}

/*Test the dlist's Constant Iterator's forward iteration*/
BOOST_AUTO_TEST_CASE(forward_const_iterator){
	//Compare My custom list stl's list
	dlist<int> myList;
	list<int> stlList;

	//Populate The Lists and make them in sync
	for(int i = 0; i < NUM_NODES; i ++)
	{
			myList.push_back(i);
			stlList.push_back(i);

			BOOST_CHECK(myList.back() == stlList.back());
			BOOST_CHECK(myList.front() == stlList.front());
			BOOST_CHECK(myList.size() == stlList.size());
			BOOST_CHECK(myList.back() == i);
	}

	//Forward Iterate the lists to ensure that they are in sync
	dlist<int>::const_iterator dlIter = myList.begin();
	dlist<int>::const_iterator dlIterEnd = myList.cend();
	list<int>::const_iterator stlIter = stlList.cbegin(), stlIterEnd = stlList.cend();
	while(dlIter != dlIterEnd && stlIter != stlList.cend()) {
			BOOST_CHECK(*dlIter++ == *stlIter++);
	}



	//Forward Iterate the lists to ensure that they are in sync
	stlIter = stlList.cbegin();
	std::for_each(myList.cbegin(),  myList.cend(), [&stlIter]( int const& i)
	{ 
			BOOST_CHECK(i == *stlIter++);
	});

	//Eliminate Half the nodes from the list
	for(int i = 0; i < NUM_NODES / 2; i ++)
	{
			myList.pop_back();
			stlList.pop_back();

			BOOST_CHECK(myList.back() == stlList.back());
			BOOST_CHECK(myList.front() == stlList.front());
			BOOST_CHECK(myList.size() == stlList.size());
			BOOST_CHECK(myList.back() == NUM_NODES - ( i + 2));
	}

	//Forward Iterate the lists to ensure that they are in sync
	stlIter = stlList.cbegin();
	std::for_each(myList.cbegin(),  myList.cend(), [&stlIter]( int const& i){BOOST_CHECK(i == *stlIter++);});

	stlIter = stlList.cbegin();
	std::for_each(myList.cbegin(),  myList.cend(), [&stlIter]( int const& i){BOOST_CHECK(i == *stlIter++);});

	//NOTE: you cannot assign a variable with the constant iterator
	//dlist<int>::const_iterator dlistIter = myList.cbegin();
	//*dlistIter = 10;

	//Ensure That the my custom list Iterator is transferring all the nodes.
	double y = 0;
	for(dlist<int>::const_iterator iter = myList.cbegin(); iter != myList.cend(); iter++)
			y +=1;

	for(;y != 0; y--)
			myList.pop_back();

	BOOST_CHECK(myList.empty());

}

/*Test dlist's iterators dereference*/
BOOST_AUTO_TEST_CASE(iterator_dereference){
	mt19937 randomEngine;
	randomEngine.seed((unsigned)time( 0 ));
	uniform_int_distribution<double> valueDistribution(-1024,1024);
	auto valueGenerator = bind(valueDistribution, randomEngine);

	dlist<double> myList;

	//Populate The Lists and make them in sync
	for(double i = 0; i < NUM_NODES; i ++)
	{
		myList.push_back(i);
	}

	for(auto iter = myList.begin(); iter != myList.end(); ++iter){
		double oldValue = *iter;
		BOOST_CHECK(*iter == oldValue);
		double newValue =  valueGenerator(randomEngine);
		*iter = newValue;
		BOOST_CHECK(*iter == newValue);
	}
}

/*Test the dlist's Iterator's reverse iteration*/
BOOST_AUTO_TEST_CASE(reverse_iterator_test){
		//Compare My custom list stl's list
		dlist<int> myList;
	list<int> stlList;

	//Populate The Lists and make them in sync
	for(int i = 0; i < NUM_NODES; i ++)
	{
			myList.push_back(i);
			stlList.push_back(i);

			//Perform checks to ensure that they are in sync
			BOOST_CHECK(myList.back() == stlList.back());
			BOOST_CHECK(myList.front() == stlList.front());
			BOOST_CHECK(myList.size() == stlList.size());
			BOOST_CHECK(myList.back() == i);
	}

	//Resverse Iterate the lists to ensure that they are in sync
	dlist<int>::reverse_iterator dlIter = myList.rbegin(), dlIterEnd = myList.rend();
	list<int>::reverse_iterator stlIter = stlList.rbegin();
	while(dlIter != dlIterEnd){
			BOOST_CHECK(*dlIter++ == *stlIter++);

	}

	//Reverse Iterate the lists to ensure that they are in sync
	stlIter = stlList.rbegin();
	std::for_each(myList.rbegin(),  myList.rend(), [&stlIter]( int const& i){BOOST_CHECK(i == *stlIter++);});

	//Eliminate Half the nodes from the list
	for(int i = 0; i < NUM_NODES / 2; i ++)
	{
			myList.pop_back();
			stlList.pop_back();

			//Perform checks to ensure that they are in sync
			BOOST_CHECK(myList.back() == stlList.back());
			BOOST_CHECK(myList.front() == stlList.front());
			BOOST_CHECK(myList.size() == stlList.size());
			BOOST_CHECK(myList.back() == NUM_NODES - ( i + 2));
	}

	//Resverse Iterate the lists to ensure that they are in sync
	stlIter = stlList.rbegin();
	std::for_each(myList.rbegin(),  myList.rend(), [&stlIter]( int const& i){BOOST_CHECK(i == *stlIter++);});

	stlIter = stlList.rbegin();
	std::for_each(myList.rbegin(),  myList.rend(), [&stlIter]( int const&  i){BOOST_CHECK(i == *stlIter++);});


	//Ensure That the Reverse Iterator is transversing all the nodes.
	double y = 0;
	for(dlist<int>::reverse_iterator riter = myList.rbegin(); riter != myList.rend(); ++riter)
			y +=1;

	for(;y != 0; y--)
			myList.pop_back();

	BOOST_CHECK(myList.empty());

}

/*Test dlist's reverse iterators dereference*/
BOOST_AUTO_TEST_CASE(reverse_iterator_dereference){
	mt19937 randomEngine;
	randomEngine.seed((unsigned)time( 0 ));
	uniform_int_distribution<double> valueDistribution(-1024,1024);
	auto valueGenerator = bind(valueDistribution, randomEngine);

	dlist<double> myList;

	//Populate The Lists and make them in sync
	for(double i = 0; i < NUM_NODES; i ++)
	{
		myList.push_back(i);
	}

	for(auto iter = myList.rbegin(); iter != myList.rend(); ++iter){
		double oldValue = *iter;
		BOOST_CHECK(*iter == oldValue);
		double newValue =  valueGenerator(randomEngine);
		*iter = newValue;
		BOOST_CHECK(*iter == newValue);
	}
}

/*Test the dlist's Constant Iterator's reverse iteration*/
BOOST_AUTO_TEST_CASE(reverse_const_iterator_test){
	//Compare My custom list stl's list
	dlist<int> myList;
	list<int> stlList;

	//Populate The Lists and make them in sync
	for(int i = 0; i < NUM_NODES; i ++)
	{
			myList.push_back(i);
			stlList.push_back(i);

			//Perform checks to ensure that they are in sync
			BOOST_CHECK(myList.back() == stlList.back());
			BOOST_CHECK(myList.front() == stlList.front());
			BOOST_CHECK(myList.size() == stlList.size());
			BOOST_CHECK(myList.back() == i);
	}

	//Reverse Iterate the lists to ensure that they are in sync
	dlist<int>::const_reverse_iterator dlIter = myList.crbegin(), dlIterEnd = myList.crend();
	list<int>::const_reverse_iterator stlIter = stlList.crbegin();
	while(dlIter != dlIterEnd){
			BOOST_CHECK(*dlIter++ == *stlIter++);

	}

	//Reverse Iterate the lists to ensure that they are in sync
	stlIter = stlList.crbegin();
	std::for_each(myList.crbegin(),  myList.crend(), [&stlIter]( int const& i){BOOST_CHECK(i == *stlIter++);});

	//Eliminate Half the nodes from the list
	for(int i = 0; i < NUM_NODES / 2; i ++)
	{
			myList.pop_back();
			stlList.pop_back();

			//Perform checks to ensure that they are in sync
			BOOST_CHECK(myList.back() == stlList.back());
			BOOST_CHECK(myList.front() == stlList.front());
			BOOST_CHECK(myList.size() == stlList.size());
			BOOST_CHECK(myList.back() == NUM_NODES - ( i + 2));
	}

	//Reverse Iterate the lists to ensure that they are in sync
	stlIter = stlList.crbegin();
	std::for_each(myList.crbegin(),  myList.crend(), [&stlIter]( int const& i){BOOST_CHECK(i == *stlIter++);});

	stlIter = stlList.crbegin();
	std::for_each(myList.crbegin(),  myList.crend(), [&stlIter]( int const&  i){BOOST_CHECK(i == *stlIter++);});

	//NOTE: you cannot assign a variable with the constant iterator
	//dlist<int>::const_reverse_iterator dlistIter = myList.crbegin();
	//*dlistIter = 10;

	//Ensure That the Reverse Iterator is transversing all the nodes.
	double y = 0;
	for(dlist<int>::const_reverse_iterator riter = myList.crbegin(); riter != myList.crend(); ++riter)
			y +=1;

	for(;y != 0; y--)
			myList.pop_back();

	BOOST_CHECK(myList.empty());

}

/*Use STL's distance method to verify dlist's compatibility with STL algorithms*/
BOOST_AUTO_TEST_CASE(distance_test){
		dlist<unsigned> myList;
		list<unsigned> stlList;

		//Populate The Lists and make them in sync
		for(unsigned i = 0; i < NUM_NODES; i ++)
		{
				myList.push_back(i);
				stlList.push_back(i);

				//Perform checks to ensure that they are in sync
				BOOST_CHECK(myList.back() == stlList.back());
				BOOST_CHECK(myList.front() == stlList.front());
				BOOST_CHECK(myList.size() == stlList.size());
				BOOST_CHECK(myList.back() == i);
		}

		dlist<unsigned>::difference_type myListSize = std::distance(myList.begin(), myList.end());
		dlist<unsigned>::difference_type stlListSize = std::distance(stlList.begin(), stlList.end());
		BOOST_CHECK( (dlist<unsigned>::value_type)myListSize == myList.size() );
		BOOST_CHECK( (dlist<unsigned>::value_type)stlListSize == stlList.size() );
		BOOST_CHECK(myListSize == stlListSize );
}

/*Test The dlist's insert method*/
BOOST_AUTO_TEST_CASE(insert){
		//Compare My custom list stl's list
		dlist<int> myList;
		list<int> stlList;

		//Populate The Lists and make them in sync
		for(int i = 0; i < NUM_NODES; i ++)
		{
				myList.push_back(i);
				stlList.push_back(i);

				//Perform checks to ensure that they are in sync
				BOOST_CHECK(myList.back() == stlList.back());
				BOOST_CHECK(myList.front() == stlList.front());
				BOOST_CHECK(myList.size() == stlList.size());
				BOOST_CHECK(myList.back() == i);
		}


		//Insert at the beginning of the list
		int begVal = 0;
		list<int>::iterator stlVal = std::find(stlList.begin(),stlList.end(), begVal);
		stlVal = stlList.insert(stlVal,begVal + 1);
		dlist<int>::iterator myVal = std::find(myList.begin(),myList.end(), begVal);
		myVal = myList.insert(myVal,begVal + 1);

		BOOST_CHECK(*stlVal == *myVal);

		//Insert in the middle of the lists
		int middleVal = NUM_NODES / 2;
		stlVal = std::find(stlList.begin(),stlList.end(), middleVal);
		stlVal = stlList.insert(stlVal,middleVal + 1);
		myVal = std::find(myList.begin(),myList.end(), middleVal);
		myVal = myList.insert(myVal,middleVal + 1);

		BOOST_CHECK(*stlVal == *myVal);

		//Insert in the end of the lists
		int endVal = NUM_NODES -1;
		stlVal = std::find(stlList.begin(),stlList.end(), endVal);
		stlVal = stlList.insert(stlVal,endVal);
		myVal = std::find(myList.begin(),myList.end(), endVal);
		myVal = myList.insert(myVal, endVal);

		BOOST_CHECK(*stlVal == *myVal);
}

/*Test The dlist's erase method*/
BOOST_AUTO_TEST_CASE(erase){

		//Compare My custom list stl's list
		dlist<int> myList;
		list<int> stlList;

		//Populate The Lists and make them in sync
		for(int i = 0; i < NUM_NODES; i ++)
		{
				myList.push_back(i);
				stlList.push_back(i);

				//Perform checks to ensure that they are in sync
				BOOST_CHECK(myList.back() == stlList.back());
				BOOST_CHECK(myList.front() == stlList.front());
				BOOST_CHECK(myList.size() == stlList.size());
				BOOST_CHECK(myList.back() == i);
		}


		//erase at the beginning of the list 
		int begVal = 0;
		list<int>::iterator stlVal = std::find(stlList.begin(),stlList.end(), begVal);
		stlVal = stlList.erase(stlVal);
		dlist<int>::iterator myVal = std::find(myList.begin(),myList.end(), begVal);
		myVal = myList.erase(myVal);
		 *stlVal;
		BOOST_CHECK(*stlVal == *myVal);

		//Insert in the middle of the lists
		int middleVal = NUM_NODES / 2;
		stlVal = std::find(stlList.begin(),stlList.end(), middleVal);
		stlVal = stlList.erase(stlVal);
		myVal = std::find(myList.begin(),myList.end(), middleVal);
		myVal = myList.erase(myVal);

		BOOST_CHECK(*stlVal == *myVal);

		//Insert two from the end of the lists
		int endVal = NUM_NODES - 2;
		stlVal = std::find(stlList.begin(),stlList.end(), endVal);
		stlVal = stlList.erase(stlVal);
		myVal = std::find(myList.begin(),myList.end(), endVal);
		myVal = myList.erase(myVal);

		BOOST_CHECK(*stlVal == *myVal);
		BOOST_CHECK(++stlVal == stlList.end() && ++myVal == myList.end());
}

/* Failure Test: Ensure that two different dlist aggregates cannot use each other iterators*/
BOOST_AUTO_TEST_CASE(different_iterator){
		dlist<int> myList;
		dlist<int> myList2;		
		
		//Populate The Lists and make them in sync
		for(int i = 0; i <= NUM_NODES; i ++)
		{
				myList.push_back(i);
				myList2.push_back(i);
		}

		//Ensure that myList's insert or erase method cannot use myList2's iterator and visa versa
		dlist<int>::iterator iter1 = std::find(myList.begin(), myList.end(), NUM_NODES);
		dlist<int>::iterator iter2 = std::find(myList2.begin(), myList2.end(), NUM_NODES);
		//myList.insert(iter2, NUM_NODES * 2);
		//myList2.insert(iter1, NUM_NODES * 2);
		//myList.erase(iter2);
		//myList2.erase(iter1);
} 


/*Class That throws an exception
 *Used to try and create memory leaks in
 *   dlist class*/
class exceptionMethodClass{
public:
	void throwException(){throw exception();}
};


/*use the exceptionClass to try to create memory leaks*/
BOOST_AUTO_TEST_CASE(exception_classes){
	dlist<exceptionMethodClass> exList;	
		
	//Populate The Lists and make them in sync
	for(int i = 0; i <= 10; i ++)
	{
			exList.push_back(exceptionMethodClass());
	}

	try{
		exList.front().throwException();
		BOOST_FAIL("Should have thrown an exception");
	}catch(...){

	}

	try{
		exList.back().throwException();
		BOOST_FAIL("Should have thrown an exception");
	}catch(...){

	}

}
/*General test to test an arbitrary situation*/
BOOST_AUTO_TEST_CASE(general_test){
	dlist<dlist<int>> dldl;
	dlist<int> dl;
	for ( unsigned i = 0; i < 10; ++i ) {
		dldl.push_back( dl );
	}

	dlist<dlist<int>>::iterator it;
	it = --dldl.end();
	dldl.erase( it );

	BOOST_CHECK( dldl.size() == 9 );

	dlist<vector<dlist<vector<std::string>>>> dlComplex;
	vector<dlist<vector<std::string>>> v;
	dlist<vector<std::string>> d;
	vector<std::string> v2;
	v2.push_back("jello");
	v2.push_back("truck");

	d.push_back(v2);
	v.push_back(d);
	v.push_back(d);
	v.push_back(d);

	dlist<vector<dlist<vector<std::string>>>>::iterator it2 = dlComplex.begin();
	for ( unsigned i = 0; i < 2000; ++i ) {
		dlComplex.insert( it2, v );
	}

	BOOST_CHECK(dlComplex.size() == 2000);

	it2 = dlComplex.end();
	for ( unsigned i = 0; i < 2000; ++i ) {
		dlComplex.insert( it2, v );
	}

	BOOST_CHECK(dlComplex.size() == 4000);
}

