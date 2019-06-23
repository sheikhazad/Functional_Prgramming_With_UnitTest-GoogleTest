#include <iostream>
#include <vector>
#include <deque>
#include <gtest/gtest.h>

using namespace std;

/********************************************************************************************************************
1. A simple demo of Functional Programming with Unit Test by using GoogleTest in C++11/14
2. T = Vector or Deque container type
3. TFun - fun - Function parameter which is passed as argument by the caller, it is called again from this function.
4. Different funtional behaviour is achieved by passing different function to the parameter "fun" by the caller 
*********************************************************************************************************************/
template<typename TFunc, typename T>
void filterData(TFunc fun, T& iContainer, T& oContainer )
{
    for(auto& anElement : iContainer)
    {
        //Calling fun - Function which was passed as argument by the caller
        if(fun(anElement)) {
           oContainer.emplace_back(anElement);
        }
    }
}

//1. Test if the functional program filtered those elements which are less than equal to 50
TEST(FuntionalProgramTest, testLessThanEqual_50)
{
    vector<int> iVec{10,20,30,40,50,60,70,80,90,100};
    vector<int> oVec;

    //Reserve oVec to avoid re-allocation
    oVec.reserve(iVec.size());

    //Lambda function is passed as parameter to filterData()
    //auto type for lambda function parameter is C++14 feature
    filterData([](auto& i) ->bool { return i<=50; }, iVec, oVec );

    //Release unused memory from oVec
    oVec.shrink_to_fit();

    cout<<"\nOutput result from Functional Program, Less than equal to 50 : " << endl << endl;
    for(auto& anElement : oVec)
    {
       cout<< anElement << " ";
       EXPECT_LE(anElement, 50);
    }
}

//2. Test if the functional program filtered those elements which are between 30 and 80
TEST(FuntionalProgramTest, testBetween_30_And_80)
{
    deque<int> iDeque{10,20,30,40,50,60,70,80,90,100};
    deque<int> oDeque;

    //Lambda function is passed as parameter to filterData()
    //auto type for lambda function parameter is C++14 feature
    filterData([](auto& i)->bool { return i>=30 && i<=80; }, iDeque, oDeque );

    cout<<"\nOutput result from Functional Program, between 30 and 80: " << endl << endl;
    for(auto& anElement : oDeque)
    {
       cout<< anElement << " ";
       EXPECT_LE(anElement, 80);
       EXPECT_GE(anElement, 30);
    }
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
