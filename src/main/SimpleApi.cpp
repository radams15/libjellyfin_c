//
// Created by rhys on 28/10/22.
//

#include <cstdio>
#include <cstring>
#include <iostream>

#include "SimpleApi.h"
#include "Conf.h"
#include "request.h"

SimpleApi::SimpleApi(std::string server, std::string username, std::string password) : config() {
    this->server = server;
    this->username = username;

    login(password);
}

void SimpleApi::login(std::string password) {
    std::string url = "Users/AuthenticateByName";

    HeaderMap data;
    data["username"] = username;
    data["Pw"] = password;

    HeaderMap headers = get_headers();
    headers["Content-Type"] = "application/json";

    json res = post(url, headers, data);

    config["auth.user_id"] = res["User"]["Id"];
    config["auth.token"] = res["AccessToken"];
}

HeaderMap SimpleApi::get_headers() {
    HeaderMap out;

    char auth_buf[4096];
    sprintf(auth_buf, "MediaBrowser Client=%s, Device=%s, DeviceId=%s, Version=%s", APP_NAME, DEVICE, DEVICE_ID, CLIENT_VERSION);

    if (config.find("auth.token") != config.end()) {
        char token_buf[1024];
        sprintf(token_buf, ", UserId=%s", config["auth.user_id"].c_str());

        strcat(auth_buf, token_buf);
    }

    out["Accept"] = "Application/json";
    out["Content-Type"] = "application/x-www-form-urlencoded; charset=UTF-8";
    out["X-Application"] = APP_NAME "/" CLIENT_VERSION;
    out["Accept-Charset"] = "UTF-8,*";
    out["User-Agent"] = USER_AGENT;
    out["x-emby-authorization"] = std::string(auth_buf);

    if (config.find("auth.token") != config.end()){
        out["X-MediaBrowser-Token"] = config["auth.token"];
    }

    return out;
}

std::string SimpleApi::get_url(std::string path) {
    if(path[0] == '/'){
        path = path.substr(1);
    }

    return server + "/" + path;
}

json SimpleApi::post(std::string url, HeaderMap headers, HeaderMap data) {
    url = get_url(url);

    Headers_t* req_headers = NULL;

    for(std::pair<std::string, std::string> x : headers){
        req_headers = headers_append(req_headers, strdup(x.first.c_str()), strdup(x.second.c_str()));
    }

    std::string data_str = json(data).dump();

    Res_t* res = req_post(url.c_str(), data_str.c_str(), req_headers);

    if(res->err){
        std::cerr << "Post failed!" << std::endl;

        throw std::exception();
    }

    json out = json::parse(res->data);

    return out;
}

json SimpleApi::get(std::string url, HeaderMap headers) {
    url = get_url(url);

    Headers_t* req_headers = NULL;

    for(std::pair<std::string, std::string> x : headers){
        req_headers = headers_append(req_headers, strdup(x.first.c_str()), strdup(x.second.c_str()));
    }

    Res_t* res = req_get(url.c_str(), req_headers);

    if(res->err){
        std::cerr << "Get failed!" << std::endl;

        throw std::exception();
    }

    json out = json::parse(res->data);

    return out;
}

Item_t to_item(json in, ItemType_t type){
    return (Item_t){
        strdup(in["Name"].get<std::string>().c_str()),
        strdup(in["Id"].get<std::string>().c_str()),
        type
    };
}

std::vector<Item_t> SimpleApi::get_media_folders() {
    json items = get("Users/" + config["auth.user_id"] + "/Items", get_headers())["Items"];

    std::vector<Item_t> out;

    for(int i=0 ; i<items.size() ; i++){
        json item = items[i];

        std::string type_str = item["CollectionType"];

        ItemType_t type;

        if(type_str == "tvshows"){
            type = TVSHOWS;
        }else if(type_str == "movies"){
            type = MOVIES;
        }else{
            type = UNKNOWN;
        }

        out.push_back(to_item(item, type));
    }

    return out;
}

std::vector<Item_t> SimpleApi::get_folder_items(std::string folder_id) {
    json items = get("Users/" + config["auth.user_id"] + "/Items?parentId=" + folder_id, get_headers())["Items"];

    std::vector<Item_t> out;

    for(int i=0 ; i<items.size() ; i++){
        json item = items[i];

        bool is_folder = item["IsFolder"];

        ItemType_t type;

        if(is_folder){
            type = FOLDER;
        }else {
            type = VIDEO;
        }

        out.push_back(to_item(item, type));
    }

    return out;
}

std::vector<Item_t> SimpleApi::get_show_seasons(std::string show_id) {
    json items = get("Shows/" + show_id + "/Seasons?userId=" + config["auth.user_id"], get_headers())["Items"];

    std::vector<Item_t> out;

    for(int i=0 ; i<items.size() ; i++){
        json item = items[i];

        out.push_back(to_item(item, SEASON));
    }

    return out;
}

std::vector<Item_t> SimpleApi::get_season_episodes(std::string show_id, std::string season_id) {
    json items = get("Shows/" + show_id + "/Episodes/?seasonId=" + season_id + "?userId=" + config["auth.user_id"], get_headers())["Items"];

    std::vector<Item_t> out;

    for(int i=0 ; i<items.size() ; i++){
        json item = items[i];

        out.push_back(to_item(item, EPISODE));
    }

    return out;
}
