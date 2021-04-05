#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <algorithm>
#include <array>
#include <cmath>
#include <fstream>

void nearestWrapper(std::istream& in, std::ostream& out);

void nearestTest(std::vector<std::string>& input, std::string& expected)
{
    std::stringstream in;
    std::stringstream ss;
    for (auto& e: input)
        in << e;
    nearestWrapper(in, ss);
    std::string out = ss.str();
    std::cout << out;
    assert(out == expected);
}

/**
 * Class for representing a point. coordinate_type must be a numeric type.
 */
template<typename coordinate_type, size_t dimensions>
class point {
public:
    point(std::array<coordinate_type, dimensions> c, size_t seq_number = 0) : coords_(c), seq_number_(seq_number) {}
    point(std::initializer_list<coordinate_type> list) {
        size_t n = std::min(dimensions, list.size());
        std::copy_n(list.begin(), n, coords_.begin());
    }
    /**
     * Returns the coordinate in the given dimension.
     *
     * @param index dimension index (zero based)
     * @return coordinate in the given dimension
     */
    coordinate_type get(size_t index) const {
        return coords_[index];
    }
    /**
     * Returns the distance squared from this point to another
     * point.
     *
     * @param pt another point
     * @return distance squared from this point to the other point
     */
    int64_t distance(const point& pt) const {
        int64_t dist = 0;
        for (size_t i = 0; i < dimensions; ++i) {
            int64_t d = get(i) - pt.get(i);
            dist += d * d;
        }
        return dist;
    }
    size_t seq_number() const
    {
        return seq_number_;
    }
private:
    std::array<coordinate_type, dimensions> coords_;
    size_t seq_number_;
};

template<typename coordinate_type, size_t dimensions>
std::ostream& operator<<(std::ostream& out, const point<coordinate_type, dimensions>& pt) {
    out << '(';
    for (size_t i = 0; i < dimensions; ++i) {
        if (i > 0)
            out << ", ";
        out << pt.get(i);
    }
    out << ')';
    out << '[' << pt.seq_number() << ']';
    return out;
}

/**
 * C++ k-d tree implementation, based on the C version at rosettacode.org.
 */
template<typename coordinate_type, size_t dimensions>
class kdtree {
public:
    typedef point<coordinate_type, dimensions> point_type;
private:
    struct node {
        node(const point_type& pt) : point_(pt), left_(nullptr), right_(nullptr) {}
        coordinate_type get(size_t index) const {
            return point_.get(index);
        }
        int64_t distance(const point_type& pt) const {
            return point_.distance(pt);
        }
        point_type point_;
        node* left_;
        node* right_;
    };
    node* root_ = nullptr;
    node* best_ = nullptr;
    const int64_t min_dist_ = 400; // 20^2
    std::vector<point_type*> closest_;
    size_t visited_ = 0;
    std::vector<node> nodes_;
 
    struct node_cmp {
        node_cmp(size_t index) : index_(index) {}
        bool operator()(const node& n1, const node& n2) const {
            return n1.point_.get(index_) < n2.point_.get(index_);
        }
        size_t index_;
    };
 
    node* make_tree(size_t begin, size_t end, size_t index) {
        if (end <= begin)
            return nullptr;
        size_t n = begin + (end - begin)/2;
        std::nth_element(&nodes_[begin], &nodes_[n], &nodes_[0] + end, node_cmp(index));
        index = (index + 1) % dimensions;
        nodes_[n].left_ = make_tree(begin, n, index);
        nodes_[n].right_ = make_tree(n + 1, end, index);
        return &nodes_[n];
    }
 
    void nearest(node* root, const point_type& point, size_t index) {
        if (root == nullptr)
            return;
        ++visited_;
        int64_t d = root->distance(point);
        if (d <= min_dist_) {
            closest_.push_back(&(root->point_));
            best_ = root;
        }
//        if (closest_.empty())
//            return;
        int64_t dx = root->get(index) - point.get(index);
        index = (index + 1) % dimensions;
        nearest(dx > 0 ? root->left_ : root->right_, point, index);
        if (dx * dx >= min_dist_)
            return;
        nearest(dx > 0 ? root->right_ : root->left_, point, index);
    }
public:
    kdtree(const kdtree&) = delete;
    kdtree& operator=(const kdtree&) = delete;
    /**
     * Constructor taking a pair of iterators. Adds each
     * point in the range [begin, end) to the tree.
     *
     * @param begin start of range
     * @param end end of range
     */
    template<typename iterator>
    kdtree(iterator begin, iterator end) : nodes_(begin, end) {
        root_ = make_tree(0, nodes_.size(), 0);
    }
 
    /**
     * Finds the nearest point in the tree to the given point.
     * It is not valid to call this function if the tree is empty.
     *
     * @param pt a point
     * @return the nearest point in the tree to the given point
     */
    const std::vector<point_type*>& nearest(const point_type& pt) {
        if (root_ == nullptr)
            throw std::logic_error("tree is empty");
        best_ = nullptr;
        visited_ = 0;
        closest_.clear();
        nearest(root_, pt, 0);
        return closest_;
    }
};

using point2d = point<int64_t, 2>;
using tree2d = kdtree<int64_t, 2>;
using CoordType = int64_t;

void nearestWrapper(std::istream& fin, std::ostream& out)
{
    std::ifstream in("input.txt");
    size_t stopsNumber, exitsNumber;
    in >> exitsNumber;
    std::vector<point2d> exits;
    exits.reserve(exitsNumber);
    for (size_t i = 0; i < exitsNumber; ++i)
    {
        CoordType x, y;
        in >> x >> y;
        exits.push_back(point2d({x, y}, i + 1));
    }

    in >> stopsNumber;
    std::vector<point2d> stops;
    stops.reserve(stopsNumber);
    for (size_t i = 0; i < stopsNumber; ++i)
    {
        CoordType x, y;
        in >> x >> y;
        stops.push_back({x, y});
    }
    
    if (exitsNumber == 1)
    {
        out << "1\n";
        return;
    }

    tree2d tree(stops.begin(), stops.end());
    size_t bestExit = 0;
    size_t bestNumberOfStops = 0;
    size_t i = 1;
    for (auto& e: exits)
    {
        size_t stopsNearby = 0;
        std::cout << "s " << e << "\n";
        for (auto& s: stops)
        {
            stopsNearby = e.distance(s) <= 400 ? stopsNearby + 1 : stopsNearby;
        }
        std::cout << stopsNearby << "\n";
    }
}

int main(int argc, char** argv)
{
//    std::ios_base::sync_with_stdio(false);
//    std::cin.tie(NULL);
    // put any argument to follow unit testing path
    nearestWrapper(std::cin, std::cout);
    std::cout << "\n";
}
