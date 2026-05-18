#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, k;
    cin >> n >> k;

    vector<int> x(n);
    for (int i = 0; i < n; i++)
    {
        cin >> x[i];
    }

    deque<int> s;
    int largest_rectangle = 0;
    int left_index = 0; // index of the leftmost bar within the rectangle
    int right_index = k - 1;
    int rectangle_height = 0;
    for (int i = 0; i < k; i++)
    {
        while (s.size() && s.back() > x[i])
        {
            int height = s.back();
            s.pop_back();
            int width = s.size() ? i - s.back() - 1 : i;
            if (height * width > largest_rectangle)
            {
                left_index = s.size() ? s.back() + 1 : 0;
                rectangle_height = height;
                largest_rectangle = height * width;
            }
        }
    }

    vector<int> res = {largest_rectangle};
    for (int i = k; i < n; i++)
    {
        if (s.front() == i - k)
        {
            s.pop_front();
        }

        int largest_rectangle = 0;
        if (left_index == i - k)
        {
            left_index++;
            largest_rectangle = rectangle_height * (right_index - left_index + 1);
        }

        while (s.size() && s.back() > x[i])
        {
            int height = s.back()
        }
    }
}