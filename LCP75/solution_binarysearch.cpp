const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};
class Solution {
public:
    int n = 0;
    int m = 0;
    int dis[210][210];
    int cost[210][210];
    // int dp[210][210][2];
    void bfs(int x, int y, vector<string>& maze) {
        for(int i=0; i<=n; i++) {
            for(int j=0; j<=m; j++) {
                dis[i][j] = INT_MAX;
            }
        }
        queue<pair<int, int> > q;
        while(!q.empty()) {
            q.pop();
        }
        // vector<vector<int> > vis(n, vector<int>(m, 0));
        q.push({x, y});
        dis[x][y] = 0;
        while(!q.empty()) {
            pair<int, int> u = q.front();
            q.pop();
            // vis[u.first][u.second] = 1;
            // cout << u.first << " " << u.second << endl;
            for(int i=0; i<4; i++) {
                int xx = u.first + dx[i];
                int yy = u.second + dy[i];
                if(xx < 0 || xx >= n || yy < 0 || yy >= m) continue;
                if(dis[xx][yy] == INT_MAX && (maze[xx][yy] == '.'||maze[xx][yy]=='S')) {
                    dis[xx][yy] = dis[u.first][u.second] + 1;
                    // cout << xx << "-" << yy << ": " << dis[xx][yy] << endl; 
                    q.push({xx, yy});
                }
            }
        }
    }
    int challengeOfTheKeeper(vector<string>& maze) {
        n = maze.size();
        m = maze[0].size();
        int tx, ty;
        int sx, sy;
        for(int i=0; i<maze.size(); i++) {
            for(int j=0; j<maze[i].size(); j++) {
                if(maze[i][j] == 'T') {
                    tx = i;
                    ty = j;
                }
                if(maze[i][j] == 'S') {
                    sx = i;
                    sy = j;
                }
            }
        }
        // cout << "Debug" << endl;
        bfs(tx, ty, maze);
        // cout << "Debug" << endl;
        for(int i=0; i<maze.size(); i++) {
            for(int j=0; j<maze[i].size(); j++) {
                if(maze[i][j] == '.') {
                    cost[i][j] = dis[i][j];
                    // pair<int, int> ver = trans_ver(i, j);
                    if(maze[i][m-j-1] != '#') {
                        cost[i][j] = max(cost[i][j], dis[i][m-j-1]);
                    }
                    // pair<int, int> hor = trans_hor(i, j);
                    if(maze[n-i-1][j] != '#') {
                        cost[i][j] = max(cost[i][j], dis[n-i-1][j]);
                    }
                    // cout << i << "-" << j << ": " << cost[i][j] << endl;
                }
            }
        }
        int left = 0, right = 1e9;
        while(left != right) {
            int mid = (left + right) / 2;
            queue<pair<int, int> > q;
            while(!q.empty()) q.pop();
            vector<vector<int> > vis(n, vector<int>(m, 0));
            q.push({sx, sy});
            vis[sx][sy] = 1;
            while(!q.empty()) {
                auto u = q.front();
                q.pop();
                for(int i=0; i<4; i++) {
                    int xx = u.first + dx[i];
                    int yy = u.second + dy[i];
                    if(xx<0 || xx>=n || yy<0 || yy>=m || vis[xx][yy]!=0 || maze[xx][yy] == '#' || cost[xx][yy] > mid) continue;
                    q.push({xx, yy});
                    vis[xx][yy] = 1;
                }
            }
            if(vis[tx][ty] == 0) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return right == 1e9 ? -1 : right;
    }
};