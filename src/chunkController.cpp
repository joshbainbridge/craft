#include <craft/chunkController.hpp>

#include <craft/segment.hpp>
#include <craft/simplex.hpp>

#include <cmath>
#include <iostream>

void dataConstructor ( int playerxpos, int playerypos, std::vector< std::vector<chunk*> > chunk_list ) {
	
	segment* segment;
	
	int xpos;
	int ypos;
	int zpos;
	
	float terrain;
	float tunnel;
	
	//Loop through each segment establishing xseg, yseg and zseg
	for (int xseg = 0; xseg < 9; xseg++) {
		for (int yseg = 0; yseg < 9; yseg++) {
			if (chunk_list[xseg][yseg]->getFlag() == 1) {
				for (int zseg = 0; zseg < 8; zseg++) {
				
					//Set pointer to current segment
					segment = chunk_list[xseg][yseg]->getSeg(zseg);
				
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
									2,
									(double) xpos * 16.0l + (double) xvox,
									(double) ypos * 16.0l + (double) yvox,
									(double) zpos * 16.0l + (double) zvox,
									75.0f,
									0.45f
								);
							
								terrain += ( ( (float) zvox + (float) zpos * 16) - 64 ) / 64.0f;
							
								segment->getData()[xvox][yvox][zvox] = terrain;
							
							}
						}
					}
				
				}
				
			chunk_list[xseg][yseg]->setFlag(2);
			}
		}
	}
	
}

void bufferConstructor ( int playerxpos, int playerypos, std::vector< std::vector<chunk*> > chunk_list ) {
	
	segment* segment;
	
	int xpos;
	int ypos;
	int zpos;
	
	int count = 0;
	
	//Loop through each segment establishing xseg, yseg and zseg
	for (int xseg = 0; xseg < 9; xseg++) {
		for (int yseg = 0; yseg < 9; yseg++) {
			if (chunk_list[xseg][yseg]->getFlag() == 2) {
				for (int zseg = 0; zseg < 8; zseg++) {
				
					//Set pointer to current segment
					segment = chunk_list[xseg][yseg]->getSeg(zseg);
				
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
								
								//If current voxel is solid
								if ( segment->getData()[xvox][yvox][zvox] < 0 ) {
									
									segment->getBuffer()[count] = (float) xvox + (float) xpos * 16.0f;
									segment->getBuffer()[count + 1] = (float) yvox + (float) ypos * 16.0f;
									segment->getBuffer()[count + 2] = (float) zvox + (float) zpos * 16.0f;
									segment->getBuffer()[count + 3] = (float) 1.0f;
									count += 4;
									
								}
						
						
							}
						}
					}
					
					//Set instance counter for segment
					segment->setCounter(count);
					
				}
				
				//Set segment flag for updating VBO
				chunk_list[xseg][yseg]->setFlag(3);
				
			}
		}
	}
	
}

chunkController::chunkController () {
}

chunkController::chunkController (character* player) {
	flag = 1;
	
	chunk_list.resize(9);
	for (int i = 0; i < 9; i++) {
		chunk_list[i].resize(9);
		for (int j = 0; j < 9; j++) {
			chunk* contructed = new chunk();
			chunk_list[i][j] = contructed;
		}
	}
	
	int playerxpos = std::floor( player->getXpos() / 16 );
	int playerypos = std::floor( player->getYpos() / 16 );
	
	dataConstructor(playerxpos, playerypos, chunk_list);
	bufferConstructor(playerxpos, playerypos, chunk_list);
	updateBuffer();
}

chunkController::~chunkController () {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			delete chunk_list[i][j];
		}
	}
}

void chunkController::updateSegFlag (character* player) {
	if (flag == 0) {
		int xold = player->getXseg();
		int xnew = std::floor( player->getXpos() / 16 );
		int yold = player->getYseg();
		int ynew = std::floor( player->getYpos() / 16 );
	
		int xdif = xnew - xold;
		int ydif = ynew - yold;
	
		if (xdif != 0) {
			if (xdif < 0) {
			
				for (int i = 0; i > xdif; i--) {
					std::vector< chunk* > holder = chunk_list.back();
					chunk_list.pop_back();
					auto iterator = chunk_list.begin();
					chunk_list.insert(iterator, holder);
					for (int i = 0; i < 9; i++) {
						chunk_list.front()[i]->setFlag(1);
					}
				}
			
			} else {
			
				for (int i = 0; i < xdif; i++) {
					std::vector< chunk* > holder = chunk_list.front();
					auto iterator = chunk_list.begin();
					chunk_list.erase(iterator);
					chunk_list.push_back(holder);
					for (int i = 0; i < 9; i++) {
						chunk_list.back()[i]->setFlag(1);
					}
				}
			
			}
		}
	
		if (ydif != 0) {
			if (ydif < 0) {
			
				for (int i = 0; i > ydif; i--) {
				
					for (int i = 0; i < 9; i++) {
						chunk* holder = chunk_list[i].back();
						chunk_list[i].pop_back();
						auto iterator = chunk_list[i].begin();
						chunk_list[i].insert(iterator, holder);
						chunk_list[i].front()->setFlag(1);
					}
				
				}
			
			} else {
			
				for (int i = 0; i < ydif; i++) {
				
					for (int i = 0; i < 9; i++) {
						chunk* holder = chunk_list[i].front();
						auto iterator = chunk_list[i].begin();
						chunk_list[i].erase(iterator);
						chunk_list[i].push_back(holder);
						chunk_list[i].back()->setFlag(1);
					}
				
				}
			
			}
		}
	
		if (xdif != 0 || ydif != 0) {
			player->setXseg(xnew);
			player->setYseg(ynew);
			flag = 1;
		}
	}
}

void chunkController::updateData (character* player) {
	if (flag == 1) {
		int playerxpos = std::floor( player->getXpos() / 16 );;
		int playerypos = std::floor( player->getYpos() / 16 );
	
		dataConstructor(playerxpos, playerypos, chunk_list);
		bufferConstructor(playerxpos, playerypos, chunk_list);
		
		flag = 2;
	}
}

void chunkController::updateBuffer () {
	if (flag == 2) {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				if (chunk_list[i][j]->getFlag() == 3) {
					for (int k = 0; k < 8; k++) {
						chunk_list[i][j]->getSeg(k)->updateGLBuffer();
					}
			
				chunk_list[i][j]->setFlag(0);
				}
			}
		}
		
		flag = 0;
	}
}

void chunkController::render (character* player, shaderVoxel* shader) {
	int countin = 0;
	int countout = 0;
	
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			for (int k = 0; k < 8; k++) {
				if (player->frustumCheck(float( (player->getXseg() - 4 + i) * 16 + 8), float( (player->getYseg() - 4 + j) * 16 + 8), float(k * 16 + 8), 11.32f) == 1) {
					chunk_list[i][j]->getSeg(k)->render(shader->getCoordAttrib(), shader->getScaleAttrib() );
					countin++;
				} else {
					countout++;
				}
			}
		}
	}
	
	//std::cout << countin << ", " << countout << std::endl;
}