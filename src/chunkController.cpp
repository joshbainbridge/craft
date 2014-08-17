#include <craft/chunkController.hpp>

#include <craft/segment.hpp>
#include <craft/simplex.hpp>

#include <iostream>

void dataConstructor ( int playerxpos, int playerypos, chunk chunk_list[9][9] ) {
	
	segment* segment;
	
	int xpos;
	int ypos;
	int zpos;
	
	float terrain;
	float tunnel;
	
	//Loop through each segment establishing xseg, yseg and zseg
	for (int xseg = 0; xseg < 9; xseg++) {
		for (int yseg = 0; yseg < 9; yseg++) {
			for (int zseg = 0; zseg < 8; zseg++) {
				
				//Set pointer to current segment
				segment = chunk_list[xseg][yseg].getSeg(zseg);
				
				//Get current virtual postion of segment 
				xpos = ( playerxpos - 4 ) + xseg;
				ypos = ( playerypos - 4 ) + yseg;
				zpos = zseg;
				
				//Loop through each voxel establishing xvox, yvox and zvox
				for (int xvox = 0; xvox < 16; xvox++) {
					for (int yvox = 0; yvox < 16; yvox++) {
						for (int zvox = 0; zvox < 16; zvox++) {
							
							//Using simplex noise, generate data for segment 
							terrain = simplex_noise(
								3,
								(double) xpos * 16.0l + (double) xvox,
								(double) ypos * 16.0l + (double) yvox,
								(double) zpos * 16.0l + (double) zvox,
								75.0f,
								0.85f
							);
							
							terrain += ( ( (float) zvox + (float) zpos * 16) - 64 ) / 24.0f;
							
							tunnel = simplex_noise(
								3,
								(double) xpos * 16.0l + (double) xvox,
								(double) ypos * 16.0l + (double) yvox,
								(double) zpos * 16.0l + (double) zvox,
								100.0f,
								0.85f
							);
							
							if (tunnel < 0)
								tunnel *= -1;
							
							if (tunnel > 0.3) {
								tunnel = 3.0f;
							} else {
								tunnel = 0.0f;
							}
							
							segment->getData()[xvox][yvox][zvox] = terrain + tunnel;
							
						}
					}
				}
				
			}
		}
	}
	
}

void bufferConstructor ( int playerxpos, int playerypos, chunk chunk_list[9][9] ) {
	
	segment* segment;
	
	int xpos;
	int ypos;
	int zpos;
	
	int count = 0;
	int check = 0;
	
	//Loop through each segment establishing xseg, yseg and zseg
	for (int xseg = 0; xseg < 9; xseg++) {
		for (int yseg = 0; yseg < 9; yseg++) {
			for (int zseg = 0; zseg < 8; zseg++) {
				
				//Set pointer to current segment
				segment = chunk_list[xseg][yseg].getSeg(zseg);
				
				//Get current virtual postion of segment 
				xpos = ( playerxpos - 4 ) + xseg;
				ypos = ( playerypos - 4 ) + yseg;
				zpos = zseg;
				
				//Set instance count to 0
				count = 0;
				
				//Loop through each voxel establishing xvox, yvox and zvox
				for (int xvox = 0; xvox < 16; xvox++) {
					for (int yvox = 0; yvox < 16; yvox++) {
						for (int zvox = 0; zvox < 16; zvox++) {
							
							//Switch check flag to off
							check = 0;
							
							//If current voxel is solid
							if ( segment->getData()[xvox][yvox][zvox] < 0 ) {
								
								//Check if West voxel is not solid
								if ( xvox == 0 ) {
									if ( xseg != 0 )
										if (chunk_list[xseg - 1][yseg].getSeg(zseg)->getData()[15][yvox][zvox] > 0)
											check = 1;
								} else {
									if (segment->getData()[xvox - 1][yvox][zvox] > 0)
										check = 1;
								}
								
								//Check if East voxel is not solid
								if ( xvox == 15 ) {
									if ( xseg != 8 )
										if (chunk_list[xseg + 1][yseg].getSeg(zseg)->getData()[0][yvox][zvox] > 0)
											check = 1;
								} else {
									if (segment->getData()[xvox + 1][yvox][zvox] > 0)
										check = 1;
								}
								
								//Check if South voxel is not solid
								if ( yvox == 0 ) {
									if ( yseg != 0 )
										if (chunk_list[xseg][yseg - 1].getSeg(zseg)->getData()[xvox][15][zvox] > 0)
											check = 1;
								} else {
									if (segment->getData()[xvox][yvox - 1][zvox] > 0)
										check = 1;
								}
								
								//Check if North voxel is not solid
								if ( yvox == 15 ) {
									if ( yseg != 8 )
										if (chunk_list[xseg][yseg + 1].getSeg(zseg)->getData()[xvox][0][zvox] > 0)
											check = 1;
								} else {
									if (segment->getData()[xvox][yvox + 1][zvox] > 0)
										check = 1;
								}
								
								//Check if Lower voxel is not solid
								if ( zvox == 0 ) {
									if ( zseg != 0 )
										if (chunk_list[xseg][yseg].getSeg(zseg - 1)->getData()[xvox][yvox][15] > 0)
											check = 1;
								} else {
									if (segment->getData()[xvox][yvox][zvox - 1] > 0)
										check = 1;
								}
								
								//Check if Upper voxel is not solid
								if ( zvox == 15 ) {
									if ( zseg != 7 )
										if (chunk_list[xseg][yseg].getSeg(zseg + 1)->getData()[xvox][yvox][0] > 0)
											check = 1;
								} else {
									if (segment->getData()[xvox][yvox][zvox + 1] > 0)
										check = 1;
								}
								
								//If check flag is 1 then add voxel to buffer
								if ( check == 1 ) {
									segment->getBuffer()[count] = (float) xvox + (float) xpos * 16.0f;
									segment->getBuffer()[count + 1] = (float) yvox + (float) ypos * 16.0f;
									segment->getBuffer()[count + 2] = (float) zvox + (float) zpos * 16.0f;
									count += 3;
								}
							}
							
							
						}
					}
				}
				
				//Set instance counter for segment
				segment->setCounter(count);
				
			}
		}
	}
	
}

chunkController::chunkController () {
}

chunkController::chunkController (character* player) {
	
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			chunk_list[i][j].init();
		}
	}
	
	int playerxpos = int( player->getXpos() / 16 );
	int playerypos = int( player->getYpos() / 16 );
	
	dataConstructor(playerxpos, playerypos, chunk_list);
	bufferConstructor(playerxpos, playerypos, chunk_list);
	updateBuffer();
}

void chunkController::updateData (character* player) {
	int playerxpos = int( player->getXpos() / 16 );
	int playerypos = int( player->getYpos() / 16 );
	
	dataConstructor(playerxpos, playerypos, chunk_list);
	bufferConstructor(playerxpos, playerypos, chunk_list);
}

void chunkController::updateBuffer () {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			for (int k = 0; k < 8; k++) {
				chunk_list[i][j].getSeg(k)->updateGLBuffer();
			}
		}
	}
}

void chunkController::render (shaderVoxel* shader) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			for (int k = 0; k < 8; k++) {
				chunk_list[i][j].getSeg(k)->render( shader->getCoordAttrib() );
			}
		}
	}
}