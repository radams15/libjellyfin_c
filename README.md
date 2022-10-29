# libjellyfin

Simple library to interface with jellyfin using c++.

## Usage:

Prints out every film, series, season and episode in every folder of the server.

```c++

#include <iostream>

#include "SimpleApi.h"

int main(){
    SimpleApi api("http://jellyfin:8096", "username", "password");

    for(auto folder : api.get_media_folders()) {
        std::cout << folder.name << std::endl;

        for (auto show: api.get_folder_items(folder.id)) {
            std::cout << "\t" << show.name << std::endl;

            if(folder.type == TVSHOWS){
                for (auto season: api.get_show_seasons(show.id)) {
                    std::cout << "\t\t" << season.name << std::endl;

                    for (auto episode: api.get_season_episodes(show.id, season.id)) {
                        std::cout << "\t\t\t" << episode.name << std::endl;
                    }
                }
            }
        }
    }
}
```