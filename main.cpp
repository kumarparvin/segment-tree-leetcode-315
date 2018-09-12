//
//  main.cpp
//  segement_tree
//  for practice
//  Created by Parvin ... on 23/09/17.
//  Copyright © 2017 Parvin ... All rights reserved.
//

#include <iostream>
#include<vector>
#include<utility>
using namespace std;

class segment_tree {
    unsigned long int seg_size;
    vector<int> seg;
    unsigned long int len;    
public:
    segment_tree(vector<int> nums) {
        len=nums.size();
        if(len!=0)
        {
        seg_size=(2* len)+1;
        seg.resize(seg_size);
        }
    }
    
    void update(int i, int val) {
        
        int diff=val-seg[i+len];
        seg[i+len]=val;
        unsigned long int x=(i+len)/2;
        while(x>0)
        {
            seg[x]+=diff;
            x=x/2;
        }
    }
    
   int sumRange(int i, int j) {
       int sum=0;
       unsigned long int left=i+len;
       unsigned long int right=j+len;
       
       while(left<right && left >0 && right>0)
       {
           if(left &1)
           {
               sum+=seg[left];
               left++;
           }
           if(!(right&1))
           {
               sum+=seg[right];
               right--;
           }
           
           left=left/2;
           right=right/2;
       }
       if(left==right)
           return sum+seg[left];
       
       return sum;
    }
};

struct mycompare
{
   bool operator() (pair<int,int>& i , pair<int,int>&  j)
    {
       // if number value is same then sort them acording to index
        if((i.first)==(j.first))
        {
            return (i.second)<(j.second);
        }
        return ((i.first)<(j.first));
    }
}mycmp;

class Solution {
    vector<pair<int,int>> temp;
public:
    vector<int> countSmaller(vector<int>& nums) {
        vector<int> result;
        segment_tree obj(nums);
        unsigned long int s=nums.size();
        
        result.resize(s);
        //result=new vector<int>[s];
        
        //making a copy of input such that each index in temp stores value and index of value in input.
        for(int i=0;i<s;i++)
        {
            temp.push_back(make_pair(nums[i], i));
        }
        //sort temp w.r.t value.
        sort(temp.begin(),temp.end(),mycmp);
        
        //update segment tree using sorted temp vector.
        for(int x=0;x<s;x++)
        {
            int a= temp[x].second;
            if(a==s-1)
            {
                result[a]=0;
                obj.update(a, 1);
            }
            else
            {
                // sum query from (a,s]  , s: size of nums
                result[a]=obj.sumRange(a+1,(int)s-1);
                obj.update(a, 1);
            }
        }
        
        return result;
        
    }
};

int main(int argc, const char * argv[]) {

    vector<int> nums={5,6,2,3,1};
    Solution s;
    vector<int> res;
    
    res= s.countSmaller(nums);
    
    
    for_each(res.begin(),res.end(),[](int i){ cout<<i<<", ";});
    
    return 0;
}
