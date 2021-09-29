#include "gtest/gtest.h"
#include <iostream>
#include "tinytmx.hpp"


class MainTestTilesetExternalObjectGroup : public ::testing::Test {
protected:

    void SetUp() override {
        fileName = "assets/TilesetExternalFiniteOrthogonalMapObjectGroup.tmx";
        tmxmap = new tinytmx::Map();
        tmxmap->ParseFile(fileName);
    }

    void TearDown() override {
        delete tmxmap;
    }

    std::string fileName;
    tinytmx::Map *tmxmap;

};


TEST_F(MainTestTilesetExternalObjectGroup, ExternalTileset) {
    auto grassExternalTileset = tmxmap->GetTileset(0);
    EXPECT_EQ(grassExternalTileset->GetFirstGid(), 1);                      // firstgid
    EXPECT_EQ(grassExternalTileset->GetName(), "grass");                    // name

    EXPECT_EQ(grassExternalTileset->GetWangSet(0)->GetName(), "New Corner Set");

}

TEST_F(MainTestTilesetExternalObjectGroup, ObjectGroup) {
    auto objectGroup = tmxmap->GetObjectGroup(0);
    EXPECT_EQ(objectGroup->GetID(), 2);                                     // id
    EXPECT_EQ(objectGroup->GetName(), "Object Layer 1");                    // name
    EXPECT_EQ(objectGroup->GetColor().ToString(), "#ff00aa00");             // color
    EXPECT_EQ(objectGroup->GetOpacity(), 0.9f);                             // opacity
    EXPECT_EQ(objectGroup->IsVisible(), true);                              // visible
    EXPECT_EQ(objectGroup->GetTintColor().ToString(), "#ffff7eff");         // tintcolor
    EXPECT_EQ(objectGroup->GetOffsetX(), 1.05f);                            // offsetx
    EXPECT_EQ(objectGroup->GetOffsetY(), -1.04f);                           // offsety
    EXPECT_EQ(objectGroup->GetDrawOrder(), tinytmx::DrawOrder::TMX_DRAWORDER_TOPDOWN); // draworder

    EXPECT_EQ(objectGroup->GetProperties().GetBoolProperty("BoolProp"), true);         //
}

TEST_F(MainTestTilesetExternalObjectGroup, ObjectGroupObjectsRectangle) {
    auto rectangularObject = tmxmap->GetObjectGroup(0)->GetObject(0);

    EXPECT_EQ(rectangularObject->GetObjectType(), tinytmx::ObjectType::TMX_OT_RECTANGLE);

    EXPECT_EQ(rectangularObject->GetId(), 2);                                   // id
    EXPECT_EQ(rectangularObject->GetName(), "RectangularObject");               // name
    EXPECT_EQ(rectangularObject->GetType(), "ArbitraryTypeString");             // type
    EXPECT_EQ(rectangularObject->GetX(), 107.978f);                             // x
    EXPECT_EQ(rectangularObject->GetY(), 28.0483f);                             // y
    EXPECT_EQ(rectangularObject->GetWidth(), 171.9f);                           // width
    EXPECT_EQ(rectangularObject->GetHeight(), 134.05f);                         // height
    EXPECT_EQ(rectangularObject->IsVisible(), true);                            // visible
    EXPECT_EQ(rectangularObject->GetRot(), 4.11278f);                           // rotation

    EXPECT_EQ(rectangularObject->IsTemplate(), false);

}

TEST_F(MainTestTilesetExternalObjectGroup, ObjectGroupObjectsPoint) {
    auto pointObject = tmxmap->GetObjectGroup(0)->GetObject(1);
    if (pointObject->GetObjectType() == tinytmx::ObjectType::TMX_OT_POINT) {
        puts("It's a Point Object");
        EXPECT_EQ(pointObject->GetId(), 3);                                     // id
        EXPECT_EQ(pointObject->GetName(), "PointObject");                       // name
        EXPECT_EQ(pointObject->GetX(), 355.95f);                                // x
        EXPECT_EQ(pointObject->GetY(), 64.04f);                                 // y

        EXPECT_EQ(pointObject->GetPoint()->x, 355.95f);
        EXPECT_EQ(pointObject->GetPoint()->y, 64.04f);

        EXPECT_EQ(pointObject->GetProperties().GetBoolProperty("BoolProp"), true);
        EXPECT_EQ(pointObject->IsTemplate(), false);
    }
}

