//
// Created by rhys on 28/10/22.
//

#ifndef JELLYFIN_STRUCTURES_H
#define JELLYFIN_STRUCTURES_H

typedef enum ItemType {
    FOLDER,
    TVSHOWS,
    MOVIES,
    SERIES,
    SEASON,
    EPISODE,
    TV,
    MOVIE,
    SONG,
    ALBUM,
    VIDEO,

    UNKNOWN
} ItemType_t;

typedef struct Item {
    const char* name;
    const char* id;

    ItemType_t type;
} Item_t;

#endif //JELLYFIN_STRUCTURES_H
