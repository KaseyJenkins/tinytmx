#ifndef TINYTMX_TINYTMXTILE_HPP
#define TINYTMX_TINYTMXTILE_HPP

#include <stdexcept>
#include <string>
#include <vector>

#include "tinytmxPropertySet.hpp"
#include "tinytmxImage.hpp"
#include "tinytmxObjectGroup.hpp"

namespace tinyxml2 {
    class XMLNode;
}

namespace tinytmx {
    class AnimationFrame;

    class Object;

    //-------------------------------------------------------------------------
    /// A Class to contain the information about every tile in the tileset/tiles
    /// element.
    /// It may expand if there are more elements or attributes added into the
    /// the tile element.
    //-------------------------------------------------------------------------
    class Tile {
    public:


        // Delete copy constructor.
        Tile(Tile const &) = delete;
        // Delete move constructor.
        Tile(Tile &&) = delete;
        // Delete copy assignment operator.
        Tile &operator=(Tile const &) = delete;
        // Delete move assignment operator.
        Tile &operator=(Tile &&) = delete;


        /// Construct a new tile with the given id.
        explicit Tile(int id);
        Tile();
        ~Tile();

        /// Parse a tile node.
        void Parse(tinyxml2::XMLNode const *tileNode, tinytmx::Map const *_map);

        /// Get the Id. (relative to the tileset)
        [[nodiscard]] int GetId() const { return id; }

        /// Returns true if the tile is animated (has one or more animation frames)
        [[nodiscard]] bool IsAnimated() const { return isAnimated; }

        /// Returns the number of frames of the animation. If the tile is not animated, returns 0.
        [[nodiscard]] auto GetFrameCount() const { return frames.size(); }

        /// Returns the total duration of the animation, in milliseconds,
        /// or 0 if the tile is not animated.
        [[nodiscard]] unsigned int GetTotalDuration() const { return totalDuration; }

        /// Returns the tile image if defined.
        [[nodiscard]] tinytmx::Image const *GetImage() const { return image; }

        /// Returns the object type of the tile.
        [[nodiscard]] std::string const &GetType() const { return type; }

        /// Returns the frames of the animation.
        [[nodiscard]] std::vector<AnimationFrame> const &GetFrames() const { return frames; }

        /// Get a set of properties regarding the tile.
        [[nodiscard]] tinytmx::PropertySet const *GetProperties() const { return properties; }

        //// Get the object group, which contains additional tile properties
        [[nodiscard]] tinytmx::ObjectGroup const *GetObjectGroup() const { return objectGroup; }

        /// Returns true if the tile has an objectgroup.
        [[nodiscard]] bool HasObjectGroup() const { return hasObjectGroup; }
        /// Returns true if tile has Collision Objects
        [[nodiscard]] bool HasObjects() const { return hasObjects; }

        /// Get probability.
        [[nodiscard]] float GetProbability() const { return probability; }

        // FIXME Do we really need these convenience functions?

//        /// Get the object group's properties, convenience function
//        const tinytmx::PropertySet &GetObjectGroupProperties() const {
//            if (!objectGroup) {
//                throw std::runtime_error(
//                        "Tile has no ObjectGroup on attempt to get ObjectGroup properties. Cannot return null ref.");
//            }
//            return objectGroup->GetProperties();
//        }
//
//        /// Get set of Collision Objects, convenience function
//        std::vector<tinytmx::Object *> GetObjects() const {
//            if (!objectGroup) { throw std::out_of_range("Tile has no objectGroup"); }
//            return objectGroup->GetObjects();
//        }
//
//        /// Get a single object, convenience function.
//        const tinytmx::Object *GetObject(int index) const {
//            if (!objectGroup) { throw std::out_of_range("Tile has no objectGroup"); }
//            return objectGroup->GetObject(index);
//        }
//
//        /// Get the number of objects in the list, convenience function.
//        auto GetNumObjects() const {
//            if (!objectGroup) { throw std::out_of_range("Tile has no objectGroup"); }
//            return objectGroup->GetNumObjects();
//        }


    private:

        bool isAnimated;
        bool hasObjects;
        bool hasObjectGroup;

        int id;
        unsigned int totalDuration;
        float probability;

        tinytmx::ObjectGroup *objectGroup;
        tinytmx::Image *image;

        std::vector<AnimationFrame> frames;
        std::vector<int> terrain;
        std::string type;

        tinytmx::PropertySet* properties;

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
        [[nodiscard]] int GetTileID() const { return tileID; }

        /// Get the duration of this frame in milliseconds.
        [[nodiscard]] unsigned int GetDuration() const { return duration; }

    private:
        int tileID;
        unsigned int duration;
    };
}

#endif //TINYTMX_TINYTMXTILE_HPP

