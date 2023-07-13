#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;


int main() {
    ll t;
    cin >> t;
    while(t--)
    {
        ll r,c,r1,r2,c1,c2;
        cin >> r >> c;
        cin >> r1 >> c1;
        cin >> r2 >> c2;
    
        vector<vector<ll>> arr(r+1,vector<ll>(c+1,0));
        for(ll i = r1; i <= r2; i++)
        {
            for(ll j = c1; j <= c2; j++)
            {
                arr[i][j] = -1;
            }
        }

        arr[1][1] = 1;
        for(ll i = 1; i < r+1; i++)
        {
            for(ll j = 1; j < c+1; j++)
            {
                if(arr[i][j] == -1)
                {
                    continue;
                }

                if(i == r && j == c)
                {
                    continue;
                }
                
                if(i == r)
                {
                    if(arr[i][j+1] != -1)
                       arr[i][j+1] = (arr[i][j+1] + arr[i][j]) % (1000000007);
                }
                else if(j == c)
                {
                    if(arr[i+1][j] != -1)
                       arr[i+1][j] = (arr[i+1][j] + arr[i][j]) % (1000000007);
                }
                else
                {
                    if(arr[i][j+1] != -1)
                       arr[i][j+1] = (arr[i][j+1] + arr[i][j]) % (1000000007);

                    if(arr[i+1][j] != -1)
                       arr[i+1][j] = (arr[i+1][j] + arr[i][j]) % (1000000007);
                }
            }
        }
        
        // for(ll i = 0; i < r+1; i++)
        // {
        //     for(ll j = 0; j < c+1; j++)
        //     {
        //         cout << arr[i][j] << " ";
        //     }
        //     cout << "\n";
        // }

        if(arr[r][c] == -1)
        {
            cout << 0 << "\n";
        }
        else
        {
            cout << arr[r][c] % (1000000007) << "\n";
        }
    }
    
    return 0;
}
