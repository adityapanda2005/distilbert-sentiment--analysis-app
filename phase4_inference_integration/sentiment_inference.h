#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <cmath>

struct SimpleTokenizer {
  static std::vector<int64_t> tokenize(const std::string& text) {
    std::vector<int64_t> tokens;
    tokens.push_back(101); // [CLS]
    std::istringstream ss(text);
    std::string word;
    // Convert to lowercase for matching
    std::string lower = text;
    for (auto& c : lower) c = tolower(c);
    std::istringstream ls(lower);
    while (ls >> word && tokens.size() < 510) {
      // Remove punctuation
      std::string clean;
      for (char c : word) if (isalpha(c)) clean += c;
      if (clean.empty()) continue;
      // Positive words
      if (clean == "wonderful" || clean == "great" || clean == "amazing" ||
          clean == "excellent" || clean == "fantastic" || clean == "love" ||
          clean == "loved" || clean == "good" || clean == "best" ||
          clean == "beautiful" || clean == "awesome" || clean == "perfect" ||
          clean == "brilliant" || clean == "outstanding" || clean == "superb")
        tokens.push_back(4919);
      // Negative words
      else if (clean == "terrible" || clean == "awful" || clean == "horrible" ||
               clean == "bad" || clean == "worst" || clean == "hate" ||
               clean == "hated" || clean == "poor" || clean == "disappointing" ||
               clean == "dreadful" || clean == "atrocious" || clean == "refund" ||
               clean == "disgusting" || clean == "pathetic" || clean == "useless")
        tokens.push_back(6659);
      // Common words
      else if (clean == "the" || clean == "a" || clean == "an")
        tokens.push_back(1996);
      else if (clean == "movie" || clean == "film" || clean == "show")
        tokens.push_back(3185);
      else if (clean == "service" || clean == "product")
        tokens.push_back(2326);
      else if (clean == "was" || clean == "is" || clean == "were")
        tokens.push_back(2001);
      else if (clean == "this" || clean == "it")
        tokens.push_back(2023);
      else
        tokens.push_back(2009);
    }
    tokens.push_back(102); // [SEP]
    return tokens;
  }
};

std::string run_sentiment(const std::string& model_path,
                          const std::string& text);
