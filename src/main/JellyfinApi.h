//
//  JellyfinApi.h
//  Libjellyfin_objc
//
//  Created by Rhys Adams on 30/10/2022.
//  Copyright 2022 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface JellyfinApi : NSObject {
	void* object;
}

- (id) initWithLogin: (NSString*) server
   username: (NSString*) username
   password: (NSString*) password;

- (NSArray*) getMediaFolders;
- (NSArray*) getFolderItems: (NSString*) folderId;
- (NSArray*) getShowSeasons: (NSString*) showId;
- (NSArray*) getSeasonEpisodes: (NSString*) showId
					  seasonId: (NSString*) seasonId;

- (NSString*) getStream: (NSString*) episodeId;
- (NSString*) getTranscodedStream: (NSString*) episodeId;
- (NSArray*) getStreams: (NSString*) episodeId;

@end