TEST_F(MainTestTilesetExternalObjectGroup, ObjectGroupObjectsEllipse) {
    auto ellipseObject = tmxmap->GetObjectGroup(0)->GetObject(2);
    if (ellipseObject->GetObjectType() == tinytmx::ObjectType::TMX_OT_ELLIPSE) {
        puts("It's an Ellipse Object");
        EXPECT_EQ(ellipseObject->GetId(), 4);                                   // id
        EXPECT_EQ(ellipseObject->GetName(), "EllipseObject");                   // name
        EXPECT_EQ(ellipseObject->GetX(), 84.0096f);                             // x
        EXPECT_EQ(ellipseObject->GetY(), 204.758f);                             // y
        EXPECT_EQ(ellipseObject->GetWidth(), 117);                              // width
        EXPECT_EQ(ellipseObject->GetHeight(),90);                               // height
        EXPECT_EQ(ellipseObject->GetRot(), 32.2682f);                           // rotation
    }
}

TEST_F(MainTestTilesetExternalObjectGroup, ObjectGroupObjectsPolygon) {
    auto polygonObject = tmxmap->GetObjectGroup(0)->GetObject(3);
    if (polygonObject->GetObjectType() == tinytmx::ObjectType::TMX_OT_POLYGON) {
        puts("It's a Polygon Object");
        EXPECT_EQ(polygonObject->GetId(), 5);                                   // id
        EXPECT_EQ(polygonObject->GetName(), "PolygonObject");                   // name

        EXPECT_EQ(polygonObject->GetPolygon()->GetNumPoints(), 3);
        EXPECT_EQ(polygonObject->GetPolygon()->GetPoint(1).x, -67);
    }
}

TEST_F(MainTestTilesetExternalObjectGroup, ObjectGroupObjectsPolyline) {
    auto polylineObject = tmxmap->GetObjectGroup(0)->GetObject(4);
    if (polylineObject->GetObjectType() == tinytmx::ObjectType::TMX_OT_POLYLINE) {
        puts("It's a Polyline Object");
        EXPECT_EQ(polylineObject->GetId(), 6);                                  // id
        EXPECT_EQ(polylineObject->GetName(), "PolylineObject");                 // name

        EXPECT_EQ(polylineObject->GetProperties().GetBoolProperty("BoolProp"), true);

        EXPECT_EQ(polylineObject->GetPolyline()->GetNumPoints(), 3);
        EXPECT_EQ(polylineObject->GetPolyline()->GetPoint(1).x, -104);
    }
}

TEST_F(MainTestTilesetExternalObjectGroup, ObjectGroupObjectsText) {
    auto textObject = tmxmap->GetObjectGroup(0)->GetObject(5);
    if (textObject->GetObjectType() == tinytmx::ObjectType::TMX_OT_TEXT) {
        puts("It's a Text Object");

        EXPECT_EQ(textObject->GetName(), "TextObject");                         // name
        EXPECT_EQ(textObject->GetText()->GetFontFamily(), "sans-serif");        // fontfamily
        EXPECT_EQ(textObject->GetText()->GetPixelSize(), 19);                   // pixelsize
        EXPECT_EQ(textObject->GetText()->Wraps(), true);                        // wrap
        EXPECT_EQ(textObject->GetText()->GetColor()->ToString(), "#ff000000");  // color
        EXPECT_EQ(textObject->GetText()->IsBold(), true);                       // bold
        EXPECT_EQ(textObject->GetText()->IsItalic(), true);                     // italic
        EXPECT_EQ(textObject->GetText()->IsUnderline(), false);                 // underline
        EXPECT_EQ(textObject->GetText()->IsStrikeout(), false);                 // strikeout
        EXPECT_EQ(textObject->GetText()->UseKerning(), true);                   // kerning
        EXPECT_EQ(textObject->GetText()->GetHorizontalAlignment(), tinytmx::HorizontalAlignment::LEFT); // halign
        EXPECT_EQ(textObject->GetText()->GetVerticalAlignment(), tinytmx::VerticalAlignment::TOP);      // valign
        EXPECT_EQ(textObject->GetText()->GetContents(), "Hello World");


        EXPECT_EQ(textObject->GetProperties().GetBoolProperty("BoolProp"), true);
    }
}
