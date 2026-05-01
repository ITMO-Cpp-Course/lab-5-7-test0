#include <catch2/catch_all.hpp>
#include "document.hpp"
#include "documentBuilder.hpp"
#include "invertedIndex.hpp"
#include <iostream>


// TODO: Your code
TEST_CASE("Test case name", "[some_tag]")
{
    REQUIRE(false);
}

TEST_CASE("Some true test", "[some_tag]")
{
    lab5::space::Document d0 = lab5::space::DocumentBuilder::build("d0.txt",
      "a, b, c, a, a b");
    lab5::space::Document d1 = lab5::space::DocumentBuilder::build("d0.txt",
      "abracadabra");
    lab5::space::InvertedIndex index;

    index.add(d0);
    index.add(d1);

    std::cout << "d0: " << d0.getId() << std::endl;
    std::cout << "d1: " << d1.getId() << std::endl;

    std::vector<std::string> words{"a", "b", "c", "d", "abracadabra"};

    for (auto& w : words)
    {
      std::cout << "-----------  " << w << "  -----------\n"; 

      auto res = index.searchByWord(w);    // вернул vector
      for (auto& e : res)
        std::cout << e << std::endl;

      std::cout << "----------------------\n"; 
      auto res1 = index.count(w);          // вернул map
      for (auto& [e1, e2] : res1)
        std::cout << e1 << " : " << e2 << std::endl;
    }

    index.remove(0);

    for (auto& w : words)
    {
      std::cout << "-----------  " << w << "  -----------\n"; 

      auto res = index.searchByWord(w);
      for (auto& e : res)
        std::cout << e << std::endl;

      std::cout << "----------------------\n"; 
      auto res1 = index.count(w);
      for (auto& [e1, e2] : res1)
        std::cout << e1 << " : " << e2 << std::endl;
    }


    REQUIRE(true);
}
