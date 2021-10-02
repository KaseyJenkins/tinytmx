#include "gtest/gtest.h"
#include <iostream>
#include "tinytmx.hpp"


class MainTestTrial : public ::testing::Test {
protected:

    void SetUp() override {
        fileName = "assets/FiniteOrthogonalMap.tmx";
        tmxmap = new tinytmx::Map();
        tmxmap->ParseFile(fileName);
    }

    void TearDown() override {
        delete tmxmap;
    }

    std::string fileName;
    tinytmx::Map *tmxmap;

};

TEST_F(MainTestTrial, Map) {
    EXPECT_EQ(tmxmap->GetVersion(), 1.5);                                            // version
    EXPECT_EQ(tmxmap->GetTiledVersion(), "2021.03.23");                              // tiledversion
    EXPECT_EQ(tmxmap->GetOrientation(), tinytmx::MapOrientation::TMX_MO_ORTHOGONAL); // orientation
    EXPECT_EQ(tmxmap->GetRenderOrder(), tinytmx::MapRenderOrder::TMX_RIGHT_DOWN);    // orientation
    EXPECT_EQ(tmxmap->GetCompressionLevel(), -1);                                    // compressionlevel
    EXPECT_EQ(tmxmap->GetWidth(), 20);                                               // width
    EXPECT_EQ(tmxmap->GetHeight(), 15);                                              // height
    EXPECT_EQ(tmxmap->GetTileWidth(), 32);                                           // tilewidth
    EXPECT_EQ(tmxmap->GetTileHeight(), 32);                                          // tileheight
    EXPECT_EQ(tmxmap->GetBackgroundColor().ToString(), "#00000000");                 // backgroundcolor
    EXPECT_EQ(tmxmap->GetNextLayerID(), 2);                                          // nextlayerid
    EXPECT_EQ(tmxmap->GetNextObjectID(), 1);                                         // nextobjectid
    EXPECT_EQ(tmxmap->IsInfinite(), false);                                          // infinite
}

