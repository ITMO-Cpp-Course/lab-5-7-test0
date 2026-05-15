#include "document.hpp"
#include "documentBuilder.hpp"
#include "invertedIndex.hpp"
#include "updateTransaction.hpp"
#include <catch2/catch_all.hpp>
using namespace lab5::space;
using namespace lab6::space;

TEST_CASE("[builder]")
{
    auto words = DocumentBuilder::split_by_words("Hello, Physics! (Kinematics?) - physics; 'hello'.");
    REQUIRE(words.size() == 3);
    REQUIRE(words["hello"] == 2);
    REQUIRE(words["physics"] == 2);
    REQUIRE(words["kinematics"] == 1);
}

TEST_CASE("[index][add][search]")
{
    InvertedIndex index;
    Document d1 = DocumentBuilder::build("doc1.txt", "Kinematics and dynamics");
    Document d2 = DocumentBuilder::build("doc2.txt", "Newton's laws of dynamics");

    const auto id1 = d1.getId();
    const auto id2 = d2.getId();

    index.add(std::move(d1));
    index.add(std::move(d2));

    SECTION("seaching existing")
    {
        auto res = index.searchByWord("dynamics");
        REQUIRE(res.size() == 2);
        REQUIRE(std::find(res.begin(), res.end(), id1) != res.end());
        REQUIRE(std::find(res.begin(), res.end(), id2) != res.end());
    }

    SECTION("seachibg nothing")
    {
        auto res = index.searchByWord("thermodynamics");
        REQUIRE(res.empty() == true);
    }
}

TEST_CASE("frequency", "[index][count]")
{
    InvertedIndex index;
    Document d = DocumentBuilder::build("repeat.txt", "word word test word");
    const auto id = d.getId();

    index.add(std::move(d));
    auto counts = index.count("word");

    REQUIRE(counts.size() == 1);
    REQUIRE(counts[id] == 3);
}

TEST_CASE("remove test", "[index][remove]")
{

    InvertedIndex index;
    Document d1 = DocumentBuilder::build("d1.txt", "uniqueword commonword");
    Document d2 = DocumentBuilder::build("d2.txt", "commonword");

    const auto id1 = d1.getId();
    const auto id2 = d2.getId();

    index.add(std::move(d1));
    index.add(std::move(d2));

    REQUIRE(index.searchByWord("uniqueword").size() == 1);
    REQUIRE(index.searchByWord("commonword").size() == 2);

    index.remove(id1);
    SECTION("no found")
    {
        auto res_unique = index.searchByWord("uniqueword");
        REQUIRE(res_unique.empty() == true);
    }

    SECTION("Shared word no longer points to the deleted document")
    {
        auto res_common = index.searchByWord("commonword");
        REQUIRE(res_common.size() == 1);
        REQUIRE(res_common[0] == id2);
    }
}

/*************
 * TO DELETE *
 *************/
TEST_CASE("store example test", "[store][example]")
{
    IndexStore store;
    Document d1 = DocumentBuilder::build("d1.txt", "uniqueword commonword");
    Document d2 = DocumentBuilder::build("d2.txt", "commonword");

    const auto id1 = d1.getId();
    const auto id2 = d2.getId();

    auto tr = store.startTransaction();

    auto voidRes = tr.add(d1);
    voidRes = tr.add(d2);

    auto res = tr.searchByWord("uniqueword");
    // REQUIRE(index.searchByWord("commonword").size() == 2);

    voidRes = tr.remove(id1);

    voidRes = tr.commit();

    tr = store.startTransaction();

    voidRes = tr.remove(id2);
    auto findRes = tr.searchByWord("");
    voidRes = tr.commit();
}