#include "gtest/gtest.h"

#include <filesystem>
#include <string>
#include <string_view>

#include "tinytmx.hpp"

namespace {

std::string FixturePath(std::string_view name) {
  return (std::filesystem::path(__FILE__).parent_path() / "fixtures" / "tmx" / name).string();
}

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

TEST(TileLayerParse, CsvFiniteLayerMixedEmptyAndNonEmptyTilesRemainStable) {
    const char *tmx = R"tmx(<?xml version="1.0" encoding="UTF-8"?>
<map version="1.5" tiledversion="1.10.2" orientation="orthogonal" renderorder="right-down" width="4" height="2" tilewidth="16" tileheight="16" infinite="0">
  <tileset firstgid="1" name="ts0" tilewidth="16" tileheight="16" tilecount="4" columns="2">
    <image source="tiles0.png" width="32" height="32"/>
  </tileset>
  <tileset firstgid="100" name="ts1" tilewidth="16" tileheight="16" tilecount="4" columns="2">
    <image source="tiles1.png" width="32" height="32"/>
  </tileset>
  <layer id="1" name="L0" width="4" height="2">
    <data encoding="csv">0,1,100,0,99,0,1000,0</data>
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
    EXPECT_EQ(data->GetWidth(), 4u);
    EXPECT_EQ(data->GetHeight(), 2u);

    // Empty tiles stay empty and unresolved.
    EXPECT_EQ(data->GetTileGid(0, 0), 0u);
    EXPECT_EQ(data->GetTileTilesetIndex(0, 0), -1);
    EXPECT_FALSE(data->IsTileFlippedHorizontally(0, 0));
    EXPECT_FALSE(data->IsTileFlippedVertically(0, 0));
    EXPECT_FALSE(data->IsTileFlippedDiagonally(0, 0));

    EXPECT_EQ(data->GetTileGid(3, 0), 0u);
    EXPECT_EQ(data->GetTileTilesetIndex(3, 0), -1);

    EXPECT_EQ(data->GetTileGid(1, 1), 0u);
    EXPECT_EQ(data->GetTileTilesetIndex(1, 1), -1);

    EXPECT_EQ(data->GetTileGid(3, 1), 0u);
    EXPECT_EQ(data->GetTileTilesetIndex(3, 1), -1);

    // Non-empty tiles still resolve the same tilesets and gids.
    EXPECT_EQ(data->GetTileGid(1, 0), 1u);
    EXPECT_EQ(data->GetTileTilesetIndex(1, 0), 0);

    EXPECT_EQ(data->GetTileGid(2, 0), 100u);
    EXPECT_EQ(data->GetTileTilesetIndex(2, 0), 1);

    EXPECT_EQ(data->GetTileGid(0, 1), 99u);
    EXPECT_EQ(data->GetTileTilesetIndex(0, 1), 0);

    EXPECT_EQ(data->GetTileGid(2, 1), 1000u);
    EXPECT_EQ(data->GetTileTilesetIndex(2, 1), 1);
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

TEST(WangSetParse, WangIdParsesCommaSeparatedValues) {
    const char *tmx = R"tmx(<?xml version="1.0" encoding="UTF-8"?>
<map version="1.5" tiledversion="1.10.2" orientation="orthogonal" renderorder="right-down" width="1" height="1" tilewidth="16" tileheight="16" infinite="0">
  <tileset firstgid="1" name="test" tilewidth="16" tileheight="16" tilecount="1" columns="1">
    <image source="tiles.png" width="16" height="16"/>
    <wangsets>
      <wangset name="ws" tile="0">
        <wangcolor name="c1" color="#ff0000" tile="0" probability="1"/>
        <wangtile tileid="0" wangid="1, 2,3,4, 5,6,7,8"/>
      </wangset>
    </wangsets>
  </tileset>
  <layer id="1" name="tile" width="1" height="1">
    <data encoding="csv">0</data>
  </layer>
</map>)tmx";

    tinytmx::Map map;
    map.ParseText(tmx);

    ASSERT_FALSE(map.HasError());
    ASSERT_EQ(map.GetNumTilesets(), 1u);

    auto const *tileset = map.GetTileset(0);
    ASSERT_NE(tileset, nullptr);
    ASSERT_EQ(tileset->GetWangSets().size(), 1u);

    auto const *wangset = tileset->GetWangSet(0);
    ASSERT_NE(wangset, nullptr);
    ASSERT_EQ(wangset->GetWangTiles().size(), 1u);

    auto const *wangtile = wangset->GetWangTiles().at(0);
    ASSERT_NE(wangtile, nullptr);

    std::vector<uint32_t> const &wangid = wangtile->GetWangID();
    ASSERT_EQ(wangid.size(), 8u);
    EXPECT_EQ(wangid[0], 1u);
    EXPECT_EQ(wangid[1], 2u);
    EXPECT_EQ(wangid[2], 3u);
    EXPECT_EQ(wangid[3], 4u);
    EXPECT_EQ(wangid[4], 5u);
    EXPECT_EQ(wangid[5], 6u);
    EXPECT_EQ(wangid[6], 7u);
    EXPECT_EQ(wangid[7], 8u);
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

TEST(FixtureParse, BasicFiniteCsvFromFile) {
  tinytmx::Map map;
  map.ParseFile(FixturePath("basic_finite_csv.tmx"));

  ASSERT_FALSE(map.HasError());
  ASSERT_EQ(map.GetNumTileLayers(), 1u);

  auto const *layer = map.GetTileLayer(0);
  ASSERT_NE(layer, nullptr);

  auto const *data = layer->GetDataTileFiniteMap();
  ASSERT_NE(data, nullptr);
  EXPECT_EQ(data->GetWidth(), 3u);
  EXPECT_EQ(data->GetHeight(), 2u);
  EXPECT_EQ(data->GetTileGid(2, 1), 6u);
}

TEST(FixtureParse, BasicFiniteBase64FromFile) {
  tinytmx::Map map;
  map.ParseFile(FixturePath("basic_finite_base64.tmx"));

  ASSERT_FALSE(map.HasError());
  ASSERT_EQ(map.GetNumTileLayers(), 1u);

  auto const *layer = map.GetTileLayer(0);
  ASSERT_NE(layer, nullptr);

  auto const *data = layer->GetDataTileFiniteMap();
  ASSERT_NE(data, nullptr);
  EXPECT_EQ(data->GetWidth(), 3u);
  EXPECT_EQ(data->GetHeight(), 2u);
  EXPECT_EQ(data->GetTileGid(2, 1), 6u);
}

TEST(FixtureParse, AllLayerTypesFromFile) {
  tinytmx::Map map;
  map.ParseFile(FixturePath("all_layer_types.tmx"));

  ASSERT_FALSE(map.HasError());
  EXPECT_EQ(map.GetNumTileLayers(), 1u);
  EXPECT_EQ(map.GetNumObjectGroups(), 1u);
  EXPECT_EQ(map.GetNumImageLayers(), 1u);
  EXPECT_EQ(map.GetNumGroupLayers(), 1u);

  auto const *groupLayer = map.GetGroupLayer(0);
  ASSERT_NE(groupLayer, nullptr);
  EXPECT_EQ(groupLayer->GetNumChildren(), 1u);

  auto const *imageLayer = map.GetImageLayer(0);
  ASSERT_NE(imageLayer, nullptr);
  auto const *image = imageLayer->GetImage();
  ASSERT_NE(image, nullptr);
  EXPECT_EQ(image->GetSource(), "bg.png");
}

TEST(FixtureParse, ObjectShapesFromFile) {
  tinytmx::Map map;
  map.ParseFile(FixturePath("objects_shapes.tmx"));

  ASSERT_FALSE(map.HasError());
  ASSERT_EQ(map.GetNumObjectGroups(), 1u);

  auto const *group = map.GetObjectGroup(0);
  ASSERT_NE(group, nullptr);
  ASSERT_EQ(group->GetNumObjects(), 6u);

  auto const *ellipse = group->GetObject(0);
  ASSERT_NE(ellipse, nullptr);
  EXPECT_EQ(ellipse->GetObjectType(), tinytmx::ObjectType::TMX_OT_ELLIPSE);
  EXPECT_NE(ellipse->GetEllipse(), nullptr);

  auto const *point = group->GetObject(1);
  ASSERT_NE(point, nullptr);
  EXPECT_EQ(point->GetObjectType(), tinytmx::ObjectType::TMX_OT_POINT);
  EXPECT_NE(point->GetPoint(), nullptr);

  auto const *polygon = group->GetObject(2);
  ASSERT_NE(polygon, nullptr);
  EXPECT_EQ(polygon->GetObjectType(), tinytmx::ObjectType::TMX_OT_POLYGON);
  ASSERT_NE(polygon->GetPolygon(), nullptr);
  EXPECT_EQ(polygon->GetPolygon()->GetNumPoints(), 3u);

  auto const *polyline = group->GetObject(3);
  ASSERT_NE(polyline, nullptr);
  EXPECT_EQ(polyline->GetObjectType(), tinytmx::ObjectType::TMX_OT_POLYLINE);
  ASSERT_NE(polyline->GetPolyline(), nullptr);
  EXPECT_EQ(polyline->GetPolyline()->GetNumPoints(), 3u);

  auto const *text = group->GetObject(4);
  ASSERT_NE(text, nullptr);
  EXPECT_EQ(text->GetObjectType(), tinytmx::ObjectType::TMX_OT_TEXT);
  ASSERT_NE(text->GetText(), nullptr);
  EXPECT_EQ(text->GetText()->GetContents(), "hello");

  auto const *rectangle = group->GetObject(5);
  ASSERT_NE(rectangle, nullptr);
  EXPECT_EQ(rectangle->GetObjectType(), tinytmx::ObjectType::TMX_OT_RECTANGLE);
}

TEST(FixtureParse, MapPropertiesFromFile) {
  tinytmx::Map map;
  map.ParseFile(FixturePath("properties_types.tmx"));

  ASSERT_FALSE(map.HasError());
  auto const *properties = map.GetProperties();
  ASSERT_NE(properties, nullptr);

  EXPECT_EQ(properties->GetStringProperty("title"), "hello");
  EXPECT_EQ(properties->GetIntProperty("lives"), 3);
  EXPECT_FLOAT_EQ(properties->GetFloatProperty("speed"), 2.5f);
  EXPECT_TRUE(properties->GetBoolProperty("enabled"));
  EXPECT_EQ(properties->GetColorProperty("tint"), tinytmx::Color("#112233"));
  EXPECT_EQ(properties->GetFileProperty("asset"), "assets/hero.png");
  EXPECT_EQ(properties->GetObjectProperty("target"), 7);
}

TEST(FixtureParse, MultipleTilesetsFromFile) {
  tinytmx::Map map;
  map.ParseFile(FixturePath("multi_tilesets.tmx"));

  ASSERT_FALSE(map.HasError());
  ASSERT_EQ(map.GetNumTilesets(), 3u);

  EXPECT_EQ(map.FindTilesetIndex(0u), -1);
  EXPECT_EQ(map.FindTilesetIndex(1u), 0);
  EXPECT_EQ(map.FindTilesetIndex(100u), 1);
  EXPECT_EQ(map.FindTilesetIndex(1000u), 2);
}

TEST(FixtureParse, InfiniteChunksCsvFromFile) {
    tinytmx::Map map;
    map.ParseFile(FixturePath("infinite_chunks_csv.tmx"));

    ASSERT_FALSE(map.HasError());
    ASSERT_TRUE(map.IsInfinite());
    ASSERT_EQ(map.GetNumTileLayers(), 1u);

    auto const *layer = map.GetTileLayer(0);
    ASSERT_NE(layer, nullptr);
    ASSERT_EQ(layer->GetChunks().size(), 1u);

    auto const *chunk = layer->GetChunk(0);
    ASSERT_NE(chunk, nullptr);
    EXPECT_EQ(chunk->GetX(), -2);
    EXPECT_EQ(chunk->GetY(), 3);
    EXPECT_EQ(chunk->GetWidth(), 2u);
    EXPECT_EQ(chunk->GetHeight(), 2u);
    EXPECT_EQ(chunk->GetTileGid(0, 0), 1u);
    EXPECT_EQ(chunk->GetTileGid(1, 0), 2u);
    EXPECT_EQ(chunk->GetTileGid(0, 1), 3u);
    EXPECT_EQ(chunk->GetTileGid(1, 1), 4u);
}

TEST(FixtureParse, InfiniteChunksBase64FromFile) {
    tinytmx::Map map;
    map.ParseFile(FixturePath("infinite_chunks_base64.tmx"));

    ASSERT_FALSE(map.HasError());
    ASSERT_TRUE(map.IsInfinite());
    ASSERT_EQ(map.GetNumTileLayers(), 1u);

    auto const *layer = map.GetTileLayer(0);
    ASSERT_NE(layer, nullptr);
    ASSERT_EQ(layer->GetChunks().size(), 1u);

    auto const *chunk = layer->GetChunk(0);
    ASSERT_NE(chunk, nullptr);
    EXPECT_EQ(chunk->GetX(), 10);
    EXPECT_EQ(chunk->GetY(), -4);
    EXPECT_EQ(chunk->GetWidth(), 2u);
    EXPECT_EQ(chunk->GetHeight(), 2u);
    EXPECT_EQ(chunk->GetTileGid(0, 0), 1u);
    EXPECT_EQ(chunk->GetTileGid(1, 0), 2u);
    EXPECT_EQ(chunk->GetTileGid(0, 1), 3u);
    EXPECT_EQ(chunk->GetTileGid(1, 1), 4u);
}

TEST(FixtureParse, TilesetExtrasFromFile) {
    tinytmx::Map map;
    map.ParseFile(FixturePath("tileset_extras.tmx"));

    ASSERT_FALSE(map.HasError());
    ASSERT_EQ(map.GetNumTilesets(), 1u);

    auto const *tileset = map.GetTileset(0);
    ASSERT_NE(tileset, nullptr);

    auto const *tileOffset = tileset->GetTileOffset();
    ASSERT_NE(tileOffset, nullptr);
    EXPECT_EQ(tileOffset->GetX(), 3);
    EXPECT_EQ(tileOffset->GetY(), -2);

    auto const *grid = tileset->GetGrid();
    ASSERT_NE(grid, nullptr);
    EXPECT_EQ(grid->GetOrientation(), tinytmx::GridOrientation::TMX_GO_ISOMETRIC);
    EXPECT_EQ(grid->GetWidth(), 32u);
    EXPECT_EQ(grid->GetHeight(), 24u);

    auto const *transformations = tileset->GetTransformations();
    ASSERT_NE(transformations, nullptr);
    EXPECT_TRUE(transformations->GetHflip());
    EXPECT_FALSE(transformations->GetVflip());
    EXPECT_TRUE(transformations->GetRotate());
    EXPECT_TRUE(transformations->GetPreferUntransformed());

    ASSERT_EQ(tileset->GetWangSets().size(), 1u);
    auto const *wangset = tileset->GetWangSet(0);
    ASSERT_NE(wangset, nullptr);
    ASSERT_EQ(wangset->GetWangTiles().size(), 1u);

    auto const *wangtile = wangset->GetWangTiles().at(0);
    ASSERT_NE(wangtile, nullptr);
    EXPECT_EQ(wangtile->GetTileId(), 0u);
    ASSERT_EQ(wangtile->GetWangID().size(), 8u);
    EXPECT_EQ(wangtile->GetWangID()[0], 1u);
    EXPECT_EQ(wangtile->GetWangID()[1], 0u);
}

TEST(FixtureParse, ExternalTsxTilesetFromFile) {
    tinytmx::Map map;
    map.ParseFile(FixturePath("external_tileset_map.tmx"));

    ASSERT_FALSE(map.HasError());
    ASSERT_EQ(map.GetNumTilesets(), 1u);

    auto const *tileset = map.GetTileset(0);
    ASSERT_NE(tileset, nullptr);
    EXPECT_EQ(tileset->GetName(), "external");

    auto const *image = tileset->GetImage();
    ASSERT_NE(image, nullptr);
    EXPECT_EQ(image->GetSource(), "external_tiles.png");
}

TEST(MapParse, MissingOptionalAttributesUseDefaults) {
    const char *tmx = R"tmx(<?xml version="1.0" encoding="UTF-8"?>
<map version="1.5" orientation="orthogonal" width="1" height="1" tilewidth="16" tileheight="16">
  <tileset firstgid="1" name="basic" tilewidth="16" tileheight="16" tilecount="1" columns="1">
    <image source="tiles.png" width="16" height="16"/>
  </tileset>
  <layer width="1" height="1">
    <data encoding="csv">0</data>
  </layer>
</map>)tmx";

    tinytmx::Map map;
    map.ParseText(tmx);

    ASSERT_FALSE(map.HasError());
    EXPECT_EQ(map.GetRenderOrder(), tinytmx::MapRenderOrder::TMX_RIGHT_DOWN);
    EXPECT_FALSE(map.IsInfinite());
    EXPECT_EQ(map.GetCompressionLevel(), -1);
    EXPECT_EQ(map.GetNextLayerID(), 0);
    EXPECT_EQ(map.GetNextObjectID(), 0);
}

TEST(PropertyParse, MultilinePropertyValueInElementText) {
    const char *tmx = R"tmx(<?xml version="1.0" encoding="UTF-8"?>
<map version="1.5" orientation="orthogonal" width="1" height="1" tilewidth="16" tileheight="16">
  <properties>
    <property name="note" type="string">line1
line2</property>
  </properties>
  <tileset firstgid="1" name="basic" tilewidth="16" tileheight="16" tilecount="1" columns="1">
    <image source="tiles.png" width="16" height="16"/>
  </tileset>
  <layer width="1" height="1"><data encoding="csv">0</data></layer>
</map>)tmx";

