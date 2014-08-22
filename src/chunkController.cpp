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
	
}

float voxelSum(segment* segment, int multi, int x, int y, int z) {
	float value = 0;
	int xn = x * multi;
	int yn = y * multi;
	int zn = z * multi;
	
	for (int i = 0; i < multi; i++) {
		value += segment->getData()[xn + i][yn + i][zn + i];
	}
	
	value /= multi;
	
	return value;
}

void bufferConstructor ( int playerxpos, int playerypos, std::vector< std::vector<chunk*> > chunk_list ) {
	
	segment* segment;
	
	int xpos;
	int ypos;
	int zpos;
	
	int size = 0;
	int multi = 0;
	int count = 0;
	int check = 0;
	
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
					
					for (int detail = 0; detail < 5; detail++) {
						
						//Set instance count to 0
						count = 0;
						
						//Get voxel count for detail
						size = std::pow(2, 4 - detail);
						multi = (16 / size);
						
						//Loop through each voxel establishing xvox, yvox and zvox
						for (int xvox = 0; xvox < size; xvox++) {
							for (int yvox = 0; yvox < size; yvox++) {
								for (int zvox = 0; zvox < size; zvox++) {
									
									//Switch check flag to off (testing detail so switched to on)
									check = 0;
									
									//If current voxel is solid
									if ( voxelSum(segment, multi, xvox, yvox, zvox) < 0 ) {
										
										//Check if West voxel is not solid
										if ( xvox == 0 ) {
											if ( xseg != 0 )
												if (voxelSum(chunk_list[xseg - 1][yseg]->getSeg(zseg), multi, size - 1, yvox, zvox) > 0)
													check = 1;
										} else {
											if (voxelSum(segment, multi, xvox - 1, yvox, zvox) > 0)
												check = 1;
										}
								
										//Check if East voxel is not solid
										if ( xvox == size - 1 ) {
											if ( xseg != 8 )
												if (voxelSum(chunk_list[xseg + 1][yseg]->getSeg(zseg), multi, 0, yvox, zvox) > 0)
													check = 1;
										} else {
											if (voxelSum(segment, multi, xvox + 1, yvox, zvox) > 0)
												check = 1;
										}
								
										//Check if South voxel is not solid
										if ( yvox == 0 ) {
											if ( yseg != 0 )
												if (voxelSum(chunk_list[xseg][yseg - 1]->getSeg(zseg), multi, xvox, size - 1, zvox) > 0)
													check = 1;
										} else {
											if (voxelSum(segment, multi, xvox, yvox - 1, zvox) > 0)
												check = 1;
										}
								
										//Check if North voxel is not solid
										if ( yvox == size - 1 ) {
											if ( yseg != 8 )
												if (voxelSum(chunk_list[xseg][yseg + 1]->getSeg(zseg), multi, xvox, 0, zvox) > 0)
													check = 1;
										} else {
											if (voxelSum(segment, multi, xvox, yvox + 1, zvox) > 0)
												check = 1;
										}
								
										//Check if Lower voxel is not solid
										if ( zvox == 0 ) {
											if ( zseg != 0 )
												if (voxelSum(chunk_list[xseg][yseg]->getSeg(zseg - 1), multi, xvox, yvox, size - 1) > 0)
													check = 1;
										} else {
											if (voxelSum(segment, multi, xvox, yvox, zvox - 1) > 0)
												check = 1;
										}
								
										//Check if Upper voxel is not solid
										if ( zvox == size - 1 ) {
											if ( zseg != 7 )
												if (voxelSum(chunk_list[xseg][yseg]->getSeg(zseg + 1), multi, xvox, yvox, 0) > 0)
													check = 1;
										} else {
											if (voxelSum(segment, multi, xvox, yvox, zvox + 1) > 0)
												check = 1;
										}
										
										//If check flag is 1 then add voxel to buffer
										if ( check == 1 ) {
											segment->getBuffer(detail + 1)[count] = (float) xvox * multi + (float) xpos * 16.0f;
											segment->getBuffer(detail + 1)[count + 1] = (float) yvox * multi + (float) ypos * 16.0f;
											segment->getBuffer(detail + 1)[count + 2] = (float) zvox * multi + (float) zpos * 16.0f;
											segment->getBuffer(detail + 1)[count + 3] = (float) multi;
											count += 4;
										}
										
									}
							
							
								}
							}
						}
						
						//Set instance counter for segment
						segment->setCounter(detail + 1, count);
						
					}
				
				}
				
				//Set segment flag for updating VBO
				chunk_list[xseg][yseg]->setFlag(0);
				
			}
		}
	}
	
}

chunkController::chunkController () {
}

chunkController::chunkController (character* player) {
	
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
	}
}

void chunkController::updateData (character* player) {
	int playerxpos = std::floor( player->getXpos() / 16 );;
	int playerypos = std::floor( player->getYpos() / 16 );
	
	dataConstructor(playerxpos, playerypos, chunk_list);
	bufferConstructor(playerxpos, playerypos, chunk_list);
}

void chunkController::updateBuffer () {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			for (int k = 0; k < 8; k++) {
				chunk_list[i][j]->getSeg(k)->updateGLBuffer();
			}
		}
	}
}

void chunkController::render (character* player, shaderVoxel* shader) {
	int countin = 0;
	int countout = 0;
	int ni;
	int nj;
	int detail = 1;
	
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			for (int k = 0; k < 8; k++) {
				
				ni = i - 4;
				if (ni < 0)
					ni *= -1;
				
				nj = j - 4;
				if (nj < 0)
					nj *= -1;
				
				if (ni >= nj) {
					detail = ni + 1;
				} else {
					detail = nj + 1;
				}
				
				if (player->frustumCheck(float( (player->getXseg() - 4 + i) * 16 + 8), float( (player->getYseg() - 4 + j) * 16 + 8), float(k * 16 + 8), 11.32f) == 1) {
					chunk_list[i][j]->getSeg(k)->render( detail, shader->getCoordAttrib(), shader->getScaleAttrib() );
					countin++;
				} else {
					countout++;
				}
				
			}
		}
	}
	//std::cout << countin << ", " << countout << std::endl;
}