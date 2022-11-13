//
// Created by rhys on 27/10/22.
//

#include <iostream>

#include "JellyfinApi.h"
#import "JfItem.h"

int main(){
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];

    JellyfinApi* api = [[JellyfinApi alloc] initWithLogin: @"http://server/jellyfin" username: @"family" password: @""];

    NSArray* folders = [api getMediaFolders];
    for(int i=0 ; i<[folders count] ; i++) {
        NSLog(@"Folder %@\n", [[folders objectAtIndex:i] getName]);

        NSArray* shows = [api getFolderItems: [[folders objectAtIndex:i] getId]];

        for (int x=0 ; x<[shows count] ; x++) {
            NSLog(@"Show %@\n", [[shows objectAtIndex:x] getName]);

            if([[folders objectAtIndex:i] getType] == TVSHOWS){
                NSArray* seasons = [api getShowSeasons: [[shows objectAtIndex:x] getId]];

                for (int y=0 ; y<[seasons count] ; y++) {
                    NSLog(@"Season %@\n", [[seasons objectAtIndex:y] getName]);

                    NSArray* episodes = [api getSeasonEpisodes:[[shows objectAtIndex:x] getId] seasonId:[[seasons objectAtIndex:y] getId]];
                    for (int z=0 ; z<[episodes count] ; z++) {
                        NSLog(@"Episode %@\n", [[episodes objectAtIndex:z] getName]);

                        NSLog(@"Stream %@\n", [api getStream: [[episodes objectAtIndex:z] getId]]);

                        //std::cout << "\t\t\t" << api.get_stream(episode.id) << std::endl;
                        NSArray* streams = [api getStreams: [[episodes objectAtIndex:z] getId]];

                        for(int a=0 ; a<[streams count] ; a++){
                            NSLog(@"\tStream: %@\n", [streams objectAtIndex:a]);
                        }

                        goto end;
                    }
                }
            }
        }
    }

end:

    [pool release];

    return 0;
}