#include <bits/stdc++.h>

struct Point
{
    int X{};
    int Y{};
};

struct Line
{
    Point A;
    Point B;
    double GetSlope() const
    {
        return (A.Y - B.Y) / static_cast<double>(A.X - B.X);
    }
};

std::pair<int, int> reduce_slope(const Line &line)
{
    int numerator{line.A.Y - line.B.Y};
    int denominator{line.A.X - line.B.X};

    int g{std::gcd(numerator, denominator)};

    return std::pair<int, int>{numerator / g, denominator / g};
}

using Lines = std::vector<Line>;

template <> struct std::hash<Line>
{
    size_t operator()(const Line &line) const
    {
    }

  private:
    pair<int, int> reduce_slope(const Line &line)
    {
        int numerator{line.A.Y - line.B.Y};
        int denominator{line.A.X - line.B.X};

        int g{gcd(numerator, denominator)};

        return pair<int, int>{numerator / g, denominator / g};
    }
};

int main()
{
    std::vector<double> xValues{0, 1.2, 4.5}, boundaries{1.2, 4.5};
    const auto results = groupByBoundaries(xValues, boundaries);
    for (auto res : results)
    {
        std::cout << res << std::endl;
    }
}