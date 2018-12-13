//problem from https://szkopul.edu.pl/problemset/problem/oNnWY6ZuzzhvG-jCmijiXkIk/site/?key=statement

#include <iostream>
#include <map>
#include <set>
using namespace std;

struct Node{
    multiset<int> starts;
    multiset<int> finishes;
};

int main(){
    map<int, map<int, Node> > m;
    int n, k, start, numBox, jump;
    cin >> n; cin >> k;
    int array[n + 1];
    for(int m = 0; m < n + 1; m++){
        array[m] = 0;
    }
    for(int i = 0; i < k; i++){
        cin >> start; cin >> numBox; cin >> jump;
        if(jump * jump >= n){
            for(int j = 0; j < numBox; j++){
                array[start + j*jump]++;
            }
        } else {
            if(m.count(jump) == 0){
                map<int, Node> newM;
                m[jump] = newM;
            }
            if(m[jump].count(start%jump) == 0){
                Node newNode;
                m[jump][start%jump] = newNode;
            }
            m[jump][start%jump].starts.insert(start);
            m[jump][start%jump].finishes.insert(start + (numBox - 1)*jump);
        }
    }
    for(map<int, map<int, Node > >::iterator it = m.begin(); it != m.end(); it++){
        for(map<int, Node>::iterator newIt = it->second.begin(); newIt != it->second.end(); newIt++){
            int startInd = *newIt->second.starts.begin();
            int endInd = *newIt->second.finishes.rbegin();
            int toAdd = 0;
            for(int i = startInd; i <= endInd; i+=it->first){
                toAdd += newIt->second.starts.count(i);
                if(toAdd == 0){
                    i = *newIt->second.starts.lower_bound(i + 1); //i????
                    toAdd += newIt->second.starts.count(i);
                }
                array[i]+= toAdd;
                toAdd -= newIt->second.finishes.count(i);

            }
        }
    }
    for(int l = 1; l < n + 1; l++){
        cout << array[l] << " ";
    }
    return 0;
}