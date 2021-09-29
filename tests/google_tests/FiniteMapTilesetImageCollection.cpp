#include "gtest/gtest.h"
#include <iostream>
#include "tinytmx.hpp"


class MainTestTrialTilesetImageCollection : public ::testing::Test {
protected:

    void SetUp() override {
        fileName = "assets/FiniteMapTilesetImageCollection.tmx";
        tmxmap = new tinytmx::Map();
        tmxmap->ParseFile(fileName);
    }

    void TearDown() override {
        delete tmxmap;
    }

    std::string fileName;
    tinytmx::Map *tmxmap;

};

TEST_F(MainTestTrialTilesetImageCollection, MainTestTrial) {
    auto tilesetImages = tmxmap->GetTileset(0);

    EXPECT_EQ(tilesetImages->GetTile(0)->GetImage()->GetSource(), "images/firstImage.png");
    EXPECT_EQ(tilesetImages->GetTile(2)->GetImage()->GetSource(), "images/thirdImage.png");
}
