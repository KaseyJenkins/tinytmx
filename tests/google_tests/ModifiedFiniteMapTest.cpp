#include "gtest/gtest.h"
#include <iostream>
#include "tinytmx.hpp"


class MainTestTrialModified : public ::testing::Test {
protected:

    void SetUp() override {
        fileName = "assets/ModifiedFiniteOrthogonalMap.tmx";
        tmxmap = new tinytmx::Map();
        tmxmap->ParseFile(fileName);
    }

    void TearDown() override {
        delete tmxmap;
    }

    std::string fileName;
    tinytmx::Map *tmxmap;

};

TEST_F(MainTestTrialModified, Map) {
    EXPECT_EQ(tmxmap->GetVersion(), 1.5);                                            // version
    EXPECT_EQ(tmxmap->GetTiledVersion(), "2021.03.23");                              // tiledversion
    EXPECT_EQ(tmxmap->GetOrientation(), tinytmx::MapOrientation::TMX_MO_ORTHOGONAL); // orientation
    EXPECT_EQ(tmxmap->GetRenderOrder(), tinytmx::MapRenderOrder::TMX_RIGHT_DOWN);    // orientation
    EXPECT_EQ(tmxmap->GetCompressionLevel(), -1);                                    // compressionlevel
    EXPECT_EQ(tmxmap->GetWidth(), 20);                                               // width
    EXPECT_EQ(tmxmap->GetHeight(), 15);                                              // height
    EXPECT_EQ(tmxmap->GetTileWidth(), 32);                                           // tilewidth
    EXPECT_EQ(tmxmap->GetTileHeight(), 32);                                          // tileheight
    EXPECT_EQ(tmxmap->GetBackgroundColor().ToString(), "#3f97a7ff");                 // backgroundcolor
    EXPECT_EQ(tmxmap->GetNextLayerID(), 2);                                          // nextlayerid
    EXPECT_EQ(tmxmap->GetNextObjectID(), 1);                                         // nextobjectid
    EXPECT_EQ(tmxmap->IsInfinite(), false);                                          // infinite
}

TEST_F(MainTestTrialModified, MapCustomProperties) {
    auto CustomMapProperties = tmxmap->GetProperties();
    EXPECT_EQ(tmxmap->GetProperties().GetBoolProperty("BoolProp"), true);                     // Bool Custom Property
    EXPECT_EQ(tmxmap->GetProperties().GetColorProperty("ColorProp").ToString(), "#ed00008b"); // Color Custom Property
    EXPECT_EQ(tmxmap->GetProperties().GetFloatProperty("FloatProp"), 2.3f);                   // Float Custom Property
    EXPECT_EQ(tmxmap->GetProperties().GetIntProperty("IntProp"), 658);                        // Int Custom Property
    EXPECT_EQ(tmxmap->GetProperties().GetStringProperty("StringProp"), "Some String\n");
}

TEST_F(MainTestTrialModified, Layer) {
    auto tileLayer = tmxmap->GetTileLayer(0);

    EXPECT_EQ(tileLayer->GetID(), 1);                                                 // id
    EXPECT_EQ(tileLayer->GetName(), "Tile Layer 1");                                  // name
    EXPECT_EQ(tileLayer->GetWidth(), 20);                                             // width
    EXPECT_EQ(tileLayer->GetHeight(), 15);                                            // height

    EXPECT_EQ(tileLayer->GetOpacity(), 1);                                            // opacity
    EXPECT_EQ(tileLayer->IsVisible(), true);                                          // visible
    EXPECT_EQ(tileLayer->GetTintColor().ToString(), "#00000000");                     // tintcolor
    EXPECT_EQ(tileLayer->GetOffsetX(), 0);                                            // offsetx
    EXPECT_EQ(tileLayer->GetOffsetY(), 0);                                            // offsety
    EXPECT_EQ(tileLayer->GetParallax().x, 1);                                         // parallaxx
    EXPECT_EQ(tileLayer->GetParallax().y, 1);                                         // parallaxy
    EXPECT_EQ(tileLayer->GetEncoding(),tinytmx::TileLayerEncodingType::TMX_ENCODING_CSV);
    EXPECT_EQ(tileLayer->GetCompression(), tinytmx::TileLayerCompressionType::TMX_COMPRESSION_NONE);
}


