//
//  JellyfinApi.m
//  Libjellyfin_objc
//
//  Created by Rhys Adams on 30/10/2022.
//  Copyright 2022 __MyCompanyName__. All rights reserved.
//

#import "JellyfinApi.h"

#import "SimpleApi.h"
#import "JfItem.h"

#define NS2CPPSTR(inp) std::string((const char*) [inp UTF8String],  [inp length])
#define CPP2NSSTR(inp) [[NSString alloc] initWithUTF8String: inp.c_str()]

NSArray* toJfItemArry(std::vector<Item_t> items){
	NSMutableArray* out = [[NSMutableArray alloc] init];
	
	for(int i=0 ; i<items.size() ; i++){
		Item_t itm = items[i];
		
		JfItem* nsitm = [[JfItem alloc] initWithPtr:itm];

		[out addObject: nsitm];
	}
	
	return out;
}

NSArray* toNSStrArry(std::vector<std::string> items){
    NSMutableArray* out = [[NSMutableArray alloc] init];

    for(int i=0 ; i<items.size() ; i++){
        std::string itm = items[i];

        [out addObject:CPP2NSSTR(itm)];
    }

    return out;
}


@implementation JellyfinApi

- (id) initWithLogin: (NSString*) server
   username: (NSString*) username
   password: (NSString*) password {
	
	self = [super init];
	
	object = new SimpleApi(NS2CPPSTR(server), NS2CPPSTR(username), NS2CPPSTR(password));
	
	return self;
}

- (NSArray*) getMediaFolders {
	return toJfItemArry(((SimpleApi *) object)->get_media_folders());
}

- (NSArray*) getFolderItems: (NSString*) folderId {
	return toJfItemArry(((SimpleApi *) object)->get_folder_items(NS2CPPSTR(folderId)));
}

- (NSArray*) getShowSeasons: (NSString*) showId {
	return toJfItemArry(((SimpleApi *) object)->get_show_seasons(NS2CPPSTR(showId)));

}

- (NSArray*) getSeasonEpisodes: (NSString*) showId
					  seasonId: (NSString*) seasonId {
	return toJfItemArry(((SimpleApi *) object)->get_season_episodes(NS2CPPSTR(showId), NS2CPPSTR(seasonId)));

}

- (NSString*) getStream: (NSString*) episodeId {
    return CPP2NSSTR(((SimpleApi*)object)->get_stream(NS2CPPSTR(episodeId)));
}

- (NSString*) getTranscodedStream: (NSString*) episodeId {
    return CPP2NSSTR(((SimpleApi*)object)->get_transcoded_stream(NS2CPPSTR(episodeId)));
}

- (NSArray*) getStreams: (NSString*) episodeId {
    return toNSStrArry(((SimpleApi *) object)->get_streams(NS2CPPSTR(episodeId)));
}

@end
