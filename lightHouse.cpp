#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Struct for a point representing a lighthouse
struct Point {
    long long x, y;
};

// BIT (Fenwick Tree) to count pairs
class BIT {
public:
    vector<long long> tree;
    int size;

    BIT(int n) {
        size = n;
        tree.resize(n + 1, 0);
    }

    void update(int index, long long value) {
        while (index <= size) {
            tree[index] += value;
            index += index & -index;
        }
    }

    long long query(int index) {
        long long sum = 0;
        while (index > 0) {
            sum += tree[index];
            index -= index & -index;
        }
        return sum;
    }
};

int main() {
    int n;
    cin >> n;

    vector<Point> lighthouses(n);
    vector<pair<long long, int> > yCoordinates; // y-coordinates to compress
    for (int i = 0; i < n; i++) {
        cin >> lighthouses[i].x >> lighthouses[i].y;
        yCoordinates.emplace_back(lighthouses[i].y, i);
    }

    // Sort lighthouses by x-coordinate (ascending)
    sort(lighthouses.begin(), lighthouses.end(), [](Point &a, Point &b) {
        return a.x < b.x;
    });

    // Compress y-coordinates
    sort(yCoordinates.begin(), yCoordinates.end());
    vector<int> compressedY(n);
    for (int i = 0; i < n; i++) {
        compressedY[yCoordinates[i].second] = i + 1;
    }

    // Calculate pairs using Fenwick Tree (BIT)
    BIT bit(n);
    long long result = 0;
    for (const auto &lh : lighthouses) {
        int yIndex = compressedY[&lh - &lighthouses[0]]; // Get compressed y-coordinate
        result += bit.query(yIndex - 1);                // Count all lighthouses below current y
        bit.update(yIndex, 1);                          // Mark current lighthouse in BIT
    }

    cout << result << endl;
    return 0;
}