TEST_F(MainTestTrial, Layer) {
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



//
//TEST_F(MainTestTrial, Map) {
//
//    EXPECT_EQ(tmxmap->GetVersion(), 1.5); // <map> version
//    EXPECT_EQ(tmxmap->GetOrientation(), tinytmx::MapOrientation::TMX_MO_ORTHOGONAL); // <map> orientation
//    EXPECT_EQ(tmxmap->GetRenderOrder(), tinytmx::MapRenderOrder::TMX_RIGHT_DOWN); // <map> renderorder
//    EXPECT_EQ(tmxmap->GetCompressionLevel(), -1); // <map> compressionlevel
//    EXPECT_EQ(tmxmap->GetWidth(), 20); // <map> width
//    EXPECT_EQ(tmxmap->GetHeight(), 15); // <map> height
//    EXPECT_EQ(tmxmap->GetTileWidth(), 32); // <map> tilewidth
//    EXPECT_EQ(tmxmap->GetTileHeight(), 32); // <map> tileheight
//    EXPECT_EQ(tmxmap->GetBackgroundColor().ToString(), "#00000000"); // backgroundcolor
//    EXPECT_EQ(tmxmap->GetNextLayerID(), 2); // nextlayerid
//    EXPECT_EQ(tmxmap->GetNextObjectID(), 1); // nextobjectid
//    EXPECT_EQ(tmxmap->IsInfinite(), false); // infinite
//    // hexsidelength
//    // staggeraxis
//}
//
//TEST_F(MainTestTrial, TileLayer) {
//
//    EXPECT_EQ(tmxmap->GetTileLayers()[0]->GetID(), 1); // <layer> id
//    EXPECT_EQ(tmxmap->GetTileLayers()[0]->GetName(), "Tile Layer 1"); // <layer> name
//    EXPECT_EQ(tmxmap->GetTileLayers()[0]->GetWidth(), 20); // <layer> width
//    EXPECT_EQ(tmxmap->GetTileLayers()[0]->GetHeight(), 15); // <layer> height
//    EXPECT_EQ(tmxmap->GetTileLayers()[0]->GetOpacity(), 1.0f); // <layer> opacity
//    EXPECT_EQ(tmxmap->GetTileLayers()[0]->IsVisible(), true); // <layer> visible
//    //EXPECT_EQ(tmxmap->GetTileLayers()[0]->GetTintColor().ToString(), "#ff000000" ); // tintcolor
//    //EXPECT_EQ(tmxmap->GetTileLayers()[0]->GetOffsetX(), 4); // offsetx
//    //EXPECT_EQ(tmxmap->GetTileLayers()[0]->GetOffsetY(), -2); // offsety
//    EXPECT_EQ(tmxmap->GetTileLayers()[0]->GetParallax().x, 1); // parallaxx
//    EXPECT_EQ(tmxmap->GetTileLayers()[0]->GetParallax().y, 1); // parallaxy
//    EXPECT_EQ(tmxmap->GetTileLayers()[0]->GetEncoding(),
//              tinytmx::TileLayerEncodingType::TMX_ENCODING_BASE64); // <data> encoding
//    EXPECT_EQ(tmxmap->GetTileLayers()[0]->GetCompression(),
//              tinytmx::TileLayerCompressionType::TMX_COMPRESSION_ZSTD); // <data> compression
//}
//
//TEST_F(MainTestTrial, TileSet) {
//    EXPECT_EQ(tmxmap->GetTilesets()[0]->GetFirstGid(), 1); // <tileset> firstgid
//    EXPECT_EQ(tmxmap->GetTilesets()[0]->GetName(), "blocks1"); // <tileset> name
//    EXPECT_EQ(tmxmap->GetTilesets()[0]->GetTileWidth(), 32); // <tileset> tilewidth
//    EXPECT_EQ(tmxmap->GetTilesets()[0]->GetTileHeight(), 32); // <tileset> tileheight
//    EXPECT_EQ(tmxmap->GetTilesets()[0]->GetSpacing(), 2); // <tileset> spacing
//    EXPECT_EQ(tmxmap->GetTilesets()[0]->GetMargin(), 2); // <tileset> margin
//    EXPECT_EQ(tmxmap->GetTilesets()[0]->GetTileCount(), 198); // <tileset> tilecount
//    EXPECT_EQ(tmxmap->GetTilesets()[0]->GetColumns(), 18); // <tileset> columnts
//    EXPECT_EQ(tmxmap->GetTilesets()[0]->GetObjectAlignment(), tinytmx::ObjectAlignment::TMX_OA_CENTER); // objectalignment
//}
//
//TEST_F(MainTestTrial, TileSetGrid) {
//    EXPECT_EQ(tmxmap->GetTilesets()[0]->GetGrid()->GetOrientation(), tinytmx::GridOrientation::TMX_GO_ISOMETRIC); // orientation
//    EXPECT_EQ(tmxmap->GetTilesets()[0]->GetGrid()->GetWidth(), 32); // width
//    EXPECT_EQ(tmxmap->GetTilesets()[0]->GetGrid()->GetHeight(), 32); // height
//
//}
//
//TEST_F(MainTestTrial, TileSetTransformations) {
//    if (auto transformations = tmxmap->GetTilesets()[0]->GetTransformations()) {
//        EXPECT_EQ(transformations->GetHflip(), false); // hflip
//        EXPECT_EQ(transformations->GetVflip(), false); // vflip
//        EXPECT_EQ(transformations->GetRotate(), false); // rotate
//        EXPECT_EQ(transformations->GetPreferUntransformed(), true); // preferuntransformed
//
//    } else {
//        puts("No Transformations Element");
//    }
//}
//
//TEST_F(MainTestTrial, TileSetWangSet) {
//    EXPECT_EQ(tmxmap->GetTilesets()[1]->GetName(), "grass");
//    EXPECT_EQ(tmxmap->GetTilesets()[1]->GetWangSets()[0]->GetName(), "Corner Set");
//    EXPECT_EQ(tmxmap->GetTilesets()[1]->GetWangSets()[0]->GetTileID(), -1);
//
//    EXPECT_EQ(tmxmap->GetTilesets()[1]->GetWangSets()[0]->GetProperties().GetBoolProperty("boolProperty"), false);
//    EXPECT_EQ(tmxmap->GetTilesets()[1]->GetWangSets()[0]->GetWangTiles()[0]->GetWangID()[0], 0);
//
//    EXPECT_EQ(tmxmap->GetTilesets()[1]->GetWangSets()[0]->GetWangTiles().size(), 8); // size of wangtiles
//
//    EXPECT_EQ(tmxmap->GetTilesets()[1]->GetWangSets()[0]->GetWangColor()[1]->GetName(), "Boulder");
//    EXPECT_EQ(tmxmap->GetTilesets()[1]->GetWangSets()[0]->GetWangColor()[1]->GetTileID(), -1);
//    EXPECT_EQ(tmxmap->GetTilesets()[1]->GetWangSets()[0]->GetWangColor()[1]->GetProbability(), 1.42f);
//    EXPECT_EQ(tmxmap->GetTilesets()[1]->GetWangSets()[0]->GetWangColor()[1]->GetColor()->ToString(), "#ffaaaaff");
//    EXPECT_EQ(tmxmap->GetTilesets()[1]->GetWangSets()[0]->GetWangColor()[1]->GetProperties().GetBoolProperty("BoulderColorProperty"), true);
//
//}
//
//TEST_F(MainTestTrial, ObjectGroupObjectTypes) {
//   // EXPECT_EQ(tmxmap->GetObjectGroups()[0]->GetObjects()[0]->GetObjectType(), tinytmx::ObjectType::TMX_OT_TEMPLATE);
//}
//
//TEST_F(MainTestTrial, PointObjectDelete) {
//    //std::cout << tmxmap->GetObjectGroups()[0]->GetObjects()[0]->GetPolyline() << std::endl;
//    //EXPECT_EQ(tmxmap->GetObjectGroups()[0]->GetObjects()[0]->GetPolyline()->GetPoint(0).x, 0);
//    //EXPECT_EQ(tmxmap->GetObjectGroups()[0]->GetObjects()[0]->GetPolyline()->GetPoint(4).y, 246);
//
////    std::cout << tmxmap->GetObjectGroups()[0]->GetObjects()[0]->GetPolyline()->GetPoint(2).y << std::endl;
//    //EXPECT_EQ(tmxmap->GetObjectGroups()[0]->GetObjects()[0]->GetPolyline()->GetPoint(2).y, 756);
//
//    //std::cout << tmxmap->GetTilesets()[0]->GetName() << std::endl;
//    std::cout << tmxmap->GetObjectGroups()[0]->GetObjects()[0]->IsTemplate() << std::endl;
//    std::cout << static_cast<int>(tmxmap->GetObjectGroups()[0]->GetObjects()[0]->GetObjectType()) << std::endl;
//    std::cout << tmxmap->GetObjectGroups()[0]->GetObjects()[0]->GetPolygon()->GetPoint(2).x << std::endl;
//}