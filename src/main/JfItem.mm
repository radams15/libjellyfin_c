//
//  JfItem.m
//  Libjellyfin_objc
//
//  Created by Rhys Adams on 31/10/2022.
//  Copyright 2022 __MyCompanyName__. All rights reserved.
//

#import "JfItem.h"

@implementation JfItem

- (id) initWithPtr: (Item_t) newPtr {
	self = [super init];
	
	ptr = newPtr;
	
	return self;
}

- (NSString*) getName {
    return [[NSString alloc] initWithUTF8String: ptr.name];
}

- (NSString*) getId {
    return [[NSString alloc] initWithUTF8String: ptr.id];
}

- (ItemType_t) getType {
    return ptr.type;
}

@end
