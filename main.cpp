#include "Game/GameManager.h"
#include "utility/Print.h"

//todo
//qc/cleanup
//	- should classes be fored to singleton?
//	- cleanup old print stuff
//	- make sure no resource leaks
//	- add uniform buffer things
//	- add the rest of the transform components and test
//	how to handle controller input for rotation>? Right now its tied to a mouse offset...
//	cleanup how windows are handled>? confusing!!
//add uniform blocks for view and projection matrices to shaders
// Left off at camera movement
// make sure only one Window class can be created
///draw cube using index buffer
///
///

// basic entity system for cubes?

int main(int argc, char* argv[]){
	
	// Testing ----------	
	GameManager game;
	game.run();
} 