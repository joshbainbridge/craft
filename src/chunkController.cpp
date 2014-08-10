#include <craft/chunkController.hpp>
#include <craft/simplex.hpp>
#include <iostream>

void dataConstructor ( float data[16][16][16], int xpos, int ypos, int zpos ) {

	for (int i = 0; i < 16; i += 1) {
		for (int j = 0; j < 16; j += 1) {
			for (int k = 0; k < 16; k += 1) {
				
				data[i][j][k] = simplex_noise(
					3,
					(float) i + (float) xpos * 16.0f,
					(float) j + (float) ypos * 16.0f,
					(float) k + (float) zpos * 16.0f,
					75.0f,
					0.85f
				) + ( ( (float) k + (float) zpos * 16) - 64 ) / 24.0f;
				
				//std::cout << data[i][j][k] << std::endl;
			}
		}
	}
	
}

int bufferConstructor ( GLfloat* position,  float data[16][16][16], int xpos, int ypos, int zpos, int xindex, int yindex ) {
	int count = 0;
	int bi, bj, bk;
	char w, e, s, n, l, h;
	char check;
	
	for (int i = 0; i < 16; i += 1) {
		for (int j = 0; j < 16; j += 1) {
			for (int k = 0; k < 16; k += 1) {
				
				if (data[i][j][k] < 0) {
					
					check = 1;
					
					for (int ri = -1; ri < 2; ri += 1) {
						for (int rj = -1; rj < 2; rj += 1) {
							for (int rk = -1; rk < 2; rk += 1) {
								if ( ri != 0 || rj != 0 || rk != 0 ) {
									
									bi = i + ri;
									bj = j + rj;
									bk = k + rk;
									w = e = s = n = l = h = 0;
									
									if ( bi < 0 ) {
										// Check if West
										w = 1;
										if (xindex == 0) {
											break;
										}
									}
									if ( bi > 15 ) {
										// Check if East
										e = 1;
										if (xindex == 8) {
											break;
										}
									}
									if ( bj < 0 ) {
										// Check if South
										s = 1;
										if (yindex == 0) {
											break;
										}
									}
									if ( bj > 15 ) {
										// Check if North
										n = 1;
										if (yindex == 8) {
											break;
										}
									}
									if ( bk < 0 ) {
										// Check if Lower
										l = 1;
										if (zpos == 0) {
											break;
										}
									} 
									if ( bk > 15 ) {
										// Check if Higher
										h = 1;
										if (zpos == 7) {
											break;
										}
									}
									
									if ( w == 0 && e == 0 && s == 0 && n == 0 && l == 0 && h == 0 ) {
										
										// If neighbour is not beyond side, edge or corner
										if ( data[bi][bj][bk] > 0 ) {
											// Check if solid
											check = 0;
										}
										
									} else {
									
										if ( w == 1 ) {
											if ( s == 0 && n == 0 && l == 0 && h == 0 ) {
												// Check for West chunk
											} else {
										
												if ( s == 1 ) {
													
													if ( l == 1 ) {
														// Check for South West chunk and Lower segment
													} else if ( h == 1 ) {
														// Check for South West chunk and Higher segment
													} else {
														// Check for South West chunk
													}
										
												} else if ( n == 1 ) {
										
													if ( l == 1 ) {
														// Check for North West chunk and Lower segment
													} else if ( h == 1 ) {
														// Check for North West chunk and Higher segment
													} else {
														// Check for North West chunk
													}
										
												}
										
												if ( l == 1 ) {
											
													if ( s == 0 && n == 0 ) {
														// Check for West chunk and Lower segment
													}
										
												} else if ( h == 1 ) {
											
													if ( s == 0 && n == 0 ) {
														// Check for West chunk and Higher segment
													}
										
												}
										
											}
										
										} else if ( e == 1 ) {
									
											if ( s == 0 && n == 0 && l == 0 && h == 0 ) {
												// Check for East chunk
											} else {
										
												if ( s == 1 ) {
										
													if ( l == 1 ) {
														// Check for South East chunk and Lower segment
													} else if ( h == 1 ) {
														// Check for South East chunk and Higher segment
													} else {
														// Check for South East chunk
													}
										
												} else if ( n == 1 ) {
										
													if ( l == 1 ) {
														// Check for North East chunk and Lower segment
													} else if ( h == 1 ) {
														// Check for North East chunk and Higher segment
													} else {
														// Check for North East chunk
													}
										
												}
										
												if ( l == 1 ) {
											
													if ( s == 0 && n == 0 ) {
														// Check for East chunk and Lower segment
													}
										
												} else if ( h == 1 ) {
											
													if ( s == 0 && n == 0 ) {
														// Check for East chunk and Higher segment
													}
										
												}
										
											}
										
										}
									
										if ( s == 1 ) {
									
											if ( w == 0 && e == 0 && l == 0 && h == 0 ) {
												// Check for South chunk
											} else if ( l == 1 ) {
											
												if ( w == 0 && e == 0 ) {
													// Check for South chunk and Lower segment
												}
										
											} else if ( h == 1 ) {
											
												if ( w == 0 && e == 0 ) {
													// Check for South chunk and Higher segment
												}
										
											}
										
										} else if ( n == 1 ) {
									
											if ( w == 0 && e == 0 && l == 0 && h == 0 ) {
												// Check for North chunk
											} else if ( l == 1 ) {
											
												if ( w == 0 && e == 0 ) {
													// Check for North chunk and Lower segment
												}
										
											} else if ( h == 1 ) {
											
												if ( w == 0 && e == 0 ) {
													// Check for North chunk and Higher segment
												}
										
											}
										
										}
									
										if ( l == 1 ) {
									
											if ( w == 0 && e == 0 && s == 0 && n == 0 ) {
												// Check for Lower segment
											}
										
										} else if ( h == 1 ) {
									
											if ( w == 0 && e == 0 && s == 0 && n == 0 ) {
												// Check for Higher segment
											}
										
										}
									
									}
								}
							}
						}
					}
					
					if ( check == 0 ) {
						// If neighbour is empty
						position[count] = (float) i + (float) xpos * 16.0f;
						position[count + 1] = (float) j + (float) ypos * 16.0f;
						position[count + 2] = (float) k + (float) zpos * 16.0f;
						count += 3;
					}
					
				}
				
			}
		}
	}
	
	return count;
}

