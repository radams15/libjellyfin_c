//
// Created by rhys on 27/10/22.
//

#include <iostream>

#include "SimpleApi.h"

int main(){
    SimpleApi api("http://mediaserver:8096", "family", "");

    for(auto folder : api.get_media_folders()) {
        std::cout << folder.name << std::endl;

        for (auto show: api.get_folder_items(folder.id)) {
            std::cout << "\t" << show.name << std::endl;

            if(folder.type == TVSHOWS){
                for (auto season: api.get_show_seasons(show.id)) {
                    std::cout << "\t\t" << season.name << std::endl;

                    for (auto episode: api.get_season_episodes(show.id, season.id)) {
                        std::cout << "\t\t\t" << api.get_stream(episode.id) << std::endl;
                    }
                }
            }
        }
    }
}