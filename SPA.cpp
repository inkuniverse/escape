#include "args.h"
//Short Path Moudle by Suhy
using namespace std;
class PFA
{
public:
    /*

以下为最短路内容

函数：GET_PFA()

传入参数：
1、a(x, y) 目标点坐标
2、b(x, y) 所在点坐标

需初始化的全局变量：
1、s[countPic][maxn][maxn] 地图
2、n 地图横向长度
3、m 地图纵向长度
4、cnt 地图的序号
5、sizeImage[pt]
返回值：
0 上 1 下 2 左 3 右

*/
    int cnt;
    int n,m;
    int s[countPic][maxn][maxn];
    point *sizeImage;
    const int MAXN = maxn;
    const int MAXM = maxn;

    PFA(int s[countPic][maxn][maxn],point *sizImage,int n,int m,int cnt):sizeImage(sizeImage),n(n),m(m),cnt(cnt)
    {
        memcpy(sizeImage,sizImage,sizeof sizeImage);
    }
    struct BfsPoint1
    {
        int x, y, dir, lans, be;
        bool operator<(const BfsPoint1 &b) const
        {
            if (x != b.x)
                return x < b.x;
            else if (y != b.y)
                return y < b.y;
            else if (dir != b.dir)
                return dir < b.dir;
            else if (lans != b.lans)
                return lans < b.lans;
            else
                return be < b.be;
        }
    };

    struct BfsPoint
    {
        int x, y, dir;
        bool operator<(const BfsPoint &b) const
        {
            if (x != b.x)
                return x < b.x;
            else if (y != b.y)
                return y < b.y;
            else
                return dir < b.dir;
        }
    };

    struct ANS
    {
        int val, dir;
    };

    ANS ans;
    map<BfsPoint, bool> vis;
    point a, b;
    queue<BfsPoint1> que;

    void GET_PFA_BFS(int lans, int dir, point b, point a)
    {
        if (que.front().be == 1)
        {
            que.pop();
            vis[{b.x, b.y, dir}] = 1;
            goto loop1;
        }
        que.pop();
        if (vis[{b.x, b.y, dir}] != 0)
            goto loop;
        if (b.x == a.x && b.y == a.y)
        {
            if (lans < ans.val)
            {
                ans.val = lans;
                ans.dir = dir;
            }
            goto loop;
        }
        vis[{b.x, b.y, dir}] = 1;

        if (s[cnt][b.x][b.y] <= '9' && s[cnt][b.x][b.y] >= '0')
        {
            for (int i = 0; i < m; i++)
            {
                for (int j = 0; j < n; j++)
                    if (b != point{i, j} && s[cnt][b.x][b.y] == s[cnt][i][j])
                        que.push({i, j, dir, lans + 1, 1});
            }
            goto loop;
        }

    loop1:
        if (b.x > 0 && s[cnt][b.x - 1][b.y] != '#' && s[cnt][b.x - 1][b.y] != 'N')
            que.push({b.x - 1, b.y, dir, lans + 1, 0});

        if (b.x < m - 1 && s[cnt][b.x + 1][b.y] != '#' && s[cnt][b.x + 1][b.y] != 'N')
            que.push({b.x + 1, b.y, dir, lans + 1, 0});

        if (b.y > 0 && s[cnt][b.x][b.y - 1] != '#' && s[cnt][b.x][b.y - 1] != 'N')
            que.push({b.x, b.y - 1, dir, lans + 1, 0});

        if (b.y < n - 1 && s[cnt][b.x][b.y + 1] != '#' && s[cnt][b.x][b.y + 1] != 'N')
            que.push({b.x, b.y + 1, dir, lans + 1, 0});

    loop:
        if (!que.empty())
            GET_PFA_BFS(que.front().lans, que.front().dir, {que.front().x, que.front().y}, a);
    }

    int GET_PFA(point a, point b)
    {
        n = sizeImage[cnt].x;
        m = sizeImage[cnt].y;
        ans.val = INT_MAX;
        for (int i = 0; i < 4; i++)
            vis[{b.x, b.y, i}] = 1;
        if (b.x > 0 && s[cnt][b.x - 1][b.y] != '#' && s[cnt][b.x - 1][b.y] != 'N')
            que.push({b.x - 1, b.y, 2, 1, 0});

        if (b.x < m && s[cnt][b.x + 1][b.y] != '#' && s[cnt][b.x + 1][b.y] != 'N')
            que.push({b.x + 1, b.y, 3, 1, 0});

        if (b.y > 0 && s[cnt][b.x][b.y - 1] != '#' && s[cnt][b.x][b.y - 1] != 'N')
            que.push({b.x, b.y - 1, 0, 1, 0});

        if (b.y < n && s[cnt][b.x][b.y + 1] != '#' && s[cnt][b.x][b.y + 1] != 'N')
            que.push({b.x, b.y + 1, 1, 1, 0});
        GET_PFA_BFS(1, que.front().dir, {que.front().x, que.front().y}, a);
        return ans.dir;
    }

    /*

Update:

2020/2/28:
1、添加功能：在计算中考虑传送门；
2、修复了若干bug。
注：从传送门这边传送到另一边算走了一步，如果踩到传送门上强制传送。

*/
};