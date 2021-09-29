#include "gtest/gtest.h"
#include <iostream>
#include "tinytmx.hpp"


class MainTestTilesetTemplatedTileObject : public ::testing::Test {
protected:

    void SetUp() override {
        fileName = "assets/FiniteOrthogonalMapObjectGroupTileObjectTemplated.tmx";
        tmxmap = new tinytmx::Map();
        tmxmap->ParseFile(fileName);
    }

    void TearDown() override {
        delete tmxmap;
    }

    std::string fileName;
    tinytmx::Map *tmxmap;

};

TEST_F(MainTestTilesetTemplatedTileObject, TileObjectEmbedded) {
    std::cout << tmxmap->GetObjectGroup(0)->GetObject(0)->GetTile()->gid << std::endl;
    std::cout << tmxmap->GetObjectGroup(0)->GetObject(0)->GetGid() << std::endl;
}