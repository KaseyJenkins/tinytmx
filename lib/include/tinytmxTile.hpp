#ifndef TINYTMX_TINYTMXTILE_HPP
#define TINYTMX_TINYTMXTILE_HPP

#include <vector>

#include "tinytmxPropertySet.hpp"
#include "tinytmxImage.hpp"
#include "tinytmxObjectGroup.hpp"
#include <stdexcept>
#include <string>

namespace tinyxml2 {
    class XMLNode;
}

namespace tinytmx {
    class AnimationFrame;

    class Object;

    //-------------------------------------------------------------------------
    /// Class to contain information about every tile in the tileset/tiles
    /// element.
    /// It may expand if there are more elements or attributes added into the
    /// the tile element.
    /// This class also contains a property set.
    //-------------------------------------------------------------------------
    class Tile {
    public:
        /// Construct a new tile with the given id.
        explicit Tile(int id);

        Tile();

        ~Tile();

        /// Parse a tile node.
        void Parse(const tinyxml2::XMLNode *tileNode, const tinytmx::Map *_map);

        /// Get the Id. (relative to the tileset)
        int GetId() const { return id; }

        /// Returns true if the tile is animated (has one or more animation frames)
        bool IsAnimated() const { return isAnimated; }

        /// Returns the number of frames of the animation. If the tile is not animated, returns 0.
        auto GetFrameCount() const { return frames.size(); }

        /// Returns the total duration of the animation, in milliseconds,
        /// or 0 if the tile is not animated.
        unsigned int GetTotalDuration() const { return totalDuration; }

        /// Returns the tile image if defined.
        const tinytmx::Image *GetImage() const { return image; }

        /// Returns the object type of the tile.
        std::string GetType() const { return type; }

        /// Returns the frames of the animation.
        const std::vector<AnimationFrame> &GetFrames() const { return frames; }

        /// Get a set of properties regarding the tile.
        const tinytmx::PropertySet &GetProperties() const { return properties; }

        //// Get the object group, which contains additional tile properties
        const tinytmx::ObjectGroup *GetObjectGroup() const { return objectGroup; }

        //// Get the object group's properties, convenience function
        const tinytmx::PropertySet &GetObjectGroupProperties() const {
            if (!objectGroup) {
                throw std::runtime_error(
                        "Tile has no ObjectGroup on attempt to get ObjectGroup properties. Cannot return null ref.");
            }
            return objectGroup->GetProperties();
        }

        /// Get set of Collision Objects, convenience function
        std::vector<tinytmx::Object *> GetObjects() const {
            if (!objectGroup) { throw std::out_of_range("Tile has no objectGroup"); }
            return objectGroup->GetObjects();
        }

        /// Returns true if tile has Collision Objects
        bool HasObjects() const { return hasObjects; }

        /// Get a single object.
        const tinytmx::Object *GetObject(int index) const {
            if (!objectGroup) { throw std::out_of_range("Tile has no objectGroup"); }
            return objectGroup->GetObject(index);
        }

        /// Get the number of objects in the list.
        auto GetNumObjects() const {
            if (!objectGroup) { throw std::out_of_range("Tile has no objectGroup"); }
            return objectGroup->GetNumObjects();
        }

        /// Get probability.
        float GetProbability() const { return probability; }

    private:
        int id;

        float probability;

        tinytmx::PropertySet properties;

        bool isAnimated;
        bool hasObjects;
        bool hasObjectGroup;
        tinytmx::ObjectGroup *objectGroup;
        unsigned int totalDuration;
        std::vector<AnimationFrame> frames;
        tinytmx::Image *image;
        std::string type;

        std::vector<int> terrain;

    };

    //-------------------------------------------------------------------------
    /// Class containing information about an animated tile. This includes the
    /// duration of each frame and the various ids of each frame in the
    /// animation.
    //-------------------------------------------------------------------------
    class AnimationFrame {
    public:
        /// This constructor shouldn't be used, ideally.
        // FIXME: just default maybe
        AnimationFrame() :
                tileID(-1), duration(0) {
        }

        /// Create a new animation frame with a specified tile id and duration.
        AnimationFrame(int tileID, unsigned int duration) :
                tileID(tileID), duration(duration) {
        }

        /// Get the tile id of this frame, relative to the containing tileset.
        int GetTileID() const { return tileID; }

        /// Get the duration of this frame in milliseconds.
        unsigned int GetDuration() const { return duration; }

    private:
        int tileID;
        unsigned int duration;
    };
}

#endif //TINYTMX_TINYTMXTILE_HPP

