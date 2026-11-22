#include "../include/exceptions/WorkflowExceptions.h"
#include "../include/documents/Document.h"
#include "../include/documents/DocumentMetadata.h"
#include "../include/documents/Tag.h"
#include "../include/search/DocumentSorter.h"
#include "../include/search/IndexEntry.h"
#include "../include/search/SearchEngine.h"
#include "../include/search/SearchFilter.h"
#include "../include/search/TagRegistry.h"
#include <gtest/gtest.h>

using namespace docflow;

TEST(SearchAndIndexingTest, SearchFilterSortingAndTagRegistry) {
    TagRegistry registry("MainTags", 5);
    Tag urgentTag("Urgent", "Priority", 9);
    registry.registerTag(urgentTag);
    EXPECT_EQ(registry.countTags(), 1U);
    EXPECT_EQ(registry.findTagByName("Urgent").getTagName(), "Urgent");

    Document doc1("D1", "Beta Report", "U1", DocumentMetadata(1, 1, "RU", 4));
    doc1.applyTag(urgentTag);
    Document doc2("D2", "Alpha Memo", "U1", DocumentMetadata(1, 1, "RU", 1));

    SearchEngine engine("ElasticSim");
    engine.indexDocument(doc1);
    engine.indexDocument(doc2);

    std::vector<std::string> hits = engine.searchByTerm("Urgent");
    ASSERT_EQ(hits.size(), 1U);
    EXPECT_EQ(hits[0], "D1");

    std::vector<Document> docs{doc1, doc2};
    DocumentSorter sorter("title", true);
    sorter.sortByTitle(docs);
    EXPECT_EQ(docs[0].getTitle(), "Alpha Memo");
    sorter.sortBySecurityLevel(docs);
    EXPECT_EQ(docs[0].getDocumentId(), "D2");

    SearchFilter filter("Beta", "DRAFT", 3);
    EXPECT_FALSE(filter.isFilterEmpty());
    std::vector<Document> filtered = engine.filterDocuments(docs, filter);
    EXPECT_EQ(filtered.size(), 1U);
    EXPECT_EQ(engine.getQueryCounter(), 2);
}

TEST(SearchAndIndexingTest, TagRegistryExceptions) {
    TagRegistry registry("SmallRegistry", 1);
    registry.registerTag(Tag("AllowedTag", "Category", 1));
    EXPECT_THROW(registry.registerTag(Tag("OverflowTag", "Category", 1)), StorageCapacityExceededException);

    EXPECT_THROW(registry.findTagByName("MissingTag"), DocumentNotFoundException);
}

TEST(SearchAndIndexingTest, IndexEntryScoreMatching) {
    std::vector<std::string> terms = {"urgent", "report"};
    IndexEntry entry("DOC-1", terms, 2);

    EXPECT_EQ(entry.scoreTermMatch("urgent"), 20);

    EXPECT_EQ(entry.scoreTermMatch("missing"), 0);
}

TEST(SearchAndIndexingTest, SearchFilterAndEngineEdgeCases) {
    Document doc("DOC-TEST", "Annual Report", "U1", DocumentMetadata(1, 1, "RU", 3));
    SearchFilter matchAll("Annual", "", 1);
    EXPECT_TRUE(matchAll.matchesDocument(doc));

    SearchFilter wrongTitle("Monthly", "DRAFT", 1);
    EXPECT_FALSE(wrongTitle.matchesDocument(doc));

    SearchFilter wrongStatus("", "APPROVED", 1);
    EXPECT_FALSE(wrongStatus.matchesDocument(doc));

    SearchFilter highSecurity("", "DRAFT", 5);
    EXPECT_FALSE(highSecurity.matchesDocument(doc));

    SearchEngine engine("TestEngine");
    engine.indexDocument(doc);

    std::vector<std::string> emptyResults = engine.searchByTerm("UnknownTerm");
    EXPECT_TRUE(emptyResults.empty());
}
