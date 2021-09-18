#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <algorithm>

void scheduleWrapper(std::istream& in, std::ostream& out);

void scheduleTest(std::vector<std::string>& input, std::string& expected)
{
    std::stringstream in;
    std::stringstream ss;
    for (auto& e: input)
        in << e;
    scheduleWrapper(in, ss);
    std::string out = ss.str();
    std::cout << out;
    assert(out == expected);
}

using TestInputType = std::vector<std::string>;
void scheduleTestWrapper()
{
    TestInputType input = { "5\n 9 10\n9.3 10.3\n10 11\n10.3 11.3\n11 12\n",};
    std::string expected = "3\n9 10\n10 11\n11 12\n";
    scheduleTest(input, expected);
    input.clear();
    expected.clear();

    input = { "3\n9 10\n11 12.25\n12.15 13.3\n" };
    expected = "2\n9 10\n11 12.25\n";
    scheduleTest(input, expected);
    input.clear();
    expected.clear();

/*
    input = { "7\n19 19\n7 14\n12 14\n8 22\n22 23\n5 21\n9 23\n" };
    expected = "3\n7 14\n19 19\n22 23\n";
    scheduleTest(input, expected);
    input.clear();
    expected.clear();
*/
    input = { "7\n11 18\n19 19\n6 15\n14 19\n14 16\n18 21\n22 22\n" };
    expected = "3\n6 15\n19 19\n22 22\n";
    scheduleTest(input, expected);
    input.clear();
    expected.clear();

    input = { "4\n20 21\n20 20\n21 21\n19 20" };
    expected = "4\n19 20\n20 20\n20 21\n21 21\n";
    scheduleTest(input, expected);
    input.clear();
    expected.clear();
}


using DataType = uint16_t;
using Time = float;

struct Event
{
    Time s;
    Time e;

    Event(const Time aS, const Time aE) : s(aS), e(aE) { }
    bool operator<(const Event& rhs)
    {
       return (e == rhs.e) ? s < rhs.s : e < rhs.e;
    }
};

std::ostream& operator<<(std::ostream& out, const Event& event)
{
    out << event.s << " " << event.e << std::endl;   
    return out;
} 

using EventVector = std::vector<Event>;

void scheduleWrapper(std::istream& in, std::ostream& out)
{
    DataType n;
    float s, e;
    in >> n;
    if (!n)
    {
        out << "0" << std::endl;
        return;
    }
    
    EventVector events, schedule;
    events.reserve(n);
    schedule.reserve(n);
    for (size_t i = 0; i < n; ++i)
    {
        in >> s;
        in >> e;
        events.emplace_back(Event(s, e));
    }

    if (n == 1)
    {
        out << "1" << std::endl;
        out << events[0] << std::endl;
        return;
    }

    std::sort(events.begin(), events.end());
//    for (auto& el: events)
//        std::cout << "sorted " << el;

    schedule.push_back(events[0]);
    for (size_t i = 1; i < events.size(); ++i)
    {
        if (events[i].s == events[i].e && events[i].s > schedule.back().e)
        {
            schedule.push_back(events[i]);
            continue;
        }
        if (events[i].s < schedule.back().e)
            continue;

        schedule.push_back(events[i]);
    }
    out << schedule.size() << std::endl;
    for (auto& event: schedule)
        out << event;
}

int main(int argc, char** argv)
{
//    std::ios_base::sync_with_stdio(false);
//    std::cin.tie(NULL);
    // put any argument to follow unit testing path
    if (argc > 1)
        scheduleTestWrapper();
    else
        scheduleWrapper(std::cin, std::cout);
    std::cout << "\n";
}
