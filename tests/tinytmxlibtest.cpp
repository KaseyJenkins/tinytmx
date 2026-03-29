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

TEST(TileLayerParse, CsvFiniteLayerHandlesWhitespaceAndNewlines) {
    const char *tmx = R"tmx(<?xml version="1.0" encoding="UTF-8"?>
<map version="1.5" tiledversion="1.10.2" orientation="orthogonal" renderorder="right-down" width="3" height="2" tilewidth="16" tileheight="16" infinite="0">
  <tileset firstgid="1" name="test" tilewidth="16" tileheight="16" tilecount="1" columns="1">
    <image source="tiles.png" width="16" height="16"/>
  </tileset>
  <layer id="1" name="L0" width="3" height="2">
    <data encoding="csv">
      1, 2 ,3,
      4,  5,	6
    </data>
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

TEST(GroupLayerParse, EmptyGroupLayerIsAllowed) {
    const char *tmx = R"tmx(<?xml version="1.0" encoding="UTF-8"?>
<map version="1.5" tiledversion="1.10.2" orientation="orthogonal" renderorder="right-down" width="1" height="1" tilewidth="16" tileheight="16" infinite="0">
  <tileset firstgid="1" name="test" tilewidth="16" tileheight="16" tilecount="1" columns="1">
    <image source="tiles.png" width="16" height="16"/>
  </tileset>
  <group id="1" name="empty"/>
</map>)tmx";

    tinytmx::Map map;
    map.ParseText(tmx);

    ASSERT_FALSE(map.HasError());
    ASSERT_EQ(map.GetNumGroupLayers(), 1u);

    auto const *groupLayer = map.GetGroupLayer(0);
    ASSERT_NE(groupLayer, nullptr);
    EXPECT_EQ(groupLayer->GetNumChildren(), 0u);
}

TEST(MapLookup, TilesetLookupBoundariesAndFlipFlagsRemainStable) {
    const char *tmx = R"tmx(<?xml version="1.0" encoding="UTF-8"?>
<map version="1.5" tiledversion="1.10.2" orientation="orthogonal" renderorder="right-down" width="1" height="1" tilewidth="16" tileheight="16" infinite="0">
  <tileset firstgid="1" name="ts0" tilewidth="16" tileheight="16" tilecount="1" columns="1">
    <image source="tiles0.png" width="16" height="16"/>
  </tileset>
  <tileset firstgid="100" name="ts1" tilewidth="16" tileheight="16" tilecount="1" columns="1">
    <image source="tiles1.png" width="16" height="16"/>
  </tileset>
  <tileset firstgid="1000" name="ts2" tilewidth="16" tileheight="16" tilecount="1" columns="1">
    <image source="tiles2.png" width="16" height="16"/>
  </tileset>
  <layer id="1" name="tile" width="1" height="1">
    <data encoding="csv">0</data>
  </layer>
</map>)tmx";

    tinytmx::Map map;
    map.ParseText(tmx);

    ASSERT_FALSE(map.HasError());
    ASSERT_EQ(map.GetNumTilesets(), 3u);

    EXPECT_EQ(map.FindTilesetIndex(0u), -1);
    EXPECT_EQ(map.FindTilesetIndex(1u), 0);
    EXPECT_EQ(map.FindTilesetIndex(99u), 0);
    EXPECT_EQ(map.FindTilesetIndex(100u), 1);
    EXPECT_EQ(map.FindTilesetIndex(999u), 1);
    EXPECT_EQ(map.FindTilesetIndex(1000u), 2);

    // Lookup must ignore flip flags when resolving a tileset index.
    unsigned const flippedGid = 100u | tinytmx::FLIPPED_HORIZONTALLY_FLAG | tinytmx::FLIPPED_DIAGONALLY_FLAG;
    EXPECT_EQ(map.FindTilesetIndex(flippedGid), 1);

    auto const *tileset0 = map.FindTileset(1u);
    auto const *tileset1 = map.FindTileset(150u);
    auto const *tileset2 = map.FindTileset(1100u);
    auto const *noTileset = map.FindTileset(0u);

    ASSERT_NE(tileset0, nullptr);
    ASSERT_NE(tileset1, nullptr);
    ASSERT_NE(tileset2, nullptr);
    ASSERT_EQ(noTileset, nullptr);

    EXPECT_EQ(tileset0->GetName(), "ts0");
    EXPECT_EQ(tileset1->GetName(), "ts1");
    EXPECT_EQ(tileset2->GetName(), "ts2");
}

} // namespace