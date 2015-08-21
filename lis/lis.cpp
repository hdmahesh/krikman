#include<iostream>
#include<set>
#include<vector>
using namespace std;
void myfunction (int i) {  // function:
  std::cout << ' ' << i;
}
 
int LIS(vector<int> &A)
{
    int N = A.size(),i;
    set<int> s;
    set<int>::iterator k;
    for (i=0;i<N;i++)
    {
        if (s.insert(A[i]).second)
        {
           k = s.find(A[i]);
           k++;
           if (k!=s.end())
              s.erase(k);
        }
        for_each(s.begin(),s.end(),myfunction);
        cout << endl;
    }
    return s.size();
}

int main() {
  vector<int> arr;
  arr.push_back(1);
  arr.push_back(100);
  arr.push_back(50);
  arr.push_back(75);
  arr.push_back(80);
  arr.push_back(20);
//  arr.push_back();
  int len = LIS(arr);
  printf("\nLIS = %u\n", len);
}
