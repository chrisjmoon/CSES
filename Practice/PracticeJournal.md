



- Tree Matching
    - Approach was fine but execution slightly off. Our idea was to handle leaves and at each step of the outer loop generate a new set of nodes from the remaining after culling leaves. This is expensive. Instead, the more elegant way was to create a queue of leaves that we would process one by one. Keep it simple stupid! We want to focus our attention on a leaf at each given moment so structure the data structures around this intent.