    tinytmx::Map map;
    map.ParseText(tmx);

    ASSERT_FALSE(map.HasError());
    auto const *properties = map.GetProperties();
    ASSERT_NE(properties, nullptr);
    EXPECT_EQ(properties->GetStringProperty("note"), "line1\nline2");
}

TEST(MapParse, AttributeOrderingVarianceAccepted) {
    const char *tmx = R"tmx(<?xml version="1.0" encoding="UTF-8"?>
<map tileheight="16" width="1" orientation="orthogonal" version="1.5" tilewidth="16" height="1" renderorder="left-up">
  <tileset columns="1" tilecount="1" tileheight="16" name="basic" firstgid="1" tilewidth="16">
    <image height="16" width="16" source="tiles.png"/>
  </tileset>
  <layer height="1" id="1" width="1" name="L0">
    <data encoding="csv">0</data>
  </layer>
</map>)tmx";

    tinytmx::Map map;
    map.ParseText(tmx);

    ASSERT_FALSE(map.HasError());
    EXPECT_EQ(map.GetRenderOrder(), tinytmx::MapRenderOrder::TMX_LEFT_UP);
    ASSERT_EQ(map.GetNumTilesets(), 1u);
    EXPECT_EQ(map.GetTileset(0)->GetName(), "basic");
}

