#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<vector>
#include<queue>
#include<stack>
#include<cmath>
#include<map>

const int maxn = 1000;//1000*1000的图是最大值
const int countPic = 100;
struct point
{
    int x,y;
    bool operator!=(point b)
    {
        return x != b.x || y != b.y;
    }
};
