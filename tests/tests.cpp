#include "document.hpp"

#include "documentBuilder.hpp"

#include "invertedIndex.hpp"

#include <catch2/catch_all.hpp>
#include "document.hpp"
#include "documentBuilder.hpp"
#include "invertedIndex.hpp"
#include <iostream>


using namespace lab5::space;

TEST_CASE("[builder]")

{

    auto words = DocumentBuilder::split_by_words("Hello, Physics! hello");

    REQUIRE(words.size() == 2);

    REQUIRE(words["hello"] == 2);

    REQUIRE(words["physics"] == 1);
}

TEST_CASE("[index][add][search]")

{

    InvertedIndex index;

    Document d1 = DocumentBuilder::build("doc1.txt", "Kinematics and dynamics");

    Document d2 = DocumentBuilder::build("doc2.txt", "Newton's laws of dynamics");

    index.add(d1);

    index.add(d2);

    SECTION("seaching existing")

    {

        auto res = index.searchByWord("dynamics");

        REQUIRE(res.size() == 2);

        REQUIRE(std::find(res.begin(), res.end(), d1.getId()) != res.end());

        REQUIRE(std::find(res.begin(), res.end(), d2.getId()) != res.end());
    }

    SECTION("seachibg nothing")

    {

        auto res = index.searchByWord("thermodynamics");

        REQUIRE(res.empty() == true);
    }
}

TEST_CASE("repeat? ", "[index][count]")

{

    InvertedIndex index;

    Document d = DocumentBuilder::build("repeat.txt", "word word test word");

    index.add(d);

    auto counts = index.count("word");

    REQUIRE(counts.size() == 1);

    REQUIRE(counts[d.getId()] == 3);
}

TEST_CASE("remove test", "[index][remove]")

{

    InvertedIndex index;

    Document d1 = DocumentBuilder::build("d1.txt", "uniqueword commonword");

    Document d2 = DocumentBuilder::build("d2.txt", "commonword");

    index.add(d1);

    index.add(d2);

    REQUIRE(index.searchByWord("uniqueword").size() == 1);

    REQUIRE(index.searchByWord("commonword").size() == 2);

    index.remove(d1.getId());

    SECTION("no found")

    {

        auto res_unique = index.searchByWord("uniqueword");

        REQUIRE(res_unique.empty() == true);
    }

    SECTION("Shared word no longer points to the deleted document")

    {

        auto res_common = index.searchByWord("commonword");

        REQUIRE(res_common.size() == 1);

        REQUIRE(res_common[0] == d2.getId());
    }
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
