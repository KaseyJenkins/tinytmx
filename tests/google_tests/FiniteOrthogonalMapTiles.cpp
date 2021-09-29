#include "gtest/gtest.h"
#include <iostream>
#include "tinytmx.hpp"


class MainTestTiles : public ::testing::Test {
protected:

    void SetUp() override {
        fileName = "assets/FiniteOrthogonalMapTiles.tmx";
        tmxmap = new tinytmx::Map();
        tmxmap->ParseFile(fileName);
    }

    void TearDown() override {
        delete tmxmap;
    }

    std::string fileName;
    tinytmx::Map *tmxmap;

};

TEST_F(MainTestTiles, TileObjectEmbedded) {
    auto tilesetTileObject = tmxmap->GetTileset(0)->GetTile(0)->GetObjectGroup()[0].GetObject(1);

    EXPECT_EQ(tilesetTileObject->GetId(), 5); // id
    auto tilesetTemplatedObject = tmxmap->GetTileset(0)->GetTile(0)->GetObjectGroup()[0].GetObject(2);
    EXPECT_EQ(tilesetTemplatedObject->GetId(), 7);
    EXPECT_EQ(tilesetTemplatedObject->GetName(), "PolygonTemplated");

}