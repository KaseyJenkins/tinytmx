#include "gtest/gtest.h"
#include <iostream>
#include "tinytmx.hpp"


class MainTestTrialTilesetWangsets : public ::testing::Test {
protected:

    void SetUp() override {
        fileName = "assets/TilesetWangsetsFiniteOrthogonalMap.tmx";
        tmxmap = new tinytmx::Map();
        tmxmap->ParseFile(fileName);
    }

    void TearDown() override {
        delete tmxmap;
    }

    std::string fileName;
    tinytmx::Map *tmxmap;

};

TEST_F(MainTestTrialTilesetWangsets, Map) {
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
    EXPECT_EQ(tmxmap->GetNextLayerId(), 2);                                          // nextlayerid
    EXPECT_EQ(tmxmap->GetNextObjectId(), 1);                                         // nextobjectid
    EXPECT_EQ(tmxmap->IsInfinite(), false);                                          // infinite
}

TEST_F(MainTestTrialTilesetWangsets, MapCustomProperties) {
    auto CustomMapProperties = tmxmap->GetProperties();
    EXPECT_EQ(tmxmap->GetProperties().GetBoolProperty("BoolProp"), true);                     // Bool Custom Property
    EXPECT_EQ(tmxmap->GetProperties().GetColorProperty("ColorProp").ToString(), "#ed00008b"); // Color Custom Property
    EXPECT_EQ(tmxmap->GetProperties().GetFloatProperty("FloatProp"), 2.3f);                   // Float Custom Property
    EXPECT_EQ(tmxmap->GetProperties().GetIntProperty("IntProp"), 658);                        // Int Custom Property
    EXPECT_EQ(tmxmap->GetProperties().GetStringProperty("StringProp"), "Some String\n");
}

TEST_F(MainTestTrialTilesetWangsets, Layer) {
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

TEST_F(MainTestTrialTilesetWangsets, EmbeddedTileset) {
    EXPECT_EQ(tmxmap->GetNumTilesets(), 1); //
    auto EmbedTileset = tmxmap->GetTileset(0);
    EXPECT_EQ(EmbedTileset->GetFirstGid(), 1);                              // firstgid
    EXPECT_EQ(EmbedTileset->GetName(), "blocks1Embedded");                  // name
    EXPECT_EQ(EmbedTileset->GetTileWidth(), 32);                            // tilewidth
    EXPECT_EQ(EmbedTileset->GetTileHeight(), 32);                           // tileheight
    EXPECT_EQ(EmbedTileset->GetSpacing(), 2);                               // spacing
    EXPECT_EQ(EmbedTileset->GetMargin(), 2);                                // margin
    EXPECT_EQ(EmbedTileset->GetTileCount(), 198);                           // tilecount
    EXPECT_EQ(EmbedTileset->GetColumns(), 18);                              // columns
    EXPECT_EQ(EmbedTileset->GetObjectAlignment(), tinytmx::ObjectAlignment::TMX_OA_CENTER); // objectalignment
}

TEST_F(MainTestTrialTilesetWangsets, EmbeddedTilesetImage) {
    auto EmbedTilesetImage = tmxmap->GetTileset(0)->GetImage();
    EXPECT_EQ(EmbedTilesetImage->GetSource(), "images/blocks1.png");         // source
    EXPECT_EQ(EmbedTilesetImage->GetWidth(), 614);                           // width
    EXPECT_EQ(EmbedTilesetImage->GetHeight(), 376);                          // height
}

TEST_F(MainTestTrialTilesetWangsets, EmbeddedTilesetOffset) {
    auto EmbedTilesetOffset = tmxmap->GetTileset(0)->GetTileOffset();
    EXPECT_EQ(EmbedTilesetOffset->GetX(), 1);                                // x
    EXPECT_EQ(EmbedTilesetOffset->GetY(), 2);                                // y
}

TEST_F(MainTestTrialTilesetWangsets, EmbeddedTilesetGrid) {
    auto EmbedTilesetGrid = tmxmap->GetTileset(0)->GetGrid();
    if (EmbedTilesetGrid->GetOrientation() == tinytmx::GridOrientation::TMX_GO_ISOMETRIC) {
        EXPECT_EQ(EmbedTilesetGrid->GetWidth(), 32);                         // width
        EXPECT_EQ(EmbedTilesetGrid->GetHeight(), 32);                        // height
    } else if (EmbedTilesetGrid->GetOrientation() == tinytmx::GridOrientation::TMX_GO_ORTHOGONAL) {
        puts("Orthogonal Orientation: Grid is only used in case of isometric orientation!");
    }
}

TEST_F(MainTestTrialTilesetWangsets, EmbeddedTilesetProperties) {
    auto EmbedTilesetProp = tmxmap->GetTileset(0)->GetProperties();
    EXPECT_EQ(EmbedTilesetProp.GetIntProperty("IntProp"), 42);
    EXPECT_EQ(EmbedTilesetProp.GetBoolProperty("BoolProp"), true);
}

TEST_F(MainTestTrialTilesetWangsets, EmbeddedTilesetTransformations) {
    auto EmbedTilesetTrans = tmxmap->GetTileset(0)->GetTransformations();
    EXPECT_EQ(EmbedTilesetTrans->GetPreferUntransformed(), false);      // preferuntransformed
    EXPECT_EQ(EmbedTilesetTrans->GetHflip(), true);                     // hflip
    EXPECT_EQ(EmbedTilesetTrans->GetVflip(), true);                     // vflip
    EXPECT_EQ(EmbedTilesetTrans->GetRotate(), true);                    // rotate
}

TEST_F(MainTestTrialTilesetWangsets, EmbeddedTilesetWangsets) {
    auto EmbedTilesetWangset = tmxmap->GetTileset(0)->GetWangSet(0);
    EXPECT_EQ(EmbedTilesetWangset->GetName(), "CornerSet");             // name
    EXPECT_EQ(EmbedTilesetWangset->GetTileId(), -1);                    // tile
    EXPECT_EQ(EmbedTilesetWangset->GetWangSetType(), tinytmx::WangSetType::TMX_WST_CORNER); // type

    EXPECT_EQ(    EmbedTilesetWangset->GetProperties().GetIntProperty("IntProp"), 78);
}

TEST_F(MainTestTrialTilesetWangsets, EmbeddedTilesetWangsetsColor) {
    auto EmbedTilesetWangset = tmxmap->GetTileset(0)->GetWangSet(0);
    EXPECT_EQ(EmbedTilesetWangset->GetWangColor()[0]->GetName(), "ColorNameHere");          // name
    EXPECT_EQ(EmbedTilesetWangset->GetWangColor()[0]->GetColor()->ToString(), "#ffff0000"); // color
    EXPECT_EQ(EmbedTilesetWangset->GetWangColor()[0]->GetProbability(), 0.53f);              // probability

    EXPECT_EQ(    EmbedTilesetWangset->GetWangColor()[0]->GetProperties().GetFloatProperty("FloatProp"), 3.23f);
}

TEST_F(MainTestTrialTilesetWangsets, EmbeddedTilesetWangsetsTile) {
    auto EmbedTilesetWangset2 = tmxmap->GetTileset(1)->GetWangSet(0);
    EXPECT_EQ(EmbedTilesetWangset2->GetWangTiles()[0]->GetTileId(), 18);   // tileid
    EXPECT_EQ(EmbedTilesetWangset2->GetWangTiles()[0]->GetWangID()[1], 1); // wangid
}

