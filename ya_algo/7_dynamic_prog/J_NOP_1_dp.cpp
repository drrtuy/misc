#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

using namespace std;

void nopWrapper(std::istream &in, std::ostream &out);

void nopTest(std::vector<std::string> &input, std::string &expected) {
  std::stringstream in;
  std::stringstream ss;
  for (auto &e : input)
    in << e;
  nopWrapper(in, ss);
  std::string out = ss.str();
  std::cout << out;
  assert(out == expected);
}

using TestInputType = std::vector<std::string>;
void nopTestWrapper() {
  TestInputType input = {"5\n4 2 9 1 13\n"};
  std::string expected = "3\n1 3 5 \n";
  nopTest(input, expected);
  input.clear();
  expected.clear();

  input = {"6\n1 2 4 8 16 32\n"};
  expected = "6\n1 2 3 4 5 6 \n";
  nopTest(input, expected);
  input.clear();
  expected.clear();
}

using DataType = int32_t;
using DPType = std::vector<DataType>;
using CellType = DataType;
using Ratings = std::vector<CellType>;
using Positions = Ratings;

void nopWrapper(std::istream &in, std::ostream &out) {
  DataType n;
  DataType tmp;
  in >> n;

  Ratings ratings(n, 0);

  for (DataType i = 0; i < n; ++i) {
    in >> tmp;
    ratings[i] = tmp;
  }

  Positions pos(n, -1);
  DPType dp(n, 1);
  for (DataType i = 0; i < n; ++i) {
    for (DataType j = 0; j < i; ++j) {
      auto jth_nop_length = dp[j] + 1;
      // cout << " i " << i << " j " << j << " jth_nop_length " <<
      // jth_nop_length
      //  << endl;
      if (jth_nop_length > dp[i] && ratings[j] < ratings[i]) {
        // cout << " yep " << i + 1 << endl;
        dp[i] = jth_nop_length;
        pos[i] = j;
      }
      // cout << "! ";
      // copy(pos.begin(), pos.end(), std::ostream_iterator<DataType>(cout, "
      // ")); cout << " ! " << endl;
    }
  }
  // cout << endl;

  auto nopLengthIt = std::max_element(dp.begin(), dp.end());
  auto nopPosIdx = nopLengthIt - dp.begin();

  out << *nopLengthIt << std::endl;

  Positions nopPos;
  nopPos.reserve(*nopLengthIt);

  // cout << "!!! initPos " << initPos << endl;

  while (nopPosIdx != -1) {
    nopPos.push_back(nopPosIdx + 1);
    nopPosIdx = pos[nopPosIdx];
  }

  copy(nopPos.rbegin(), nopPos.rend(),
       std::ostream_iterator<DataType>(out, " "));
  out << endl;
}

int main(int argc, char **argv) {
  //    std::ios_base::sync_with_stdio(false);
  //    std::cin.tie(NULL);
  // put any argument to follow unit testing path
  if (argc > 1)
    nopTestWrapper();
  else
    nopWrapper(std::cin, std::cout);
  std::cout << "\n";
}
