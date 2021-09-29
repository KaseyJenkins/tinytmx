#include "gtest/gtest.h"
#include <iostream>
#include "tinytmx.hpp"


class MainTestTrialTilesetExternal : public ::testing::Test {
protected:

    void SetUp() override {
        fileName = "assets/TilesetExternalFiniteOrthogonalMap.tmx";
        tmxmap = new tinytmx::Map();
        tmxmap->ParseFile(fileName);
    }

    void TearDown() override {
        delete tmxmap;
    }

    std::string fileName;
    tinytmx::Map *tmxmap;

};


TEST_F(MainTestTrialTilesetExternal, ExternalTileset) {
    auto grassExternalTileset = tmxmap->GetTileset(0);
    EXPECT_EQ(grassExternalTileset->GetFirstGid(), 1);                      // firstgid
    EXPECT_EQ(grassExternalTileset->GetName(), "grass");                    // name

    EXPECT_EQ(grassExternalTileset->GetWangSet(0)->GetName(), "New Corner Set");

}