TEST(MapParse, EmptyPropertiesElementParsesAsEmptySet) {
    const char *tmx = R"tmx(<?xml version="1.0" encoding="UTF-8"?>
<map version="1.5" orientation="orthogonal" width="1" height="1" tilewidth="16" tileheight="16">
  <properties/>
  <tileset firstgid="1" name="basic" tilewidth="16" tileheight="16" tilecount="1" columns="1">
    <image source="tiles.png" width="16" height="16"/>
  </tileset>
  <layer width="1" height="1"><data encoding="csv">0</data></layer>
</map>)tmx";

    tinytmx::Map map;
    map.ParseText(tmx);

    ASSERT_FALSE(map.HasError());
    auto const *properties = map.GetProperties();
    ASSERT_NE(properties, nullptr);
    EXPECT_TRUE(properties->Empty());
}

TEST(MapParse, UnknownElementsAndAttributesAreIgnored) {
    const char *tmx = R"tmx(<?xml version="1.0" encoding="UTF-8"?>
<map version="1.5" orientation="orthogonal" width="1" height="1" tilewidth="16" tileheight="16" unknownattr="ignored">
  <tileset firstgid="1" name="basic" tilewidth="16" tileheight="16" tilecount="1" columns="1" weird="x">
    <image source="tiles.png" width="16" height="16" custom="y"/>
  </tileset>
  <unknownnode foo="bar"><nested/></unknownnode>
  <layer id="1" name="L0" width="1" height="1" odd="z">
    <data encoding="csv">0</data>
  </layer>
</map>)tmx";

    tinytmx::Map map;
    map.ParseText(tmx);

    ASSERT_FALSE(map.HasError());
    ASSERT_EQ(map.GetNumTileLayers(), 1u);
    EXPECT_EQ(map.GetTileLayer(0)->GetName(), "L0");
}

} // namespace