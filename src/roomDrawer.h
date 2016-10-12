//
//  roomDrawer.hpp
//  system06_space
//
//  Created by Ovis aries on 2016/10/11.
//
//

#ifndef roomDrawer_hpp
#define roomDrawer_hpp

#include "ofMain.h"
#include "roomManager.h"

class roomDrawer{
public:
	
	void setup();
	void update();
	void draw();
	
	roomManager *room;
};

#endif /* roomDrawer_hpp */
