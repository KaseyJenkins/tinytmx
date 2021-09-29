#include "gtest/gtest.h"
#include <iostream>
#include "tinytmx.hpp"


class MainTestTilesetEmbeddedTileObject : public ::testing::Test {
protected:

    void SetUp() override {
        fileName = "assets/FiniteOrthogonalMapObjectGroupTileObjectEmbedded.tmx";
        tmxmap = new tinytmx::Map();
        tmxmap->ParseFile(fileName);
    }

    void TearDown() override {
        delete tmxmap;
    }

    std::string fileName;
    tinytmx::Map *tmxmap;

};

TEST_F(MainTestTilesetEmbeddedTileObject, TileObjectEmbedded) {
    auto tileObjectEmbed = tmxmap->GetObjectGroup(0)->GetObject(0);
    if (tileObjectEmbed->GetObjectType() == tinytmx::ObjectType::TMX_OT_TILE) {
        puts("It's a Tile Object");
        std::cout << tileObjectEmbed->GetTile()->gid << std::endl;
    }
}