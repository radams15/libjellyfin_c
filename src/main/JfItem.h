//
//  JfItem.h
//  Libjellyfin_objc
//
//  Created by Rhys Adams on 31/10/2022.
//  Copyright 2022 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SimpleApi.h"

@interface JfItem : NSObject {
	Item_t ptr;
}

- (id) initWithPtr: (Item_t) newPtr;

- (NSString*) getName;
- (NSString*) getId;
- (ItemType_t) getType;

@end
