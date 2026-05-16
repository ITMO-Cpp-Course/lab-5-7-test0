#include "document.hpp"
#include "documentBuilder.hpp"
#include "indexError.hpp"
#include "indexStore.hpp"
#include "invertedIndex.hpp"
#include "updateTransaction.hpp"
#include <catch2/catch_all.hpp>

using namespace lab5::space;
using namespace lab6::space;

TEST_CASE("Document and Builder basics", "[document][builder]")
{
    SECTION("split_by_words and lowercase")
    {
        auto words = DocumentBuilder::split_by_words("Hello, Physics! (Kinematics?) - physics; 'hello'.");
        REQUIRE(words.size() == 3);
        REQUIRE(words["hello"] == 2);
        REQUIRE(words["physics"] == 2);
        REQUIRE(words["kinematics"] == 1);
    }

    SECTION("Document getters")
    {
        Document d = DocumentBuilder::build("test.txt", "Some content");
        REQUIRE(d.getName() == "test.txt");
        REQUIRE(d.getContent() == "Some content");
    }
}

TEST_CASE("InvertedIndex basic operations", "[index][add][search]")
{
    InvertedIndex index;
    Document d1 = DocumentBuilder::build("doc1.txt", "Kinematics and dynamics");
    Document d2 = DocumentBuilder::build("doc2.txt", "Newton's laws of dynamics");

    const auto id1 = d1.getId();
    const auto id2 = d2.getId();

    index.add(std::move(d1));
    index.add(std::move(d2));

    SECTION("searching existing word")
    {
        auto res = index.searchByWord("dynamics");
        REQUIRE(res.size() == 2);
        REQUIRE(std::find(res.begin(), res.end(), id1) != res.end());
        REQUIRE(std::find(res.begin(), res.end(), id2) != res.end());
    }

    SECTION("searching missing word")
    {
        auto res = index.searchByWord("thermodynamics");
        REQUIRE(res.empty() == true);
    }
}

TEST_CASE("InvertedIndex frequency counting", "[index][count]")
{
    InvertedIndex index;
    Document d = DocumentBuilder::build("repeat.txt", "word word test word");
    const auto id = d.getId();

    index.add(std::move(d));
    auto counts = index.count("word");

    REQUIRE(counts.size() == 1);
    REQUIRE(counts[id] == 3);
}

TEST_CASE("InvertedIndex document removal", "[index][remove]")
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

    SECTION("unique word is no longer found")
    {
        auto res_unique = index.searchByWord("uniqueword");
        REQUIRE(res_unique.empty() == true);
    }

    SECTION("shared word no longer points to the deleted document")
    {
        auto res_common = index.searchByWord("commonword");
        REQUIRE(res_common.size() == 1);
        REQUIRE(res_common[0] == id2);
    }
}

TEST_CASE("IndexStore direct operations and error handling", "[store][errors]")
{
    IndexStore store;

    SECTION("Successful operations without transaction")
    {
        Document d = DocumentBuilder::build("direct.txt", "direct access test");
        REQUIRE(store.add(d).has_value());

        auto res = store.searchByWord("direct");
        REQUIRE(res.has_value());
        REQUIRE(res->size() == 1);
    }

    SECTION("Error on empty search query")
    {
        auto res = store.searchByWord("");
        REQUIRE_FALSE(res.has_value());
        REQUIRE(res.error().what() != std::string(""));
    }

    SECTION("Error on empty count query")
    {
        auto res = store.count("");
        REQUIRE_FALSE(res.has_value());
    }
}

TEST_CASE("UpdateTransaction commit mechanism", "[transaction][commit]")
{
    IndexStore store;
    Document d1 = DocumentBuilder::build("doc.txt", "transactional update test");
    const auto id = d1.getId();

    SECTION("Changes are applied after commit")
    {
        auto tr = store.startTransaction();
        REQUIRE(tr.add(d1).has_value());

        auto tr_res = tr.searchByWord("update");
        REQUIRE(tr_res.has_value());
        REQUIRE(tr_res->size() == 1);

        auto store_res_before = store.searchByWord("update");
        REQUIRE(store_res_before.has_value());
        REQUIRE(store_res_before->empty());

        REQUIRE(tr.commit().has_value());

        auto store_res_after = store.searchByWord("update");
        REQUIRE(store_res_after.has_value());
        REQUIRE(store_res_after->size() == 1);
        REQUIRE(store_res_after.value()[0] == id);
    }
}

TEST_CASE("UpdateTransaction rollback mechanism", "[transaction][rollback]")
{
    IndexStore store;

    SECTION("Changes are discarded if commit is not called")
    {
        {
            auto tr = store.startTransaction();
            Document d = DocumentBuilder::build("temp.txt", "temporary data");
            REQUIRE(tr.add(d).has_value());

            auto tr_res = tr.searchByWord("temporary");
            REQUIRE(tr_res.has_value());
            REQUIRE(tr_res->size() == 1);
        }

        auto res = store.searchByWord("temporary");
        REQUIRE(res.has_value());
        REQUIRE(res->empty());
    }
}

TEST_CASE("UpdateTransaction state and invalidation logic", "[transaction][state]")
{
    IndexStore store;

    SECTION("Cannot open multiple transactions simultaneously")
    {
        auto tr1 = store.startTransaction();
        REQUIRE_THROWS_AS(store.startTransaction(), IndexError);
    }

    SECTION("Transaction becomes invalid after commit")
    {
        auto tr = store.startTransaction();
        REQUIRE(tr.commit().has_value());

        REQUIRE_FALSE(tr.valid());

        Document d = DocumentBuilder::build("fail.txt", "fail");
        auto res = tr.add(d);
        REQUIRE_FALSE(res.has_value());
    }

    SECTION("Transaction invalidates on inner error")
    {
        auto tr = store.startTransaction();

        auto err_res = tr.searchByWord("");
        REQUIRE_FALSE(err_res.has_value());

        REQUIRE_FALSE(tr.valid());
        REQUIRE_FALSE(tr.commit().has_value());
    }
}