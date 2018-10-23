#include <string>

struct AlphaStrComp {
  bool operator()(const std::string& lhs, const std::string& rhs) 
  { // Uses string's built in operator< 
    // to do lexicographic (alphabetical) comparison
    return lhs < rhs; 
  }
};

struct LengthStrComp {
  bool operator()(const std::string& lhs, const std::string& rhs) 
  { 
    return lhs.size() < rhs.size(); 
  }
};

struct NumStrComp {
  bool operator()(const std::string& lhs, const std::string& rhs);
  int sum(const std::string& str);
};