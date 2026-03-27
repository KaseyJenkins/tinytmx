#include "gtest/gtest.h"

#include <string>

#include "tinytmx.hpp"

namespace {

TEST(TileLayerParse, Base64FiniteLayerUsesCorrectRowMajorIndexing) {
    // 6 little-endian uint32 gids: 1,2,3,4,5,6
    const char *tmx = R"tmx(<?xml version="1.0" encoding="UTF-8"?>
<map version="1.5" tiledversion="1.10.2" orientation="orthogonal" renderorder="right-down" width="3" height="2" tilewidth="16" tileheight="16" infinite="0">
  <tileset firstgid="1" name="test" tilewidth="16" tileheight="16" tilecount="1" columns="1">
    <image source="tiles.png" width="16" height="16"/>
  </tileset>
  <layer id="1" name="L0" width="3" height="2">
    <data encoding="base64">AQAAAAIAAAADAAAABAAAAAUAAAAGAAAA</data>
  </layer>
</map>)tmx";

    tinytmx::Map map;
    map.ParseText(tmx);

    ASSERT_FALSE(map.HasError());
    ASSERT_EQ(map.GetNumTileLayers(), 1u);

    tinytmx::TileLayer const *layer = map.GetTileLayer(0);
    ASSERT_NE(layer, nullptr);

    tinytmx::DataChunkTile const *data = layer->GetDataTileFiniteMap();
    ASSERT_NE(data, nullptr);
    EXPECT_EQ(data->GetWidth(), 3u);
    EXPECT_EQ(data->GetHeight(), 2u);

    // Ensure row-major order is preserved for non-square maps.
    EXPECT_EQ(data->GetTileGid(0, 0), 1u);
    EXPECT_EQ(data->GetTileGid(1, 0), 2u);
    EXPECT_EQ(data->GetTileGid(2, 0), 3u);
    EXPECT_EQ(data->GetTileGid(0, 1), 4u);
    EXPECT_EQ(data->GetTileGid(1, 1), 5u);
    EXPECT_EQ(data->GetTileGid(2, 1), 6u);
}

TEST(LayerParse, ParallaxIsParsedForObjectImageAndGroupLayers) {
    const char *tmx = R"tmx(<?xml version="1.0" encoding="UTF-8"?>
<map version="1.5" tiledversion="1.10.2" orientation="orthogonal" renderorder="right-down" width="1" height="1" tilewidth="16" tileheight="16" infinite="0">
  <tileset firstgid="1" name="test" tilewidth="16" tileheight="16" tilecount="1" columns="1">
    <image source="tiles.png" width="16" height="16"/>
  </tileset>
  <layer id="1" name="tile" width="1" height="1" parallaxx="1.25" parallaxy="1.5">
    <data encoding="csv">0</data>
  </layer>
  <objectgroup id="2" name="objects" parallaxx="2.0" parallaxy="2.5"/>
  <imagelayer id="3" name="image" parallaxx="3.0" parallaxy="3.5"/>
  <group id="4" name="group" parallaxx="4.0" parallaxy="4.5">
    <layer id="5" name="nested" width="1" height="1">
      <data encoding="csv">0</data>
    </layer>
  </group>
</map>)tmx";

    tinytmx::Map map;
    map.ParseText(tmx);

    ASSERT_FALSE(map.HasError());
    ASSERT_EQ(map.GetNumObjectGroups(), 1u);
    ASSERT_EQ(map.GetNumImageLayers(), 1u);
    ASSERT_EQ(map.GetNumGroupLayers(), 1u);

    auto const *objectGroup = map.GetObjectGroup(0);
    auto const *imageLayer = map.GetImageLayer(0);
    auto const *groupLayer = map.GetGroupLayer(0);

    ASSERT_NE(objectGroup, nullptr);
    ASSERT_NE(imageLayer, nullptr);
    ASSERT_NE(groupLayer, nullptr);

    EXPECT_FLOAT_EQ(objectGroup->GetParallaxX(), 2.0f);
    EXPECT_FLOAT_EQ(objectGroup->GetParallaxY(), 2.5f);
    EXPECT_FLOAT_EQ(imageLayer->GetParallaxX(), 3.0f);
    EXPECT_FLOAT_EQ(imageLayer->GetParallaxY(), 3.5f);
    EXPECT_FLOAT_EQ(groupLayer->GetParallaxX(), 4.0f);
    EXPECT_FLOAT_EQ(groupLayer->GetParallaxY(), 4.5f);
}

} // namespace