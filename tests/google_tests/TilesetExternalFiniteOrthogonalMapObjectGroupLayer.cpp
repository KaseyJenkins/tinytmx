#include "gtest/gtest.h"
#include <iostream>
#include "tinytmx.hpp"


class MainTestTilesetExternalObjectGroupLayer : public ::testing::Test {
protected:

    void SetUp() override {
        fileName = "assets/TilesetExternalFiniteOrthogonalMapObjectGroupLayer.tmx";
        tmxmap = new tinytmx::Map();
        tmxmap->ParseFile(fileName);
    }

    void TearDown() override {
        delete tmxmap;
    }

    std::string fileName;
    tinytmx::Map *tmxmap;

};


TEST_F(MainTestTilesetExternalObjectGroupLayer, GroupLayer) {
    auto groupLayer = tmxmap->GetGroupLayer(0);

    EXPECT_EQ(groupLayer->GetName(), "Group Layer");
    EXPECT_EQ(groupLayer->GetID(), 6);
    EXPECT_EQ(groupLayer->GetChild(0)->GetName(), "Object Layer 1");
}