void compoundConstructor ( character* player, chunk chunk_list[9][9] ) {
	
	int bi, bj, bk;
	char w, e, s, n, l, h;
	char check;
	
	int playerxpos = int( player->getXpos() / 16 );
	int playerypos = int( player->getYpos() / 16 );
	
	int xpos;
	int ypos;
	int zpos;
	
	for (int iseg = 0; iseg < 9; iseg++) {
		for (int jseg = 0; jseg < 9; jseg++) {
			for (int kseg = 0; kseg < 8; kseg++) {
				xpos = ( playerxpos - 4 ) + iseg;
				ypos = ( playerypos - 4 ) + jseg;
				zpos = kseg;
				
				dataConstructor( chunk_list[iseg][jseg].getSeg(kseg)->getData(), xpos, ypos, zpos );
				
				int count = 0;
				
				for (int i = 0; i < 16; i += 1) {
					for (int j = 0; j < 16; j += 1) {
						for (int k = 0; k < 16; k += 1) {
			
							if (chunk_list[iseg][jseg].getSeg(kseg)->getData()[i][j][k] < 0) {
				
								check = 1;
				
								for (int ri = -1; ri < 2; ri += 1) {
									for (int rj = -1; rj < 2; rj += 1) {
										for (int rk = -1; rk < 2; rk += 1) {
											if ( ri != 0 || rj != 0 || rk != 0 ) {
								
												bi = i + ri;
												bj = j + rj;
												bk = k + rk;
												w = e = s = n = l = h = 0;
								
												if ( bi < 0 ) {
													// Check if West
													w = 1;
													if (iseg == 0) {
														break;
													}
												}
												if ( bi > 15 ) {
													// Check if East
													e = 1;
													if (iseg == 8) {
														break;
													}
												}
												if ( bj < 0 ) {
													// Check if South
													s = 1;
													if (jseg == 0) {
														break;
													}
												}
												if ( bj > 15 ) {
													// Check if North
													n = 1;
													if (jseg == 8) {
														break;
													}
												}
												if ( bk < 0 ) {
													// Check if Lower
													l = 1;
													if (zpos == 0) {
														break;
													}
												} 
												if ( bk > 15 ) {
													// Check if Higher
													h = 1;
													if (zpos == 7) {
														break;
													}
												}
								
												if ( w == 0 && e == 0 && s == 0 && n == 0 && l == 0 && h == 0 ) {
									
													// If neighbour is not beyond side, edge or corner
													if ( chunk_list[iseg][jseg].getSeg(kseg)->getData()[bi][bj][bk] > 0 ) {
														// Check if solid
														check = 0;
													}
									
												} else {
								
													if ( w == 1 ) {
														if ( s == 0 && n == 0 && l == 0 && h == 0 ) {
															// Check for West chunk
															if ( chunk_list[iseg-1][jseg].getSeg(kseg)->getData()[15][bj][bk] > 0 ) {
																// Check if solid
																check = 0;
															}
														} else {
									
															if ( s == 1 ) {
												
																if ( l == 1 ) {
																	// Check for South West chunk and Lower segment
																} else if ( h == 1 ) {
																	// Check for South West chunk and Higher segment
																} else {
																	// Check for South West chunk
																	if ( chunk_list[iseg-1][jseg-1].getSeg(kseg)->getData()[15][15][bk] > 0 ) {
																		// Check if solid
																		check = 0;
																	}
																}
									
															} else if ( n == 1 ) {
									
																if ( l == 1 ) {
																	// Check for North West chunk and Lower segment
																} else if ( h == 1 ) {
																	// Check for North West chunk and Higher segment
																} else {
																	// Check for North West chunk
																	if ( chunk_list[iseg-1][jseg+1].getSeg(kseg)->getData()[15][0][bk] > 0 ) {
																		// Check if solid
																		check = 0;
																	}
																}
									
															}
									
															if ( l == 1 ) {
										
																if ( s == 0 && n == 0 ) {
																	// Check for West chunk and Lower segment
																	if ( chunk_list[iseg-1][jseg].getSeg(kseg-1)->getData()[15][bj][15] > 0 ) {
																		// Check if solid
																		check = 0;
																	}
																}
									
															} else if ( h == 1 ) {
										
																if ( s == 0 && n == 0 ) {
																	// Check for West chunk and Higher segment
																	if ( chunk_list[iseg-1][jseg].getSeg(kseg+1)->getData()[15][bj][0] > 0 ) {
																		// Check if solid
																		check = 0;
																	}
																}
									
															}
									
														}
									
													} else if ( e == 1 ) {
								
														if ( s == 0 && n == 0 && l == 0 && h == 0 ) {
															// Check for East chunk
															if ( chunk_list[iseg+1][jseg].getSeg(kseg)->getData()[0][bj][bk] > 0 ) {
																// Check if solid
																check = 0;
															}
														} else {
									
															if ( s == 1 ) {
									
																if ( l == 1 ) {
																	// Check for South East chunk and Lower segment
																} else if ( h == 1 ) {
																	// Check for South East chunk and Higher segment
																} else {
																	// Check for South East chunk
																	if ( chunk_list[iseg+1][jseg-1].getSeg(kseg)->getData()[0][15][bk] > 0 ) {
																		// Check if solid
																		check = 0;
																	}
																}
									
															} else if ( n == 1 ) {
									
																if ( l == 1 ) {
																	// Check for North East chunk and Lower segment
																} else if ( h == 1 ) {
																	// Check for North East chunk and Higher segment
																} else {
																	// Check for North East chunk
																	if ( chunk_list[iseg+1][jseg+1].getSeg(kseg)->getData()[0][0][bk] > 0 ) {
																		// Check if solid
																		check = 0;
																	}
																}
									
															}
									
															if ( l == 1 ) {
										
																if ( s == 0 && n == 0 ) {
																	// Check for East chunk and Lower segment
																	if ( chunk_list[iseg+1][jseg].getSeg(kseg-1)->getData()[0][bj][15] > 0 ) {
																		// Check if solid
																		check = 0;
																	}
																}
									
															} else if ( h == 1 ) {
										
																if ( s == 0 && n == 0 ) {
																	// Check for East chunk and Higher segment
																	if ( chunk_list[iseg+1][jseg].getSeg(kseg+1)->getData()[0][bj][0] > 0 ) {
																		// Check if solid
																		check = 0;
																	}
																}
									
															}
									
														}
									
													}
								
													if ( s == 1 ) {
								
														if ( w == 0 && e == 0 && l == 0 && h == 0 ) {
															// Check for South chunk
															if ( chunk_list[iseg][jseg-1].getSeg(kseg)->getData()[bi][15][bk] > 0 ) {
																// Check if solid
																check = 0;
															}
														} else if ( l == 1 ) {
										
															if ( w == 0 && e == 0 ) {
																// Check for South chunk and Lower segment
																if ( chunk_list[iseg][jseg-1].getSeg(kseg-1)->getData()[bi][15][15] > 0 ) {
																	// Check if solid
																	check = 0;
																}
															}
									
														} else if ( h == 1 ) {
										
															if ( w == 0 && e == 0 ) {
																// Check for South chunk and Higher segment
																if ( chunk_list[iseg][jseg-1].getSeg(kseg+1)->getData()[bi][15][0] > 0 ) {
																	// Check if solid
																	check = 0;
																}
															}
									
														}
									
													} else if ( n == 1 ) {
								
														if ( w == 0 && e == 0 && l == 0 && h == 0 ) {
															// Check for North chunk
															if ( chunk_list[iseg][jseg+1].getSeg(kseg)->getData()[bi][0][bk] > 0 ) {
																// Check if solid
																check = 0;
															}
														} else if ( l == 1 ) {
										
															if ( w == 0 && e == 0 ) {
																// Check for North chunk and Lower segment
																if ( chunk_list[iseg][jseg+1].getSeg(kseg-1)->getData()[bi][0][15] > 0 ) {
																	// Check if solid
																	check = 0;
																}
															}
									
														} else if ( h == 1 ) {
										
															if ( w == 0 && e == 0 ) {
																// Check for North chunk and Higher segment
																if ( chunk_list[iseg][jseg+1].getSeg(kseg+1)->getData()[bi][0][0] > 0 ) {
																	// Check if solid
																	check = 0;
																}
															}
									
														}
									
													}
													
													if ( l == 1 ) {
													
														if ( w == 0 && e == 0 && s == 0 && n == 0 ) {
															// Check for Lower segment
															if ( chunk_list[iseg][jseg].getSeg(kseg-1)->getData()[bi][bj][15] > 0 ) {
																// Check if solid
																check = 0;
															}
														}
									
													} else if ( h == 1 ) {
													
														if ( w == 0 && e == 0 && s == 0 && n == 0 ) {
															// Check for Higher segment
															if ( chunk_list[iseg][jseg].getSeg(kseg+1)->getData()[bi][bj][0] > 0 ) {
																// Check if solid
																check = 0;
															}
														}
													
													}
												
												}
											}
										}
									}
								}
								
								if ( check == 0 ) {
									// If neighbour is empty
									chunk_list[iseg][jseg].getSeg(kseg)->getBuffer()[count] = (float) i + (float) xpos * 16.0f;
									chunk_list[iseg][jseg].getSeg(kseg)->getBuffer()[count + 1] = (float) j + (float) ypos * 16.0f;
									chunk_list[iseg][jseg].getSeg(kseg)->getBuffer()[count + 2] = (float) k + (float) zpos * 16.0f;
									count += 3;
								}
							
							}
						
						}
					}
				}
				
				chunk_list[iseg][jseg].getSeg(kseg)->setCounter(count);
				
			}
		}
	}
}

chunkController::chunkController () {
}

chunkController::chunkController (character* player_input, shaderVoxel* shader_input) {
	
	player = player_input;
	shader = shader_input;
	
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			chunk_list[i][j].init();
		}
	}
	
	compoundConstructor(player, chunk_list);
	updateBuffer();
}

chunk* chunkController::getChunk (int index_x, int index_y) {
	return &chunk_list[index_x][index_y];
}

void chunkController::updateData () {
	compoundConstructor(player, chunk_list);
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

void chunkController::render () {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			for (int k = 0; k < 8; k++) {
				( chunk_list[i][j].getSeg(k) )->render( shader->getCoordAttrib() );
			}
		}
	}
}