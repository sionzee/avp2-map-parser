//
// Created by sionzee on 12. 12. 2019. Dec.
//

#ifndef AVP2MAPREADER_WORLDFLAGS_H
#define AVP2MAPREADER_WORLDFLAGS_H

enum WorldFlags: unsigned int {
    /**
     * 1. WorldData::m_pWorldBsp is set so the world model
	 * can be moved and rotated around.
     */
    MOVEABLE = 1,

    /**
     *  1. Preprocessor lib this in its poly stats
	 * and shows detail stats for this world.
	 * 2. FLAG_GOTHRUWORLD is checked for world models
	 * with this WorldBsp.
     */
    MAINWORLD = 2,

    /** This is the physics BSP (only one of these). */
    PHYSICSBSP = 4,

    /** This is the visibility BSP (only one of these). */
    VISBSP = 5,
};

inline WorldFlags operator|(WorldFlags a, WorldFlags b) {
    return static_cast<WorldFlags>(static_cast<unsigned int>(a) | static_cast<unsigned int>(b));
}

inline WorldFlags operator&(WorldFlags a, WorldFlags b) {
    return static_cast<WorldFlags>(static_cast<unsigned int>(a) & static_cast<unsigned int>(b));
}

inline WorldFlags operator^(WorldFlags a, WorldFlags b) {
    return static_cast<WorldFlags>(static_cast<unsigned int>(a) ^ static_cast<unsigned int>(b));
}

inline WorldFlags operator~(WorldFlags a) {
    return static_cast<WorldFlags>(~static_cast<unsigned int>(a));
}

#endif //AVP2MAPREADER_WORLDFLAGS_H
