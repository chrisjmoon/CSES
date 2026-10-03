#include <deque>
#include <iostream>
#include <vector>

int main()
{
    int h, w;
    std::cin >> h >> w;

    std::vector<std::string> grid(h);
    for (int i = 0; i < h; i++)
    {
        std::cin >> grid[i];
    }

    // run bfs
    // record for each cell the position we came from

    std::vector<std::pair<int, int>> dir{{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    std::string dir_char{"URDL"};

    std::vector<std::vector<char>> dir_grid{h, std::vector<char>(w, '\0')};
    std::deque<std::pair<int, int>> q;

    // determine starting position
    int x, y;
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            if (grid[i][j] == 'A')
            {
                x = i;
                y = j;
                break;
            }
        }
    }

    int fx{-1}, fy{-1};

    q.push_back({x, y});
    while (!q.empty())
    {
        auto [cx, cy] = q.front();
        q.pop_front();

        for (int i = 0; i < 4; i++)
        {
            auto [dx, dy] = dir[i];
            int nx{dx + cx};
            int ny{dy + cy};

            // check if we can go from (cx, cy) in the direction of (dx, dy)
            if (0 <= nx && nx < h && 0 <= ny && ny < w)
            {
                // check to see if we have visited this cell before
                // if we have visited, then ignore
                // we also want to check if its not a wall
                // then check if the cell is our destination; if it is,
                // then we may stop

                if (dir_grid[nx][ny] != '\0' || grid[nx][ny] == '#')
                {
                    continue;
                }

                dir_grid[nx][ny] = dir_char[i];
                if (grid[nx][ny] == 'B')
                {
                    fx = nx;
                    fy = ny;
                    q.clear();
                    break;
                }

                q.push_back({nx, ny});
            }
        }
    }

    if (fx == -1 && fy == -1)
    {
        std::cout << "NO" << std::endl;
        return 0;
    }

    std::string path{""};
    while (fx != x || fy != y)
    {
        path.push_back(dir_grid[fx][fy]);
        size_t dir_index = dir_char.find(dir_grid[fx][fy]);
        dir_index = (dir_index + 2) % 4;

        fx += dir[dir_index].first;
        fy += dir[dir_index].second;
    }

    std::cout << "YES" << std::endl;
    std::cout << path.size() << std::endl;
    for (int i = path.size() - 1; i >= 0; i--)
    {
        std::cout << path[i];
    }
    std::cout << std::endl;
}