//
// Created by rhys on 28/10/22.
//

#ifndef JELLYFIN_SIMPLEAPI_H
#define JELLYFIN_SIMPLEAPI_H

#include <string>
#include <map>
#include <vector>

#include <json.hpp>
#include "Structures.h"

using json = nlohmann::json;

typedef std::map<std::string, std::string> HeaderMap;

class SimpleApi {
public:
    SimpleApi(std::string server, std::string username, std::string password);

    std::vector<Item_t> get_media_folders();
    std::vector<Item_t> get_folder_items(std::string folder_id);
    std::vector<Item_t> get_show_seasons(std::string show_id);
    std::vector<Item_t> get_season_episodes(std::string show_id, std::string season_id);

private:
    std::string server;
    std::string username;
    std::string password;

    HeaderMap config;

    HeaderMap get_headers();

    std::string get_url(std::string path);

    json post(std::string url, HeaderMap headers, HeaderMap data);
    json get(std::string url, HeaderMap headers);

    void login(std::string password);
};


#endif //JELLYFIN_SIMPLEAPI_H
